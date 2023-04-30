#include <iostream>
#include <thread>

#include "mysocket.h"

using namespace std;

#define PORTA_TESTE "23456"
#define TIMEOUT_TESTE 15

/// Socket global
tcp_mysocket s;
/// Flag para sinalizar o encerramento das threads
bool fim = false;

/// Thread de leitura e impressao das mensagens recebidas no socket
void main_thread(void)
{
  mysocket_status iResult;
  string msg;

  cout << "Thread iniciada!\n";
  while (!fim && s.connected())
  {
    iResult = s.read_string(msg, TIMEOUT_TESTE*1000);
    if (iResult == mysocket_status::SOCK_OK)
    {
      cout << "Mensagem recebida do cliente: " << msg << endl;
      if (msg == "FIM")
      {
        cout << "Cliente encerrou\n";
        s.close();
        fim = true;
      }
    }
    else
    {
      if (iResult==mysocket_status::SOCK_ERROR)
      {
        cout << "Erro na recepcao de msg do cliente. Desconectando\n";
        s.close();
        fim = true;
      }
      if (iResult==mysocket_status::SOCK_DISCONNECTED)
      {
        cout << "Cliente desconectou\n";
        s.close();
        fim = true;
      }
      if (iResult==mysocket_status::SOCK_TIMEOUT)
      {
        cout << "Inatividade de " << TIMEOUT_TESTE << " segundos\n";
      }
    }
  }
  cout << "Thread encerrada!\n";
}

/// Thread principal e de digitacao e envio das mensagens
int main(void)
{
  /// Socket de conexoes
  tcp_mysocket_server c;
  /// Thread de leitura
  thread thr;

  mysocket_status iResult;
  string msg;

  // Inicializa a biblioteca de sockets
  iResult = mysocket::init();
  if (iResult != mysocket_status::SOCK_OK) {
    cerr << "Biblioteca mysocket nao pode ser inicializada\n";
    exit(1);
  }

  // Coloca o socket de controle em modo de espera
  iResult = c.listen(PORTA_TESTE,1);
  if (iResult == mysocket_status::SOCK_OK)
  {
    // Aguarda uma conexao
    cout << "Aguardando conexao do cliente...\n";
    iResult = c.accept(s);
    if (iResult == mysocket_status::SOCK_OK)
    {
      cout << "Cliente conectado no socket " << s << endl;
    }
    else
    {
      cerr << "Não foi possível estabelecer uma conexão\n";
      fim = true;
    }
  }
  else
  {
    cerr << "Não foi possível abrir o socket de controle\n";
    fim = true;
  }

  // Cria a thread
  if (!fim)
  {
    thr = thread(main_thread);
    if (!thr.joinable())
    {
      cerr << "Problema ao criar thread\n";
      fim = true;
    }
  }

  while (!fim && s.connected())
  {
    do
    {
      cout << "Mensagem para o cliente [FIM para terminar]: ";
      cin >> ws;
      getline(cin, msg);
    } while (msg.size()==0);
    if (!fim) fim = (msg=="FIM");

    iResult = s.write_string(msg);
    if ( iResult == mysocket_status::SOCK_ERROR )
    {
      cerr << "Problema ao enviar mensagem para o cliente\n";
      s.close();
      fim = true;
    }
  }

  /// Desliga os sockets
  cout << "Encerrando o socket de conexoes\n";
  c.close();
  cout << "Encerrando o socket de comunicacao\n";
  s.close();

  /// Espera encerramento da outra thread
  if (thr.joinable()) thr.join();

  /// Encerramento da biblioteca de sockets
  mysocket::end();
}
