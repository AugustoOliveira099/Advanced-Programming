#include <iostream>
#include <limits>
#include <string>
#include "loja_polim.h"

using namespace std;

int main()
{
  Loja X;
  Livro L;
  CD C;
  DVD D;
  string A;
  int opcao(0);
  unsigned id(0);

  cout << "CONTROLE DE ACERVO\n\n";
  do
  {
    do{
      cout << "0 - Sair\n";
      cout << "1 - Incluir livro\n";
      cout << "2 - Incluir CD\n";
      cout << "3 - Incluir DVD\n";
      cout << "4 - Imprimir acervo em tela\n";
      cout << "5 - Ler acervo de arquivo\n";
      cout << "6 - Salvar acervo em arquivo\n";
      cout << "7 - Excluir produto\n";
      cout << "Opcao: ";
      cin >> opcao;
    } while (opcao<0 || opcao>7);
    cin.ignore();

    // Entrada de dados, de acordo com a opcao
    switch (opcao)
    {
    case 1:
      cout << "LIVRO>>\n";
      cin >> L;
      break;
    case 2:
      cout << "CD>>\n";
      cin >> C;
      break;
    case 3:
      cout << "DVD>>\n";
      cin >> D;
      break;
    case 4:
    default:
      break;
    case 5:
    case 6:
      cout << "Nome do arquivo: ";
      getline(cin,A);
      break;
    case 7:
      cout << "Id do produto a excluir: ";
      cin >> id;
      break;
    }

    // Funcao a ser chamada, de acordo com a opcao
    switch (opcao)
    {
    case 0:
    default:
      break;
    case 1:
      X.incluir(L);
      break;
    case 2:
      X.incluir(C);
      break;
    case 3:
      X.incluir(D);
      break;
    case 4:
      cout << endl;
      X.imprimir();
      break;
    case 5:
      if (!X.ler(A))
      {
        cerr << "Erro ao ler arquivo " << A << endl;
      }
      break;
    case 6:
      if (!X.salvar(A))
      {
        cerr << "Erro ao salvar arquivo " << A << endl;
      }
      break;
    case 7:
      if (!X.excluir(id))
      {
        cerr << "Produto " << id << " nao existe!\n";
      }
      break;
    }
  } while (opcao!=0);
}
