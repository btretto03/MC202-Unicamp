#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#define MAX 5001

int main() {
    char linha[16800]; 
    char nomes[MAX][16];
    char vertice_inicial[16] = "";
    int cont = 0;
    
    p_dfs dfs = malloc(sizeof(struct dfs));
    p_hash tabela = criar_hash();
    p_grafo grafo = criar_grafo(MAX);

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        char vert[16]; 
        int k = 0, j= 0;

        if (linha[0] == '\n' && linha[1] == '\0') { //se linha vazia pula
            continue;
        }
        int i = 0;
        while (linha[i] != ':') {  //encontra a posicao do ':'
            i ++;
        }
        while (j < i) { //copia o vertice(vem antes do :), nao deu certo com strcpy por isso fiz manual
          vert[k ++] = linha[j];
          j ++;
        }
        vert[k] = '\0';

        int novo_id = cont;
        p_no_hash no_v = adicionar_palavra_hash(tabela, vert, 0, &cont);
        int id_vert = no_v->dado;

        if (id_vert == novo_id) {// se novo, salva o nome
            strcpy(nomes[id_vert], vert);
        }
        if (vertice_inicial[0] == '\0') { // Se ainda vazio salva ele
            strcpy(vertice_inicial, vert);
        }
        i += 2;  //pula o : e o espaço
        char palavra[16];
        k = 0;

        while (1) {
            char sinal = linha[i];
                if (sinal == ' ' || //se eh fim da palavra
                    sinal == '\n'||
                    sinal == '\0') {
                    palavra[k] = '\0';
                    int novo_id2 = cont;
                    p_no_hash no2 = adicionar_palavra_hash(tabela, palavra, 0, &cont);
                    int id2 = no2->dado;

                    if (id2 == novo_id2) {
                        strcpy(nomes[id2], palavra);
                    }
                    insere_aresta(grafo, id_vert, id2, nomes);
                    k = 0;
                } else { //se nao e faz parte da palavra e devemos copiar
                  palavra[k ++] = linha[i];
                }
                if (sinal == '\n' || sinal == '\0') {
                  break;
                }
            i ++;
        }
    }
    grafo->n = cont;  //salva os dados do grafo para as buscas
    int id = adicionar_palavra_hash(tabela, vertice_inicial, 0, &cont)->dado;

    inicia_dfs(dfs, grafo->n);
    if (detecta(grafo, id, dfs) == 1) {
        imprime_ciclo(grafo, dfs->inicio, dfs->fim, nomes, vertice_inicial, dfs->pai);
    } else {
        for (int k = 0; k < dfs->tam_ordem; k ++) {
            printf("SEQ - %d: %s\n", k + 1, nomes[dfs->ordem[k]]);
        }
        bfs(grafo, id, nomes, vertice_inicial);
    }
    free(dfs);
    liberar_hash(tabela);
    destroi_grafo(grafo);
    return 0;
}

