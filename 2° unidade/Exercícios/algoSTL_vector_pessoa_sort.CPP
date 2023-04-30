#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Pessoa
{
private:
  string nome;
  int idade;
public:
  inline Pessoa(string no, int id): nome(no), idade(id) {}
  inline string getNome() const {return nome;}
  inline int getIdade() const {return idade;}
};

bool ordena_por_nome(const Pessoa& A, const Pessoa& B)
{
    return (A.getNome() < B.getNome());
}

int main()
{
    vector <Pessoa> VP;
    vector <Pessoa>::iterator ptr;

    VP.push_back(Pessoa("Joao", 25));
    VP.push_back(Pessoa("Maria", 32));
    VP.push_back(Pessoa("Carla", 4));
    VP.push_back(Pessoa("Abel", 30));

    // Coloca em ordem utilizando funcao ordena_por_nome
    // Coloca em ordem alfabetica de nome
    sort ( VP.begin(), VP.end(), ordena_por_nome );

    // Percorrendo a lista com um ITERATOR
    for(ptr = VP.begin(); ptr != VP.end(); ptr++)
    {
        cout << "Nome: " << ptr->getNome();
        cout << " - Idade: " << ptr->getIdade() << endl;
    }
}

