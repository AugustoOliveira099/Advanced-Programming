#include <iostream>
#include "console.h"
#include "sudoku.h"
#include <conio.h>  // Para getch()

using namespace std;

/// Uma variavel global que representa o console formatado
Console Term;

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
AS FUNCOES DE ENTRADA/SAIDA FORMATADA
=================================================================== */

/// Leh uma Jogada do teclado
void ler_jogada(Jogada& J)
{
  unsigned II,JJ,VV;
  char tecla;

  Term.gotoYX(22,2);
  cout << "[A-I] Linha";
  Term.gotoYX(23,2);
  cout << "  [V] Voltar ao inicio";
  Term.gotoYX(24,2);
  cout << "  [P] Preencher imediatas";
  Term.gotoYX(25,2);
  cout << "  [R] Resolver";
  Term.gotoYX(26,2);
  cout << "  [S] Sair";
  Term.gotoYX(22,32);
  Term.exibir_cursor();
  cout << "OPCAO? ";
  do
  {
    tecla = toupper(getch());
  } while ((tecla<'A' || tecla>'I') && tecla!='V' && tecla!='P' && tecla!='R' && tecla!='S');
  cout << tecla << endl;
  Term.ocultar_cursor();

  // Apaga todas as linhas
  for (unsigned i=19; i<=26; i++)
  {
    Term.gotoYX(i,1);
    Term.limpar_linha();
  }

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
  Term.gotoYX(7+II+II/3,1);
  Term.cores(CONSOLE_CORES::BLACK, CONSOLE_CORES::WHITE);
  cout << tecla;
  Term.cores(CONSOLE_CORES::DEFAULT, CONSOLE_CORES::DEFAULT);

  Term.gotoYX(22,2);
  cout << "[1-9] Coluna";
  Term.gotoYX(22,32);
  Term.exibir_cursor();
  cout << "OPCAO? ";
  do
  {
    tecla = toupper(getch());
  } while (tecla<'1' || tecla>'9');
  cout << tecla << endl;
  Term.ocultar_cursor();
  Term.gotoYX(22,1);
  Term.limpar_linha();

  JJ = tecla-'1';  // De 0 a 8
  Term.gotoYX(5,4+2*(JJ+JJ/3));
  Term.cores(CONSOLE_CORES::BLACK, CONSOLE_CORES::WHITE);
  cout << tecla;
  Term.cores(CONSOLE_CORES::DEFAULT, CONSOLE_CORES::DEFAULT);

  Term.gotoYX(22,2);
  cout << "[1-9] Valor";
  Term.gotoYX(23,2);
  cout << "  [0] Apagar]";
  Term.gotoYX(22,32);
  Term.exibir_cursor();
  cout << "OPCAO? ";
  do
  {
    tecla = toupper(getch());
  } while (tecla<'0' || tecla>'9');
  cout << tecla << endl;
  Term.ocultar_cursor();
  for (unsigned i=22; i<=23; i++)
  {
    Term.gotoYX(i,1);
    Term.limpar_linha();
  }

  VV = tecla-'0';  // De 0 a 9

  // Restaura as etiquetas normais
  Term.gotoYX(7+II+II/3,1);
  cout << char('A'+II);
  Term.gotoYX(5,4+2*(JJ+JJ/3));
  cout << JJ+1;

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

/// Funcao auxiliar para desenhar as bordas de um tabuleiro
///
/// O parametro booleano de entrada "inicial" indica a posicao da impressao:
/// true: lado direito da tela (tabuleiro inicial)
/// false: lado esquerdo da tela (tabuleiro atual)
void desenha_moldura(bool inicial)
{
  Term.ocultar_cursor();
  int J = (inicial ? 29 : 1);

  // Muda para o modo de desenho de linhas
  Term.modo_linhas();

  for (unsigned i=7; i<=17; i++)
  {
    Term.gotoYX(i,J+1);
    cout << "x       x       x       x";  // |   |   |   |
  }
  for (unsigned i=0; i<4; i++)
  {
    Term.gotoYX(6,J+1);
    cout << "lqqqqqqqwqqqqqqqwqqqqqqqk";  // -------------
    Term.gotoYX(10,J+1);
    cout << "tqqqqqqqnqqqqqqqnqqqqqqqu";  // -------------
    Term.gotoYX(14,J+1);
    cout << "tqqqqqqqnqqqqqqqnqqqqqqqu";  // -------------
    Term.gotoYX(18,J+1);
    cout << "mqqqqqqqvqqqqqqqvqqqqqqqj";  // -------------
  }

  // Retorna para o modo normal
  Term.modo_texto();

  // Imprime as etiquetas
  for (unsigned i=0; i<9; i++)
  {
    Term.gotoYX(7+i+i/3,J);
    cout << char('A'+i);
    Term.gotoYX(5,J+3+2*(i+i/3));
    cout << i+1;
  }
}

/// Desenha os textos iniciais e molduras dos tabuleiros
void exibir_cabecalho()
{
  if (!Term.formatado())
  {
    cerr << "O terminal nao permite saida formatada!\n";
    cerr << "Este arquivo soh pode ser executado no Windows 10\n";
    cerr << "Compile com o arquivo na versao nao formatada\n";
    cerr << "Saindo...\n";
    exit(1);
  }

  Term.tela_alternativa();
  Term.clrscr();

  Term.modo_linhas();
  Term.cores(CONSOLE_CORES::BRIGHT_YELLOW, CONSOLE_CORES::DEFAULT);
  cout << " lqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqk \n";
  cout << " x                                                   x \n";
  cout << " mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj \n";
  Term.modo_texto();
  Term.gotoYX(2,3);
  Term.cores(CONSOLE_CORES::BRIGHT_BLACK, CONSOLE_CORES::BRIGHT_YELLOW);
  cout << "                      SUDOKU                       ";
  Term.cores(CONSOLE_CORES::BRIGHT_WHITE, CONSOLE_CORES::DEFAULT);
  Term.gotoYX(4,7);
  cout << "TABULEIRO ATUAL";
  Term.gotoYX(4,34);
  cout << "TABULEIRO INICIAL";
  Term.cores(CONSOLE_CORES::DEFAULT, CONSOLE_CORES::DEFAULT);

  desenha_moldura(true);
  desenha_moldura(false);
}

/// Funcao auxiliar para exibir objetos da classe Sudoku
///
/// Imprime o conteudo do tabuleiro S na tela
/// O parametro booleano de entrada "inicial" indica a posicao da impressao:
/// true: lado direito da tela (tabuleiro inicial)
/// false: lado esquerdo da tela (tabuleiro atual)
void imprimir_tabuleiro(const Sudoku &S, bool inicial)
{
  int J = (inicial ? 32 : 4);
  Term.ocultar_cursor();
  for (unsigned i=0; i<9; i++)
  {
    for (unsigned j=0; j<9; j++)
    {
      Term.gotoYX(7+i+i/3, J+2*(j+j/3));
      if (S.at(i,j)>=1 && S.at(i,j)<=9) cout << int(S.at(i,j));
      else cout << '-';
      cout << ' ';
      if (!Term.formatado()) if (j%3 == 2) cout << "| ";
    }
    cout << endl;
  }
}

/// Imprimir dois tabuleiros de Sudoku lado a lado
/// Atual na esquerda, original na direita
void exibir_tabuleiros(const Sudoku& L, const Sudoku& R)
{
  imprimir_tabuleiro(L, false);
  imprimir_tabuleiro(R, true);
}

/// Exibe se a jogada escolhida eh valida ou nao
void exibir_jogada(Jogada J, bool jogada_valida)
{
  if (J.tipo()==TipoJogada::Jogar || J.tipo()==TipoJogada::Apagar)
  {
    Term.gotoYX(19,2);
    cout << '[' << char('A'+J.linha()) << ',' << char('1'+J.coluna()) << "] <- "
         << (J.tipo()==TipoJogada::Apagar ? 0 : J.valor()) << ": Jogada "
         << (jogada_valida ? "valida" : "invalida") << endl;
  }
}

/// Exibe o numero de casas faceis preenchidas imediatamente
void exibir_preenchidas(int N)
{
  unsigned NN = abs(N);
  if (NN>81) NN=0;
  Term.gotoYX(19,4);
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
}

// Imprime a quantidade de nohs testados, gerados e nao analisados
// na execucao do algoritmo de resolucao
void exibir_quantidades(unsigned Ntab_testados, unsigned Ntab_gerados, unsigned Ntab_analisar)
{
  Term.gotoYX(19,4);
  cout << "Gerados:          Testados:         A analisar:";
  Term.gotoYX(19,12);
  cout << Ntab_gerados << ' ';
  Term.gotoYX(19,31);
  cout << Ntab_testados << ' ';
  Term.gotoYX(19,51);
  if (Term.formatado()) cout << "    ";
  Term.gotoYX(19,51);
  cout << Ntab_analisar << endl;
}

/// Informa que o tabuleiro foi resolvido
void exibir_tem_solucao()
{
  Term.gotoYX(20,19);
  Term.cores(CONSOLE_CORES::BRIGHT_GREEN, CONSOLE_CORES::DEFAULT);
  cout << "TABULEIRO RESOLVIDO!";
  Term.cores(CONSOLE_CORES::DEFAULT, CONSOLE_CORES::DEFAULT);
}

/// Informa que o tabuleiro nao tem solucao
void exibir_sem_solucao()
{
  Term.gotoYX(20,15);
  Term.cores(CONSOLE_CORES::BRIGHT_GREEN, CONSOLE_CORES::DEFAULT);
  cout << "O TABULEIRO NAO TEM SOLUCAO!";
  Term.cores(CONSOLE_CORES::DEFAULT, CONSOLE_CORES::DEFAULT);
}

/// Encerra o modo de exibicao formatada
void encerra_exibicao()
{
  Term.tela_normal();
  cout << "FIM DO JOGO!\n";
}

