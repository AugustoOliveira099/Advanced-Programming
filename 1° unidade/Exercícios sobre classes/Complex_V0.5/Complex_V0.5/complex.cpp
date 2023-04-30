#include <iostream>
#include <cmath>

#include "complex.h"

using namespace std;

// Os metodos da classe
void Complex::ler()
{
  cout << "R? ";
  cin >> real;
  cout << "I? ";
  cin >> imag;
}

void Complex::imprimir() const
{
  cout << real << (imag<0.0 ? '-' : '+') << 'j' << fabs(imag);
}

Complex Complex::soma(Complex C2) const
{
  Complex prov;
  prov.real = real+C2.real;
  prov.imag = imag+C2.imag;
  return prov;
}

Complex Complex::produto(Complex C2) const
{
  Complex prov;
  prov.real = real*C2.real - imag*C2.imag;
  prov.imag = real*C2.imag + C2.real*imag;
  return prov;
}
