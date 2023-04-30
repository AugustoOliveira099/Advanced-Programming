#ifndef Mensageiro2_Cliente_Thread_H
#define Mensageiro2_Cliente_Thread_H

#include <QObject>
#include <QString>
#include <thread>

class Mensageiro2_Cliente_Thread: public QObject
{
  Q_OBJECT

private:
  /// A thread de leitura do socket no cliente
  std::thread thr;

  /// Este eh o metodo principal da thread (laco sem fim)
  /// Ele recebe as informacoes do socket e exibe atraves da emissao de sinais
  void main_thread();

  /// A funcao main_thread() executa o metodo main_thread()
  friend void main_thread(Mensageiro2_Cliente_Thread *mct);

  /// Thread estah ou nao em execucao
  bool em_execucao;

public:
  /// Construtor
  explicit Mensageiro2_Cliente_Thread(QObject *parent = nullptr);

  /// Funcao de consulta do estado da thread
  inline bool executing() const {return em_execucao;}

signals:
  void signThreadIniciada();
  void signAdicionarMsgRecebida(QString, QString);
  void signErro(QString, QString);
  void signThreadEncerrada();

public slots:
  /// Iniciar a thread
  bool executar();
  /// Encerrar e aguardar fim da thread
  void encerrar();
};

#endif // Mensageiro2_Cliente_Thread_H
