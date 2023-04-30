#ifndef _JOGOVELHA_H
#define _JOGOVELHA_H
#include <vector>
#include <algorithm>

enum class JogadorVelha
{
  X,
  O,
  NINGUEM
};

char jogador2char(JogadorVelha J);

class JogoVelha
{
private:
  /// As 9 casas do tabuleiro
  std::vector<JogadorVelha> tab;

  /// Quem estah na vez de jogar
  JogadorVelha vez;

  /// Quem venceu o jogo
  JogadorVelha venc;

  /// Retorna referencia que permite alterar o conteudo da casa <I,J>
  inline JogadorVelha& set(int I, int J) {return tab.at(3*I+J);}
public:
  /// Construtor default (tabuleiro vazio)
  inline JogoVelha(): tab(9) {reiniciar();}

  /// Limpa o tabuleiro
  void reiniciar();

  /// Retorna o conteudo da casa <I,J>
  inline JogadorVelha at(int I, int J) const {return tab.at(3*I+J);}
  inline JogadorVelha operator()(int I, int J) const {return tab.at(3*I+J);}

  /// Retorna quem estah na vez de jogar (JogadorVelha::NINGUEM se ninguem)
  inline JogadorVelha jogadorVez() const {return vez;}

  /// Retorna quem ganhou o jogo (JogadorVelha::NINGUEM se ninguem)
  inline JogadorVelha vencedor() const {return venc;}

  /// Retorna numero de casas X
  inline int numX() const {return count(tab.begin(), tab.end(), JogadorVelha::X);}

  /// Retorna numero de casas O
  inline int numO() const {return count(tab.begin(), tab.end(), JogadorVelha::O);}

  /// Retorna true se alguem ganhou
  /// Se teste for positivo, altera venc e vez <- JogadorVelha::NINGUEM
  bool vitoria();

  /// Retorna true se nao pode mais ganhar
  /// (vitoria ou tabuleiro completo)
  /// Se teste for positivo, vez <- JogadorVelha::NINGUEM
  bool fimDeJogo();

  /// Testa se o jogador da vez pode jogar na casa <I,J>
  bool jogadaValida(int I, int J) const;

  /// Coloca a marca do jogador da vez na casa <I,J>
  void fazerJogada(int I, int J);
};

#endif // _JOGOVELHA_H
