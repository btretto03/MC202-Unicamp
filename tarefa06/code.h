#ifndef GATACCA_H
#define GATTACA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//define a estrutura da arvore a ser usada
typedef struct no *p_no;
typedef char *dna;

struct no {             //funcao de aula adicionado o campo dna
    int chave, altura;
    p_no esq, dir;
    dna dna;
};

//Funcao responsavel por criar a arvore recursivamente;
p_no criar_arvore(char *dna, int tamanho, int max);

//Função responsavel por imprimir tudo;
void print_all (p_no no);

//Funcao resposavel por imprimir um trecho;
void print_pedaco(p_no no, int posicao_i, int posicao_f, int *posicao);

//Funcao responsavel por contar para o print final:
void contar_letras(p_no no, int *a, int*c, int *g, int *t);

//FUncao responsavel por inserir elementos no DNA
p_no inserir(p_no no, int posicao, char letra, int max);

//Funcao responsavel por remover elementos do DNA
p_no remover(p_no no, int posicao, int max);

//Funcao que libera recursivamente a memoria da arvore
void liberar_arvore(p_no no);

#endif