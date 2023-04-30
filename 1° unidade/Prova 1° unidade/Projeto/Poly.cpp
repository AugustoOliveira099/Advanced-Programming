#include <iostream>
#include <cmath>
#include "Poly.h"

using namespace std;


/// CRIA POLINOMIA COM GRAU a_n

void Poly::create(unsigned a_n)
{
    D = a_n+1;
    coef = new double[D]; /// Nao eh necessario o ternario, uma vez que "n" eh um natural positivo, incluindo o zero,
                          /// como D = n+1, D possui o dominio D>0
}


/// FAZ A COPIA DE UM POLINOMIO

void Poly::copy(const Poly &P)
{
    unsigned a_n = P.D-1;
    create(a_n);
    for (unsigned i=0; i<D; i++) coef[i] = P.coef[i];
}


/// CONSTRUTOR
/// Costrutor especifico

Poly::Poly(unsigned a_n)
{
    create(a_n);
    if(D>0)
    {
        if(D==1) coef[a_n] = 0.0;
        else
        {
            for(unsigned i=0; i<a_n; i++) coef[i] = 0.0; /// A condicao do laco eh i<n pois nao queremos que o
                                                         /// ultimo coeficiente receba 0.0
            coef[a_n] = 1.0;
        }
    }
}


/// DESTRUTOR

void Poly::clean()
{
    if (coef!=NULL) delete[] coef;
    coef = NULL;
    D = 0;
}


/// SOBRECARGA DE OPERADORE
/// Operador de atribuicao

void Poly::operator=(const Poly &P)
{
    if(this != &P)
    {
        if(this->D == P.D)
        {
            for(unsigned i=0; i<D; i++) coef[i] = P.coef[i];
        }
        else
        {
            clean();
            copy(P);
        }
    }
}


/// SOBRECARGA DE OPERADORE
/// Soma de polinomios

Poly Poly::operator+(const Poly &P) const
{
    unsigned a_n, dimMenor;
    if(P.D>D) {a_n = (P.D-1); dimMenor = D;}
    else {a_n = (D-1); dimMenor = P.D;}
    Poly prov(a_n);
    unsigned dimMaior = a_n+1;
    for(unsigned i=0; i<dimMaior; i++)
    {
        if(i<dimMenor) {prov.coef[i] = coef[i] + P.coef[i];}
        else if(P.D>D) {prov.coef[i] = P.coef[i];}
        else {prov.coef[i] = coef[i];}
    }
    if(prov.coef[a_n] == 0.0) {prov = prov.ajusta_D();}
    return prov;
}


/// SOBRECARGA DE OPERADORE
/// Subatracao de polinomios

Poly Poly::operator-(const Poly &P) const
{
    unsigned a_n, dimMenor;
    if(P.D>D) {a_n = (P.D-1); dimMenor = D;}
    else {a_n = (D-1); dimMenor = P.D;}
    Poly prov(a_n);
    unsigned dimMaior = a_n+1;
    for(unsigned i=0; i<dimMaior; i++)
    {
        if(i<dimMenor) {prov.coef[i] = coef[i] - P.coef[i];}
        else if(P.D>D) {prov.coef[i] = P.coef[i];}
        else {prov.coef[i] = coef[i];}
    }
    if(prov.coef[a_n] == 0.0) {prov = prov.ajusta_D();}
    return prov;
}


/// SOBRECARGA DE OPERADORE
/// Negativo de um polinomio

Poly Poly::operator-() const
{
    unsigned a_n = D-1;
    Poly prov(a_n);
    for(unsigned i=0; i<D; i++) prov.coef[i] = -coef[i];
    return prov;
}


/// SOBRECARGA DE OPERADORE
/// Multiplicacao de polinomios

Poly Poly::operator*(const Poly &P) const
{
    /// Ps.: Em vez de criar algumas variaveis a mais e fazer condicoes "if" dentro dos lacos, eu poderia ter copiado os elementos do
    ///     polinomio de menor grau para uma variavel do tipo Poly, chamado a funcao membro setGrau, alterado para o grau do
    ///     polinomio de menor grau para ficar igual ao do polinomio de maior grau, depois fazer um laco com o grau do antigo
    ///     polinomio, que tinha grau inferior. Dentro do laco chamar a funcao membro setCoef e passado como parametro os
    ///     coeficientes da variavel provisoria, alem de zerar o coeficiente a_n. Entretanto achei que ficaria mais otimizado
    ///     da seguinte maneira:

    unsigned a_n, dimMenor, dimMaior;
    unsigned dimNova = P.D+D-1;
    a_n = dimNova-1;
    if(P.D>D) {dimMaior = P.D ;dimMenor = D;}
    else {dimMaior = D; dimMenor = P.D;}
    Poly prov(a_n), soma(a_n); /// Cria polinomios com grau a_n
    soma.coef[a_n] = 0.0;
    prov.coef[a_n] = 0.0;

    for(unsigned i=0; i<dimMenor; i++)
    {
        for(unsigned j=0; j<dimMaior; j++)
        {
            if(dimMaior==D) {prov.coef[i+j] = P.coef[i] * coef[j];}
            else {prov.coef[i+j] = coef[i] * P.coef[j];}
        }

        for(unsigned k=0; k<dimNova; k++)
        {
            soma.coef[k] += prov.coef[k];
        }

        prov.zera();
    }

    if(soma.coef[a_n] == 0.0) {soma = soma.ajusta_D();} /// "soma.coef[a_n] == 0.0" == 1, somente se P1 ou P2 for igual a zero

    return soma;
}


