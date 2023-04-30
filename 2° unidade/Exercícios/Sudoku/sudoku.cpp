#include <iostream>  /* cerr */
#include <cstdlib>   /* srand, rand */
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <time.h>

#include "sudoku.h"

using namespace std;

/**********************************************************
 * CLASSE JOGADA                                          *
 **********************************************************/

/// Construtor
Jogada::Jogada(TipoJogada T, unsigned I, unsigned J, unsigned V)
{
  setTipo(T);
  setCoord(I,J);
  setValor(V);
}

/// Fixa as coordenadas de uma jogada
void Jogada::setCoord(unsigned I, unsigned J)
{
  if (I>8) I=0;
  if (J>8) J=0;
  i = I;
  j = J;
}

/// Fixa o valor de uma jogada
void Jogada::setValor(unsigned V)
{
  if (V>9) V=0;
  v = V;
}

/**********************************************************
 * CLASSE SUDOKU                                          *
 **********************************************************/

/// Limpa o tabuleiro
void Sudoku::limpar()
{
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    set(i,j) = 0;
  }
}

/// Leh um tabuleiro do arquivo nome_arq
/// Caso ocorra erro, gera tabuleiro parcialmente preenchido
/// e retorna false; se der tudo certo, retorna true
bool Sudoku::ler(const char *nome_arq)
{
  // Comeca com tabuleiro vazio
  limpar();

  // Abre o arquivo
  ifstream arq(nome_arq);
  if (!arq.is_open())
  {
    return false;
  }

  string prov;
  int valor;

  // Leh o cabecalho
  arq >> prov;
  if (prov != "SUDOKU")
  {
    arq.close();
    return false;
  }

  // Leh os valores iniciais das casas do tabuleiro
  bool valido=true;
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    arq >> valor;
    if (valor != 0)
    {
      Jogada J(TipoJogada::Jogar,i,j,valor);
      if (!fazer_jogada(J) && valido) valido=false;
    }
  }
  arq.close();
  return valido;
}

/// Compara se dois tabuleiros sao iguais
bool Sudoku::operator==(const Sudoku &S) const
{
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (at(i,j) != S.at(i,j)) return false;
  }
  return true;
}

/// Testa se a jogada J eh possivel para o tabuleiro
bool Sudoku::jogada_valida(Jogada J) const
{
  unsigned i,j;
  // Testar a jogada
  if (J.tipo() != TipoJogada::Jogar) return false;
  if (J.linha()>=9 || J.coluna()>=9) return false;
  if (J.valor()<1 || J.valor()>9) return false;

  // Testar se a casa nao estah vazia
  if (at(J.linha(),J.coluna()) != 0) return false;

  // Testar a linha
  for (i=0; i<9; i++)
  {
    if (at(i,J.coluna()) == J.valor()) return false;
  }
  // Testar a coluna
  for (j=0; j<9; j++)
  {
    if (at(J.linha(),j) == J.valor()) return false;
  }
  // Testar o bloco
  unsigned iIni = 3*(J.linha()/3);
  unsigned jIni = 3*(J.coluna()/3);
  for (i=0; i<3; i++) for (j=0; j<3; j++)
  {
    if (at(iIni+i,jIni+j) == J.valor()) return false;
  }
  return true;
}

/// Testa se a jogada J eh um apagamento valido de uma casa para o tabuleiro,
/// levando em conta o tabuleiro original (nao eh permitido apagar casas que
/// estavam preenchidas no tabuleiro original)
bool Sudoku::apagamento_valido(Jogada J, const Sudoku &Origem) const
{
  // Testar a jogada
  if (J.tipo() != TipoJogada::Apagar) return false;
  if (J.linha()>=9 || J.coluna()>=9) return false;

  // Testar se a casa estah vazia
  if (at(J.linha(),J.coluna()) == 0) return false;

  // Testar se a casa do tabuleiro original nao estah vazia
  if (Origem.at(J.linha(),J.coluna()) != 0) return false;

  return true;
}

/// Executa uma jogada (altera o tabuleiro)
bool Sudoku::fazer_jogada(Jogada J)
{
  bool valid = jogada_valida(J);
  if (valid) set(J.linha(),J.coluna()) = J.valor();
  return valid;
}

/// Apaga uma casa (altera o tabuleiro)
bool Sudoku::apagar_jogada(Jogada J, const Sudoku &O)
{
  bool valid = apagamento_valido(J,O);
  if (valid) set(J.linha(),J.coluna()) = 0;
  return valid;
}

/// Testa se o tabuleiro estah completo (fim de jogo)
bool Sudoku::fim_de_jogo() const
{
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (at(i,j) == 0) return false;
  }
  return true;
}

/// Retorna o numero de casas vazias no tabuleiro
unsigned Sudoku::num_casas_vazias() const
{
  unsigned N(0);
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (at(i,j) == 0) N++;
  }
  return N;
}

