#ifndef DEQUE_HEROIS_H
#define DEQUE_HEROIS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 51

//Estrutura de no para a lista ligada duplamente
typedef struct no {
    char dado[MAX];
    struct no *prox, *ant;
} No;

//Ponteiro para a estrutura nó
typedef No * p_no;

typedef struct {
    p_no inicio, fim;
} deque;

typedef deque * p_deque;


//função responsável por criar um deque
p_deque cria_deque();


//Fução responsável por inserir um elemento no início do deque
void insere_inicio(p_deque d, char *dado);


//Fução responsável por inserir um elemento no fim do deque
void insere_fim(p_deque d, char *dado);


//Função responsável por inserir um personagem no meio e no fim
void insere_meio(p_deque d, char *dado, int posicao, int tamanho);


//Fução responsável por remover um elemento no incio do deque
char* remove_inicio(p_deque d, int lugar);
//se chamar a funcao no deque_herois.c quero o print que ele foi removido e devo colocar lugar = 0
//se chamar a funcao no proprio code.c para outros processos nao quero o print e, portanto, lugar = 1


//Fução responsável por remover um elemento no fim do deque
char* remove_fim(p_deque d, int lugar);


//funcao que remove um heroi do meio do deque
void remove_meio(p_deque d, int posicao, int tamanho);


//Função de ataque, copia o primeiro elemento para o fim e o remove do início
void troca_inicio_fim(p_deque d);


//Funcao resposanvel por imprimir todos guerreiros da lista
void imprime_guerreiros(p_no deque);


//Funcao que libera a memoria do deque
void limpa_deque(p_deque d);


//Funcao responsavel pelo feitico caos
p_no inverte_comeco(p_deque d, int prefixo);


//Funcao responsavel pelo feitico confusao
p_no inverte_fim(p_deque d, int sufixo);


#endif