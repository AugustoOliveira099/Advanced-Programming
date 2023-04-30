#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdlib.h> // Para o exit
#include <stdint.h> // Em alguns compiladores, para o uint64_t

/// O arquivo "lista_alunos.csv" eh uma listagem obtida do SIGAA
/// com os alunos do curso de Engenharia de Computacao em 17/06/20
/// Esse arquivo estah em formato CSV, compativel com varios aplicativos
/// de planilhas e manipulacao de dados, como o Excel
/// No arquivo, cada linha contem um aluno, no formato:
///    Matrícula;Nome;Curso;Status;\n
///
/// Este programa deve:
/// 1) Ler todos os alunos do arquivo e armazenar em uma estrutura de dados
///    apropriada (um array dinamico), com os elementos do array contendo
///    todos os dados de um aluno em uma struct
/// 2) Imprimir em tela apenas os alunos com status FORMANDO; e
/// 3) Salvar no arquivo "trancados.csv" apenas os alunos com status TRANCADO,
///    obedecendo ao formato dos arquivos CSV
/// 4) Testar se voce consegue abrir o arquivo "trancados.csv" no Excel ou em
///    outro aplicativo que leia arquivos nesse formato

using namespace std;

/// UMA STRUCT PARA ARMAZENAR ALUNOS

struct Aluno
{
  uint64_t matricula;
  string nome;
  string curso;
  string status;
};

/// Funcao que leh um Aluno de uma stream de entrada
/// Parte da premissa que a stream estah posicionada no inicio da linha
/// Deixa a stream posicionada no inicio da proxima linha
/// Formato da linha: Matrícula;Nome;Curso;Status;\n

Aluno readAluno(ifstream& I)
{
  Aluno prov;

  // Leh o numero ateh antes do ;
  I >> prov.matricula;

  // Ignora o ; que deve ser o proximo caractere
  I.ignore(1, ';');

  // Leh o nome
  getline(I, prov.nome, ';');

  // Leh o curso
  getline(I, prov.curso, ';');

  // Leh o nome
  getline(I, prov.status, ';');

  // Consome o \n no final da linha
  I >> ws;

  return prov;
}

/// Funcao que imprime um aluno em uma stream de saida

void imprimeAluno(ostream& O, const Aluno& A)
{
  O << A.matricula << ';' << A.nome << ';'
    << A.curso << ';' << A.status << ';' << endl;
}

/// Programa principal

int main(void)
{
  // O array de alunos: ponteiro e dimensao
  Aluno* X = NULL;
  unsigned int N(0);

  // Constantes com os nomes dos arquivos
  const string arquivo_in("lista_alunos.csv");
  const string arquivo_out("trancados.csv");

  // Variaveis auxiliares
  string cabecalho;
  unsigned int i;

  // Abertura da stream de leitura
  ifstream stream_in(arquivo_in.c_str());
  if (!stream_in.is_open())
  {
    cerr << "Erro na abertura do arquivo " << arquivo_in << " para leitura\n";
    cerr << "Encerrando o programa!\n";
    exit(1);
  }

  // Leitura da primeira linha do arquivo
  getline(stream_in, cabecalho);  // Leh ateh \n
  if (cabecalho != "Matricula;Nome;Curso;Status;")
  {
    cerr << "Cabecalho do arquivo " << arquivo_in << " invalido\n";
    cerr << "Encerrando o programa!\n";
    exit(2);
  }

  // Leitura da quantidade de alunos:
  // igual ao numero de linhas do arquivo apos o cabecalho
  bool leitura_ok;
  do
  {
    string linha;
    getline(stream_in, linha);   // Leh ateh \n
    // Testa se:
    // nao acabou ou houve erro no arquivo
    // a string lida tem tamanho > 0 (nao contar linhas em branco)
    leitura_ok = stream_in.good();
    if (leitura_ok)
    {
      if (linha.size()>0) N++;
    }
    else if (stream_in.fail())
    {
      // Nao saiu porque o arquivo acabou
      cerr << "Erro na leitura do " << arquivo_in << "\n";
      cerr << "Encerrando o programa!\n";
      exit(3);
    }
  } while (leitura_ok);

  // Testa se existem alunos no arquivo
  if (N>0)
  {
    cout << "Arquivo contem " << N << " alunos\n";
  }
  else
  {
    cerr << "Nao hah nenhum aluno no arquivo " << arquivo_in << "\n";
    cerr << "Encerrando o programa!\n";
    exit(4);
  }

  // Volta a stream para o inicio do arquivo
  stream_in.seekg(0, stream_in.beg);

  // Cria o array para conter os N alunos
  X = new Aluno[N];

  // Leh o cabecalho inicial: jah foi testado
  getline(stream_in, cabecalho);  // Leh ateh \n

  // Leh os N alunos
  for (i=0; i<N; i++)
  {
    X[i] = readAluno(stream_in);
  }

  // Fecha a stream de leitura
  stream_in.close();

  // Imprime os alunos FORMANDO
  cout << "ALUNOS FORMADOS:\n";
  for (i=0; i<N; i++)
  {
    if (X[i].status == "FORMANDO")
    {
      imprimeAluno(cout, X[i]);
    }
  }

  // Abertura da stream de escrita
  ofstream stream_out(arquivo_out.c_str());
  if (!stream_out.is_open())
  {
    cerr << "Erro na abertura do arquivo " << arquivo_out << " para escrita\n";
    cerr << "Encerrando o programa!\n";
    exit(5);
  }

  // Escreve o cabecalho
  stream_out << cabecalho << endl;
  // Escreve os alunos TRANCADO
  for (i=0; i<N; i++)
  {
    if (X[i].status == "TRANCADO")
    {
      imprimeAluno(stream_out, X[i]);
    }
  }

  // Fecha a stream de escrita
  stream_out.close();

  // Libera a memoria
  delete[] X;

  return 0;
}
