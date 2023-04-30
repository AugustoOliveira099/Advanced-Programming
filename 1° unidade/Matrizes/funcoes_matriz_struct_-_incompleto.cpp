#include <iostream>
#include <cmath>

using namespace std;

/*
Exercicio de utilizacao de funcoes em conjunto com arrays alocados dinamicamente (ponteiros)

Nesse exercicio, voce deve definir o novo tipo Matriz utilizando uma struct, que armazena
tanto o numero de linhas e de colunas de cada matriz quanto o ponteiro

A partir desse tipo Matriz, voce deve programar as funcoes necessarias para executar o programa
principal a seguir. A ideia eh permitir fazer as operacoes indicadas com matrizes de quaisquer
dimensoes, fornecidas pelo usuario no momento da execucao (e nao na compilacao).

*/

// FACA SEUS ACRESCIMOS NO CODIGO AQUI

struct Matriz
{
    unsigned L,C;
    double **M;
};

Matriz novaMatriz (int L, int C)
{
    Matriz prov;
    prov.L = L;
    prov.C = C;
    prov.M = new double*[L];
    for (unsigned i=0; i<L; i++)
    {
        prov.M[i] = new double[C];
        for (unsigned j=0; j<C; j++) prov.M[i][j] = 0.0;
    }
    return prov;
}

void leMatriz (Matriz &prov)
{
    cout << "Sua matriz possui " << prov.L << " linhas e " << prov.C << " colunas. Insira os elementos linha a linha: \n";
    for (unsigned i=0; i<prov.L; i++)
    {
        for (unsigned j=0; j<prov.C; j++)
        {
            cin >> prov.M[i][j];
        }
    }
}

void imprimeMatriz (const Matriz &prov)
{
    if (prov.M == NULL) cerr << "A matriz possui apenas elementos nulos.";
    cout << endl;
    for (unsigned i=0; i<prov.L; i++)
    {
        for (unsigned j=0; j<prov.C; j++) cout << prov.M[i][j] << ' ';
        cout << endl;
    }
}

void liberaMatriz (Matriz &prov)
{
    if (prov.M != NULL)
    {
        for (unsigned i=0; i<prov.L; i++) delete[] prov.M[i];
        delete[] prov.M;
        prov.M = NULL;
        prov.L = prov.C = 0;
    }
}

Matriz produtoMatrizes (const Matriz &A, const Matriz &B)
{
    Matriz C;
    if (A.C == B.L)
    {
        C = novaMatriz(A.L, B.C);
        for (unsigned i=0; i<A.L; i++)
        {
            for (unsigned j=0; j<B.C; j++)
            {
                for (unsigned k=0; k<A.C; k++) C.M[i][j] += A.M[i][k]*B.M[k][j];
            }
        }
        return C;
    }

    cout << "Matrizes com dimensoes invalidas \n";
    C.L = C.C = 0;
    C.M = NULL;
    return C;
}


int main(void)
{
    // Declaracao das matrizes
    Matriz A, B, C;

    unsigned NLa, NCa, NLb, NCb;
    do {
        cout << "Linhas de A: ";
        cin >> NLa;
    } while (NLa <= 0);
    do {
        cout << "Colunas de A: ";
        cin >> NCa;
    } while (NCa <= 0);
    // Obs: NLb = NCa
    NLb = NCa;
    do {
        cout << "Colunas de B: ";
        cin >> NCb;
    } while (NCb <= 0);

    // Alocacao das matrizes
    A = novaMatriz(NLa,NCa);
    B = novaMatriz(NLb,NCb);

    // Leitura das matrizes A e B
    leMatriz(A);
    leMatriz(B);

    // produto das matrizes
    C = produtoMatrizes(A,B);

    // Impressao das matrizes
    imprimeMatriz(C);

    // Liberacao das memorias
    liberaMatriz(A);
    liberaMatriz(B);
    liberaMatriz(C);

    return  0;
}
