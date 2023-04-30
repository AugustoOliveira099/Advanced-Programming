#include <iostream>
#include <string.h>

#include "mysocket.h"

using namespace std;

#define PORTA_TESTE "23456"

int main(int argc, char **argv)
{
  tcp_mysocket s;
  mysocket_status iResult;

  bool fim = false;
  string msg;

  // Inicializa a biblioteca de sockets
  iResult = mysocket::init();
  if (iResult != mysocket_status::SOCK_OK) {
    cerr << "Biblioteca mysocket nao pode ser inicializada\n";
    exit(1);
  }

  /// Leh o IP do servidor
  if( argc<2 ) {
    cout << "Maquina onde esta rodando o servidor (IP): ";
    cin >> ws;
    getline(cin, msg);
  }
  else {
    msg = argv[1];
  }

  if (s.connect(msg, PORTA_TESTE) == mysocket_status::SOCK_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE
         << " pelo socket " << s << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
    fim = true;
  }

  while (!fim)
  {
    do
    {
      cout << "Mensagem a enviar [FIM para terminar]: ";
      cin >> ws;
      getline(cin, msg);
    } while (msg.size()==0);
    if (!fim) fim = (msg=="FIM");

    iResult = s.write_string(msg);
    if ( iResult == mysocket_status::SOCK_ERROR )
    {
      cerr << "Problema ao enviar mensagem para o servidor\n";
      s.close();
      fim = true;
    }

    cout << "Aguardando msg do servidor...\n";
    iResult = s.read_string(msg);
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
      if (iResult == mysocket_status::SOCK_ERROR)
      {
        cout << "Erro na recepcao de msg do servidor. Desconectando\n";
        s.close();
        fim = true;
      }
      if (iResult == mysocket_status::SOCK_DISCONNECTED)
      {
        cout << "Servidor desconectou\n";
        s.close();
        fim = true;
      }
      if (iResult == mysocket_status::SOCK_TIMEOUT)
      {
        // Nunca deve acontecer, jah que a read_string nao tem timeout
      }
    }
  }

  // Desliga o socket
  cout << "Encerrando o socket de comunicacao\n";
  s.close();

  /// Encerramento da biblioteca de sockets
  mysocket::end();
}
