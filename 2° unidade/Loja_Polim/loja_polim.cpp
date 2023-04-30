#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include "loja_polim.h"


using namespace std;

void Produto::digitar()
{
  // Leh o nome do produto
  do
  {
    cout << "Nome: ";
    getline(cin,nome);
  } while (nome=="");
  // Leh o preco do produto
  double Pr;
  do
  {
    cout << "Preco (##.##): ";
    cin >> Pr;
  } while (Pr <= 0.0);
  cin.ignore();
  preco = (unsigned)round(100.0*Pr);
}

bool Produto::ler(istream &I)
{
  // Formato da linha no arquivo-> "STRING_AUTOR";$FLOAT_PRECO
  double Pr;

  // Ignora ateh aspa inicial
  I.ignore(numeric_limits<streamsize>::max(),'"');
  // Leh ateh a aspa final do nome do produto
  getline(I,nome,'"');
  // Ignora o ";" e o "$"
  I.ignore(numeric_limits<streamsize>::max(),'$');
  // Leh o preco como numero real
  I >> Pr;
  // Converte o preco para centavos (inteiro)
  preco = (unsigned)round(100.0*Pr);
  // Testa a leitura
  if (nome=="" || preco==0)
  {
    nome = "";
    preco = 0;
    return false;
  }
  return true;
}

void Produto::salvar(ostream &O) const
{
  // Formato da linha-> "STRING_NOME";$FLOAT_PRECO;
  O << '"' << nome << '"' << ";$" << fixed << setprecision(2) << double(preco)/100.0;
}

void Livro::digitar()
{
  Produto::digitar();
  do
  {
    cout << "Autor: ";
    getline(cin,autor);
  } while (autor=="");
}

bool Livro::ler(istream &I)
{
  // Formato da linha no arquivo->  L: <Conteudo do Produto>;"STRING_AUTOR"

  // Leh o caractere inicial
  char opcao;
  I >> opcao;
  if (opcao!='L')
  {
    *this = Livro();
    return false;
  }
  // Ignora o ":" apos a letra inicial
  I.ignore(numeric_limits<streamsize>::max(),':');
  // Comeca da aspa da string do nome do Produto
  if (!Produto::ler(I))
  {
    *this = Livro();
    return false;
  }
  // Ignora o ";" e a aspa inicial do nome do autor
  I.ignore(numeric_limits<streamsize>::max(),'"');
  // Leh o nome do autor
  getline(I,autor,'"');
  // Ignora o "\n" no fim da linha
  I.ignore();
  if (autor == "")
  {
    *this = Livro();
    return false;
  }
  return true;
}

void Livro::salvar(ostream &O) const
{
  // Formato da linha-> L: <Conteudo do Produto>;"STRING_AUTOR"
  O << "L: ";
  Produto::salvar(O);
  O << ';' << '"' << autor << '"';
}

void CD::digitar()
{
  Produto::digitar();
  do
  {
    cout << "Numero de faixas: ";
    cin >> nfaixas;
  } while (nfaixas == 0);
  cin.ignore();
}

bool CD::ler(istream &I)
{
  // Formato da linha no arquivo->  C: <Conteudo do Produto>;UNSIGNED_NFAIXAS

  // Leh o caractere inicial
  char opcao;
  I >> opcao;
  if (opcao!='C')
  {
    *this = CD();
    return false;
  }
  // Ignora o ":" apos a letra inicial
  I.ignore(numeric_limits<streamsize>::max(),':');
  // Comeca da aspa da string do nome do Produto
  if (!Produto::ler(I))
  {
    *this = CD();
    return false;
  }
  // Ignora o ";"
  I.ignore(numeric_limits<streamsize>::max(),';');
  // Leh o numero de faixa
  I >> nfaixas;
  // Ignora o "\n" no fim da linha
  I.ignore();
  if (nfaixas == 0)
  {
    *this = CD();
    return false;
  }
  return true;
}

void CD::salvar(ostream &O) const
{
  // Formato da linha-> C: <Conteudo do Produto>;UNSIGNED_NFAIXAS
  O << "C: ";
  Produto::salvar(O);
  O << ';' << nfaixas;
}

void DVD::digitar()
{
  Produto::digitar();
  do
  {
    cout << "Duracao: ";
    cin >> duracao;
  } while (duracao == 0);
  cin.ignore();
}

