#ifndef MENSAGEIRO2_CLIENTE_H
#define MENSAGEIRO2_CLIENTE_H

#include <QMainWindow>
#include <QLabel>
#include <QString>

#include "connectserver.h"
#include "mensageiro2_cliente_thread.h"

namespace Ui {
  class Mensageiro2_Cliente;
}

class Mensageiro2_Cliente : public QMainWindow
{
  Q_OBJECT

public:
  explicit Mensageiro2_Cliente(QWidget *parent = 0);
  ~Mensageiro2_Cliente();
  inline bool connected() const {return cl_thr->executing();}

  void desconectar();

public slots:
  void interfaceConectada();
  void interfaceDesconectada();

  void adicionarMsgEnviada(QString dest, QString msg);
  void adicionarMsgRecebida(QString remet, QString msg);
  void exibirErro(QString title, QString msg);

private slots:
  void on_actionSair_triggered();
  void on_actionConectar_triggered();
  void on_actionApagar_triggered();
  void on_actionDesconectar_triggered();
  void on_enviarButton_clicked();

private:
  Ui::Mensageiro2_Cliente *ui;

  QLabel ipServidor;
  QLabel myLogin;

  Mensageiro2_Cliente_Thread *cl_thr;
  ConnectServer *connectServer;
};

#endif // MENSAGEIRO2_CLIENTE_H
