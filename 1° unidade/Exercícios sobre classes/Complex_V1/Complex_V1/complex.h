#include <iostream>

/// Tipo Complex

class Complex
{
private:
  double real, imag;
public:
  /// Construtores
  Complex();
  Complex(double R);
  Complex(double R, double I);

  /// Metodos de consulta
  inline double getReal() const {return real;}
  inline double getImag() const {return imag;}

  /// Metodos de entrada e saida
  void ler();
  void imprimir() const;

  /// Operacoes especificas da classe
  Complex operator+(const Complex &C2) const;
  Complex operator*(const Complex &C2) const;
};

