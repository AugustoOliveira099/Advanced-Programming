#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QDialog>
#include <QString>

namespace Ui {
  class ConnectServer;
}

class ConnectServer : public QDialog
{
  Q_OBJECT

public:
  explicit ConnectServer(QWidget *parent = 0);
  ~ConnectServer();
  inline QString getServer() const {return server;}
  inline QString getUsuario() const {return usuario;}

signals:
  void signExecutarThread();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::ConnectServer *ui;

  QString server;
  QString usuario;
};

#endif // CONNECTSERVER_H
