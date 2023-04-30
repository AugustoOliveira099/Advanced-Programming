#ifndef _Poly_H_
#define _Poly_H_

#include <iostream>

using namespace std;

class Poly
{
private:
    unsigned D;
    double *coef;

    /// CRIA POLINOMIA COM GRAU a_n
    void create(unsigned a_n);

    /// FAZ A COPIA DE UM POLINOMIO
    void copy(const Poly &P);

public:
    /// CONSTRUTORES
    /// Construtor default
    inline Poly(): D(0), coef(NULL) {}
    /// Construtor por copia
    inline Poly(const Poly &P) {copy(P);}
    /// Costrutor especifico
    explicit Poly(unsigned a_n);


    /// DESTRUTOR
    void clean();
    inline ~Poly() {clean();}

    /// SOBRECARGA DE OPERADORES
    /// Operador de atribuicao
    void operator=(const Poly &P);
    /// Soma de polinomios
    Poly operator+(const Poly &P) const;
    /// Subatracao de polinomios
    Poly operator-(const Poly &P) const;
    /// Negativo de um polinomio
    Poly operator-() const;
    /// Multiplicacao de polinomios
    Poly operator*(const Poly &P) const;
    /// Operador usado para retornar o valor do polinomio em um dado numero
    inline double operator() (double x) const {return getValor(x);}

    /// ENTRADA E SAIDA DE DADOS
    friend istream &operator>>(istream &W, Poly &P);
    friend ostream &operator<<(ostream &W, const Poly &P);


    /// METODOS DE CONSULTA
    /// Metodo que permite consultar o grau do polinomio(D-1)
    inline int getGrau() const {return int(D)-1;}
    /// Metodo que utiliza o operador de consulta "[]"
    inline double getCoef(unsigned i) const {return (i<D ? coef[i] : 0.0);}
    /// Metodo de consulta que retorna o valor do polinomio para um dado numero
    double getValor(double x) const;
    /// Sobrecarga do operador "[]", que serve para consultar o elemento do array. Ex.: cout << x[1];
    double operator[](unsigned i) const;


    /// METODOS DE ALTERACAO DE VALORES
    /// Segunda sobrecarga do operador "[]", que serve para fixar valores. Ex.: x[1]=7;
    double &operator[](unsigned i);
    /// Permite alterar o grau de um polinomio
    inline void setGrau(unsigned a_n) {if(a_n!=(D-1)) {clean(); Poly(a_n);}}
    /// Permite alterar um certo coeficiente de um polinomio
    void setCoef(unsigned i, double x);

    /// FUNÇAO MEMBRO AUXILIAR
    /// Ajusta a dimensao no caso dela diminuir ou aumentar, na soma e na subtracao
    /// Na multiplicacao ela eh utilizada caso P1 ou P2 seja igual a zero
    Poly ajusta_D();
    /// Zera todos os coeficientes e mantem conservada a dimensao
    inline void zera() {for(unsigned i=0; i<D; i++) {coef[i] = 0.0;}}

};

#endif
