#include "code.h"

p_no criar_no() {                       //Funcao que cria o no
    p_no d = malloc(sizeof(struct no));
    d->esq = d->dir= NULL;
    d->altura = 1;
    d->dna = NULL;
    return d;
}

int maximo(int a, int b) {            //funcao para decidir o valor maximo(como ela é auxiliar nao sei se devia coloca-la no .h)
    if(a > b) {                       //tiveram mais funcoes que estao aqui e nao estao no .h por só serem usadas por outras funcoes e nao na main em si
        return a;
    } else {
        return b;
    }
}

p_no criar_arvore(char *dna, int tamanho, int max) {                                     //funcao recursiva que cria a arvore(ela fica da direita pra esquerda, inverso de como esta nas imagens da terefa, mas acho que funciona da mesma forma)
    if (tamanho <= max) {                                                                //tamanho <= max funcao chegou ao fim
        p_no folha = criar_no();
        folha->dna = malloc((tamanho + 1) * sizeof(char));  
        for (int i = 0; i < tamanho; i ++) {                                             //copia a parte do dna para a folha(eu nao consegui usar a funcao strcpy, dá erro, pedir na monitoria pq n da)
            folha->dna[i] = dna[i];
        }
        folha->dna[tamanho] = '\0';
        folha->chave = tamanho;
        folha->altura = 1;                                                               //definido na tarefa que a altura das folhas é 1
        return folha;
        
    } else {
        int meio = tamanho / 2;
        p_no interno = criar_no();
        interno->esq = criar_arvore(dna, meio, max);                                    //cria a subarvore esquerda
        interno->dir = criar_arvore(dna + meio, tamanho - meio, max);                   //cria a subarvore direita
        interno->chave = meio;
        interno->altura = 1 + maximo(interno->esq->altura, interno->dir->altura);       //definido na tarefa 
        return interno;
    }
}


void print_all(p_no no) {
    if (no == NULL) {            //Caso base da recursao
        return;
    }
    print_all(no->esq);          // subarvore da esquerda
    if (no->esq == NULL && no->dir == NULL) { //se é uma folha tem dna e precisamos imprimir ele
        printf("%s", no->dna);
    }
    print_all(no->dir);          // subarvore da direita
}

void print_pedaco(p_no no, int posicao_i, int posicao_f, int *posicao) { //fucao parecida com a de cima mas agora tem um ponteiro para guardar a posicao dos elementos
    if (no == NULL) {            //Caso base da recursao
        return;
    }
    print_pedaco(no->esq, posicao_i, posicao_f, posicao); //subarvore da esquerda

    if (no->esq == NULL && no->dir == NULL) {             //se é folha
        int tamanho_folha = strlen(no->dna);

        for (int i = 0; i < tamanho_folha; i ++) {       //percorre letra a letra
        if(*posicao >= posicao_i && *posicao < posicao_f) {
        printf("%c", no->dna[i]);
            }
        (*posicao)++;                                    //adiciona um valor na posicao
        }
    }

    print_pedaco(no->dir, posicao_i, posicao_f, posicao);
}

void contar_letras(p_no no, int *a, int*c, int *g, int *t) {
    if (no == NULL) {                                       //Caso base
        return;
    }
    contar_letras(no->esq, a, c, g, t);                     // subarvore da esquerda

    if (no->esq == NULL && no->dir == NULL) {               //se é folha
        int tamanho_folha = strlen(no->dna);
        for (int i = 0; i < tamanho_folha; i ++) {          //percorre letra a letra
            if (no->dna[i] == 'A'){
                (*a) ++;
            }
            if(no->dna[i] == 'C') {
                (*c) ++;
            } 
            if(no->dna[i] == 'G') {
                (*g) ++;
            } 
            if(no->dna[i] == 'T') {
                (*t) ++;
            }
        }
    }
    contar_letras(no->dir, a, c, g, t);                  // subarvore da direita
}

int tamanho_total(p_no no) {
    if (no->esq == NULL && no->dir == NULL) {  //Se o no for uma folha, o tamanho é o valor da sua chave e a contagem para
        return no->chave;
    }
    int tamanho_esquerda = tamanho_total(no->esq);
    int tamanho_direita = tamanho_total(no->dir);
    return tamanho_esquerda + tamanho_direita; 
}

void arvore_para_string(p_no no, char* novo_dna, int* indice) {
    if (no == NULL) {
        return;
    }
    arvore_para_string(no->esq, novo_dna, indice); //se for interno executa a funcao para a esquerda e para direita

    if (no->esq == NULL && no->dir == NULL) {      // Se o no for uma folha, copia o seu dna para a string novo_dna
        for (int i = 0; no->dna[i] != '\0'; i ++) {
            novo_dna[*indice] = no->dna[i];
            (*indice) ++;
        }
    }
    arvore_para_string(no->dir, novo_dna, indice);
}

