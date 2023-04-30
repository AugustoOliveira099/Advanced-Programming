#include <string>
#include <QMessageBox>

#include "connectserver.h"
#include "ui_connectserver.h"
#include "mysocket.h"
#include "mensageiro.h"

using namespace std;

// Variaveis globais
extern tcp_mysocket sock;

ConnectServer::ConnectServer(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectServer),
  server(""),
  usuario("")
{
  ui->setupUi(this);
}

ConnectServer::~ConnectServer()
{
  delete ui;
}

void ConnectServer::on_buttonBox_accepted()
{
  server = ui->editServidor->text();
  usuario = ui->editLogin->text();

  // O numero IP de um servidor deve ter no minimo 7 caracteres
  // O nome de login deve ter entre 4 e 16 caracteres
  if (server.size()>7 && usuario.size()>=4 && usuario.size()<=16)
  {
    if (sock.connect(server.toStdString(), MENSAGEIRO_PORTA) == mysocket_status::SOCK_OK)
    {
      // Socket estah conectado
      if ( sock.write_string(usuario.toStdString()) == mysocket_status::SOCK_OK )
      {
        emit signExecutarThread();
      }
      else
      {
        // Emitir msg de erro: nao foi possivel enviar nome de login
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro na conexao");
        msgBox.setText("Nao foi possivel enviar nome de login "+usuario);
        msgBox.exec();
        server = usuario = "";
      }
    }
    else
    {
      // Emitir msg de erro: nao foi possivel conectar
      QMessageBox msgBox;
      msgBox.setWindowTitle("Erro na conexao");
      msgBox.setText("Nao foi possivel conectar com o servidor "+server);
      msgBox.exec();
      server = usuario = "";
    }
  }
  else
  {
    // Emitir msg de erro: dado(s) invalido(s)
    QMessageBox msgBox;
    msgBox.setWindowTitle("Erro na conexao");
    msgBox.setText("Valor invalido de servidor ("+server+") e/ou login ("+usuario+")");
    msgBox.exec();
    server = usuario = "";
  }
}
