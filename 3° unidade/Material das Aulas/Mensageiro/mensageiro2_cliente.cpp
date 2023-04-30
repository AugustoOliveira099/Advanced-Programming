#include <QMessageBox>

#include "mysocket.h"
#include "mensageiro2_cliente.h"
#include "ui_mensageiro2_cliente.h"

// Variaveis globais
extern tcp_mysocket sock;

Mensageiro2_Cliente::Mensageiro2_Cliente(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Mensageiro2_Cliente),
  ipServidor(""),
  myLogin(""),
  cl_thr(NULL),
  connectServer(NULL)
{
  ui->setupUi(this);

  // Cria novo objeto gerenciador da thread
  cl_thr = new Mensageiro2_Cliente_Thread(this);

  // Cria caixas de dialogos de conexao
  connectServer = new ConnectServer(this);

  // Largura das colunas da tabela de msg
  ui->msgTable->setColumnWidth(0,140);
  ui->msgTable->setColumnWidth(1,502);
  ui->msgTable->setColumnWidth(2,140);

  // Cabecalhos da tabela de msg
  ui->msgTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->msgTable->setHorizontalHeaderLabels(QStringList() << "REMETENTE" << "MENSAGEM" << "DESTINATARIO");

  // Widgets da barra de status
  statusBar()->insertWidget(0,new QLabel("Servidor: "));
  statusBar()->insertWidget(1,&ipServidor);
  statusBar()->insertWidget(2,new QLabel("   Login: "));
  statusBar()->insertWidget(3,&myLogin);

  // Conexao dos sinais e slots

  // Avisa ao controlador de thread que foi feita conexao e a thread pode iniciar
  connect(connectServer, SIGNAL(signExecutarThread()),
          cl_thr, SLOT(executar()));
  // O controlador de thread avisa que a thread iniciou a execucao
  connect(cl_thr, SIGNAL(signThreadIniciada()),
          this, SLOT(interfaceConectada()));
  // O controlador de thread avisa que chegou mensagem
  connect(cl_thr, SIGNAL(signAdicionarMsgRecebida(QString,QString)),
          this, SLOT(adicionarMsgRecebida(QString,QString)));
  // O controlador de thread avisa que houve erro na recepcao
  connect(cl_thr, SIGNAL(signErro(QString,QString)),
          this, SLOT(exibirErro(QString,QString)));
  // O controlador de thread avisa que a thread se encerrou
  // Acao 1: colocar a interface em modo desconectado
  connect(cl_thr, SIGNAL(signThreadEncerrada()),
          this, SLOT(interfaceDesconectada()));
  // Acao 2: dar o join na thread que se encerrou
  connect(cl_thr, SIGNAL(signThreadEncerrada()),
          cl_thr, SLOT(encerrar()));

  // Inicia colocando a interface no modo desconectado
  interfaceDesconectada();
}

Mensageiro2_Cliente::~Mensageiro2_Cliente()
{
  delete ui;
}

void Mensageiro2_Cliente::desconectar()
{
  // Envia FIM para o servidor
  if (sock.connected()) sock.write_string("FIM");

  // Encerra a thread
  cl_thr->encerrar();
}

// Coloca a interface no modo conectado
void Mensageiro2_Cliente::interfaceConectada()
{
  if (connected())
  {
    // Habilita o envio de msgs
    ui->userEdit->setEnabled(true);
    ui->msgEdit->setEnabled(true);
    ui->enviarButton->setEnabled(true);

    // Desabilita a acao de conectar
    ui->actionConectar->setEnabled(false);
    // Habilita a acao de desconectar
    ui->actionDesconectar->setEnabled(true);

    //Barra de status
    ipServidor.setText(connectServer->getServer());
    myLogin.setText(connectServer->getUsuario());
  }
}

// Coloca a interface no modo desconectado
void Mensageiro2_Cliente::interfaceDesconectada()
{
  if (!connected())
  {
    // Desabilita o envio de msgs
    ui->userEdit->setEnabled(false);
    ui->msgEdit->setEnabled(false);
    ui->enviarButton->setEnabled(false);

    // Habilita a acao de conectar
    ui->actionConectar->setEnabled(true);
    // Desabilita a acao de desconectar
    ui->actionDesconectar->setEnabled(false);

    //Barra de status
    ipServidor.setText("NAO CONECTADO");
    myLogin.setText("NAO DEFINIDO");
  }
}

