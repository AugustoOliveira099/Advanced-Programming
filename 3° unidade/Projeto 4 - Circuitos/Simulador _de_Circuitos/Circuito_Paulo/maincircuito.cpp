#include <QFileDialog>
#include <QMessageBox>
#include "maincircuito.h"
#include "ui_maincircuito.h"

#include <QDebug>

maincircuito::maincircuito(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::maincircuito)
    , C()
    , modPorta(nullptr)
    , modSaida(nullptr)
    , newCirc(nullptr)
    , totalEntradas(nullptr)
    , totalSaidas(nullptr)
    , totalPortas(nullptr)
{
    ui->setupUi(this);

    // JANELAS QDIALOG
    modPorta = new modifyPorta(this);
    modSaida = new modifySaida(this);
    newCirc = new newCircuito(this);

    // STATUS BAR
    statusBar()->insertWidget(0, new QLabel("N° entradas: "));
        totalEntradas = new QLabel(this);
        totalEntradas->setNum(0);
        statusBar()->insertWidget(1, totalEntradas);
    statusBar()->insertWidget(2, new QLabel("N° saídas: "));
        totalSaidas = new QLabel(this);
        totalSaidas->setNum(0);
        statusBar()->insertWidget(3, totalSaidas);
    statusBar()->insertWidget(4, new QLabel("N° portas: "));
        totalPortas = new QLabel(this);
        totalSaidas->setNum(0);
        statusBar()->insertWidget(5, totalPortas);

    // CONEXÃO ENTRE AS JANELAS
        // ==> Novo Circuito
    connect(newCirc, SIGNAL(signNewCircuito(QString, QString, QString)),
            this, SLOT(slotNewCircuito(QString, QString, QString)));
        // ==> Modificar Porta
    connect(modPorta, SIGNAL(signModifyPorta(QString, QString, QString, QString[4])),
            this, SLOT(slotModifyPorta(QString, QString, QString, QString[4])));
        // ==> Modificar Saída
    connect(modSaida, SIGNAL(signModifySaida(QString, QString)),
            this, SLOT(slotModifySaida(QString, QString)));
        // ==> ID Saida
    connect(this, SIGNAL(signSaidaID(int)), modSaida, SLOT(slotSaidaID(int)));
        // ==> ID Porta
    connect(this, SIGNAL(signPortaID(int)), modPorta, SLOT(slotPortaID(int)));
        // ==> Intervalo Saida
    connect(this, SIGNAL(signIntervaloSaida(int, int)), modSaida, SLOT(slotIntervaloSaida(int, int)));
        // ==> Intervalo Porta
    connect(this, SIGNAL(signIntervaloPorta(int, int)), modPorta, SLOT(slotIntervaloPorta(int, int)));
        // ==> Maximo entradas
    connect(newCirc, SIGNAL(signMaximoEntradas(int)), modPorta, SLOT(slotMaximoEntradas(int)));

    // FRONT-END TABELA
    // ==> Labels
    ui->portasConexoesLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    ui->saidasLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    ui->tabelaVerdadeLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    ui->circuitosLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    // ==> Headers
    ui->portasConexoesWidget->setHorizontalHeaderLabels(QStringList() << "TIPO" << "N°\nENTR" << "ENTR\n1" << "ENTR\n2" << "ENTR\n3" << "ENTR\n4");
    ui->saidasWidget->setHorizontalHeaderLabels(QStringList() << "ORIG\nSAÍDA");
    ui->portasConexoesWidget->setStyleSheet("QHeaderView::section{background-color:white}");
    ui->saidasWidget->setStyleSheet("QHeaderView::section{background-color:white}");
}

maincircuito::~maincircuito()
{
    delete ui;
}

