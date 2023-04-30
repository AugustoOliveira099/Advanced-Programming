#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include <vector>
#include <cstdint>  // Para uint8_t em alguns compiladores

/// Possiveis tipos de jogada
enum class TipoJogada
{
  Jogar, Apagar, PreencherImediatas, Resolver,
  VoltarInicio, FimJogo, JogadaInvalida
};

/// Classe que representa uma possivel jogada:
/// tipo, coordenadas e valor
class Jogada
{
private:
  /// Tipo de jogada
  TipoJogada t;

  /// Coordenadas (faz sentido apenas para Jogar e Apagar)
  unsigned i,j;

  /// Valor a ser jogado (faz sentido apenas para Jogar)
  unsigned v;
public:
  /// Construtor (por default, cria Jogada invalida)
  Jogada(TipoJogada T=TipoJogada::JogadaInvalida,
         unsigned I=0, unsigned J=0, unsigned V=0);

  /// Funcoes de consulta
  inline TipoJogada tipo() const {return t;}
  inline int linha() const {return i;}
  inline int coluna() const {return j;}
  inline int valor() const {return v;}

  /// Fixa o tipo de uma jogada
  inline void setTipo(TipoJogada T) {t=T;}

  /// Fixa as coordenadas de uma jogada
  void setCoord(unsigned I, unsigned J);

  /// Fixa o valor de uma jogada
  void setValor(unsigned V);
};

class Sudoku
{
private:
  /// "Matriz 9x9" que contem os valores das casas do tabuleiro.
  /// Na realidade, a "matriz 9x9" eh um vector de 81 bytes sem sinal (uint8_t)
  /// O acesso aos elementos da "matriz" se dah atraves dos metodos "set" e "at",
  /// que transformam os indices linha e coluna da matriz no indice do vetor
  /// Conteudo da "matriz":
  /// 1 a 9 - Casa preenchida
  /// 0 - Casa vazia
  std::vector<uint8_t> tab;

  /// Funcao set de alteracao de valor
  /// Retorna uma referencia ao i-j-esimo elemento do tabuleiro
  inline uint8_t& set(unsigned i, unsigned j) {return tab.at(9*i+j);}

  /// Calcula o numero de possibilidades para preencher a casa (i,j)
  /// utilizando apenas as regras "faceis" (linha, coluna e bloco)
  /// Se houver uma unica possibilidade de preenchimento, retorna o valor (1 a 9)
  /// Se nao houver nenhuma possibilidade de preenchimento, retorna 0, o que
  /// indica que o tabuleiro nao tem solucao
  /// Se houver mais de uma possibilidade de preenchimento, retorna um numero
  /// negativo (<0), cujo modulo eh o numero de possibilidades
  int numero_possibilidades(unsigned i, unsigned j) const;

public:
  /// Limpa o tabuleiro
  void limpar();

  /// Cria um tabuleiro vazio
  inline Sudoku(): tab(81) {limpar();}

  /// Leh um tabuleiro do arquivo nome_arq
  /// Caso ocorra erro, gera tabuleiro parcialmente preenchido
  /// e retorna false; se der tudo certo, retorna true
  bool ler(const char *nome_arq);

  /// Cria um tabuleiro com o conteudo do arquivo nome_arq
  inline Sudoku(const char *nome_arq): tab(81) {ler(nome_arq);}

  /// Destrutor (nao eh obrigatorio...)
  inline ~Sudoku() {}

  /// Funcao de consulta
  /// Retorna o i-j-esimo elemento do tabuleiro
  inline uint8_t at(unsigned i, unsigned j) const {return tab.at(9*i+j);}

  /// Compara se dois tabuleiros sao iguais
  bool operator==(const Sudoku &S) const;

  /// Testa se a jogada J eh possivel para o tabuleiro
  /// Retorna true se jogada valida; false se invalida
  bool jogada_valida(Jogada J) const;

  /// Testa se a jogada J eh um apagamento valido de uma casa para o tabuleiro,
  /// levando em conta o tabuleiro original (nao eh permitido apagar casas que
  /// estavam preenchidas no tabuleiro original)
  /// Retorna true se apagamento valido; false se invalido
  bool apagamento_valido(Jogada J, const Sudoku &Origem) const;

  /// Executa uma jogada (altera o tabuleiro)
  /// Retorna true se jogada valida e foi feita; false se invalida e nao foi feita
  bool fazer_jogada(Jogada J);

  /// Apaga uma casa (altera o tabuleiro)
  /// Retorna true se apagamento valido e foi feito; false se invalido e nao foi feito
  bool apagar_jogada(Jogada J, const Sudoku &O);

  /// Testa se o tabuleiro estah completo (fim de jogo)
  bool fim_de_jogo() const;

  /// Retorna o numero de casas vazias no tabuleiro
  unsigned num_casas_vazias() const;

  /// Preenche todas as casas "faceis" do tabuleiro, ou seja, aquelas que tem um
  /// unico valor possivel pelas regras do Sudoku
  /// Retorna o numero de casas adicionais preenhidas (0 ou >0) ou entao
  /// retorna <0 se houver alguma casa sem possibilidade de jogada (tabuleiro insoluvel)
  /// Quando retorna um valor negativo (ou seja, o tabuleiro eh insoluvel), o numero
  /// retornado serah o negativo do numero de casas preenchidas. Caso nenhuma casa
  /// tenha sido preeenchida e o tabuleiro seja insoluvel, serah retornado um numero
  /// negativo menor que -81.
  int resolver_casas_faceis();

  /// Determina automaticamente a solucao do tabuleiro (preenche as casas vazias).
  /// Retorna false se nao foi encontrada solucao, true se foi encontrada solucao.
  /// Altera os parametros para indicar as quantidades de nohs testados, gerados e
  /// que ficaram sem analisar na determinacao da solucao
  bool resolver(unsigned long long int& Ntab_testados,
                unsigned long long int& Ntab_gerados,
                unsigned long long int& Ntab_analisar);
};

#endif // _SUDOKU_H_