void Mensageiro2_Cliente::adicionarMsgEnviada(QString dest, QString msg)
{
  if (connected())
  {
    // Incrementa o numero de linhas da tabela de msgs
    int nMsg = ui->msgTable->rowCount();
    nMsg++;
    ui->msgTable->setRowCount(nMsg);

    // Cria os conteudos da nova linha
    QTableWidgetItem *prov;
    // O remetente
    prov = new QTableWidgetItem(myLogin.text());
    prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    prov->setBackground(QBrush(QColor(200,255,200)));
    ui->msgTable->setItem(nMsg-1,0,prov);
    // A mensagem
    prov = new QTableWidgetItem(msg);
    prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    prov->setBackground(QBrush(QColor(200,255,200)));
    ui->msgTable->setItem(nMsg-1,1,prov);
    // O destinatario
    prov = new QTableWidgetItem(dest);
    prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    prov->setBackground(QBrush(QColor(200,255,200)));
    ui->msgTable->setItem(nMsg-1,2,prov);
  }
}

void Mensageiro2_Cliente::adicionarMsgRecebida(QString remet, QString msg)
{
  if (connected())
  {
    // Incrementa o numero de linhas da tabela de msgs
    int nMsg = ui->msgTable->rowCount();
    nMsg++;
    ui->msgTable->setRowCount(nMsg);

    // Cria os conteudos da nova linha
    QTableWidgetItem *prov;
    // O remetente
    prov = new QTableWidgetItem(remet);
    prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    prov->setBackground(QBrush(QColor(255,255,255)));
    ui->msgTable->setItem(nMsg-1,0,prov);
    // A mensagem
    prov = new QTableWidgetItem(msg);
    prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    prov->setBackground(QBrush(QColor(255,255,255)));
    ui->msgTable->setItem(nMsg-1,1,prov);
    // O destinatario
    prov = new QTableWidgetItem(myLogin.text());
    prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    prov->setBackground(QBrush(QColor(255,255,255)));
    ui->msgTable->setItem(nMsg-1,2,prov);
  }
}

void Mensageiro2_Cliente::exibirErro(QString title, QString msg)
{
  QMessageBox msgBox;
  msgBox.setWindowTitle(title);
  msgBox.setText(msg);
  msgBox.exec();
}

void Mensageiro2_Cliente::on_actionSair_triggered()
{
  desconectar();
  QCoreApplication::quit();
}

void Mensageiro2_Cliente::on_actionConectar_triggered()
{
  if (!connected())
  {
    connectServer->show();
  }
}

void Mensageiro2_Cliente::on_actionApagar_triggered()
{
   ui->msgTable->clearContents();
   ui->msgTable->setRowCount(0);
}

void Mensageiro2_Cliente::on_actionDesconectar_triggered()
{
  if (connected())
  {
    desconectar();
  }
}

void Mensageiro2_Cliente::on_enviarButton_clicked()
{
  QString destinatario = ui->userEdit->text();
  QString msg = ui->msgEdit->text();
  mysocket_status iResult;

  if (connected())
  {
    if (msg.size()>0 && destinatario.size()>=4 && destinatario.size()<=16)
    {
      iResult = sock.write_string(destinatario.toStdString());
      if ( iResult == mysocket_status::SOCK_OK )
      {
        iResult = sock.write_string(msg.toStdString());
        if ( iResult == mysocket_status::SOCK_OK )
        {
          adicionarMsgEnviada(destinatario,msg);
        }
        else
        {
          desconectar();

          // Emitir msg de erro: nao foi possivel enviar texto
          QMessageBox msgBox;
          msgBox.setWindowTitle("Erro no envio");
          msgBox.setText("Nao foi possivel enviar texto "+msg);
          msgBox.exec();
        }
      }
      else
      {
        desconectar();

        // Emitir msg de erro: nao foi possivel enviar nome de destinatario
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro no envio");
        msgBox.setText("Nao foi possivel enviar nome de destinatario "+destinatario);
        msgBox.exec();
      }
    }
    else
    {
      // Emitir msg de erro: dado(s) invalido(s)
      QMessageBox msgBox;
      msgBox.setWindowTitle("Erro no envio");
      msgBox.setText("Valor invalido de mensagem ("+msg+") e/ou destinatario ("+destinatario+")");
      msgBox.exec();
    }
  }
  ui->userEdit->clear();
  ui->msgEdit->clear();
}
