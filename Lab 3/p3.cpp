/*********************************
* Gustavo Henrique Storti Salibi *
* RA: 174135                     *
* Laboratorio 03                 *
*********************************/

/********************************* RELATORIO **********************************/
/*
   A funcao main aloca os elementos em vetor e depois coloca todos os k separadores
 em suas devidas posicoes nesse vetor, utilizando para isso a funcao
 ordenarSeparadores e, depois, imprime os elementos (ja devidamente posicionados)
 referentes as k posicoes que separam os subvetores. Apenas a funcao
 ordenarSeparadores possui custo relevante dentro da main.

   A funcao ordenarSeparadores utiliza a funcao posicionarElemento, que, por sua
 vez, utiliza a funcao particionar (aleatorizada), assim, a funcao particionar
 gasta O(n) e a funcao posicionarElemento também gasta O(n), já que podemos
 considera-la como otima por estar aleatorizada, conforme enunciado.

   Dessa forma, o começo da funcao ordenarSeparadores gasta O(n), pois chama a
 funcao posicionarElemento. Depois disso, ela é executa recursivamente em duas
 chamadas, com parâmetros de ordem n/2 e k/2, essas chamadas somadas gastam,
 portanto, O(n). E, ja que n também é dividido por dois a cada recursão, não
 importa que se chame k vezes a funcao recursivamente, pois o total será
 k*O(n/k), totalizando sempre O(n).

   A cada vez, as duas chamadas recursivas fazem k ser dividido pela metade e
 serao executadas, por tanto, até que k atinja 1, depois de logk + 1 vezes.

   Assim, o programa tem complexidade O(n logk).
*/

/************************* BIBLIOTECAS E DEFINICOES ***************************/
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

/*************************** DECLARACAO DE FUNCOES ****************************/
void ordenarSeparadores (vector<int> &A, long int p, long int r, long int k);
void posicionarElemento (vector<int> &A, long int p, long int r, long int i);
long int particionar (vector<int> &A, long int p, long int r);
void trocarPosicoes (vector<int> &A, long int i, long int j);

/************************************ MAIN ************************************/
int main ()
{
    vector<int> A;
    long int n, k;
    int temp;

    // Recebe quantidade de elementos e quantidade de divisores
    cin >> n;
    cin >> k;

    // Recebe os elementos do vetor
    for (long int i = 0; i < n; i++)
    {
        cin >> temp;
        A.push_back(temp);
    }

    // Coloca os separadores nas posições corretas
    ordenarSeparadores(A, 0, n-1, k);

    // Percorre as posições dos separadores e os imprime
    for (int i = 0, j = (n-k)/(k+1); i < k; i++)
    {
        cout << A[j] << " ";
        j += (n+1)/(k+1);
    }
    cout << endl;
}

/********************************** FUNCOES ***********************************/
// Coloca os k separadores em suas respectivas pocicoes dentro do vetor
void ordenarSeparadores(vector<int> &A, long int p, long int r, long int k)
{
    // Coloca a mediana do intervalo em sua posicao correta
    posicionarElemento(A, p, r, (p + r)/2);
    k--; // Atualiza quantidade de separadores
    if (k > 1)
    {
        // Posiciona, recursivamente, as medianas dos dois subvetores
        ordenarSeparadores(A, p, (p + r)/2 - 1, k/2);
        ordenarSeparadores(A, (p + r)/2 + 1, r, k/2);
    }
}

// Coloca corretamente o elemento referente a posicao i dentro do intervalo p-r
void posicionarElemento(vector<int> &A, long int p, long int r, long int i)
{
    if (p != r)
    {
        long int q = particionar(A, p, r);
        if (i < q)
        {
            posicionarElemento(A, p, q - 1, i);
        }
        else if (i > q)
        {
            posicionarElemento(A, q + 1, r, i);
        }
    }
}

// Particiona um intervalo de um vetor a partir de um pivo e retorna a posicao
long int particionar (vector<int> &A, long int p, long int r)
{
    srand(0);
    long int aleatorio = rand()%(r-p+1) + p; // Posicao aleatoria
    int pivo, i = p-1;

    // Seleciona o pivo aleatorio
    trocarPosicoes(A, aleatorio, r);
    pivo = A[r];

    for (int j = p; j < r; j++)
    {
        if (A[j] <= pivo)
        {
            i++;
            trocarPosicoes(A,i, j);
        }
    }
    trocarPosicoes(A, r, i + 1);

    return i + 1;
}

// Troca a posicao de dois elementos i e j de um vetor A
void trocarPosicoes (vector<int> &A, long int i, long int j)
{
    long int temp = A[j];
    A[j] = A[i];
    A[i] = temp;
}
