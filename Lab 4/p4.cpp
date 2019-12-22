/*********************************
* Gustavo Henrique Storti Salibi *
* RA: 174135                     *
* Laboratorio 04                 *
*********************************/

/********************************* RELATORIO **********************************/
/*
   Para receber os elementos, sao executados dois lacos de tamanho N cada um,
 totalizando 2*O(N). Entao, a funcao "melhorCusto" eh chamada. Fora isso, todas
 as operacoes sao de ordem constante.
   A funcao "melhorCusto" possui um primeiro laco com "i" indo da posicao "N-1"
 até "0", nele, são percorridas "N" casas e selecionado o menor custo entre a
 posicao atual e N; este laco possui, portanto, complexidade O(N).
   Em seguida, um segundo laco eh iniciado em funcao de "j", ele testa todas as
 posicoes da atual ate a ultima e verifica o menor custo possivel ate tal
 posicao. Esse laco roda, no maximo, "N-2" vezes e tem, assim, complexidade O(N).
   Existe também um verificador que interrompe o laco no caso dos custos
 anteriores sozinhos ultrapasserem o custo de se pagar o frete no dia i, isso
 funciona porque sempre somamos os custos anteriores ao possivel valor do
 menor custo atual e enquanto o laco roda ele so pode aumentar, caso esse valor
 sozinho somado ao resto seja maior do que se comprar no dia, nao compensa.
   Dessa forma, o laco roda menos vezes, aumentando o desempenho.
   Depois, a funcao salva o menor custo possivel ate entao em um vetor auxiliar
 "C".
   Por fim, retorna o menor custo de todos.
   Esses lacos juntos possuem complexidade O(N)*O(N) = O(N²), somamos isso aos
 2*O(N) para receber a entrada: O(N²) + O(N) = O(N²). Todas as outras operações
 da funcao são de ordem constante.
*/

/************************* BIBLIOTECAS E DEFINICOES ***************************/
#include <iostream>
#include <vector>

using namespace std;


/*************************** DECLARACAO DE FUNCOES ****************************/
long int melhorCusto(vector<int> &K, vector<int> &D, long int H, long int N);
long int minimo (long int a, long int b);

/************************************ MAIN ************************************/
int main ()
{
    vector<int> K, D;
    long int H, N, temp;

    // Recebe custo H e N dias
    cin >> H >> N;

    // Recebe N fretes e salva em K
    for (long int i = 0; i < N; i++)
    {
        cin >> temp;
        K.push_back(temp);
    }

    // Recebe N demandas e salva em D
    for (long int i = 0; i < N; i++)
    {
        cin >> temp;
        D.push_back(temp);
    }

    // Imprime o custo mínimo
    cout << melhorCusto(K,D,H,N) << endl;

}

/********************************** FUNCOES ***********************************/
// Retorna o menor custo possivel
long int melhorCusto(vector<int> &K, vector<int> &D, long int H, long int N)
{
    long int custoMin, custoAnteriores;
    vector<long int> C(N+1); // vetor com o menor custo ate cada posicao

    for (long int i = N-1; i >= 0; i--)
    {
        custoMin = K[i] + C[i+1]; // reinicia com o custo do frete atual + custo anterior
        custoAnteriores = 0; // reinicia a variavel
        for (long int j = (i+1); j < N; j++)
        {
            // Verifica e atualiza o menor custo ate entao
            custoMin = minimo(custoMin, K[i] + D[j]*H*(j-i) + custoAnteriores + C[j+1]);
            custoAnteriores += D[j]*H*(j-i); // atualiza custo das posicoes anteriores
            // Caso o custo dos valores anteriores seja >= ao custo de se comprar no dia, nao compensa
            if (custoAnteriores >= K[i] + C[i+1])
            {
                break;
            }
        }
        C[i] = custoMin; // preenche vetor com o menor custo ate o dia j
    }

    return C[0]; // retorna o menor custo de todos
}

// Retorna o menor dos dois valores
long int minimo (long int a, long int b)
{
    return (a < b) ? a : b;
}
