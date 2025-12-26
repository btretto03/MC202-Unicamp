#ifndef REDE_C
#define REDE_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no *p_no;

struct no {
    int v;
    p_no prox;
};

typedef struct grafo *p_grafo;

struct grafo {
    p_no *adjacencia;
    int *pesos;
    int n;
};

typedef struct dados *p_dados;

struct dados { //como fiz na ultima tarefa, criei essa struct pra nao precisar passar muitos parametros pras funcoes do backtracking
    int *resposta;     //vai guardar a resposta
    int *teste;
    int tam;
    int peso;
};

//grafo
p_no insere_na_lista(p_no lista, int v);
void inserir_aresta(p_grafo g, int u, int v);
p_grafo criar_grafo(int n);
void destroi_grafo(p_grafo g);

//funcoes do backingtracking
void rodar_backtracking(p_grafo g, p_dados d);

#endif