void maincircuito::ExibirTabelas()
{
    // Dados para o tamanho das tabelas
    unsigned nEntradas, nSaidas, nPortas;
    QLabel *prov;
    nEntradas = C.getNumInputs();
    nSaidas = C.getNumOutputs();
    nPortas = C.getNumPorts();

    // Números para o rodapé
    totalEntradas->setNum((int)nEntradas);
    totalSaidas->setNum((int)nSaidas);
    totalPortas->setNum((int)nPortas);

    // ===== PORTAS E CONEXÕES =====
    // Limpando conteúdo
    ui->portasConexoesWidget->clearContents();
    // Tamanho total
    ui->portasConexoesWidget->setRowCount(nPortas);
    // Exibir portas e conexões
    for(unsigned i=0; i<nPortas; i++){
        ExibirPorta(i);
    }

    // ===== SAÍDAS =====
    // Limpando conteúdo
    ui->saidasWidget->clearContents();
    // Tamanho total
    ui->saidasWidget->setRowCount(nSaidas);
    // Exibir saídas
    for(unsigned i=0; i<nSaidas; i++){
        ExibirSaida(i);
    }

    // ===== TABELA VERDADE =====
    // Limpando conteúdo
    ui->tabelaVerdadeWidget->clearSpans();
    ui->tabelaVerdadeWidget->clear();
    // Tamanho total
    ui->tabelaVerdadeWidget->setColumnCount(nEntradas+nSaidas);
    int totalTV = pow(3, nEntradas);
    ui->tabelaVerdadeWidget->setRowCount(1 + totalTV);

    if(nEntradas > 0){
        ui->tabelaVerdadeWidget->setSpan(0, 0, 1, nEntradas);
        prov = new QLabel("ENTRADAS");
        prov->setAlignment(Qt::AlignCenter);
        ui->tabelaVerdadeWidget->setCellWidget(0, 0, prov);
    }

    if(nSaidas > 0){
        ui->tabelaVerdadeWidget->setSpan(0, nEntradas, 1, nSaidas);
        prov = new QLabel("SAIDAS");
        prov->setAlignment(Qt::AlignCenter);
        ui->tabelaVerdadeWidget->setCellWidget(0, nSaidas, prov);
    }

    int min = (int)-nEntradas;
    int max = nPortas;

    // Range do modifyPorta
    emit signIntervaloPorta(min, max);
    // Range do modifySaida
    emit signIntervaloSaida(min, max);
}

void maincircuito::ExibirPorta(unsigned idPorta)
{
    string tipoPorta = C.getNamePort(idPorta);
    unsigned nEntradas = C.getNumInputsPort(idPorta);
    int id[4];
    QLabel *prov;

    for(unsigned i=0; i<nEntradas; i++){
        id[i] = C.getId_inPort(idPorta, i);
    }

    // PRIMEIRA COLUNA (TIPO DE PORTA)
    prov = new QLabel(tipoPorta.c_str());
    prov->setAlignment(Qt::AlignCenter);
    ui->portasConexoesWidget->setCellWidget(idPorta, 0, prov);

    // SEGUNDA COLUNA (N° ENTRADAS)
    prov = new QLabel(QString::number(nEntradas));
    prov->setAlignment(Qt::AlignCenter);
    ui->portasConexoesWidget->setCellWidget(idPorta, 1, prov);

    // COLUNAS ADIANTES (ENTRADAS)
    for(unsigned i=0; i<nEntradas; i++){
        prov = new QLabel(QString::number(id[i]));
        prov->setAlignment(Qt::AlignCenter);
        ui->portasConexoesWidget->setCellWidget(idPorta, 2+i, prov);
    }
}

void maincircuito::ExibirSaida(unsigned idPorta)
{
    int idOrigem = C.getIdOutput(idPorta);
    QLabel *prov;

    prov = new QLabel(QString::number(idOrigem));
    prov->setAlignment(Qt::AlignCenter);
    ui->saidasWidget->setCellWidget(idPorta, 0, prov);
}

// ==========================================
// ============== ITENS MENU ================
// ==========================================

// AO CLICAR NO MENU->NOVO
void maincircuito::on_actionNovo_triggered()
{
    newCirc->show();
}


// AO CLICAR NO MENU->LER
void maincircuito::on_actionLer_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Arquivo de circuito", "", "Circuitos (*.txt);;Todos (*.*)");
    QString archiveName = QFileInfo(fileName).fileName();
    if(!archiveName.isEmpty()){
        bool okFile = C.ler(archiveName.toStdString());
        if(!okFile){
            QMessageBox::critical(this, "Circuito", "Erro ao ler um circuito a partir do arquivo\n" + archiveName);
        }
        // FUNÇÃO PARA EXIBIR NA TELA
        ExibirTabelas();
    }
}

// AO CLICAR NO MENU->SALVAR
void maincircuito::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Salvar circuito", "", "Circuitos (*.txt);;Todos (*.*)");
    QString archiveName = QFileInfo(fileName).fileName();

    if(!archiveName.isEmpty()){
        bool okFile = C.salvar(archiveName.toStdString());
        if(!okFile){
            QMessageBox::critical(this, "Circuito", "O circuito não está completamente definido. Não pode ser salvo\n" + archiveName);
        }
    }
}

