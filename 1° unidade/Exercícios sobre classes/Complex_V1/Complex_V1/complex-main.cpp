#include <iostream>
#include "complex.h"

using namespace std;

int main(void)
{
  Complex C1, C2, S, P;

  cout << "Digite o primeiro numero complexo (C1):\n";
  C1.ler();

  cout << "Digite o segundo numero complexo (C2):\n";
  C2.ler();

  S = C1+C2; // S = C1.operator+(C2);
  P = C1*C2; // P = C1.operator*(C2);

  cout << "Soma = ";
  S.imprimir();
  cout << endl;

  cout << "Produto = ";
  P.imprimir();
  cout << endl;
}

