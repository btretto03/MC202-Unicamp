#include "code.h"
//Ao estudar as funcoes que o professor criou adicionei comentarios para melhor me achar no codigp

p_deque cria_deque() {
    p_deque d = malloc(sizeof(deque));
    d->inicio = d->fim = NULL;
    return d;
}

void insere_inicio(p_deque d, char *dado) {
    p_no novo = malloc(sizeof(No));        //ponteiro para no
    strcpy(novo->dado, dado);             //copiando dado com campo dado da nova estrutura 
    novo->prox = d->inicio;              //prox do dado de agora sera o "primeiro" 
    novo->ant = NULL;                   //ant do dado é NULL, tem ngm antes dele(agr ele é o primeiro)
    if (d->inicio != NULL)             //só executa esse if se a lista estava vazia 
        d->inicio->ant = novo;        //ponteiro ant do antigo dado aponte de volta para o dado novo
    else                             //so executa se a lista estiver vazia
        d->fim = novo;              //pont fim aponta para o novo
    d->inicio = novo;
}

void insere_fim(p_deque d, char *dado) { //funcao similiar a insere_inicio
    p_no novo = malloc(sizeof(No));
    strcpy(novo->dado, dado);
    novo->prox = NULL;
    novo->ant = d->fim;
    if (d->fim != NULL)
        d->fim->prox = novo;
    else
        d->inicio = novo;
    d->fim = novo;
}

void insere_meio(p_deque d, char *dado, int posicao, int tamanho) { //tentei seguir uma estrutura parecida com a funcao do professor para inserir e remover
    if (posicao == 0) {                                         
        insere_inicio(d, dado);
        return;                   //sem esses returns estava adicionando duas vezes
    }
    if (posicao == tamanho) {
        insere_fim(d,dado);
       return;
    }
    p_no novo = malloc(sizeof(No)); //cria o no depois dos ifs(se chamar a funcao nao precisa dar free nele pq ele nao foi criado ainda)
    strcpy(novo->dado, dado);
    p_no atual = d->inicio;
    for (int i = 0; i < posicao - 1; i ++) {
        atual = atual -> prox;
    }
    
    p_no proximo_no = atual->prox;
    novo->prox = proximo_no;
    novo->ant = atual;        //ponteiro que era anterior do novo agora é o do atual
    atual->prox = novo;
    proximo_no->ant = novo;
    }    

char* remove_inicio(p_deque d, int lugar) {
    p_no aux = d->inicio;
    char *dado = malloc(strlen(aux->dado) + 1);
    strcpy(dado, aux->dado);
    if (lugar == 0) {                            //so vai printar isso se a funcao tiver sido chamada no deque_herois.c
        printf("%s removido do inicio\n", dado);
    }
    d->inicio = d->inicio->prox;
    if (d->inicio != NULL)
        d->inicio->ant = NULL;
    else
        d->fim = NULL;
    free(aux);
    return dado;
}

char* remove_fim(p_deque d, int lugar) {
    p_no aux = d->fim;
    char *dado = malloc(strlen(aux->dado) + 1);
    strcpy(dado, aux->dado);
    if (lugar == 0) {
        printf("%s removido do fim\n", dado);
    }
    d->fim = d->fim->ant;
    if (d->fim != NULL)
        d->fim->prox = NULL;
    else
        d->inicio = NULL;
    free(aux);
    return dado;
}

void remove_meio(p_deque d, int posicao, int tamanho) {
    if (posicao == 0) {
        char* dado = remove_inicio(d, 1);
        printf("%s removido da posicao %d\n", dado, posicao);
        free(dado);
        return;
    }
    if (posicao == tamanho - 1) {
        char* dado = remove_fim(d, 1);
        printf("%s removido da posicao %d\n", dado, posicao);
        free(dado);
        return;
    }

    p_no atual = d->inicio;
    for (int i = 0; i < posicao - 1; i ++) {                              //percorre os elementos do deque até um antes daquele que será removido
        atual = atual->prox;
    }

    p_no removido = atual->prox;                                       //Cria um ponteiro que aponta para o nó que será removido
    printf("%s removido da posicao %d\n", removido->dado, posicao);               
    atual->prox = removido->prox;                                    //o prox do no atual agora aponta para o nó depois do que será removido
    p_no proximo_no = removido->prox;                               //aponta para o no depois que será removido
    proximo_no->ant = atual;                                       //O prox do anterior que sera removido liga 
    free(removido);
}

