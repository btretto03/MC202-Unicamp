//O deque foi escolhido porque ele permite manipulações na sua estrutura em O(1) pelas duas extremidades,
//ele foi implementado com listas duplamente ligadas, seguindo o exemplo dado pelo professor em aula, 
//as suas funções foram copiadas dos slides de aula, somente as adaptei para receber strings e nao inteiros
//Como sugestao no ultimo exercicio, tentei deixar a TAD mais "limpa" no arquivo principal e todas as funcoes no code.c

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "code.h"
#define MAX 51

int main() {
    char comando[16], personagem[MAX]; 
    int tamanho = 0;  
    p_deque deque = cria_deque();

    while(1){
        scanf("%s", comando);

        if (strcmp(comando, "convocar-frente") == 0) {
            scanf("%s", personagem);
            insere_inicio(deque, personagem);
            printf("%s entrou no inicio\n", personagem);
            imprime_guerreiros(deque->inicio);
            tamanho ++;
        }

        if (strcmp(comando, "convocar-fim") == 0) {
            scanf("%s", personagem);
            insere_fim(deque, personagem);
            printf("%s entrou no fim\n", personagem);
            imprime_guerreiros(deque->inicio);
            tamanho ++;
        }

        if (strcmp(comando, "posicionar") == 0) {
            int posicao;
            scanf("%s", personagem);
            scanf("%d", &posicao);
            insere_meio(deque, personagem, posicao, tamanho);
            printf("%s inserido na posicao %d\n", personagem, posicao);
            imprime_guerreiros(deque->inicio);
            tamanho ++;
        }

        if (strcmp(comando, "puxar-frente") == 0) {
            char* removido = remove_inicio(deque, 0);
            imprime_guerreiros(deque->inicio);
            free(removido);
            tamanho --;
        }   

        if (strcmp(comando, "puxar-tras") == 0) {
            char* removido = remove_fim(deque, 0);
            imprime_guerreiros(deque->inicio);
            free(removido);
            tamanho --;
        }

        if (strcmp(comando, "ataque") == 0) {
            troca_inicio_fim(deque);
            imprime_guerreiros(deque->inicio);
        }

        if (strcmp(comando, "remover") == 0) {
            int posicao;
            scanf("%d", &posicao);
            remove_meio(deque, posicao, tamanho);
            imprime_guerreiros(deque->inicio);
            tamanho --;
        }

        if (strcmp(comando, "caos") == 0) {
            int prefixo;
            scanf("%d", &prefixo);
            inverte_comeco(deque, prefixo);
            imprime_guerreiros(deque->inicio);
        }
        
        if (strcmp(comando, "confusao") == 0) {
            int sufixo;
            scanf("%d", &sufixo);
            inverte_fim(deque, sufixo);
            imprime_guerreiros(deque->inicio);
        }

        if (strcmp(comando, "sair") == 0) {
            break;
        }

    }
    limpa_deque(deque);
    return 0;
}