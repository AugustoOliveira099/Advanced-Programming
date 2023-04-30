#include <iostream>
#include "jogovelha.h"

using namespace std;

ostream& operator<<(ostream &O, const JogoVelha &J)
{
  JogadorVelha prov;

  O << "    1   2   3 \n";
  O << "  +---+---+---+";
  prov = J.jogadorVez();
  if (prov==JogadorVelha::X || prov==JogadorVelha::O)
  {
    cout << "   Jogador da vez = " << jogador2char(prov);
  }
  O << endl;
  O << "A | "
    << jogador2char(J(0,0)) << " | "
    << jogador2char(J(0,1)) << " | "
    << jogador2char(J(0,2)) << " |\n";
  O << "  +---+---+---+\n";
  O << "B | "
    << jogador2char(J(1,0)) << " | "
    << jogador2char(J(1,1)) << " | "
    << jogador2char(J(1,2)) << " |\n";
  O << "  +---+---+---+\n";
  O << "C | "
    << jogador2char(J(2,0)) << " | "
    << jogador2char(J(2,1)) << " | "
    << jogador2char(J(2,2)) << " |\n";
  O << "  +---+---+---+";
  prov = J.vencedor();
  if (prov==JogadorVelha::X || prov==JogadorVelha::O)
  {
    cout << "   Vencedor = " << jogador2char(prov);
  }
  O << endl;
  return O;
}

int main(void)
{
  JogoVelha JV;
  bool terminar(false), fim_de_jogo;
  char tecla;

  cout << " +-----------------------+\n";
  cout << " |     JOGO DA VELHA     |\n";
  cout << " +-----------------------+\n";

  do
  {
    cout << JV;
    fim_de_jogo = JV.fimDeJogo();
    do
    {
      cout << (!fim_de_jogo ? "Linha [A-C; " : "[");
      cout << "R=Reiniciar; S=Sair]? ";
      cin >> tecla;
      tecla = toupper(tecla);
    } while ((tecla<'A' || tecla>'C' || fim_de_jogo) && tecla!='R' && tecla!='S');

    if (tecla=='R')
    {
      JV.reiniciar();
    }
    if (tecla=='S')
    {
      terminar = true;
    }
    if (tecla>='A' && tecla<='C' && !fim_de_jogo)
    {
      int i = tecla-'A';  // De 0 a 2
      do
      {
        cout << "Coluna [1-3]? ";
        cin >> tecla;
        tecla = toupper(tecla);
      } while (tecla<'1' || tecla>'3');
      int j = tecla-'1';  // De 0 a 2
      if (JV.jogadaValida(i,j))
      {
        JV.fazerJogada(i,j);
      }
      else
      {
        cout << "Jogada invalida!\n";
      }
    }
  } while(!terminar);
}