void troca_inicio_fim(p_deque d){
    char *dado = remove_inicio(d, 1);                         //Remove o personagem do inicio e guarda seu nome, como nao quero o  print em remove_inicio, preciso colocar lugar = 1
    insere_fim(d, dado);                                    //Adiciona esse heroi no fim da fila
    printf("%s atacou e foi para o fim\n", dado); 
    free(dado);
}

void imprime_guerreiros(p_no deque) {
    p_no atual;
    printf("ordem de ataque:");
    for (atual = deque; atual != NULL; atual = atual -> prox) {
        printf(" %s", atual -> dado);
    }
    printf("\n");
}

void limpa_deque(p_deque d) {
    p_no atual = d->inicio;
    while (atual != NULL) {
        p_no proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(d);
}

p_no inverte_comeco(p_deque d, int prefixo) {                                        //funcao do professor para lista ligada adaptada para o deque
    p_no atual = d->inicio, ant, ponteiro_print = d->inicio, invertida = NULL;      //invertida comeca como 0 e se torna o ponteiro pra nova lista pronta no final
    p_no ant_invertido = d->inicio;                                                //guarda o endereço do no original
  

    printf("caos ");
    for (int i = 0; i < prefixo; i ++) {
            printf("%s ", ponteiro_print -> dado);
            ponteiro_print = ponteiro_print -> prox;
    }
    printf("-> ");

    int cont = 0;                             
    while (cont < prefixo) {                      //Deque A-B-C
        ant = atual;                             //ant -> A
        atual = ant->prox;                      //atual -> B
        ant->prox = invertida;                 //prox do A -> lista invertida(Null ou no anterior depende se ela ja tem algum elemento)
        if (invertida != NULL) {              
            invertida->ant = ant;              
        }
        ant->ant = NULL;                     //A como primeiro elemento da invertida
        invertida = ant;                    //lista invertida agora tem A
        cont ++;                           //repete pra tods outros ate o contador estourar
    }
    d->inicio = invertida;
    ant_invertido->prox = atual;

    if (atual == NULL) {                    //se prefixo = tamanho nao sobra nenhum no e o ultimo d alista vira d->fim
        d->fim = ant_invertido; 
    }else{
        atual->ant = ant_invertido;
    }

    ponteiro_print = d->inicio;
    for (int i = 0; i < prefixo; i ++) {
        printf("%s ", ponteiro_print -> dado);
        ponteiro_print = ponteiro_print -> prox;
    }
    printf("\n");
    return d->inicio;
}

p_no inverte_fim(p_deque d, int sufixo) {                      
    p_no atual, ant, ponteiro_print = d -> fim, invertida = NULL;     
    p_no ant_invertido = d->fim;

    for (int i = 0; i < sufixo - 1; i ++) {              //basicamenta a funcao anterior mas comeca de tras pra frente e percorre sufixo - 1 posicoes pra comecar a inverter
        ant_invertido = ant_invertido -> ant;
        ponteiro_print = ponteiro_print -> ant;
    }
    p_no no_anterior = ant_invertido->ant;

    printf("confusao ");
    for (int i = 0; i < sufixo; i ++) {
            printf("%s ", ponteiro_print -> dado);
            ponteiro_print = ponteiro_print -> prox;
    }
    printf("-> ");

    int cont = 0;                             
    atual = ant_invertido;                          //começa apontando pro inicio da lista do fim

    while (atual != NULL && cont < sufixo) {      //Deque A-B-C
        ant = atual;                             //ant -> A
        atual = ant->prox;                      //atual -> B
        ant->prox = invertida;                 //prox do A -> lista invertida(Null ou no anterior depende se ela ja tem algum elemento)
        if (invertida != NULL) {               
            invertida->ant = ant;              
        }
        ant->ant = NULL;                    //A como primeiro elemento da invertida
        invertida = ant;                   //lista invertida agora tem a
        cont ++;                           
    }
    if (no_anterior != NULL) {
        no_anterior->prox = invertida;
        invertida->ant = no_anterior;
        
    }else {
    d->inicio = invertida;           //se ainda nao existe no anterior o invertida vira o inicio
    
}          

    d->fim = ant_invertido;
    d->fim->prox = NULL;        //o ponteiro final deve ser NULL diferente do caso anterior

    ponteiro_print = invertida;
    for (int i = 0; i < sufixo; i ++) {
        printf("%s ", ponteiro_print -> dado);
        ponteiro_print = ponteiro_print -> prox;
    }
    printf("\n");

    return d->inicio;
}

