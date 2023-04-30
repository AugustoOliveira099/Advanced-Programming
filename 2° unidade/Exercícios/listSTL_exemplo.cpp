#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

inline void imprimir(double X) {cout << X << endl;}

int main()
{
  list<double> minhaLista;   // cria uma lista de double vazia
  list<double>::iterator k;  // cria um iterador para lista de double

  minhaLista.push_back(7.5);
  minhaLista.push_back(27.26);
  minhaLista.push_front(-44);    // inserindo no início da lista
  minhaLista.push_front(7.5);    // inserindo no início da lista
  minhaLista.push_back(69.09);

  // vai imprimir seis elementos {7.5, -44, 7.5, 27.26, 69.09}
  cout << "Imprimindo a lista:\n";
  for_each ( minhaLista.begin(), minhaLista.end(), imprimir );

  // insere -2.888 como ultimo elemento
  minhaLista.insert( minhaLista.end(), -2.888);

  // retira o elemento -44 da lista
  minhaLista.remove(-44);

  // ordena a lista, em ordem ascendente
  minhaLista.sort();

  // vai imprimir cinco elementos {-2.888, 7.5, 7.5, 27.26, 69.09}
  cout << "Lista ordenada (com repeticoes):\n";
  for_each ( minhaLista.begin(), minhaLista.end(), imprimir );

  // remove elementos duplicados da lista (no caso, 7.5 aparece 2x)
  minhaLista.unique();

  // deve imprimir quatro elementos {-2.888, 7.5, 27.26, 69.09}
  cout << "Lista final ordenada...:\n";
  for_each ( minhaLista.begin(), minhaLista.end(), imprimir );

  // para usar find, informe o inicio e final+1, mais o elemento
  // este método STL devolve um iterador para o objeto.
  k = find(minhaLista.begin(), minhaLista.end(), 27.26);
  if( k == minhaLista.end() )
    cout << "Não existe o elemento procurado!!!" << endl;
  else
  {
    cout << "Elemento 27.26 encontrado!!!" << endl;
    k++;
    if (k == minhaLista.end())
      cout << "Ele eh o ultimo elemento\n";
    else
      cout << "Ele vem antes do elemento " << *k << endl;
  }

  delete k;

  if (minhaLista.empty())
    cout << "Lista vazia!" << endl;
  else
    cout << minhaLista.size() << " elemento(s) na lista!" << endl;

  minhaLista.clear();  // limpa toda a lista

  return 0;
}
