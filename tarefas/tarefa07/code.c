#include "code.h"
#define PAI(i) (((i)-1)/2)
#define F_ESQ(i) (2*i+1) //Filho esquerdo de i
#define F_DIR(i) (2*i+2) //Filho direito de i

void remover(Item *a, Item *b, p_fp fprio, int i, int j) { //funcao de aula, mas adicionei alguns campos para poder acessar o id na remover
    fprio->pos[a->id] = j;
    fprio->pos[b->id] = i;
    Item t = *a;
    *a = *b;
    *b = t;
}

p_fp criar_filaprio(int tam) {                      //Funcao de aula para criar a fila de prioridade
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tam * sizeof(Item));
    fprio->pos = malloc(tam * sizeof(int));
    fprio->n = 0;
    fprio->tamanho = tam;
    return fprio;
}

Item *criar_item(char *nome, int chave, int duracao, int id) {   //Funcao de aula para criar o item
    Item *novo = malloc(sizeof(Item));
    novo->chave = chave;
    novo->duracao = duracao;
    novo->id = id;
    strcpy(novo->nome, nome);
    return novo;
}

int desempate_sobe (p_fp fprio, int k, int lugar) {
    if (lugar == 1) {                                                  //heap de max
        if (fprio->v[PAI(k)].chave < fprio->v[k].chave) {             //primeiro compara a chave
            return 1; 
        } 
        else if (fprio->v[PAI(k)].chave > fprio->v[k].chave) {
            return 0;
        }
        else if (fprio->v[PAI(k)].chave == fprio->v[k].chave) {        //se igual compara a duracao
            if (fprio->v[PAI(k)].duracao < fprio->v[k].duracao) {
                return 1;
            } 
            else if (fprio->v[PAI(k)].duracao > fprio->v[k].duracao) {
                return 0;
            }
            else if (fprio->v[PAI(k)].duracao == fprio->v[k].duracao) {  //se igual compara o id que eh unico e tem que acabar aqui
                if (fprio->v[PAI(k)].id > fprio->v[k].id) {
                    return 1;
                }
                if (fprio->v[PAI(k)].id < fprio->v[k].id) {
                    return 0;
                }
                return 0;
            }   
        }
    } else {                                                           //heap de min, mesma logica de max
        if (fprio->v[PAI(k)].duracao > fprio->v[k].duracao) {              
            return 1; 
        } 
        else if (fprio->v[PAI(k)].duracao < fprio->v[k].duracao) {
            return 0;
        }
        else if (fprio->v[PAI(k)].duracao == fprio->v[k].duracao) {       
            if (fprio->v[PAI(k)].chave < fprio->v[k].chave) {
                return 1;
            }
            else if (fprio->v[PAI(k)].chave > fprio->v[k].chave) {
                return 0;
            }
            else if (fprio->v[PAI(k)].chave == fprio->v[k].chave) {  
                if (fprio->v[PAI(k)].id > fprio->v[k].id) {
                    return 1;
                }
                else if (fprio->v[PAI(k)].id < fprio->v[k].id) {
                    return 0;
                }
            } 
        }
    }
    return 0;   
}

int desempate_desce (p_fp fprio, int filho1, int filho2, int lugar) {
    if (lugar ==1) {                                                        //heap de max(logica muito parecida com a funcao do desempata sobe)
        if (fprio->v[filho1].chave < fprio->v[filho2].chave) {
            return 1; 
        } 
        else if (fprio->v[filho1].chave > fprio->v[filho2].chave) {
            return 0;
        }
        else if (fprio->v[filho1].chave == fprio->v[filho2].chave) { 
            if (fprio->v[filho1].duracao < fprio->v[filho2].duracao) {
                return 1;
            }
            else if (fprio->v[filho1].duracao > fprio->v[filho2].duracao) {
                return 0;
            }
            else if (fprio->v[filho1].duracao == fprio->v[filho2].duracao)  {
                if (fprio->v[filho1].id > fprio->v[filho2].id) {
                    return 1;
                } else if (fprio->v[filho1].id < fprio->v[filho2].id) {
                    return 0;
                    }
                }
            }
        return 0;
    } else {                                                             //heap de min, mesma logica
        if (fprio->v[filho1].duracao > fprio->v[filho2].duracao) {
            return 1; 
        } 
        else if (fprio->v[filho1].duracao < fprio->v[filho2].duracao) {
            return 0;
        }
        else if (fprio->v[filho1].duracao == fprio->v[filho2].duracao) { 
            if (fprio->v[filho1].chave < fprio->v[filho2].chave) {
                return 1;
            }
            else if (fprio->v[filho1].chave > fprio->v[filho2].chave) {
                return 0;
            }
            else if (fprio->v[filho1].chave == fprio->v[filho2].chave)  {
                if (fprio->v[filho1].id > fprio->v[filho2].id) {
                    return 1;
                } else if (fprio->v[filho1].id < fprio->v[filho2].id)
                    return 0;
            }
        }
    }
    return 0;
}

