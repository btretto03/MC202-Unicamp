#ifndef AGENDA_H
#define AGENDA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 151

typedef struct {
    char nome[MAX];
    int chave, duracao, id;
} Item;

typedef struct {
    Item *v;
    int *pos; //vetor de indices
    int n, tamanho;
} FP;

typedef FP * p_fp;
//Funcao responsavel por criar o heap
p_fp criar_filaprio(int tam);

//Funcao responsavel por criar os itens 
Item* criar_item(char *nome, int chave, int duracao, int id);

//Funcao responsavel por inserir um elemento no heap de maximo
void insere_maximo(p_fp fprio, Item item);

//Funcao responsavel por inserir um elemento no heap de maximo
void insere_minimo(p_fp fprio, Item item);

//Funcao responsavel por remover um elemento do topo no heap de maximo
Item extrai_maximo(p_fp fprio);

//Funcao responsavel por remover um elemento do topo no heap de minimo
Item extrai_minimo(p_fp fprio);

//Funcao que altera a prioridade de elementos
void altera(p_fp heap_max, p_fp heap_min, int id, int x);

//Funcao que libera memoria
void liberar_filaprio(p_fp fprio);

Item extrai_por_id(p_fp fprio, int id, int modo);

#endif