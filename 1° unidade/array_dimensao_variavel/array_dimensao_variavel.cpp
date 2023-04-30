/*
O objetivo eh fazer um programa que solicite ao usuario que
digite uma sequencia de numeros reais nao nulos. Quando o
usuario digitar zero, entende-se que ele concluiu a entrada
dos dados.
Apos a entrada dos dados, o programa deve calcular e imprimir
as seguintes informacoes:
1) A media aritmetica dos numeros digitados (sem incluir o
zero final).
2) Quantos dos numeros estao acima e abaixo da media (sem
contar com o zero final.
*/

#include <iostream>

using namespace std;

int main()
{
    float Num, media, soma = 0.0;
    unsigned N=0, acima_da_media=0, abaixo_da_media=0;
    float *arr = NULL;
    unsigned i;

    do
    {
        cout << "Digite um numero [0.0 para parar]: ";
        cin >> Num;
        if (Num != 0.0)
        {
            float *prov = new float[N+1];
            for (i=0; i<N; i++) prov[i] = arr[i];
            prov[N] = Num;
            if (arr != NULL) delete[] arr;
            arr = prov;
            N++;
        }
    } while (Num != 0.0);

    if (N==0)
    {
        cout << "Voce nao digitou nenhum numero!!!\n";
    }
    else
    {
        for (i=0; i<N; i++) soma += arr[i];
        media = soma/N;
        for (i=0; i<N; i++)
        {
            if (arr[i] < media) abaixo_da_media++;
            if (arr[i] > media) acima_da_media++;
        }
        cout << "os numeros digitados sao: ";
        for (i=0; i<N; i++) cout << arr[i] << ' ';
        cout << endl;
        cout << "A media eh: " << media << endl;
        cout << "Acima da media: " << acima_da_media << endl;
        cout << "Abaixo da media: " << abaixo_da_media << endl;
    }

    return 0;
}
