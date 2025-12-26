#include "code.h"
#define MAX 5001

//tabela hash(funcoes de hash da ultima tarefa adaptadas)
int hash(char *chave) {      //Funcao hash
    int n = 0;
    for (int i = 0; i < strlen(chave); i ++)
        n = (256 * n + abs(chave[i])) % MAX_HASH; 
    return n;
}

p_no_hash criar_palavra_hash(char chave[], int dado) {
    p_no_hash novo = malloc(sizeof(struct no_hash));
    strcpy(novo->chave, chave);
    novo->dado = dado;
    return novo;
}

p_hash criar_hash() {
    p_hash tab = malloc(sizeof(struct hash));
    tab->tamanho_tot = MAX_HASH;
    tab->tamanho_at = 0;
    tab->nome = malloc(tab->tamanho_tot * sizeof(p_no_hash));
    tab->estado = malloc(tab->tamanho_tot * sizeof(int));
    for (int i = 0; i < tab->tamanho_tot; i ++) {
        tab->estado[i] = -1;    //vazio
        tab->nome[i] = NULL;
    }
    return tab;
}

p_no_hash adicionar_palavra_hash(p_hash tab, char *chave, int k, int *dado) {
    int num = hash(chave);
    int recursao = num + k;

    if (recursao >= tab->tamanho_tot) {                          //se percorreu a lista toda volta pro começo 
        recursao -= tab->tamanho_tot;
    }

    if (tab->estado[recursao] == -1) {                             //se esta vazio(-1) a palavra nao esta no hash
        p_no_hash novo = criar_palavra_hash(chave, *dado);
        tab->nome[recursao] = novo;
        tab->estado[recursao] = 0;
        tab->tamanho_at ++;
        (*dado) ++;
        return novo;
    }
    if (tab->estado[recursao] == 0) {                            //se esta ocupado pode ser colisao ou ja ter a mesma palavra
        if (strcmp(tab->nome[recursao]->chave, chave) == 0) {    //se for a memsa palavra
            return tab->nome[recursao]; 
        } else {
            return adicionar_palavra_hash(tab, chave, k + 1, dado);  //se for colisao chama a funcao para inserir novamente

        }
    }
    return adicionar_palavra_hash(tab, chave, k + 1, dado);
}

void liberar_hash(p_hash tab) {
    for (int i = 0; i < tab->tamanho_tot; i++) {
        if (tab->estado[i] == 0) {
            free(tab->nome[i]);
        }
    }
    free(tab->nome);
    free(tab->estado);
    free(tab);
}

//fila(aplicando as funcoes exatamente iguais as dos slides)
 p_fila criar_fila(int N) {
    p_fila f;
    f = malloc(sizeof(struct fila));
    f->v = malloc(N * sizeof(int));
    f->ini = 0;
    f->fim = 0;
    f->N = N;
    f->tamanho = 0;
    return f;
}

void enfileira(p_fila f, int valor) {
    f->v[f->fim] = valor;
    f->fim = (f->fim + 1) % f->N;
    f->tamanho++;
}

int desenfileira(p_fila f) {
    int valor = f->v[f->ini];
    f->ini = (f->ini + 1) % f->N;
    f->tamanho--;
    return valor;
}

void destroi_fila(p_fila f) {
    free(f->v);
    free(f);
}

//grafo
p_grafo criar_grafo(int n) {  //Funcao criar grafo da aula
    int i;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));
    for (i = 0; i < n; i ++)
        g->adjacencia[i] = NULL;
    return g;
}

