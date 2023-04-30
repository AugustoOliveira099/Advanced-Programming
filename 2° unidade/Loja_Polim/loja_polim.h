#ifndef _LOJA_POLIM_H_
#define _LOJA_POLIM_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Produto;

typedef Produto* pProduto;

class Produto
{
private:
  string nome;
  unsigned preco;
public:
  inline Produto(const char *N="", unsigned P=0): nome(N), preco(P) {}

  /// Destrutor virtual: recomendado em classes bases que tem algum metodo virtual
  inline virtual ~Produto() {}

  /// Funcao clone (virtual):
  /// necessaria para o construtor por copia das classes com vetores polimorficos de pProduto
  /// Essa funcao aloca memoria e inicializa o valor para criar uma copia de si mesmo (do objeto)
  /// Deve ser virtual para criar o objeto do tipo apropriado (das classes derivadas)
  /// Metodo virtual puro (=0) porque nao faz sentido criar um objeto que seja da classe base (Produto)
  /// Todos os objetos no estoque sao de alguma classe derivada
  /// Com isso, a classe Produto se torna uma classe abstrata (nao posso criar objetos dessa classe)
  virtual pProduto clone() const = 0;

  /// Funcoes de consulta
  inline string getNome() const {return nome;}
  inline double getPreco() const {return preco/100.0;}

  /// Metodos virtuais de entrada e saida
  virtual bool ler(istream &I);
  virtual void salvar(ostream &O) const;
  virtual void digitar();
  /// Define a funcao imprimir como sendo salvar em cout
  inline void imprimir() const {salvar(cout);}
};

/// Operator >> e << "virtualizados"
/// Para que os operadores sejam "virtuais", eles devem:
/// 1) Chamar um metodo que seja virtual, como eh o caso dos metodos digitar e imprimir
/// 2) Chamarem o metodo virtual atraves de um ponteiro, e nao de um objeto
/// Por isso:
/// X.imprimir(O);     ERRO: nao eh virtual
/// (&X)->imprimir(O); OK: eh virtual
inline istream &operator>>(istream &I, Produto &X) {(&X)->digitar(); return I;}
inline ostream &operator<<(ostream &O, const Produto &X) {(&X)->salvar(O); return O;}

class Livro: public Produto
{
private:
  string autor;
public:
  inline Livro(const char *N="", unsigned P=0, const char *A=""): Produto(N,P), autor(A) {}

  /// Note que o metodo clone cria um objeto do tipo certo para cada classe derivada
  inline pProduto clone() const {return new Livro(*this);}

  /// Funcoes de consulta
  inline string getAutor() const {return autor;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {return salvar(cout);};
};

class CD: public Produto
{
private:
  unsigned nfaixas;
public:
  inline CD(const char *N="", unsigned P=0, unsigned NF=0): Produto(N,P), nfaixas(NF) {}

  /// Note que o metodo clone cria um objeto do tipo certo para cada classe derivada
  inline pProduto clone() const {return new CD(*this);}

  /// Funcoes de consulta
  inline unsigned getNumFaixas() const {return nfaixas;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {return salvar(cout);};
};

class DVD: public Produto
{
private:
  unsigned duracao;
public:
  inline DVD(const char *N="", unsigned P=0, unsigned D=0): Produto(N,P), duracao(D) {}

  /// Note que o metodo clone cria um objeto do tipo certo para cada classe derivada
  inline pProduto clone() const {return new DVD(*this);}

  /// Funcoes de consulta
  inline unsigned getDuracao() const {return duracao;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {return salvar(cout);};
};

class Loja
{
private:
  vector<pProduto> x;
  void copiar(const Loja &L);
public:
  /// Metodos basicos obrigatorios
  inline Loja(): x() {}
  inline Loja(const Loja &L): x() {copiar(L);}
  void limpar();
  inline ~Loja() {limpar();}
  inline void operator=(const Loja &L) {if (this!=&L) {limpar(); copiar(L);}}


  /// Funcoes de consulta
  inline size_t size() const {return x.size();}
  pProduto getItem(unsigned id) const;

  /// Funcoes de manipulacao (inclusao/exclusao) de itens do estoque
  void incluir(const Produto &X);
  bool excluir(unsigned id);

  /// Funcoes de entrada/saida
  bool ler(const string& arq);
  bool salvar(const string& arq) const;
  void imprimir() const;
};
#endif // _LOJA_POLIM_H_
