#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

struct Aluno
{
    uint64_t matricula;
    string nome;
    string curso;
    string status;
};

Aluno leAluno (ifstream &I);

void imprimeAluno (ostream &P, const Aluno &A);


int main ()
{
    Aluno *A;
    string cabecalho;

    const string arquivo_in("lista_alunos.csv");
    const string arquivo_out("deu_certo_bctttt.csv");

    ifstream stream_in(arquivo_in.c_str());
    if (!stream_in.is_open())
    {
        cerr << "Erro ao abrir o arquivo " << arquivo_in << ", tente novamente alterando o arquivo, por favor. \n";
        cerr << "Encerrando o programa. \n";
        exit (1);
    }

    getline (stream_in, cabecalho);
    if (cabecalho != "Matricula;Nome;Curso;Status;")
    {
        cerr << "Arquivo nao contem o cabecalho esperado. \n";
        cerr << "Encerrando programa. \n";
        exit (2);
    }

    unsigned N = 0;
    bool leitura_ok;
    do
    {
        string linha;
        getline (stream_in, linha);
        leitura_ok = stream_in.good();
        if (leitura_ok)
        {
            if (linha.size()>0) N++;
        }
        else if (stream_in.fail())
        {
            cerr << "Erro na leitura do arquivo.\n";
            cerr << "Encerrando programa.\n";
            exit(3);
        }
    } while (leitura_ok);

    stream_in.seekg(0, stream_in.beg);

    A = new Aluno[N];

    getline(stream_in, cabecalho);

    for (unsigned i=0; i<N; i++)
    {
        A[i] = leAluno(stream_in);
    }

    stream_in.close();

    cout << "O arquivo possui: " << N << " alunos.\n";
    cout << "Alunos formandos:\n";

    for (unsigned i=0; i<N; i++)
    {
        if (A[i].status == "FORMANDO") imprimeAluno(cout, A[i]);
    }

    ofstream stream_out(arquivo_out.c_str());
    if(!stream_out.is_open())
    {
        cerr << "O arquivo de saída não abriu corretamente.\n";
        cerr << "Encerrando programa.\n";
        exit(4);
    }

    stream_out << cabecalho << endl;

    for (unsigned i=0; i<N; i++)
    {
        if (A[i].status == "TRANCADO") imprimeAluno(stream_out, A[i]);
    }

    delete[] A;
    stream_out.close();

    return 0;
}

Aluno leAluno(ifstream &I)
{
    Aluno prov;

    I >> prov.matricula;
    I.ignore(1, ';');
    getline(I, prov.nome, ';');
    getline(I, prov.curso, ';');
    getline(I, prov.status, ';');
    I >> ws;

    return prov;
}

void imprimeAluno(ostream &P, const Aluno &A)
{
    P << A.matricula << ';' << A.nome
      << ';' << A.curso << ';' << A.status << ';' << endl;
}