p_no insere_na_lista(p_no lista, int v) { //Funcao de aula
    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void insere_aresta(p_grafo g, int u, int v, char nomes[MAX][16]) {
    char *nome_v = nomes[v];
    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = NULL;

    if (g->adjacencia[u] == NULL) { //se a lista ainda nao tem nenhum elemento
        g->adjacencia[u] = novo;
        return;
    }
    if (strcmp(nome_v, nomes[g->adjacencia[u]->v]) < 0) { // se for menor que o primeiro da lista
        novo->prox = g->adjacencia[u];
        g->adjacencia[u] = novo;
        return;
    } else {
        p_no p = g->adjacencia[u]; // começa no primeiro nó
        if (p->prox == NULL) {    //a lista tem 1 elemento
            p->prox = novo;
            return;
        }
        while (strcmp(nome_v, nomes[p->prox->v]) > 0) { //a lista tem mais elementos
            p = p->prox;
            if (p->prox == NULL) {  // chegou no último
                p->prox = novo;
                return;
        }
    }
        novo->prox = p->prox;   // liga novo ao nó seguinte
        p->prox = novo;         // liga p ao novo
    }
}

int detecta(p_grafo g, int u, p_dfs dfs) { //retorna 1 se um ciclo for encontrado e 0 caso nao 
    dfs->caminho[u] = 1; //marca o que vamos analisar
    p_no p = g->adjacencia[u]; //primeiro vizinho de u

    while (p != NULL) { //percorre todos vizinhos
        int vizinho_atual = p->v;
        if (dfs->visitado[vizinho_atual] == 0) { //ainda tem vizinhos nao visitados
            if (dfs->caminho[vizinho_atual] == 0) { //se é novo
                dfs->pai[vizinho_atual] = u;
                if (detecta(g, vizinho_atual, dfs) == 1) {  //chama a recursao para o vizinho
                    return 1; //se achou ciclo para
                }
            } else {
                dfs->ciclo = 1;
                dfs->inicio = u;
                dfs->fim = vizinho_atual;
                return 1;
            }
        }
        p = p->prox; //vai pro prox vizihno
    }

    dfs->caminho[u] = 0; //0 marca que nao esta mais na recursao
    dfs->visitado[u] = 1; //marca o vertice q pegamos no inicio como totalemnte visitado
    dfs->ordem[dfs->tam_ordem ++] = u; //adiciona o vertice na lista de ordenacao
    return 0; //nenhum ciclo nesse caminho
}

void imprime_ciclo(p_grafo g, int inicio, int fim, char nomes[MAX][16], char alvo[], int *pai) {
    int ciclo_v[MAX];
    int tam = 0;
    int atual = inicio; //indice que achou o ciclo

    while (atual != fim) { //faz o percurso ate primeiro vertice do ciclo
        ciclo_v[tam ++] = atual;
        atual = pai[atual];
    }
    ciclo_v[tam ++] = fim; //o ultimo vertice do ciclo
    for (int i = 0; i < tam / 2; i ++) { //inverte o vetor dos vertices
        int troca = ciclo_v[i];
        ciclo_v[i] = ciclo_v[tam - 1 - i];
        ciclo_v[tam - 1 - i] = troca;
    }
     
    int id_min = 0; //aqui vai botar na ordem lexografica que o enunciado pede
    for (int i = 1; i < tam; i ++) {
        if (strcmp(nomes[ciclo_v[i]], nomes[ciclo_v[id_min]]) < 0) {
            id_min = i;
        }
    }
    printf("Erro: dependências circulares entre os arquivos necessários para construir '%s'\n", alvo);
    printf("Ciclo: ");
    for (int i = id_min; i < tam; i ++) {
        printf("%s -> ", nomes[ciclo_v[i]]);
    }
    for (int i = 0; i < id_min; i ++) {
        printf("%s -> ", nomes[ciclo_v[i]]);
    }
    printf("%s\n", nomes[ciclo_v[id_min]]);
}

void inicia_dfs(p_dfs dfs, int N) {
    dfs->tam_ordem = 0; //conta quanto s nos tem para ordenacao
    dfs->ciclo = 0; //indica se tem ciclo
    dfs->inicio = -1; //guarda id do inicio
    dfs->fim = -1; //guarda id do fim

    for (int i = 0; i < N; i ++) { 
        dfs->visitado[i] = 0; //incia como nao visitado
        dfs->caminho[i] = 0;
        dfs->pai[i] = -1; //sem ninguem antes do pai
    }
}

void dfs(p_grafo g, int inicio, char nomes[MAX][16], char alvo[], int N) {
    p_dfs dfs = malloc(sizeof(struct dfs));
    inicia_dfs(dfs, N);
    detecta(g, inicio, dfs);

    if (dfs->ciclo == 1) { //se achou o ciclo
        imprime_ciclo_completo(g, dfs->inicio, dfs->fim, nomes, alvo, dfs->pai);
    } else { // se nao
        for (int k = dfs->tam_ordem - 1; k >= 0; k --) {
            printf("SEQ - %d: %s\n", dfs->tam_ordem - k, nomes[dfs->ordem[k]]);
        }
    }
    free(dfs);
}

void insertionsort_v2(int *v, int n, char nomes[MAX][16]) { //funcao para ordenar do slide professor
    int i, j, t;
    for (i = 1; i < n; i ++) {
        t = v[i];
        for (j = i; j > 0 && strcmp(nomes[t], nomes[v[j - 1]]) < 0; j --)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void calcula_distancias(p_grafo g, int s, int dist[MAX]) {
    int visitado[MAX];
    for (int i = 0; i < g->n; i ++) { //inicia todos vertices como:
        dist[i] = -1; //sem distancias
        visitado[i] = 0; //nao visitados
    }
    p_fila f = criar_fila(g->n); //cria a fila
    enfileira(f, s);
    dist[s] = 0;
    visitado[s] = 1;
    while (f->tamanho > 0) { //percorrer por todos vertices
        int v = desenfileira(f);
        p_no p = g->adjacencia[v]; //percorre os vizinhos de v
        while (p != NULL) {
            int w = p->v;
            if (visitado[w] == 0) {
                visitado[w] = 1;
                dist[w] = dist[v] + 1;
                enfileira(f, w);
            }
            p = p->prox;
        }
    }
    destroi_fila(f);
}

void imprime_distancias(p_grafo g, int dist[MAX], char nomes[MAX][16], char alvo[]) {
    int maior_dist = 0;
    for (int k = 0; k < g->n; k ++) { //encontra a maior distancia
        if (dist[k] > maior_dist) {
            maior_dist = dist[k];
        }
    }
    for (int nivel = 0; nivel <= maior_dist; nivel ++) { //percorre todos os niveis
        int lista[MAX];
        int tam = 0;
        for (int k = 0; k < g->n; k ++) { //pega todos os nos com essa distancia
            if (dist[k] == nivel) { 
                lista[tam ++] = k;
            }
        }
        insertionsort_v2(lista, tam, nomes);
        for (int i = 0; i < tam; i ++) {
            printf("Distância até %s - %d: %s\n", alvo, nivel, nomes[lista[i]]);
        }
    }
}

void bfs(p_grafo g, int s, char nomes[MAX][16], char alvo[]) {
    int dist[MAX];
    calcula_distancias(g, s, dist);
    imprime_distancias(g, dist, nomes, alvo);
}

void libera_lista(p_no lista) {  //Funcao de aula auxiliar para a destroi grafo
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g) { //Funcao da aula para liberar a memoria do grafo
    for (int i = 0; i < g->n; i ++)
        libera_lista(g->adjacencia[i]);
    free(g->adjacencia);
    free(g);
}