#include <iostream>
#include <cmath>

using namespace std;

// Tipo Complex

class Complex
{
private:
  double real, imag;
public:
  void ler();
  void imprimir() const;
  Complex soma(Complex C2) const;
  Complex produto(Complex C2) const;
};
