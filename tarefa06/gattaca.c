#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "code.h"


int main() {
    int vezes, tamanho, max;
    int a = 0, c = 0, g = 0, t = 0; 
    char *dna;
    char comando[10];
    p_no raiz;

    scanf("%d %d %d", &vezes, &tamanho, &max);

    dna = malloc((tamanho + 1) * sizeof(char));
    scanf("%s", dna);
    raiz = criar_arvore(dna, tamanho, max);

    for(int i = 0; i < vezes; i ++) {
        scanf("%s", comando);
        if (strcmp(comando, "INSERT") == 0) {
            int posicao;
            char letra;
            scanf("%d %c", &posicao, &letra);
            raiz = inserir(raiz, posicao, letra, max);
        }
        if (strcmp(comando, "REMOVE") == 0) {
            int posicao;
            scanf("%d", &posicao);
            raiz = remover(raiz, posicao, max);
        }
        if (strcmp(comando, "PRINT") == 0) {
            int posicao_i, posicao_f;
            int contador = 0;
            scanf("%d %d", &posicao_i, &posicao_f);
            printf("Trecho %d-%d: ", posicao_i, posicao_f);
            print_pedaco(raiz, posicao_i, posicao_f, &contador);
            printf("\n");
        }
        if (strcmp(comando, "PRINTALL") == 0) {
            printf("DNA inteiro: ");
            print_all(raiz);
            printf("\n");
        }
    }

    contar_letras(raiz, &a, &c, &g, &t);
    printf("Contagem final: A:%d T:%d C:%d G:%d", a, t, c, g);
    printf("\n");
    liberar_arvore(raiz);
    free(dna);
    
    return 0;
}