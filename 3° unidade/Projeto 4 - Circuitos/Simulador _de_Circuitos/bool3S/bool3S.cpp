#include <iostream>
#include "bool3S.h"

using namespace std;

//Os operadores logicos para a classe bool3S

// NOT 3S
bool3S operator~(bool3S x)
{
  return ( x==bool3S::UNDEF ?
             bool3S::UNDEF :
             (x==bool3S::TRUE ? bool3S::FALSE : bool3S::TRUE) );
}

// AND 3S
bool3S operator&(bool3S x1, bool3S x2)
{
  return ( (x1==bool3S::FALSE || x2==bool3S::FALSE) ?
             bool3S::FALSE :
             ((x1==bool3S::UNDEF || x2==bool3S::UNDEF) ?
                bool3S::UNDEF :
                bool3S::TRUE) );
}

// OR 3S
bool3S operator|(bool3S x1, bool3S x2)
{
  return ( (x1==bool3S::TRUE || x2==bool3S::TRUE) ?
             bool3S::TRUE :
             ((x1==bool3S::UNDEF || x2==bool3S::UNDEF) ?
                bool3S::UNDEF :
                bool3S::FALSE) );
}

// XOR 3S
bool3S operator^(bool3S x1, bool3S x2)
{
  return ( (x1==bool3S::UNDEF || x2==bool3S::UNDEF) ?
             bool3S::UNDEF :
             ((x1==x2) ?
                bool3S::FALSE :
                bool3S::TRUE) );
}

// Os operadores de incremento/decremento para a classe bool3S

// Prefixados (++B, --B: incrementa, depois retorna)

bool3S& operator++(bool3S &B)
{
    if (B==bool3S::UNDEF) {B=bool3S::FALSE; return B;}
    if (B==bool3S::FALSE) {B=bool3S::TRUE; return B;}
    // Vamos fazer um incremento circular: TRUE->UNDEF
    B=bool3S::UNDEF; return B;
}

bool3S& operator--(bool3S &B)
{
    if (B==bool3S::TRUE) {B=bool3S::FALSE; return B;}
    if (B==bool3S::FALSE) {B=bool3S::UNDEF; return B;}
    // Vamos fazer um decremento circular: UNDEF->TRUE
    B=bool3S::TRUE; return B;
}

// Posfixados (B++, B--: retorna copia do valor antes de incrementar)
// O parametro int nao serve para nada, apenas diferencia dos prefixados

bool3S operator++(bool3S &B, int)
{
    bool3S prov(B);
    ++B;
    return prov;
}

bool3S operator--(bool3S &B, int)
{
    bool3S prov(B);
    --B;
    return prov;
}

// As conversoes entre bool3S e char

// Converte um bool3S para um char que o representa (F T ?)
char toChar(bool3S B)
{
   return (B==bool3S::TRUE ?
             'T' :
             (B==bool3S::FALSE ?
                'F' :
                '?'));
}

// Converte um char (F T ?) para o bool3S correspondente
bool3S toBool_3S(char C)
{
    C = toupper(C);
    return (C=='T' ?
              bool3S::TRUE :
              (C=='F' ?
                 bool3S::FALSE :
                 bool3S::UNDEF));
}

// Os operadores de entrada/saida para a classe bool3S

// Impressao de bool3S
ostream &operator<<(ostream &O, bool3S B)
{
  O << toChar(B);
  return O;
}

// Leitura de bool3S (? T F)
istream &operator>>(istream &I, bool3S &B)
{
  char prov;
  I >> prov;
  B = toBool_3S(prov);
  return I;
}
