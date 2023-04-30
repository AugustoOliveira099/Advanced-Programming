#include <iostream>
#include <cmath>
#include "complex.h"

using namespace std;

// As funcoes
istream &operator>>(istream &X, Complex &C)
{
  cout << "R? "; // == operator<<(cout, "R? ");
  X >> C.real;   // == operator>>(X, C.real);
  cout << "I? "; // == operator<<(cout, "I? ");
  X >> C.imag;   // == operator>>(X, C.imag);
  // A funcao tem que retornar a stream que recebeu como parametro
  // para que possa ser encadeada com a chamada da funcao seguinte
  // caso o usuario faca algo como:
  // cin >> C1 >> C2;
  return X;
}

ostream &operator<<(ostream &X, const Complex &C)
{
  X << C.real << (C.imag<0.0 ? '-' : '+') << 'j' << fabs(C.imag);
  // 4 chamadas aa funcao operator<< (que estou abreviando como op<<)
  // A mais interna tem como primeiro parametro a ostream X
  // As outras "imprimem" no retorno de uma funcao op<<, que eh uma stream:
  //
  // op<<( op<<( op<<( op<<(X,C.real) , ternario ) , 'j') , fabs(C.imag) );
  //                   |------------|
  //             |-------------------------------|
  //       |--------------------------------------------|
  // |-------------------------------------------------------------------|
  //
  // Faria o mesmo efeito:
  // X << C.real;
  // X << (C.imag<0.0 ? '-' : '+');
  // X << 'j';
  // X << fabs(C.imag);
  //
  // A funcao tem que retornar a stream que recebeu como parametro
  // para que possa ser encadeada com a chamada da funcao seguinte
  return X;
}

// Os metodos
Complex Complex::operator+(const Complex &C2) const
{
  Complex prov;
  prov.real = real+C2.real;
  prov.imag = imag+C2.imag;
  return prov;
}

Complex Complex::operator*(const Complex &C2) const
{
  Complex prov;
  prov.real = real*C2.real - imag*C2.imag;
  prov.imag = real*C2.imag + C2.real*imag;
  return prov;
}
