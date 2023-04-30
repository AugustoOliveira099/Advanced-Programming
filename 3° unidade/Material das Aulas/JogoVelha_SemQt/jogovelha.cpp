#include "jogovelha.h"

char jogador2char(JogadorVelha J)
{
  switch(J)
  {
    case JogadorVelha::X: return 'X';
    case JogadorVelha::O: return 'O';
    case JogadorVelha::NINGUEM: return ' ';
  }
  // Nunca chega aqui
  return '?';
}

void JogoVelha::reiniciar()
{
  for (int i=0; i<3; i++) for (int j=0; j<3; j++)
  {
    set(i,j) = JogadorVelha::NINGUEM;  // Espaco = casa vazia;
  }
  vez = JogadorVelha::X; // Sempre comeca com o jogador X
  venc = JogadorVelha::NINGUEM; // Nenhum vencedor
}

// Retorna true se alguem ganhou
// Se teste for positivo, altera venc e vez <- JogadorVelha::NINGUEM
bool JogoVelha::vitoria()
{
  for (int k=0; k<3; k++)
  {
    // Testa as linhas
    if ((at(k,0)==JogadorVelha::X || at(k,0)==JogadorVelha::O) &&
       at(k,1)==at(k,0) && at(k,2)==at(k,0) )
    {
      venc = at(k,0);
      vez = JogadorVelha::NINGUEM;
      return true;
    }
    // Testa as colunas
    if ((at(0,k)==JogadorVelha::X || at(0,k)==JogadorVelha::O) &&
       at(1,k)==at(0,k) && at(2,k)==at(0,k) )
    {
      venc = at(0,k);
      vez = JogadorVelha::NINGUEM;
      return true;
    }
  }
  // Testa as diagonais
  if ((at(1,1)==JogadorVelha::X || at(1,1)==JogadorVelha::O) &&
    ( (at(0,0)==at(1,1) && at(2,2)==at(1,1)) ||
      (at(0,2)==at(1,1) && at(2,0)==at(1,1)) ))
  {
    venc = at(1,1);
    vez = JogadorVelha::NINGUEM;
    return true;
  }
  // Ninguem venceu
  return false;
}

// Retorna true se nao pode mais ganhar
// (vitoria ou tabuleiro completo)
// Se teste for positivo, vez <- JogadorVelha::NINGUEM
bool JogoVelha::fimDeJogo()
{
  // Alguem jah ganhou o jogo?
  if (venc == JogadorVelha::NINGUEM)
  {
    for (int i=0; i<3; i++) for (int j=0; j<3; j++)
    {
      if (at(i,j) == JogadorVelha::NINGUEM) return false;
    }
  }
  // Jogo acabou: nao tem mais jogador valido
  vez = JogadorVelha::NINGUEM;
  return true;
}

// Testa se o jogador da vez pode jogar na casa <I,J>
bool JogoVelha::jogadaValida(int I, int J) const
{
  // Alguem jah ganhou o jogo?
  if (venc != JogadorVelha::NINGUEM) return false;
  // Tem um jogador apto a jogar?
  if (vez!=JogadorVelha::X && vez!=JogadorVelha::O) return false;
  // Checa os indices
  if (I<0 || I>=3 || J<0 || J>=3) return false;
  // Checa se a casa estah vazia
  if (at(I,J) != JogadorVelha::NINGUEM) return false;

  // Jogada eh valida
  return true;
}

// Coloca a marca do jogador da vez na casa <I,J>
void JogoVelha::fazerJogada(int I, int J)
{
  if (jogadaValida(I,J))
  {
    set(I,J) = vez;
  }
  // Testa se ganhou o jogo
  if (!vitoria() && !fimDeJogo())
  {
    vez = (vez==JogadorVelha::O ? JogadorVelha::X : JogadorVelha::O);
  }
}
