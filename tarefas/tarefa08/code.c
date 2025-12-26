#include "code.h"

p_arquivo criar_arquivo(char nome[], char desc[], int posicao) {
    p_arquivo novo = malloc(sizeof(Arquivo));
    strcpy(novo->nome, nome);
    strcpy(novo->desc, desc);
    novo->num_tags = 0;
    novo->posicao = posicao;
    return novo;
}

p_tag criar_tag(char nome[]) {
    p_tag novo = malloc(sizeof(Tag));
    strcpy(novo->nome, nome);
    novo->num_arq = 0;
    return novo;
}

int hash(char *chave, int tamanho_tabela) { //Funcao hash da aula
    int n = 0;
    for (int i = 0; i < strlen(chave); i ++)
        n = (256 * n + abs(chave[i])) % tamanho_tabela; //"ç" estava dando negativo, por isso o abs
    return n;
}

p_hash_arquivos criar_hash_arq() {
    p_hash_arquivos novo = malloc(sizeof(struct hash_arquivos));
    novo->tamanho_tot = TAM_ARQ;
    novo->tamanho_at = 0;
    novo->itens = malloc(novo->tamanho_tot * sizeof(p_arquivo));
    novo->estado = malloc(novo->tamanho_tot * sizeof(int));
    for (int i = 0; i < novo->tamanho_tot; i ++) {
        novo->itens[i] = NULL;
        novo->estado[i] = -1;                 //vazio
    }
    return novo;
}

p_hash_tags criar_hash_tags() {
    p_hash_tags novo = malloc(sizeof(struct hash_tags));
    novo->tamanho_tot = TAM_TAGS;
    novo->tamanho_at = 0;
    novo->itens = malloc(novo->tamanho_tot * sizeof(p_tag));
    novo->estado = malloc(novo->tamanho_tot * sizeof(int));
    for (int i = 0; i < novo->tamanho_tot; i ++) {
        novo->itens[i] = NULL;
        novo->estado[i] = -1;
    }
    return novo;
}

p_arquivo adicionar_arquivo(p_arquivo arq, p_hash_arquivos h_arq, int k) { //funcao que adiciona arquivo no hash dos arq
    int num = hash(arq->nome, h_arq->tamanho_tot);
    int recursao = num + k;              //comeca com 0 e se tem colisao k++
    if (recursao >= h_arq->tamanho_tot) { //se chegar no final da tabela volta para a posicao 0 dela
        recursao -= h_arq->tamanho_tot;
    }
    if(h_arq->estado[recursao] == -1 || h_arq->estado[recursao] == 1) { //vazio ou removido
        h_arq->estado[recursao] = 0; //agora esta ocupado
        h_arq->itens[recursao] = arq;
        arq->posicao = recursao;
        h_arq->tamanho_at++;
        return arq;
    } else{                                            //se estiver ocupado
        return adicionar_arquivo(arq, h_arq, k + 1);    //skill recursao desbloqueada na tarefa da arvore kkk
    }
}

p_tag adicionar_tag(p_tag tag, p_hash_tags h_tag, int k) { //funcao que adiciona tag no hash das tags(identica a de cima)
    int num = hash(tag->nome, h_tag->tamanho_tot);
    int recursao = num + k;
    if (recursao >= h_tag->tamanho_tot) {
        recursao -= h_tag->tamanho_tot;
    }
    if(h_tag->estado[recursao] == -1 || h_tag->estado[recursao] == 1) {
        h_tag->estado[recursao] = 0; 
        h_tag->itens[recursao] = tag;
        h_tag->tamanho_at++; 
        return tag;
    } else{                                            //se estiver ocupado
        return adicionar_tag(tag, h_tag, k + 1);
    }
}

p_arquivo buscar_arq(p_hash_arquivos h_arq, char *nome, int k) {  //funcao auxiliar logica muito parecida com a adiciona
    int num = hash(nome, h_arq->tamanho_tot); 
    int recursao = num + k;
    if (k >= h_arq->tamanho_tot) {     //nao achou o arquivo percorrendo toda lista retorna null
        return NULL; 
    }
    if (recursao >= h_arq->tamanho_tot) {
        recursao -=h_arq-> tamanho_tot;
    }
    if (h_arq->estado[recursao] == -1) {        //se estiver vazio nao esta no hash
        return NULL;
    }
    if (h_arq->estado[recursao] == 0) {                          //se esta ocupado
        if (strcmp(h_arq->itens[recursao]->nome, nome) == 0) {   //se nao for colisao
            return h_arq->itens[recursao];                       //elemento da busca
        }
    }
    return buscar_arq(h_arq, nome, k + 1);          //se for removido(1) ou colisao, continua
}

