#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#define MAX 201

int main(){
    int num, relacoes;
    int melhor_vetor[MAX];
    int vetor[MAX];
    p_dados d = malloc(sizeof(struct dados));

    scanf("%d %d", &num, &relacoes);

    p_grafo g = criar_grafo(num);

    for (int i = 0; i < num; i ++) {
        int peso;
        scanf("%d", &peso);
        g->pesos[i] = peso;
    }
    for (int i = 0; i < relacoes; i ++) {
        int id1, id2;
        scanf("%d %d", &id1, &id2);
        inserir_aresta(g, id1, id2);
    }
    d->resposta = melhor_vetor; //inicializa a struct dos dados
    d->teste = vetor;
    d->peso = -1;
    d->tam = 0;

    rodar_backtracking(g, d);
    free(d);
    destroi_grafo(g);
    return 0;
}