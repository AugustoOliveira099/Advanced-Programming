#include <iostream>
#include <cmath>
#include "sudoku.h"

using namespace std;

/* ===================================================================
DECLARACAO DAS FUNCOES AUXILIARES DE ENTRADA/SAIDA
=================================================================== */

/// Leh uma Jogada do teclado
void ler_jogada(Jogada& J);

/// Imprimir o titulo do jogo
void exibir_cabecalho();

/// Imprimir dois tabuleiros de Sudoku lado a lado
/// Atual na esquerda, original na direita
void exibir_tabuleiros(const Sudoku& L, const Sudoku& R);

/// Exibe se a jogada escolhida eh valida ou nao
void exibir_jogada(Jogada J, bool jogada_valida);

/// Exibe o numero de casas faceis preenchidas imediatamente
void exibir_preenchidas(int N);

/// Imprime a quantidade de nohs testados, gerados e nao analisados
/// na execucao do algoritmo de resolucao
void exibir_quantidades(unsigned Ntab_testados, unsigned Ntab_gerados, unsigned Ntab_analisar);

/// Informa que o tabuleiro foi resolvido
void exibir_tem_solucao();

/// Informa que o tabuleiro nao tem solucao
void exibir_sem_solucao();

/// Encerra o modo de exibicao
void encerra_exibicao();

/* ===================================================================
PROGRAMA PRINCIPAL
=================================================================== */

int main(void)
{
  Sudoku Origem("sudoku.txt"),S(Origem);
  Jogada J;
  unsigned long long int N_test, N_gera, N_anal;
  int N_preench;
  bool jogada_valida,tabuleiro_insoluvel;

  exibir_cabecalho();
  exibir_tabuleiros(S,Origem);

  do
  {
    tabuleiro_insoluvel = false;
    do
    {
      ler_jogada(J);
    } while(J.tipo()==TipoJogada::JogadaInvalida);
    switch (J.tipo())
    {
    case TipoJogada::Jogar:
      jogada_valida=S.fazer_jogada(J);
      exibir_jogada(J,jogada_valida);
      break;
    case TipoJogada::Apagar:
      jogada_valida=S.apagar_jogada(J,Origem);
      exibir_jogada(J,jogada_valida);
      break;
    case TipoJogada::PreencherImediatas:
      N_preench = S.resolver_casas_faceis();
      tabuleiro_insoluvel = (N_preench < 0);
      exibir_preenchidas(N_preench);
      break;
    case TipoJogada::Resolver:
      tabuleiro_insoluvel = !S.resolver(N_test, N_gera, N_anal);
      exibir_quantidades(N_test, N_gera, N_anal);
      break;
    case TipoJogada::VoltarInicio:
      S = Origem;
      break;
    default:
      break;
    }
    exibir_tabuleiros(S,Origem);
    if (S.fim_de_jogo()) exibir_tem_solucao();
    if (tabuleiro_insoluvel) exibir_sem_solucao();
  } while(J.tipo() != TipoJogada::FimJogo);

  encerra_exibicao();
}

/* ===================================================================
AS FUNCOES DE ENTRADA/SAIDA NAO FORMATADAS
=================================================================== */

/// Leh uma Jogada do teclado
void ler_jogada(Jogada& J)
{
  unsigned II,JJ,VV;
  char tecla;

  cout << endl;
  cout << "Linha [A-I; V=Voltar; P=Preencher; R=Resolver; S=Sair]? ";
  do
  {
    cin >> tecla;
    tecla = toupper(tecla);
  } while ((tecla<'A' || tecla>'I') && tecla!='V' && tecla!='L' && tecla!='P' && tecla!='R' && tecla!='S');

  if (tecla=='V')
  {
    // Voltar ao inicio
    J.setTipo(TipoJogada::VoltarInicio);
    return;
  }
  if (tecla=='P')
  {
    J.setTipo(TipoJogada::PreencherImediatas);
    return;
  }
  if (tecla=='R')
  {
    J.setTipo(TipoJogada::Resolver);
    return;
  }
  if (tecla=='S')
  {
    J.setTipo(TipoJogada::FimJogo);
    return;
  }
  II = tecla-'A';  // De 0 a 8
  cout << "Coluna [1-9]? ";
  do
  {
    cin >> tecla;
    tecla = toupper(tecla);
  } while (tecla<'1' || tecla>'9');

  JJ = tecla-'1';  // De 0 a 8

  cout << "Valor [1-9; 0=apagar]? ";
  do
  {
    cin >> tecla;
    tecla = toupper(tecla);
  } while (tecla<'0' || tecla>'9');

  VV = tecla-'0';  // De 0 a 9
  J.setCoord(II,JJ);
  if (VV!=0)
  {
    J.setTipo(TipoJogada::Jogar);
    J.setValor(VV);
  }
  else
  {
    J.setTipo(TipoJogada::Apagar);
  }
}

