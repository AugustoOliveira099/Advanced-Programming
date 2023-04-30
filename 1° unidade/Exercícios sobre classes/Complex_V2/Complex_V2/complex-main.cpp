#include <iostream>
#include "complex.h"

using namespace std;

int main(void)
{
  Complex C1, C2, S, P;

  cout << "Digite o primeiro numero complexo (C1):\n";
                     // == operator<<(cout, "Digite...");
  cin >> C1;         // == operator>>(cin,C1);

  cout << "Digite o segundo numero complexo (C2):\n";
                     // == operator<<(cout, "Digite...");
  cin >> C2;         // == operator>>(cin,C2);

  S = C1+C2;         // == S = C1.operator+(C2);
                     // == S.operator=( C1.operator+(C2) );
  P = C1*C2;         // == P = C1.operator*(C2);
                     // == P.operator=( C1.operator*(C2) );

  cout << "Soma = "; // == operator<<(cout, "Soma = ");
  cout << S;         // == operator<<(cout, S);
  cout << endl;      // == operator<<(cout, endl);

  cout << "Soma+1.0 = "; // == operator<<(cout, "Soma+1.0 = ");
  cout << S+1.0;     // == cout << S+Complex(1.0);
  cout << endl;      // == operator<<(cout, endl);

  cout << "Produto = ";  // == operator<<(cout, "Produto = ");
  cout << P << endl; // == operator<<( operator<<(cout,P), endl );
}

