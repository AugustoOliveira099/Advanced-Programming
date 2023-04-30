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
      cout << "Mensagem recebida do servidor: " << msg << endl;
      if (msg == "FIM")
      {
        cout << "Servidor encerrou\n";
        s.close();
        fim = true;
      }
    }
    else
    {
      if (iResult==mysocket_status::SOCK_ERROR)
      {
        cerr << "Erro na recepcao de msg do servidor. Desconectando\n";
        s.close();
        fim = true;
      }
      if (iResult==mysocket_status::SOCK_DISCONNECTED)
      {
        cout << "Servidor desconectou\n";
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
int main(int argc, char **argv)
{
  // Thread de leitura
  thread thr;

  mysocket_status iResult;
  string msg;

  // Inicializa a biblioteca de sockets
  iResult = mysocket::init();
  if (iResult != mysocket_status::SOCK_OK) {
    cerr << "Biblioteca mysocket nao pode ser inicializada\n";
    exit(1);
  }

  if( argc<2 ) {
    cout << "Maquina onde esta rodando o servidor (IP): ";
    cin >> ws;
    getline(cin, msg);
  }
  else {
    msg = argv[1];
  }

  iResult = s.connect(msg, PORTA_TESTE);
  if (iResult == mysocket_status::SOCK_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE
         << " pelo socket " << s << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
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
      cout << "Mensagem a enviar [FIM para terminar]: ";
      cin >> ws;
      getline(cin, msg);
    } while (msg.size()==0);
    if (!fim) fim = (msg=="FIM");

    iResult = s.write_string(msg);
    if ( iResult != mysocket_status::SOCK_OK )
    {
      cerr << "Problema ao enviar mensagem para o servidor\n";
      s.close();
      fim = true;
    }
  }

  /// Desliga o socket
  cout << "Encerrando o socket de comunicacao\n";
  s.close();

  /// Espera encerramento da outra thread
  if (thr.joinable()) thr.join();

  /// Encerramento da biblioteca de sockets
  mysocket::end();
}