p_no balancear(p_no no, int max) {
    int altura_esq = 0, altura_dir = 0;
    if (no == NULL) {
        return NULL;
    }
    if (no->esq == NULL && no->dir != NULL) { //verificando a regra do filho único nas remocoes
        p_no filho_restante = no->dir;
        free(no);
        return filho_restante;
    }
    if (no->dir == NULL && no->esq != NULL) {
        p_no filho_restante = no->esq;
        free(no);
        return filho_restante;
    }

    if (no->esq != NULL) {
    altura_esq = no->esq->altura;
    }
    if (no->dir != NULL) {
    altura_dir = no->dir->altura;
    }

    int diferenca = altura_esq - altura_dir;

    if (diferenca > 4 || diferenca < -4) {   //Se o modulo da diferença for maior que 4, precisamos mexer na subarvore
        int tamanho_total_subarvore = tamanho_total(no);
        char* dna_string = malloc((tamanho_total_subarvore + 1) * sizeof(char));
        dna_string[0] = '\0';
        int indice = 0;
        arvore_para_string(no, dna_string, &indice);
        liberar_arvore(no);
        p_no no_balanceado = criar_arvore(dna_string, tamanho_total_subarvore, max);
        free(dna_string);
        return no_balanceado;
    }
    return no;  
}

p_no inserir(p_no no, int posicao, char letra, int max) {
    if (no->esq != NULL && no->dir != NULL) {                  //nó interno
        if (posicao <= no->chave) {                            //se for menor ou igual vai pra esquerda
            no->esq = inserir(no->esq, posicao, letra, max);
            no->chave++;
        } else {                                               //se for maior vai pra direita e nao adiciona, a chave é só dos elementos da subarvore esquerda
            no->dir = inserir(no->dir, posicao - no->chave, letra, max);
        }

    } else {                                                   //folha, fim da recursao
        int tamanho = no->chave;
        char* novo_dna = malloc((tamanho + 2) * sizeof(char)); //alem da string anterior temos o \0 e a nova letra
        for (int i = 0; i < posicao; i ++) {                   //copia a parte da string antes da insercao
            novo_dna[i] = no->dna[i];
        }

        novo_dna[posicao] = letra;                             //coloca a nova letra

        for (int i = posicao; i < tamanho; i ++) {             //copia o resto da string uma posicao a frente
            novo_dna[i + 1] = no->dna[i]; 
        }
        novo_dna[tamanho + 1] = '\0';
        free(no->dna);
        no->dna = novo_dna;
        no->chave++;

        if (no->chave > max) {                                 //se ao adicionar passou do maximo cria uma nova subarvore utilizando a funcao dr criar de cima
            p_no sub_arvore = criar_arvore(no->dna, no->chave, max);
            no->esq = sub_arvore->esq;
            no->dir = sub_arvore->dir;
            no->chave = sub_arvore->chave;
            free(sub_arvore);
        }
    }
    int altura_esq = 0;
    int altura_dir = 0;
    if (no->esq != NULL) {
        altura_esq = no->esq->altura;
    }
    if (no->dir != NULL) {
        altura_dir = no->dir->altura;
    }

    no->altura = 1 + maximo(altura_esq, altura_dir);
    no = balancear(no, max); 
    return no;
}

p_no remover(p_no no, int posicao, int max) { //funcao remover estrutura muitp parecida com inserir
    if (no->esq != NULL && no->dir != NULL) { //nó interno
        if (posicao < no->chave) {            //se for menor vai pra esquerda
            no->esq = remover(no->esq, posicao, max);
            no->chave--;
        } else {
            no->dir = remover(no->dir, posicao - no->chave, max);
        }
    } else {                                //na folha
        int tamanho_atual = no->chave;
        char* novo_dna = malloc(tamanho_atual * sizeof(char)); //como vai remover um o lugar da anterior vai o \0
        for (int i = 0; i < posicao; i++) {
            novo_dna[i] = no->dna[i];
        }
        for (int i = posicao + 1; i < tamanho_atual; i++) {
            novo_dna[i - 1] = no->dna[i];
        }
        novo_dna[tamanho_atual - 1] = '\0';
        
        free(no->dna);
        no->dna = novo_dna;
        no->chave--;

        if (no->chave == 0) { //se a folha nao tem mais dna ela deve ser removida
            free(no->dna);
            free(no);

            return NULL;
        }
    }

    int altura_esq = 0; 
    int altura_dir = 0;

    if (no->esq != NULL) {
        altura_esq = no->esq->altura;
    }
    if (no->dir != NULL) {
        altura_dir = no->dir->altura;
    }

    no->altura = 1 + maximo(altura_esq, altura_dir);
    no = balancear(no, max);
    return no;
}

void liberar_arvore(p_no no) {
    if (no == NULL) {
        return;
    }
    liberar_arvore(no->esq);
    liberar_arvore(no->dir);
    free(no->dna);
    free(no);
}