p_tag buscar_tag(p_hash_tags h_tag, char *nome, int k) {  //funcao auxiliar logica muito parecida com a adiciona
    int num = hash(nome, h_tag->tamanho_tot); 
    int recursao = num + k;
    if (k >= h_tag->tamanho_tot) {
        return NULL; 
    }
    if (recursao >= h_tag->tamanho_tot) {
        recursao -=h_tag-> tamanho_tot;
    }
    if (h_tag->estado[recursao] == -1) { 
        return NULL;
    }
    if (h_tag->estado[recursao] == 0) {
        if (strcmp(h_tag->itens[recursao]->nome, nome) == 0) {
            return h_tag->itens[recursao];
        }
    }
    return buscar_tag(h_tag, nome, k + 1);
}

void print_buscar_tag(p_hash_tags h_tag, char *nome_tag) {
    printf("Busca por tag: %s\n", nome_tag);
    p_tag tag = buscar_tag(h_tag, nome_tag, 0);
    if (tag == NULL || tag->num_arq == 0) {
        printf("0 resultados encontrados.\n");
    } else { 
        for (int i = 0; i < tag->num_arq; i ++) {
            printf("%s\n", tag->arquivos[i]->nome);
        }
    }
    printf("----------\n");
}

void print_buscar_arquivo(p_hash_arquivos h_arq, char *nome) {
    printf("Acessando arquivo: %s\n", nome);
    p_arquivo arq = buscar_arq(h_arq, nome, 0);
    if (arq == NULL) {
        printf("Arquivo %s não existe.\n", nome);
    } else {
        printf("Descrição: %s\nTags:", arq->desc);
        for (int i = 0; i < arq->num_tags; i ++) {
            printf(" %s", arq->tags[i]->nome);
        }
        printf(" \n");
    }
    printf("----------\n");
}

void inserir_tag(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome, char *nome_tag) {
    p_arquivo arq = buscar_arq(h_arq, nome, 0);
    p_tag tag = buscar_tag(h_tag, nome_tag, 0);
    if (tag == NULL) {              //se a tag nao existir cria ela
        tag = criar_tag(nome_tag);
        tag->arquivos[0] = arq;
        tag->num_arq = 1;
        adicionar_tag(tag, h_tag, 0);
    } else {                            //se ela existir adiciona o arquivo na lista dela
        tag->arquivos[tag->num_arq] = arq;
        tag->num_arq++;
    }
    arq->tags[arq->num_tags] = tag;
    arq->num_tags++;
}

void remover_tag(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome, char *nome_tag) {
    p_arquivo arq = buscar_arq(h_arq, nome, 0);
    p_tag tag = buscar_tag(h_tag, nome_tag, 0);
   
    for (int i = 0; i < arq->num_tags; i ++) {  //remove a tag da lista de arq
        if (arq->tags[i] == tag) {
            for (int k = i; k < arq->num_tags - 1; k ++) { //move todas a direita da tag a ser removida pra esq
                arq->tags[k] = arq->tags[k + 1];
            }
            arq->num_tags--;
            break;
            }
        }
    for (int i = 0; i < tag->num_arq; i ++) {   //remove o arquivo da lista da tag
        if (tag->arquivos[i] == arq) {
            for (int k = i; k < tag->num_arq -1; k ++) {
                tag->arquivos[k] = tag->arquivos[k + 1];
            }
            tag-> num_arq--;
            break;
        }
    }
}

void remover_arquivo(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome) {
    p_arquivo arq = buscar_arq(h_arq, nome, 0);
    for (int i = 0; i < arq->num_tags; i ++) { //tira o arq da lista de cada tag
        p_tag tag = arq->tags[i];
        for (int k = 0; k < tag->num_arq; k ++) {   //desloca todos os arquivos da direita dele(removido) para esq
            if (tag->arquivos[k] == arq) {
                for (int j = k; j < tag->num_arq - 1; j ++) {
                    tag->arquivos[j] = tag->arquivos[j + 1];
                }
                tag-> num_arq--;
                break;
            }
        }
    }
    h_arq->estado[arq->posicao] = 1; //marca como removido
    h_arq->tamanho_at--;
    free(arq);
}

void alterar_arquivo(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome_atual, char *novo_nome, char *nova_desc) {
    p_arquivo arq = buscar_arq(h_arq, nome_atual, 0);
    strcpy(arq->desc, nova_desc);
    h_arq->estado[arq->posicao] = 1; //marca a posicao antiga como removido
    h_arq->tamanho_at--;
    strcpy(arq->nome, novo_nome);

    adicionar_arquivo(arq, h_arq, 0);
}

void liberar_hasharq(p_hash_arquivos h_arq) {
    for (int i = 0; i < h_arq->tamanho_tot; i ++) {
        if (h_arq->estado[i] == 0) {
            free(h_arq->itens[i]); 
        }
    }
    free(h_arq->itens);
    free(h_arq->estado);
    free(h_arq);
}

void liberar_hashtags(p_hash_tags h_tag) {
    for (int i = 0; i < h_tag->tamanho_tot; i ++) {
        if (h_tag->estado[i] == 0) {
            free(h_tag->itens[i]);
        }
    }
    free(h_tag->itens);
    free(h_tag->estado);
    free(h_tag);
}