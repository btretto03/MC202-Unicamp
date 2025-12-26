#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "code.h"
#define MAX_TAGS 30

int main() {
    int posicao = 0;
    p_hash_arquivos h_arq = criar_hash_arq();
    p_hash_tags h_tag = criar_hash_tags();

    while(1) {
        char comando1[17], comando2[17];
        scanf("%s", comando1);

        if (strcmp(comando1, "INSERIR") == 0) {
            scanf("%s", comando2);
            if(strcmp(comando2, "ARQUIVO") == 0) {
                char nome[31];
                char descricao[101];
                int quant_tags;
                char tags_nomes[MAX_TAGS][31];

                scanf(" %s", nome);
                scanf(" %[^\n]", descricao);
                scanf("%d", &quant_tags);

                for (int i = 0; i < quant_tags; i ++) {
                    scanf("%s", tags_nomes[i]);
                }
                posicao ++;
                p_arquivo novo_arq = criar_arquivo(nome, descricao, posicao);
                
                adicionar_arquivo(novo_arq, h_arq, 0);
                for (int i = 0; i < quant_tags; i ++) {
                    inserir_tag(h_arq, h_tag, nome, tags_nomes[i]);
                }
            
            } else if (strcmp(comando2, "TAG") == 0) {
                char nome[31];
                char tag[31];
                scanf(" %s %s", nome, tag);
                inserir_tag(h_arq, h_tag, nome, tag);
            }

        } else if (strcmp(comando1, "REMOVER") == 0) {
            scanf("%s", comando2);
            if (strcmp(comando2, "ARQUIVO") == 0){
                char nome[31];
                scanf(" %s", nome);
                remover_arquivo(h_arq, h_tag, nome);

            } else if (strcmp(comando2, "TAG")== 0) {
                char nome[31];
                char tag[31];
                scanf(" %s %s", nome, tag);
                remover_tag(h_arq, h_tag, nome, tag);
            }

        } else if (strcmp(comando1, "ALTERAR") == 0) {
            scanf("%s", comando2);
            if (strcmp(comando2, "ARQUIVO") == 0) {
            char nome[31];
            char novo_nome[31];
            char nova_desc[101];
            scanf(" %s", nome);
            scanf(" %s", novo_nome);
            scanf(" %[^\n]", nova_desc);
            alterar_arquivo(h_arq, h_tag, nome, novo_nome, nova_desc);
            }

        } else if (strcmp(comando1, "BUSCAR") == 0) {
            scanf("%s", comando2);
            if (strcmp(comando2, "TAG") == 0){
                char nome_tag[31];
                scanf(" %s", nome_tag);
                print_buscar_tag(h_tag, nome_tag);
            } else if (strcmp(comando2, "ARQUIVO") == 0) {
                char nome[31];
                scanf(" %s", nome);
                print_buscar_arquivo(h_arq, nome);
            }

        } else if (strcmp(comando1, "ENCERRAR") == 0) {
            liberar_hasharq(h_arq);
            liberar_hashtags(h_tag);
            break;
        }
    }
    return 0;
}