/// Calcula o numero de possibilidades para preencher a casa (i,j)
/// utilizando apenas as regras "faceis" (linha, coluna e bloco)
/// Se houver uma unica possibilidade de preenchimento, retorna o valor (1 a 9)
/// Se nao houver nenhuma possibilidade de preenchimento, retorna 0, o que
/// indica que o tabuleiro nao tem solucao
/// Se houver mais de uma possibilidade de preenchimento, retorna um numero
/// negativo (<= -2), cujo modulo eh o numero de possibilidades
int Sudoku::numero_possibilidades(unsigned i, unsigned j) const
{
  // A principio, todos os 9 valores de jogada sao possiveis
  bool valor_possivel[]={true,true,true,true,true,true,true,true,true};
  unsigned ii,I,jj,J,k;

  // Se a casa jah estiver preenchida, nao hah nenhuma possibilidade
  if (at(i,j)!=0) return -1;

  // Varre a linha
  for (k=0; k<9; k++)
  {
    if (at(i,k)>0) valor_possivel[at(i,k)-1] = false;
  }

  // Varre a coluna
  for (k=0; k<9; k++)
  {
    if (at(k,j)>0) valor_possivel[at(k,j)-1] = false;
  }

  // Varre a quadra
  I = 3*(i/3);
  J = 3*(j/3);
  for (ii=0; ii<3; ii++) for (jj=0; jj<3; jj++)
  {
    if (at(I+ii,J+jj)>0) valor_possivel[at(I+ii,J+jj)-1] = false;
  }

  // Conta o numero de valores possiveis
  int num_possiveis=0;
  for (k=0; k<9; k++)
  {
    if (valor_possivel[k]) num_possiveis++;
  }

  // Nao hah nenhum valor possivel
  if (num_possiveis == 0) return 0;

  // Hah mais de um valor possivel
  if (num_possiveis > 1) return -num_possiveis;

  // Hah uma unica possibilidade de preenchimento da casa
  // Retorna o valor possivel
  k = 0;
  while (!valor_possivel[k]) k++;
  return k+1;
}

/// Preenche todas as casas "faceis" do tabuleiro, ou seja, aquelas que tem um
/// unico valor possivel pelas regras do Sudoku
/// Retorna o numero de casas adicionais preenhidas (0 ou >0) ou entao
/// retorna <0 se houver alguma casa sem possibilidade de jogada (tabuleiro insoluvel)
/// Quando retorna um valor negativo (ou seja, o tabuleiro eh insoluvel), o numero
/// retornado serah o negativo do numero de casas preenchidas. Caso nenhuma casa
/// tenha sido preeenchida e o tabuleiro seja insoluvel, serah retornado um numero
/// negativo menor que -81.
int Sudoku::resolver_casas_faceis()
{
  int num_casas=0;
  bool insoluvel(false),resolveu_alguma;
  unsigned i,j;
  int valor;

  do
  {
    resolveu_alguma = false;
    for (i=0; i<9; i++) for (j=0; j<9; j++) if (at(i,j)==0)
    {
      valor = numero_possibilidades(i,j);
      if (valor == 0)
      {
        // Hah uma casa na qual nenhum valor eh possivel
        // O tabuleiro nao tem solucao
        insoluvel = true;
      }
      if (valor > 0)
      {
        set(i,j) = valor;
        resolveu_alguma = true;
        num_casas++;
      }
    }
  } while (resolveu_alguma);
  if (insoluvel)
  {
    if (num_casas==0) return -666;
    return (-num_casas);
  }
  return num_casas;
}

