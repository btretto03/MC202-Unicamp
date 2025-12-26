#ifndef HASHTAGS_C
#define HASHTAGS_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAM_ARQ 4273
#define TAM_TAGS 89

typedef struct arquivo *p_arquivo;
typedef struct tag *p_tag; 
typedef struct arquivo Arquivo;

struct arquivo {
    char nome[31], desc[101];
    int num_tags;
    int posicao; //ideia tirada de uma duvida de alguem no discord para guardar a posicao usada na funcao busca :)
    p_tag tags[30];
};

struct tag {
    char nome[31];
    int num_arq;
    p_arquivo arquivos[2000];
};
typedef struct tag Tag;

typedef struct hash_arquivos *p_hash_arquivos;
typedef struct hash_tags *p_hash_tags; 

struct hash_arquivos {
    p_arquivo *itens;
    int tamanho_tot, tamanho_at;
    int *estado;                //-1 vazio, 0 ocupado, 1 removido
};

struct hash_tags {
    p_tag *itens;
    int tamanho_tot, tamanho_at;
    int *estado;                //-1 vazio, 0 ocupado, 1 removido
};

//Funcao hash (a mesma da aula do professor)
int hash(char *chave, int tamanho_tabela);

//Funcoes responsaveis por criar os arquivos e as tags
p_arquivo criar_arquivo(char nome[], char desc[], int posicao);
p_tag criar_tag(char nome[]);

//Funcoes responsaveis por criar os hashs de arquivos e tags
p_hash_arquivos criar_hash_arq();
p_hash_tags criar_hash_tags();

//fucoes para adicionar tags e arquivos nos hashs
p_tag adicionar_tag(p_tag tag, p_hash_tags h_tag, int k);
p_arquivo adicionar_arquivo(p_arquivo arq, p_hash_arquivos h_arq, int k);

//Funcoes para buscar tags e arquivos
p_arquivo buscar_arq(p_hash_arquivos h_arq, char *nome, int k);
p_tag buscar_tag(p_hash_tags h_tag, char *nome, int k);

//Funcoes para printar igual o enunciado pede
void print_buscar_tag(p_hash_tags h_tag, char *tag);
void print_buscar_arquivo(p_hash_arquivos h_arq, char *nome);

//funcoes que inserem e removem tags da lista de um arquivo especifico
void inserir_tag(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome, char *nome_tag);
void remover_tag(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome, char *nome_tag);

//Funcao que remove arquivo de uma tag especifica
void remover_arquivo(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome);

//Funcao responsavel por alterar arquivos conforme o enunciado
void alterar_arquivo(p_hash_arquivos h_arq, p_hash_tags h_tag, char *nome_atual, char *novo_nome, char *nova_desc);

//FUncoes responsaveis por liberar a memoria dos hash das tags
void liberar_hasharq(p_hash_arquivos h_arq);
void liberar_hashtags(p_hash_tags h_tag);

#endif