// Gustavo Henrique Storti Salibi / 174135

/*
    Relatório

         A resolução é análoga ao algoritmo "Merge Sort".

         Começamos a função "contar" pelo caso base, onde o tamanho do vetor é menor ou igual a 1,
        neste caso, a função devolve 0, já que não há inversões. E, assim, a base está correta.

         Caso o vetor tenha tamanho maior que 1, dividimos o problema em dois subvetores e chamamos
        a função "contar" recursivamente para cada um deles. Esse processo tem complexidade igual a
        O(lg(n)), já que o problema sempre é dividido em dois até que se chegue ao caso base. Essa
        parte também está correta, pois se funciona para um número n qualquer, também funciona para
        "n+1", já que dividindo "n+1" em dois, chegamos ao caso n, o qual está correto.

         Depois disso, chamamos a função "intercalarr", onde o vetor todo é percorrido por um "for" e
        possui, portanto, complexidade igual a O(n). A função funciona, já que como invariante de laço
        temos o subvetor de v indo de 0 até i, onde o número de inversões foi contado corretamente,
        junto a isso, os subvetores "sub1" e "sub2" estão ordenados e os comparamos a fim de saber
        quantos elementos maiores do segundo subvetor existem com relação a um elemento do primeiro
        subvetor, obtendo o número total de inversões facilmente subtraindo o elemento atual do total,
        já que o subvetor está ordenado.

         Portanto, o algoritmo está correto e possui complexidade igual a O(nlg(n)).
*/


#include <iostream>
#include <vector>
#include <stdio.h>
#define LIMITE 2147483647 

using namespace std;
unsigned long long int contar(vector<int> &v);
unsigned long long int intercalar (vector<int> &v, vector<int> &sub1, vector<int> &sub2);

int main() {
    vector <int> v;
    int tamanho, temp;

    // Leitura do tamanho e dos elementos do vetor
    scanf ("%d", &tamanho);
    for (int i = 0; i < tamanho; i++) {
        scanf ("%d", &temp);
        v.push_back(temp);
    }

    // Impressão do resultado final
    cout << contar(v) << "\n";
}

// Ordena recursivamente o vetor para fazer a contagem
unsigned long long int contar(vector<int> &v) {
	// Caso base
	if(v.size() <= 1)
        return 0;

    // Caso o vetor tenha tamanho maior que 1
	unsigned long long int totalInvercoes = 0;

	// Divide v em dois subvetores e atribui os elementos a eles
	vector<int> sub1, sub2;

	for(int i = 0; i < (int) v.size()/2; i++)
		sub1.push_back(v[i]);
		
	for(int i = v.size()/2; i < (int) v.size(); i++)
	 	sub2.push_back(v[i]);

	// Ordena recursivamente os subvetores e recebe o total de inversões de cada um deles
	totalInvercoes += contar(sub1);
	totalInvercoes += contar(sub2);

	// Adiciona um valor alto no final para que a comparação funcione
	sub1.push_back(LIMITE);
	sub2.push_back(LIMITE);

    // Intercala os resultados obtidos
    totalInvercoes += intercalar(v, sub1, sub2);

	return totalInvercoes;
}

// Intercala dois subvetores e retorna o total de inversões entre eles
unsigned long long int intercalar (vector<int> &v, vector<int> &sub1, vector<int> &sub2) {
    unsigned long long int inversoes = 0;
    int i1 = 0, i2 = 0; // Índices dos subvetores

	// Percorre todas as posições do vetor
	for(int i = 0; i < (int) v.size(); i++) {
		if(sub1[i1] <= sub2[i2]) {
			v[i] = sub1[i1];
			i1++;
		} else {
			v[i] = sub2[i2];
			i2++;
			inversoes += (sub1.size() - i1 -1);
		}
	}

	return inversoes;
}
