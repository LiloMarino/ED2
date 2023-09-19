#include <stdio.h>
#include <limits.h>

int main() {
    int V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int maior_par = -1;     // Inicialize com -1 para o caso de não haver números pares
    int menor_impar = -2;   // Inicialize com -2 para o caso de não haver números ímpares
    int n_primos = 0;       // Inicialize com 0
    int soma = 0;
    int produto = 0;
    int maior = INT_MIN;    // Inicialize com o menor valor possível para int
    int menor = INT_MAX;    // Inicialize com o maior valor possível para int

    for (int i = 0; i < 20; i++) {  // Altere para i < 20 para percorrer todos os elementos
        soma += V[i];

        if (V[i] % 2 == 0) { // Se for par
            if (V[i] > maior_par) {
                maior_par = V[i];
            }
        } else { // Se for ímpar
            if (V[i] < menor_impar) {
                menor_impar = V[i];
            }
            if (ehPrimo(V[i])) { // Chame uma função para verificar se é primo
                n_primos++;
            }
        }

        if (V[i] > maior) {
            maior = V[i];
        }

        if (V[i] < menor) {
            menor = V[i];
        }
    }

    produto = maior * menor;

    // Imprimir os resultados
    printf("Maior número par: %d\n", maior_par);
    printf("Menor número ímpar: %d\n", menor_impar);
    printf("Número de elementos primos: %d\n", n_primos);
    printf("Soma dos números: %d\n", soma);
    printf("Produto do maior e do menor número: %d\n", produto);

    return 0;
}

int ehPrimo(int num) {
    if (num <= 1) {
        return 0; // Números menores ou iguais a 1 não são primos
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // Não é primo
        }
    }
    return 1; // É primo
}

.set CODIGO 0x0
.set VETOR 0x200
.set DADOS 0x300
.set MAX_INT 0x7FFFFFFFFF
.set MIN_INT 0x8000000001

.org CODIGO
    for:
    
    fim_for:
    
    
.org VETOR
    .word 1
    .word 2
    .word 3
    .word 4
    .word 5
    .word 6
    .word 7
    .word 8
    .word 9
    .word 10
    .word 11
    .word 12
    .word 13
    .word 14
    .word 15
    .word 16
    .word 17
    .word 18
    .word 19
    .word 20

.org DADOS
    maior_par:
        .word 0
    menor_impar:
        .word 0
    n_primos:
        .word 0
    soma:
        .word 0
    produto:
        .word 0
    maior:
        .word MIN_INT
    menor:
        .word MAX_INT
    i:
        .word 19  # 20 repetições
        