/// ENTRADA DE DADOS

istream &operator>>(istream &W, Poly &P)
{
    if(P.D)
    {
        unsigned a_n = P.D-1;
        do
        {
            for(unsigned i=0; i<P.D; i++) W >> P.coef[i];

            if(P.coef[a_n]==0) cerr << "O coeficiente a_n nao pode ser nulo! Por favor digite todos os coeficientes novamente.\n";

        } while (P.coef[a_n]==0);
    }

    return W;
}


/// SAIDA DE DADOS

ostream &operator<<(ostream &W, const Poly &P)
{
    if(P.D)
    {
        int a_n = P.D-1;
        for(int i=a_n; i>=0; i--)
        {
            if(fabs(P.coef[i])==1.0)
            {
                if(i==a_n)
                {
                    if(P.coef[i]<0) {W << '-';}
                    if(i>1) {W << "x^" << i;}
                    else if(i==1) {W << 'x';}
                    else {W << fabs(P.coef[i]);}
                }
                else
                {
                    if(i>1) {W << (P.coef[i]<0 ? '-' : '+') << "x^" << i;}
                    else if(i) {W << (P.coef[i]<0 ? '-' : '+') << 'x';}
                    else {W << (P.coef[i]<0 ? '-' : '+') << fabs(P.coef[i]);}
                }
            }
            else if(fabs(P.coef[i])!=0.0 || a_n==0)  /// O usuario pode colocar - erroniamente - "-0.0" como coeficiente
                                                     /// Queremos que entre quando a_n==0, pois quando o grau do polinomio for
                                                     /// nulo e o unico coeficiente for zero, ainda deve ser impresso
            {
                if(i==a_n)
                {
                    if(P.coef[i]<0) {W << '-';}
                    if(i>1) {W << fabs(P.coef[i]) << "*x^" << i;}
                    else if(i) {W << fabs(P.coef[i]) << "*x";}
                    else {W << fabs(P.coef[i]);}
                }
                else
                {
                    if(i>1) {W << (P.coef[i]<0 ? '-' : '+') << fabs(P.coef[i]) << "*x^" << i;}
                    else if(i) {W << (P.coef[i]<0 ? '-' : '+') << fabs(P.coef[i]) << "*x";}
                    else {W << (P.coef[i]<0 ? '-' : '+') << fabs(P.coef[i]);}
                }
            }
        }
    }
    return W;
}


/// METODO DE CONSULTA
/// Metodo de consulta que retorna o valor do polinomio para um dado numero

double Poly::getValor(double x) const
{
    double P_x = 0.0;
    for(unsigned i=0; i<D; i++) P_x += coef[i]*pow(x,i);
    return P_x;
}


/// METODO DE CONSULTA
/// Sobrecarga do operador "[]", que serve para consultar o elemento do array. Ex.: cout << x[1];

double Poly::operator[](unsigned i) const
{
    if(i>=D)
    {
        cerr << "O indice eh maior do que o esperador.\n";
        return 0.0;
    }
    return getCoef(i);
}


/// METODO DE ALTERACAO DE VALORES
/// Segunda sobrecarga do operador "[]", que serve para fixar valores. Ex.: x[1]=7;

double &Poly::operator[](unsigned i)
{
    static double prov = 0.0;
    if(i>=D)
    {
        cerr << "ERROR! O indice eh maior do que o esperador.\n";
        return prov;
    }
    return coef[i];
}


/// METODO DE ALTERACAO DE VALORES
/// Permite alterar um certo coeficiente de um polinomio

void Poly::setCoef(unsigned i, double x)
{
    if(i>=D) {cerr << "ERROR! O indice eh maior do que o esperador.\n";}
    else
    {
        unsigned a_n = D-1;
        if(i==a_n && a_n!=0 && fabs(x)==0.0) {cerr << "O coeficiente a_n nao pode ser nulo!\n";}

        else {coef[i] = x;}  /// Nao eh preciso testar se a_n==0 (grau 0), ou seja, fazer um outro if com essa condicao,
                             /// pois se nao satisfez a condicao acima, o coeficiente vai poder receber zero
                             /// independente da posicao
    }
}


/// FUNÇAO MEMBRO AUXILIAR
/// Ajusta a dimensao no caso dela diminuir ou aumentar, na soma e na subtracao
/// Na multiplicacao ela eh utilizada caso P1 ou P2 seja igual a zero

Poly Poly::ajusta_D()
{
    int a_n = D-1;
    unsigned cont = 0;
    for(int i=a_n; i>=0; i--)
    {
        if(coef[i]==0) {cont++;}
        else {break;}
    }
    D = D-cont;
    if (!D) {D = 1;}
    Poly P(*this);

    return P;
}