/// Determina automaticamente a solucao do tabuleiro (preenche as casas vazias).
/// Retorna false se nao foi encontrada solucao, true se foi encontrada solucao
/// Altera os parametros para indicar as quantidades de nohs testados, gerados e
/// que ficaram sem analisar na determinacao da solucao
bool Sudoku::resolver(unsigned long long int& Ntab_testados,
                      unsigned long long int& Ntab_gerados,
                      unsigned long long int& Ntab_analisar)
{
  // As constantes de compilacao (#define) a seguir permitem modificar o comportamento
  // do algoritmo de resolucao da classe Sudoku

  // Fazer (descomentar) ou não (comentar) o preenchimento das casas faceis de cada tabuleiro
  // sendo analisado antes de gerar os sucessores
  #define RESOLVER_CASAS_FACEIS_PREVIAMENTE

  // Gera sucessores preenchendo a casa com menos possibilidades de preenchimento (descomentar)
  // ou preenchendo sempre a primeira vaga (comentar)
  #define RESOLVER_OTIMIZADO

  // Numero (muito grande...) de nohs gerados a partir do qual gera a impressao de um aviso
  // de que a resolucao estah demorando muito.
  // A constante, como pode ser um numero muito grande que nao "cabe" em um int, eh declarada
  // como uma constante unsigned long long int (com sufixo ull)
  #define NUM_MUITO_GRANDE_NOS 1000000ull // um milhao

  // Inicializa numero de tabuleiros testados e gerados
  Ntab_testados=0;
  Ntab_gerados=1;
  Ntab_analisar=0;

  // Testa se jah nao estah resolvido desde o inicio
  if (this->fim_de_jogo())
  {
    Ntab_testados=1;
    return true;
  }

  // aberto eh a pilha de tabuleiros ainda nao analisados, a partir do qual
  // serah executado o algoritmo de resolucao
  // Por busca em profundidade (backtracking) - com pilha
  // Por busca em largura - com fila
  stack<Sudoku> aberto;
  //queue<Sudoku> aberto;
  // Inicializa aberto com o tabuleiro inicial
  aberto.push(*this);

  // Solucao encontrada?
  bool solucao_encontrada(false);

  // Melhor serah o tabuleiro encontrado com mais casas preenchidas ateh o momento
  // Inicializa com o tabuleiro inicial
  Sudoku Melhor(*this);
  // Numero de casas vazias do melhor tabuleiro ateh o momento
  unsigned num_vazias_melhor = Melhor.num_casas_vazias();

  // Tabuleiro sendo analisado no momento
  Sudoku S;
  // Numero de casas resolvidas facilmente e de casas vazias no tabuleiro sendo analisado
  int num_resolvidas;
  unsigned num_vazias;

  #ifdef RESOLVER_OTIMIZADO
  // Numero de possibilidades de preenchimento de uma casa
  int num_possib;
  // Possibilidades de preenchimento da casa com menor numero de possibilidades
  int menor_num_possib;
  #endif

  // Variaveis auxiliares
  unsigned I,J,i,j,k;

  do
  {
    S = aberto.top();  // Com pilha
    //S = aberto.front();  // Com fila
    aberto.pop();

    #ifdef RESOLVER_CASAS_FACEIS_PREVIAMENTE
    // Resolve as casas faceis
    num_resolvidas = S.resolver_casas_faceis();
    #else
    num_resolvidas = 0;
    #endif

    num_vazias = S.num_casas_vazias();
    if (num_vazias < num_vazias_melhor)
    {
      Melhor = S;
      num_vazias_melhor = num_vazias;
    }
    solucao_encontrada =(num_vazias == 0);
    Ntab_testados++;

    // Soh gera sucessores se nao for solucao e nao for insoluvel
    if (num_vazias!=0 && num_resolvidas>=0)
    {
      I = J = 10;  // Valores invalidos
      #ifdef RESOLVER_OTIMIZADO
      menor_num_possib = 10;
      #endif
      for (i=0; i<9; i++) for (j=0;j<9; j++) if (S.at(i,j)==0)
      {
        #ifdef RESOLVER_OTIMIZADO
        // Escolhe a casa (I,J) com menor numero de possibilidades de preenchimento
        num_possib = S.numero_possibilidades(i,j);
        // Soh existe uma possibilidade de preenchimento
        if (num_possib >= 1) num_possib = 1;
        // Existem varias possibilidades de preenchimento
        if (num_possib < 0) num_possib = abs(num_possib);

        if (num_possib == 0)
        {
          // Tabuleiro insoluvel, pois existe uma casa insoluvel
          I = J = 10;  // Valores invalidos
          // Sai dos lacos for
          i = j = 10;
        }
        else if (num_possib < menor_num_possib)
        {
          I = i;
          J = j;
          menor_num_possib = num_possib;
        }
        #else
        // Escolhe a primeira casa livre
        I = i;
        J = j;
        // Sai dos lacos for
        i = j = 10;
        #endif
      }

      if (I<9 && J<9)  // Existe casa a ser preenchida
      {
        // Gera todas as jogadas validas na casa escolhida
        Jogada Jog(TipoJogada::Jogar,I,J);

        // Testa todos os valores validos para uma jogada na posicao (I,J)
        for (k=0; k<9; k++)
        {
          Jog.setValor(k+1);
          if (S.jogada_valida(Jog))
          {
            Sudoku Suc(S);

            Suc.fazer_jogada(Jog);
            aberto.push(Suc);
            Ntab_gerados++;
            // Emite advertencia quando numero muito grande de nohs eh gerado
            if (Ntab_gerados%NUM_MUITO_GRANDE_NOS == 0)
            {
              cerr << "AVISO: jah foram gerados " << Ntab_gerados << " nohs...\n";
            }
          }
        }
      }
    }
    // O algoritmo repete se duas condicoes forem satisfeitas:
    // a) existe algum tabuleiro para expandir; e
    // b) ainda nao foi encontrada uma solucao
  } while(!aberto.empty() && !solucao_encontrada);

  *this = Melhor;
  Ntab_analisar = aberto.size();

  return solucao_encontrada;
}