bool DVD::ler(istream &I)
{
  // Formato da linha no arquivo-> D: <Conteudo do Produto>;UNSIGNED_DURACAO

  // Leh o caractere inicial
  char opcao;
  I >> opcao;
  if (opcao!='D')
  {
    *this = DVD();
    return false;
  }
  // Ignora o ":" apos a letra inicial
  I.ignore(numeric_limits<streamsize>::max(),':');
  // Comeca da aspa da string do nome do Produto
  if (!Produto::ler(I))
  {
    *this = DVD();
    return false;
  }
  // Ignora o ";"
  I.ignore(numeric_limits<streamsize>::max(),';');
  // Leh a duracao
  I >> duracao;
  // Ignora o "\n" no fim da linha
  I.ignore();
  if (duracao == 0)
  {
    *this = DVD();
    return false;
  }
  return true;
}

void DVD::salvar(ostream &O) const
{
  // Formato da linha-> D: <Conteudo do Produto>;UNSIGNED_DURACAO
  O << "D: ";
  Produto::salvar(O);
  O << ';' << duracao;
}

pProduto Loja::getItem(unsigned id) const
{
  if (x.empty() || id>=x.size()) return nullptr;
  return x[id];
}

// Esta funcao soh eh chamada no construtor ou depois de se executar um limpar()
// Portanto, o vetor x estah sempre vazio, nao precisando ser liberado
void Loja::copiar(const Loja &X)
{
  // Faz cada ponteiro do novo array apontar para uma area de memoria alocada e que
  // contem uma copia da area de memoria correspondente no array original
  // Utiliza a funcao clone
  for (unsigned i=0; i<X.size(); i++) x.push_back(X.x[i]->clone());
}

void Loja::limpar()
{
  // Libera a area de memoria que cada um dos ponteiros do vector x aponta
  // Em seguida, limpa o vetor x
  for (unsigned i=0; i<size(); i++) if (x[i]!=nullptr) delete x[i];
  x.clear();
}

void Loja::incluir(const Produto &X)
{
  // Inclui no vetor x um novo elemento (um novo ponteiro) que aponta para
  // uma area de memoria alocada e que contem uma copia de X
  // Utiliza a funcao clone
  x.push_back( (&X)->clone() );
}

bool Loja::excluir(unsigned id)
{
  // Checa o indice
  if ( id>=size() ) return false;

  // Libera a area de memoria para a qual x[id] aponta
  if (x[id]!=nullptr)
  {
    delete x[id];
    x[id] = nullptr;
  }
  // Em seguida, exclui o elemento do vetor x
  x.erase( x.begin()+id );

  return true;
}

void Loja::imprimir() const
{
  cout << ">> ACERVO:\n";
  for (unsigned i=0; i<size(); i++) cout << i << ") " << *x[i] << endl;
}

bool Loja::ler(const string& arq)
{
  // Cria a stream associada ao arquivo
  ifstream myfile(arq.c_str());
  if (!myfile.is_open()) return false;

  string pS;
  unsigned NN;
  char opcao;
  bool status(true);
  Livro L;
  CD C;
  DVD D;

  myfile >> pS >> NN;
  myfile.ignore();
  if (pS!="LOJA" || NN==0)
  {
    myfile.close();
    return false;
  }

  // Antes de ler os dados de um arquivo, zera o conteudo atual da Loja
  limpar();

  for (unsigned i=0; status && i<NN; i++)
  {
    // Inspeciona o primeiro caractere da linha
    opcao = myfile.peek();
    switch(opcao)
    {
    // De acordo com o primeiro caractere, le a linha em uma das variaveis temporarias (C, D ou L)
    // Em seguida, inclui a variavel temporaria na Loja
    case 'C':
      status = C.ler(myfile);
      if (status) incluir(C);
      break;
    case 'D':
      status = D.ler(myfile);
      if (status) incluir(D);
      break;
    case 'L':
      status = L.ler(myfile);
      if (status) incluir(L);
      break;
    default:
      // Primeiro caractere da linha nao era nenhuma das opçoes validas
      status = false;
    }
  }
  myfile.close();
  if (!status) limpar();
  return status;
}

bool Loja::salvar(const string& arq) const
{
  ofstream myfile(arq.c_str());
  if (!myfile.is_open()) return false;

  // Salva o cabecalho em uma linha
  myfile << "LOJA " << size() << endl;

  // Salva cada um dos produtos em uma linha
  for (unsigned i=0; i<size(); i++) myfile << *x[i] << endl;

  myfile.close();
  return true;
}