// AO CLICAR NO MENU->SAIR
void maincircuito::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

// AO CLICAR NO MENU->GERAR TABELA
void maincircuito::on_actionGerar_tabela_triggered()
{
    vector<bool3S> inputs(C.getNumInputs());
    int i, j;
    QLabel *prov;

    for(j=0; j<(int)C.getNumInputs(); j++){
        inputs[j] = bool3S::UNDEF;
    }

    do{
        C.simular(inputs);

        // ENTRADA
        for(i=0; i<(int)C.getNumInputs(); i++){
            switch(C.getInput(-i-1)){
            case bool3S::UNDEF:
                prov = new QLabel("?");
                break;
            case bool3S::TRUE:
                prov = new QLabel("T");
                break;
            case bool3S::FALSE:
                prov = new QLabel("F");
                break;
            }
            // Colocar nas linhas
            prov->setAlignment(Qt::AlignCenter);
            ui->tabelaVerdadeWidget->setCellWidget(j+1, i, prov);
        }

        // SAIDA
        for(i=0; i<(int)C.getNumOutputs(); i++){
            switch(C.getOutput(i+1)){
            case bool3S::UNDEF:
                prov = new QLabel("?");
                break;
            case bool3S::TRUE:
                prov = new QLabel("T");
                break;
            case bool3S::FALSE:
                prov = new QLabel("F");
                break;
            }
            // Colocar nas linhas
            prov->setAlignment(Qt::AlignCenter);
            ui->tabelaVerdadeWidget->setCellWidget(j+1, i+C.getNumInputs(), prov);
        }

        j = C.getNumInputs()-1;
        while(inputs[j] == bool3S::TRUE && j>=0){
            inputs[j]++;
            j--;
        }
        if(j >= 0) inputs[j]++;

    } while(j>=0);
}

// AO CLICAR NA LINHA PARA ABRIR A JANELA MODIFICAR PORTA
void maincircuito::on_portasConexoesWidget_cellDoubleClicked(int row, int)
{
    qDebug() << "VALOR DOUBLE CLICK: " << row;
    emit signPortaID(row);
    modPorta->show();
}

// AO CLICAR NA LINHA PARA ABRIR A JANELA MODIFICAR SAÍDA
void maincircuito::on_saidasWidget_cellDoubleClicked(int row, int)
{
    emit signSaidaID(row);
    modSaida->show();
}

// =============================
// ===== SLOTS DAS JANELAS =====
// =============================

void maincircuito::slotNewCircuito(QString nEntradas, QString nSaidas, QString nPortas)
{
    unsigned newNEntradas = nEntradas.toUInt();
    unsigned newNSaidas = nSaidas.toUInt();
    unsigned newNPortas = nPortas.toUInt();

    qDebug() << newNEntradas << " " << newNSaidas << " " << newNPortas;

    C.realloc(newNEntradas, newNSaidas, newNPortas);

    //bool circuitoOK = C.valid();
    //if(circuitoOK){
        ExibirTabelas();
    //} else {
        //QMessageBox::critical(this, "ERRO", "MENSAGEM DE ERRO");
    //}
}

void maincircuito::slotModifyPorta(QString idPorta, QString tipoPorta, QString nEntradas, QString id[4])
{
    unsigned newIdPorta = idPorta.toUInt();
    string newTipoPorta = tipoPorta.toStdString();
    unsigned newNEntradas = nEntradas.toUInt();
    int newId[4];
        for(int i=0; i<4; i++){
            newId[i] = id[i].toInt();
            qDebug() << "ID: " << newId[i];
        }

    qDebug() << "TESTE PORTA:";
    C.setPort(newIdPorta-1, newTipoPorta, newNEntradas);
    for(unsigned i=0; i<newNEntradas; i++){
        C.setId_inPort(newIdPorta-1, i, newId[i]);
    }

    qDebug() << "EXIBINDO PORTA";
    ExibirPorta(newIdPorta-1);
}

void maincircuito::slotModifySaida(QString idSaida, QString idOrigem)
{
    unsigned newIdSaida = idSaida.toUInt();
    int newIdOrigem = idOrigem.toInt();

    C.setIdOutput(newIdSaida-1, newIdOrigem);

    ExibirSaida(newIdSaida-1);
}



