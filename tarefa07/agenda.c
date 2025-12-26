#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "code.h"
#define MAX 151

int main() {
    int num_atividades;           //tamanho dos heaps
    char comando[10];
    scanf("%d", &num_atividades);
    p_fp heap_max = criar_filaprio(num_atividades + 1); 
    p_fp heap_min = criar_filaprio(num_atividades + 1);

    while (1) {
    
        scanf("%s", comando);
        if (strcmp(comando, "atividade") == 0) {
            int id, chave, duracao;
            char nome[MAX];
            Item *item;

            scanf("%d %d %d", &id, &chave, &duracao);
            scanf(" %[^\n]", nome);                       //%ficou vermelho
            item = criar_item(nome, chave, duracao, id);

            insere_maximo(heap_max, *item);
            insere_minimo(heap_min, *item);
            printf("%s adicionada - Atividades futuras: %d\n", item->nome, heap_max->n);
            free(item);
        }
        if (strcmp(comando, "altera") == 0) {
            int id, x;
            scanf("%d %d", &id, &x);
            altera(heap_max, heap_min, id, x);
        }
        if (strcmp(comando, "agenda") == 0) {
            printf("--AGENDA--\n");
            int tempo = 0;
            while (heap_max->n > 0 && heap_max->v[0].duracao + tempo <= 600) {
                Item maior_prioridade = heap_max->v[0];
                tempo += maior_prioridade.duracao;
                printf("(%d) %s - Prioridade %d - Estimativa: %d minutos\n", maior_prioridade.id, maior_prioridade.nome, maior_prioridade.chave, maior_prioridade.duracao);
                extrai_maximo(heap_max);
                extrai_por_id(heap_min, maior_prioridade.id, 2);
            }
            while (heap_min->n > 0 && heap_min->v[0].duracao + tempo <= 600) {
                Item maior_prioridade = heap_min->v[0];
                tempo += maior_prioridade.duracao;
                printf("(%d) %s - Prioridade %d - Estimativa: %d minutos\n", maior_prioridade.id, maior_prioridade.nome, maior_prioridade.chave, maior_prioridade.duracao);
                extrai_minimo(heap_min);
                extrai_por_id(heap_max, maior_prioridade.id, 1);
            }
            printf("----------\n");
        }
        if (strcmp(comando, "encerrar") == 0) {
            printf("Restaram %d atividades\n", heap_max->n);
            liberar_filaprio(heap_max);
            liberar_filaprio(heap_min);
            break;
            }
        }
    return 0;
}