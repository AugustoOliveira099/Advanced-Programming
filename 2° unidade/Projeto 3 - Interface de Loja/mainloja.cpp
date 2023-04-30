#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <cmath>  
#include "mainloja.h"
#include "ui_mainloja.h"
#include "QTextStream"

MainLoja::MainLoja(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainLoja)
  , X()
  , janelaLivro(NULL)
  , janelaCD(NULL)
  , janelaDVD(NULL)
  , total_itens(NULL)
{
  ui->setupUi(this);

  // Cria as janelas para que o usuario adione um item
  janelaLivro = new IncluirLivro(this);
  janelaCD = new IncluirCD(this);
  janelaDVD = new IncluirDVD(this);

  // Cria os QLabels para mostrar o total de itens
  statusBar()->insertWidget(0,new QLabel("Total de itens: "));
  total_itens = new QLabel(this);
  total_itens->setNum(0);
  statusBar()->insertWidget(1,total_itens);

  // Muda a cor de fundo dos Qlabels que nomeiam os itens e alinha cada um
  ui->QlabelDVD->setStyleSheet("background:lightgray");
  ui->QlabelDVD->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->QlabelLivro->setStyleSheet("background:lightgray");
  ui->QlabelLivro->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  ui->QlabelCD->setStyleSheet("background:lightgray");
  ui->QlabelCD->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  // Liga o sinal de incluir item ao slot adequado
  connect(janelaDVD, SIGNAL(signIncluirDVD(QString,QString,QString)),
          this, SLOT(slotIncluirDVD(QString,QString,QString)));
  connect(janelaLivro, SIGNAL(signIncluirLivro(QString,QString,QString)),
          this, SLOT(slotIncluirLivro(QString,QString,QString)));
  connect(janelaCD, SIGNAL(signIncluirCD(QString,QString,QString)),
          this, SLOT(slotIncluirCD(QString,QString,QString)));

  /// Cabecalhos:
  /// As demais mudanças foram feitas nas listas de propriedades da tabela de cada item

  // CDs
  ui->tabelaCD->setStyleSheet("QHeaderView::section {background-color:lightgray}");
  ui->tabelaCD->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->tabelaCD->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
  ui->tabelaCD->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->tabelaCD->setHorizontalHeaderLabels(QStringList() << "NOME" << "PRECO" << "N DE FAIXAS");

  // Livros
  ui->tabelaLivro->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->tabelaLivro->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->tabelaLivro->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
  ui->tabelaLivro->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->tabelaLivro->setHorizontalHeaderLabels(QStringList() << "NOME" << "PRECO" << "AUTOR");

  // DVDs
  ui->tabelaDVD->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->tabelaDVD->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->tabelaDVD->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
  ui->tabelaDVD->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->tabelaDVD->setHorizontalHeaderLabels(QStringList() << "NOME" << "PRECO" << "DURACAO");

  exibeListas();
}

// Ler um arquivo
void MainLoja::on_actionLer_triggered()
{
    QString fileName = QFileDialog::
        getOpenFileName(this
                        , "Ler estoque"
                        , QString()
                        , "Text Files (*.txt)");

    if (!fileName.isEmpty()) {
      bool leu = X.ler(fileName.toStdString());
      if (!leu){
          QMessageBox::critical(this, "Error", "Nao foi possivel ler o arquivo:\n"+fileName);
      }
    }

    exibeListas();
}

// Salvar um arquivo
void MainLoja::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::
          getSaveFileName(this
                          , "Salvar estoque"
                          , QString()
                          , "Text Files (*.txt)");

      if (!fileName.isEmpty()) {
        bool leu = X.salvar(fileName.toStdString());
        if (!leu){
            QMessageBox::critical(this, "Error", "Nao foi possivel salvar o arquivo:\n"+fileName);
        }
      }
}

void MainLoja::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

void MainLoja::on_actionIncluir_Livro_triggered()
{
  janelaLivro->show();
}

void MainLoja::on_actionIncluir_CD_triggered()
{
  janelaCD->show();
}

void MainLoja::on_actionIncluir_DVD_triggered()
{
  janelaDVD->show();
}

// Destrutor
MainLoja::~MainLoja()
{
  delete ui;
}

void MainLoja::on_tabelaLivro_cellDoubleClicked(int i, int)
{
  if (i>=0 && unsigned(i)<X.getNumLivro())
  {
    X.excluirLivro(i);
    exibeListaLivro();
  }
}

void MainLoja::on_tabelaCD_cellDoubleClicked(int i, int)
{
  if (i>=0 && unsigned(i)<X.getNumCD())
  {
    X.excluirCD(i);
    exibeListaCD();
  }
}

