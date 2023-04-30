#include <iostream>
#include <string.h>

#include "mysocket.h"

using namespace std;

#define PORTA_TESTE "23456"

int main(void)
{
  mysocket_status iResult;
  tcp_mysocket_server c;
  tcp_mysocket s;

  bool fim = false;
  string msg;

  // Inicializa a biblioteca de sockets
  iResult = mysocket::init();
  if (iResult != mysocket_status::SOCK_OK) {
    cerr << "Biblioteca mysocket nao pode ser inicializada\n";
    exit(1);
  }

  /// Coloca o socket de controle em modo de espera
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

  while (!fim)
  {
    cout << "Aguardando msg do cliente...\n";
    iResult = s.read_string(msg);
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
        // Nunca deve acontecer, jah que a read_string nao tem timeout
      }

    }

    if (!fim) do
    {
      cout << "Mensagem para o cliente [FIM para terminar]: ";
      cin >> ws;
      getline(cin,msg);
    } while (msg.size()==0);
    if (!fim) fim = (msg=="FIM");

    iResult = s.write_string(msg);
    if ( iResult != mysocket_status::SOCK_OK )
    {
      cerr << "Problema ao enviar mensagem para o cliente\n";
      s.close();
      fim = true;
    }
  }

  // Desliga os sockets
  cout << "Encerrando o socket de conexoes\n";
  c.close();
  cout << "Encerrando o socket de comunicacao\n";
  s.close();

  /// Encerramento da biblioteca de sockets
  mysocket::end();
}
