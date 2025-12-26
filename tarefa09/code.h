#ifndef BUILDMAP_C
#define BUILDMAP_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_HASH 11279
#define MAX 5001


//Vou utiliar as structs dadas em aula pelo professor, trabalhando com uma hash para atribuir ids nas leituras e inseri-las no grafo
//grafo
typedef struct no *p_no;

struct no {
    int v;
    p_no prox;
};

typedef struct grafo *p_grafo;

struct grafo {
    p_no *adjacencia;
    int n;
};

//hash
typedef struct no_hash *p_no_hash;

struct no_hash {
    char chave[16]; 
    int dado;
};

typedef struct hash *p_hash;

struct hash {
    p_no_hash *nome;
    int tamanho_tot, tamanho_at;
    int *estado;              //-1 para vazio, 0 ocupado
};

//fila de prioridade
typedef struct fila *p_fila;

struct fila {
    int *v;
    int ini, fim, N, tamanho;
};

//informacoes relevantes para o dfs
typedef struct dfs *p_dfs; //pra nao fazer uma função com 20 parametros pensei em criar essa struct

struct dfs {
    int visitado[MAX], caminho[MAX], ordem[MAX], pai[MAX];
    int ciclo, inicio, fim, tam_ordem;
};

//grafo
p_grafo criar_grafo(int n);
void insere_aresta(p_grafo g, int u, int v, char nomes[MAX][16]);
p_no insere_na_lista(p_no lista, int v);
void destroi_grafo(p_grafo g);
void inicia_dfs(p_dfs dfs, int N);
void dfs(p_grafo g, int inicio, char nomes[MAX][16], char alvo[], int N);
void imprime_ciclo(p_grafo g, int inicio, int fim, char nomes[MAX][16], char alvo[], int *pai);
int detecta(p_grafo g, int u, p_dfs dfs);
void imprime_distancias(p_grafo g, int dist[MAX], char nomes[MAX][16], char alvo[]);
void bfs(p_grafo g, int s, char nomes[MAX][16], char alvo[]);

//fila
p_fila criar_fila(int N);
void enfileira(p_fila f, int valor);
int desenfileira(p_fila f);
int fila_vazia(p_fila f);
void destroi_fila(p_fila f);

//hash
p_no_hash criar_palavra_hash(char chave[], int dado);
p_hash criar_hash();
p_no_hash adicionar_palavra_hash(p_hash tab, char *chave, int k, int *dado);
void liberar_hash(p_hash tab);

#endif