void MainLoja::on_tabelaDVD_cellDoubleClicked(int i, int)
{
  if (i>=0 && unsigned(i)<X.getNumDVD())
  {
    X.excluirDVD(i);
    exibeListaDVD();
  }
}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
  double preco_reais = preco.toFloat();
  unsigned preco_inteiro = round(100.0*preco_reais);
  Livro livro_prov(nome.toStdString(), preco_inteiro, autor.toStdString());
  if (livro_prov.getNome()!="" && livro_prov.getPreco()!=0.0 && livro_prov.getAutor()!="")
  {
    X.incluirLivro(livro_prov);
    exibeListaLivro();
  }
  else
  {
    QMessageBox::critical(this
                          ,"ERROR"
                          ,QString("O livro a seguir nao eh valido:\n")+
                          "Nome="+nome+"\nPreco="+preco+"\nAutor="+autor);
  }
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas)
{
  double preco_reais = preco.toFloat();
  unsigned preco_inteiro = round(100.0*preco_reais);
  unsigned faixas = numfaixas.toUInt();
  CD C(nome.toStdString(), preco_inteiro, faixas);
  if (C.getNome()!="" && C.getPreco()!=0.0 && C.getNumFaixas()!=0)
  {
    X.incluirCD(C);
    exibeListaCD();
  }
  else
  {
    QMessageBox::critical(this
                          ,"ERROR"
                          ,QString("O CD a seguir nao eh valido:\n")+
                          "Nome="+nome+"\nPreco="+preco+"\nNum faixas="+numfaixas);
  }
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
  double preco_reais = preco.toFloat();
  unsigned preco_inteiro = round(100.0*preco_reais);
  unsigned DURACAO = duracao.toUInt();
  DVD D(nome.toStdString(), preco_inteiro, DURACAO);
  if (D.getNome()!="" && D.getPreco()!=0.0 && D.getDuracao()!=0)
  {
    X.incluirDVD(D);
    exibeListaDVD();
  }
  else
  {
    QMessageBox::critical(this
                          ,"ERROR"
                          ,QString("O DVD a seguir nao eh valido:\n")+
                          "Nome="+nome+"\nPreco="+preco+"\nDuracao="+duracao);
  }
}

void MainLoja::exibeListaLivro()
{
  unsigned Livros(X.getNumLivro());

  // Apaga o conteudo, deixa os cabecalhos
  ui->tabelaLivro->clearContents();

  // Determina o numero de linhas da tabela
  ui->tabelaLivro->setRowCount(Livros);

  // Fixa na tabela cada livro que estah na memoria
  QLabel *prov;
  for (unsigned i=0; i<Livros; i++)
  {
    Livro L = X.getLivro(i);
    // Fixa o nome do livro na primeira coluna
    prov = new QLabel(L.getNome().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tabelaLivro->setCellWidget(i,0,prov);
    // Fixa o preco do livro na segunda coluna
    prov = new QLabel(QString::number(L.getPreco(),'f',2));
    prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tabelaLivro->setCellWidget(i,1,prov);
    // Fixa o nome do autor na terceira coluna
    prov = new QLabel(L.getAutor().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tabelaLivro->setCellWidget(i,2,prov);
  }

  // Exibe o total de itens na barra de status
  exibeStatus();
}

void MainLoja::exibeListaCD()
{
  unsigned CDs(X.getNumCD());

  // Apaga o conteudo, deixa os cabecalhos
  ui->tabelaCD->clearContents();

  // Determina o numero de linhas da tabela
  ui->tabelaCD->setRowCount(CDs);

  // Fixa na tabela cada CD que estah na memoria
  QLabel *prov;
  for (unsigned i=0; i<CDs; i++)
  {
    CD cd = X.getCD(i);
    // Fixa o nome do CD na primeira coluna
    prov = new QLabel(cd.getNome().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tabelaCD->setCellWidget(i,0,prov);
    // Fixa o preco do CD na segunda coluna
    prov = new QLabel(QString::number(cd.getPreco(),'f',2));
    prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tabelaCD->setCellWidget(i,1,prov);
    // Fixa na terceira coluna o numero de faixas contidas no CD
    prov = new QLabel(QString::number(cd.getNumFaixas()));
    prov->setAlignment(Qt::AlignCenter);
    ui->tabelaCD->setCellWidget(i,2,prov);
  }

  // Exibe o total de itens na barra de status
  exibeStatus();
}

void MainLoja::exibeListaDVD()
{
  unsigned DVDs(X.getNumDVD());

  // Apaga o conteudo, deixa os cabecalhos
  ui->tabelaDVD->clearContents();

  // Determina o numero de linhas da tabela
  ui->tabelaDVD->setRowCount(DVDs);

  // Fixa na tabela cada DVD que estah na memoria
  QLabel *prov;
  for (unsigned i=0; i<DVDs; i++)
  {
    DVD dvd = X.getDVD(i);
    // Fixa o nome do DVD na primeira coluna
    prov = new QLabel(dvd.getNome().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tabelaDVD->setCellWidget(i,0,prov);
    // Fixa o preco do DVD na segunda coluna
    prov = new QLabel(QString::number(dvd.getPreco(),'f',2));
    prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tabelaDVD->setCellWidget(i,1,prov);
    // Fixa na terceira coluna a duracao do DVD
    prov = new QLabel(QString::number(dvd.getDuracao()));
    prov->setAlignment(Qt::AlignCenter);
    ui->tabelaDVD->setCellWidget(i,2,prov);
  }

  // Exibe o total de itens na barra de status
  exibeStatus();
}

void MainLoja::exibeListas()
{
  exibeListaLivro();
  exibeListaCD();
  exibeListaDVD();
}

// Exibe o total de itens na barra de status
void MainLoja::exibeStatus()
{
  int itens = X.getNumDVD()+ X.getNumLivro()+ X.getNumCD();
  total_itens->setNum(itens);
}