/// Imprimir o titulo do jogo
void exibir_cabecalho()
{
  cout << " +-----------------------+\n";
  cout << " |         SUDOKU        |\n";
  cout << " +-----------------------+\n";
}

/// Imprimir dois tabuleiros de Sudoku lado a lado
/// Atual na esquerda, original na direita
void exibir_tabuleiros(const Sudoku& L, const Sudoku& R)
{
  cout << endl;
  cout << "      TABULEIRO ATUAL      "
       << "     TABULEIRO INICIAL     " << endl;
  cout << "   1 2 3   4 5 6   7 8 9   "
       << "   1 2 3   4 5 6   7 8 9   " << endl;
  for (unsigned i=0; i<9; i++)
  {
    if (i%3 == 0)
    {
      cout << " +-------+-------+-------+ "
           << " +-------+-------+-------+ " << endl;
    }

    // Impressao do tabuleiro da esquerda
    cout << char('A'+i) << "| ";
    for (unsigned j=0; j<9; j++)
    {
      if (L.at(i,j)>=1 && L.at(i,j)<=9) cout << int(L.at(i,j));
      else cout << '-';
      cout << ' ';
      if (j%3 == 2) cout << "| ";
    }

    // Impressao do tabuleiro da direita
    cout << char('A'+i) << "| ";
    for (unsigned j=0; j<9; j++)
    {
      if (R.at(i,j)>=1 && R.at(i,j)<=9) cout << int(R.at(i,j));
      else cout << '-';
      cout << ' ';
      if (j%3 == 2) cout << "| ";
    }
    cout << endl;
  }
  cout << " +-------+-------+-------+ "
       << " +-------+-------+-------+ " << endl;
}

/// Exibe se a jogada escolhida eh valida ou nao
void exibir_jogada(Jogada J, bool jogada_valida)
{
  if (J.tipo()==TipoJogada::Jogar || J.tipo()==TipoJogada::Apagar)
  {
    cout << '[' << char('A'+J.linha()) << ',' << char('1'+J.coluna()) << "] <- "
         << (J.tipo()==TipoJogada::Apagar ? 0 : J.valor()) << ": Jogada "
         << (jogada_valida ? "valida" : "invalida") << endl;
  }
}

// Exibe o numero de casas faceis preenchidas imediatamente
void exibir_preenchidas(int N)
{
  unsigned NN = abs(N);
  if (NN>81) NN=0;
  if (NN>0) cout << NN;
  else cout << "Nenhuma";
  cout << ' ';
  if (NN>1)
  {
    cout << "casas preenchidas";
  }
  else
  {
    cout << "casa preenchida";
  }
  cout << endl;
}

// Imprime a quantidade de nohs testados, gerados e nao analisados
// na execucao do algoritmo de resolucao
void exibir_quantidades(unsigned Ntab_testados, unsigned Ntab_gerados, unsigned Ntab_analisar)
{
  cout << "Nos gerados, testados e a analisar: ";
  cout << Ntab_gerados << ' ';
  cout << Ntab_testados << ' ';
  cout << Ntab_analisar << endl;
}

/// Informa que o tabuleiro foi resolvido
void exibir_tem_solucao()
{
  cout << "TABULEIRO RESOLVIDO!\n";
}

/// Informa que o tabuleiro nao tem solucao
void exibir_sem_solucao()
{
  cout << "O TABULEIRO NAO TEM SOLUCAO!\n";
}

/// Encerra o modo de exibicao
void encerra_exibicao()
{
  cout << "FIM DO JOGO!\n";
}