void sobe_no_heap_maximo(p_fp fprio, int k) {      //funcao de aula alterando a chamada da funcao remover
    if (k > 0 && desempate_sobe(fprio, k, 1) == 1) {
        remover(&fprio->v[k], &fprio->v[PAI(k)], fprio, k, PAI(k));
        sobe_no_heap_maximo(fprio, PAI(k));
    }
}

void desce_no_heap_maximo(p_fp fprio, int k) {  //funcao de aula alterando a chamada da funcao remover
    int maior_filho;
    if (F_ESQ(k) < fprio->n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n && desempate_desce(fprio, F_ESQ(k), F_DIR(k), 1) == 1)
            maior_filho = F_DIR(k);
        if (desempate_desce(fprio, k, maior_filho, 1) == 1) {
            remover(&fprio->v[k], &fprio->v[maior_filho], fprio, k, maior_filho);
            desce_no_heap_maximo(fprio, maior_filho);
        }
    }
}

void insere_maximo(p_fp fprio, Item item) { //funcao de aula adicionando o campo do id
    fprio->v[fprio->n] = item;
    fprio->pos[item.id] = fprio->n;
    fprio->n++;
    sobe_no_heap_maximo(fprio, fprio->n - 1);
}
 
Item extrai_maximo(p_fp fprio) {   //funcao de aula alterando a chamada da funcao remover
    Item item = fprio->v[0];
    remover(&fprio->v[0], &fprio->v[fprio->n - 1], fprio, 0, fprio->n - 1);
    fprio->n--;
    desce_no_heap_maximo(fprio, 0);
    return item;
}

void sobe_no_heap_minimo(p_fp fprio, int k) { //funcao de aula alterando a chamada da funcao remover
    if (k > 0 && desempate_sobe(fprio, k, 2) == 1) {
        remover(&fprio->v[k], &fprio->v[PAI(k)], fprio, k, PAI(k));
        sobe_no_heap_minimo(fprio, PAI(k));
    }
}

void desce_no_heap_minimo(p_fp fprio, int k) {  //funcao de aula alterando a chamada da funcao remover
    int menor_filho;
    if (F_ESQ(k) < fprio->n) {
        menor_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n && desempate_desce(fprio, F_ESQ(k), F_DIR(k), 2) == 1)
            menor_filho = F_DIR(k);
        if (desempate_desce(fprio, k, menor_filho, 2) == 1) {
            remover(&fprio->v[k], &fprio->v[menor_filho], fprio, k, menor_filho);
            desce_no_heap_minimo(fprio, menor_filho);
        }
    }
}

void insere_minimo(p_fp fprio, Item item) { //funcao de aula adicionando o campo do id
    fprio->v[fprio->n] = item;
    fprio->pos[item.id] = fprio->n;
    fprio->n++;
    sobe_no_heap_minimo(fprio, fprio->n - 1);
}

Item extrai_minimo(p_fp fprio) { //funcao de aula alterando a chamada da funcao remover
    Item item = fprio->v[0];
    remover(&fprio->v[0], &fprio->v[fprio->n - 1], fprio, 0, fprio->n - 1);
    fprio->n--;
    desce_no_heap_minimo(fprio, 0);
    return item;
}

Item extrai_por_id(p_fp fprio, int id, int lugar) { 
    Item item = fprio->v[fprio->pos[id]];
    int indice_remover = fprio->pos[id]; 

    if ( indice_remover == fprio->n - 1) { //se for o ultimo elemento nao precisa balancear e nem remover nada
        fprio->n--;
        return item;
    }
    
    remover(&fprio->v[indice_remover], &fprio->v[fprio->n - 1], fprio, indice_remover, fprio->n - 1);
    fprio->n--;

    if (lugar == 1) {                                 //para o heap de max
        sobe_no_heap_maximo(fprio, indice_remover);
        desce_no_heap_maximo(fprio, indice_remover);
    } else {                                             //para o heap de min
        sobe_no_heap_minimo(fprio, indice_remover);
        desce_no_heap_minimo(fprio, indice_remover);
    }
    return item;
}

void altera(p_fp heap_max, p_fp heap_min, int id, int x) {
    int prio_anterior = heap_max->v[heap_max->pos[id]].chave;
    int prio_nova = prio_anterior + x;
    printf("Alterado %s %d -> %d\n", heap_max->v[heap_max->pos[id]].nome, prio_anterior, prio_nova);
    
    heap_max->v[heap_max->pos[id]].chave = prio_nova;
    heap_min->v[heap_min->pos[id]].chave = prio_nova;

    sobe_no_heap_maximo(heap_max, heap_max->pos[id]);
    sobe_no_heap_minimo(heap_min, heap_min->pos[id]);
    desce_no_heap_maximo(heap_max, heap_max->pos[id]);
    desce_no_heap_minimo(heap_min, heap_min->pos[id]);
}

void liberar_filaprio(p_fp fprio) {
    if (fprio == NULL) {
        return;
    }
    free(fprio->v);
    free(fprio->pos);
    free(fprio);
}
