/*********************************
* Gustavo Henrique Storti Salibi *
* RA: 174135                     *
* Laboratorio 02                 *
*********************************/

/********************************* RELATORIO **********************************/
/*
      A solucao utiliza uma scruct para representar os elementos, contendo a
    especie e a idade da arvore.
      Primeiro, o algoritmo aloca todos os elementos em uma matriz[i][j], onde i
    representa a especie e j o elemento da especie.
      Depois, o maior elemento de cada especie eh armazenado em um vetor em heap.
      Por fim, a funcao totalCortes eh chamada. Nela, um primeiro laco eh executado
    enquanto podem haver arvores a serem cortadas, m/k vezes (o numero de elementos
    da maior espécie, ja que dentro desta, há outro laco que percorre todas as k
    especies).
      Dentro do while, outros dois lacos sao executados: o primeiro verifica se
    eh ou nao necessario remover uma arvore da especie e a remove, ele percorre k
    elementos e chama a funcao pop_heap (complexidade O(logk)) no máximo k vezes; o
    segundo laco atualiza o maior valor de cada especie alterada e mantem o heap,
    ele eh percorrido n = (numero de arvores cortadas nesta iteracao) vezes, que
    eh sempre menor ou igual a k, e chama a funcao push_heap (complexidade O(logk)).
    Assim, os dois laços internos possuem complexidade maxima de O(k*logk + k*logk) =
    = O(2*k*logk).
      Alem disso, no comeco do codigo sao utilizas m iteracoes para alocar os elementos
    na matriz, k iteracoes para alocar os maiores elementos em um vetor e k*logk para
    executar o make_heap;
      Todo o resto do codigo eh executado em O(1), ja que nao ha outros lacos ou
    chamadas recursivas.
      Portanto, a complexidade total é de O(m + k + k*logk + (m/k)*(2k)*logk) =
    = O(2m*logk + k*logk + m + k) = O(logk*(2m + k) + m + k) = O(2m*logk + m + k) =
    =  O(m*logk).
*/

/************************* BIBLIOTECAS E DEFINICOES ***************************/
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

/**************************** ESTRUTURAS DE DADOS *****************************/
typedef struct
{
    int especie;
    int idade;
} arvore;

/*************************** DECLARACAO DE FUNCOES ****************************/
arvore criarArvore (int especie, int idade);
bool compararArvores (arvore a, arvore b);
int totalCortes (vector < vector<int> > especies, vector<arvore> maisVelhas, int k);

/************************************ MAIN ************************************/
int main ()
{
    vector<arvore> maisVelhas;
    int k, nElementos, temp;

    cin >> k; // Recebe número de espécies
    vector < vector<int> > especies(k); // Cria vetor de espécies

    // Recebe entradas
    for(int i = 0; i < k ; i++)
    {
        cin >> nElementos;
        for(int j = 0; j < nElementos; j++)
        {
            cin >> temp;
            (especies[i]).push_back(temp);
        }
        // Adiciona a mais velha ao outro vetor
        maisVelhas.push_back(criarArvore(i, temp));
    }

    // Imprime saida
    cout << totalCortes(especies, maisVelhas, k) << "\n";
}

/********************************** FUNCOES ***********************************/
// Cria e retorna um elemento do tipo arvore
arvore criarArvore (int especie, int idade)
{
    arvore novaArvore;
    novaArvore.especie = especie;
    novaArvore.idade = idade;
    return novaArvore;
}

// Compara dois elementos do tipo arvore e retorna o mais novo
bool compararArvores (arvore a, arvore b)
{
    if(a.idade <= b.idade)
        return true;
    else
        return false;
}

// Calcula e retorna o total de cortes
int totalCortes (vector < vector<int> > especies, vector<arvore> maisVelhas, int k)
{
    int totalAntes, totalFinal = 0;
    float idadeLimite;

    // Cria heap com as arvores mais velhas de cada especie
    make_heap(maisVelhas.begin(), maisVelhas.end(), compararArvores);

    // Executa enquanto houver arvores a serem cortadas
    do
    {
        totalAntes = totalFinal;
        idadeLimite = 0.6 * maisVelhas[0].idade;

        // Verifica se eh ou nao necessario remover uma arvore
        for (int i = 0, j = 0; i < k; i++)
        {
            // Remove arvore, colocando no final
            if (especies[maisVelhas[j].especie][ceil(0.6 * especies[maisVelhas[j].especie].size()) - 1] > idadeLimite)
            {
                especies[maisVelhas[j].especie].pop_back();
                pop_heap(maisVelhas.begin() + j, maisVelhas.end(), compararArvores);
                totalFinal++;
            }
            else
            {
                j++;
            }
        }

        // Atualiza o maior valor de cada especie alterada antes e mantem o heap
        for (int i = (totalFinal - totalAntes); i > 0; i--)
        {
            maisVelhas[k - i].idade =
                especies[maisVelhas[k - i].especie][especies[maisVelhas[k - i].especie].size() - 1];
            push_heap(maisVelhas.begin(), maisVelhas.end() - i + 1, compararArvores);
        }
    }
    while (totalAntes != totalFinal);

    // Total de arvores cortadas
    return totalFinal;
}
