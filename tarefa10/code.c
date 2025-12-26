#include "code.h"

//Funcoes grafo
p_grafo criar_grafo(int n) {  //Funcao criar grafo da aula
    int i;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));
    g->pesos = malloc(n * sizeof(int));
    for (i = 0; i < n; i  ++)
        g->adjacencia[i] = NULL;
    return g;
}

p_no insere_na_lista(p_no lista, int v) { //Funcao de aula
    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void inserir_aresta(p_grafo g, int u, int v) { //funcao da aula
    g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
    g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
}

void libera_lista(p_no lista) {  //Funcao de aula kiliar para a destroi grafo
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g) { //Funcao da aula para liberar a memoria do grafo
    for (int i = 0; i < g->n; i  ++)
        libera_lista(g->adjacencia[i]);
    free(g->adjacencia);
    free(g->pesos);
    free(g);
}

//Funcoes do backtracking
int verifica_caminho(p_grafo g, int v, int *grupo, int tam) {
    int teste = 1; //assume que tem ligacao entre dois vertices
    
    for (int i = 0; i < tam; i ++) {
        int atual = grupo[i];
        p_no lista = g->adjacencia[v]; // pega a lista dos vizinhos doatual
        int achou_vizinho = 0; //se tem conexao entre v e o atual
        
        while (lista != NULL) { //procura o vertice atual
            if (lista->v == atual) {
                achou_vizinho = 1; //tem conexao
                break; 
            }
            lista = lista->prox;
        }
        if (achou_vizinho == 0) { //se percorreu tudo e nao achou
            teste = 0;
            break;
        }
    }
    if (teste ==1) {
        return 1;
    } else {
        return 0;
    }
}

void chute_inicial(p_grafo grafo, p_dados d) {
    d->peso = -1;
    d->tam = 0;

    for (int i = 0; i < grafo->n; i ++) { // testa todos vertices
        int soma = grafo->pesos[i];
        d->teste[0] = i; //coloca no grupo de teste
        int tamanho = 1;

        for (int j = 0; j < grafo->n; j ++) { //tenta adicionar outros
            if (j != i) {
                if (verifica_caminho(grafo, j, d->teste, tamanho) == 1) {
                    d->teste[tamanho] = j; //adiciona j
                    tamanho ++;
                    soma += grafo->pesos[j]; //soma o peso do j
                }
            }
        }
        if (soma > d->peso) { //se a soma for maior que a anteriro
            d->peso = soma;
            d->tam = tamanho;
            for (int k = 0; k < tamanho; k ++) {
                d->resposta[k] = d->teste[k];
            }
        }
    }
}

int poda_milagrosa(p_grafo g, int v) { //dica milagrosa do professor Schouery no discord que salvou o time limit faltando 3h pra entregar a tarefa
    int soma = 0;
    p_no vizinho = g->adjacencia[v]; //lista de vizinhos
    while (vizinho != NULL) {
        if (vizinho->v > v) {
            soma += g->pesos[vizinho->v];
        }
        vizinho = vizinho->prox;
    }
    return soma;
}

void backtracking(p_grafo grafo, p_dados d, int inicio, int peso_atual, int tam) {
    int i = inicio; 
    if (peso_atual > d->peso) { //se for maior que o que esta guardado troca
        d->peso = peso_atual; 
        d->tam = tam;
        for (int k = 0 ; k < tam; k ++) { //copia para a resposta
            d->resposta[k] = d->teste[k];
        }
    }
    while (i < grafo->n) { //agora vai pros vertices restantes
        int soma_proximos = poda_milagrosa(grafo, i);
        if (peso_atual + grafo->pesos[i] + soma_proximos <= d->peso) {
            i ++;
            continue; // Vai pro proximo
        }
        if (verifica_caminho(grafo, i, d->teste, tam) == 1) { //se tem conexao add
            d->teste[tam] = i;
            backtracking(grafo, d, i + 1, peso_atual + grafo->pesos[i], tam + 1);
        }
        i ++;
    }
}

void insertionsort_v2(int *v, int n) { //funcao de aula para ordenar
    int i, j, t;
    for (i = 1; i < n; i ++) {
        t = v[i];
        for (j = i; j > 0 && t < v[j - 1]; j --)
            v[j] = v[j - 1];
        v[j] = t;
    }
}

void imprime_resultado(p_dados d) {
    printf("%d\n", d->peso);
    insertionsort_v2(d->resposta, d->tam);
    for (int i = 0; i < d->tam; i ++) {
        printf("%d", d->resposta[i]);
        if (i < d -> tam - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void rodar_backtracking(p_grafo g, p_dados d) {
    chute_inicial(g, d);
    backtracking(g, d, 0, 0, 0);
    imprime_resultado(d);
}