#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct goals {
    int *v;
    int qtd;
    char name[20];//O problema enuncia que o nome pode ter até 20 caracteres e não somente 8
};

void liberar(struct goals *p) {
    if (p != NULL) {
        free(p->v); //Primeiro deve liberar o vetor
        free(p);
    }
}

int sum(struct goals *p) {
    int r = 0;
    for (int i = 0; i < p->qtd; i++) {
        r += p->v[i];
    }
    return r;
}

int main() {
    char name[20];
    struct goals *players[2];
    players[0] = malloc(sizeof(struct goals));
    players[1] = malloc(sizeof(struct goals)); //Players[1] não estava sendo alocado

    // Player 0
    scanf("%s", name);
    strcpy(players[0]->name, name);
    players[0]->v = malloc(3 * sizeof(int));
    (*players[0]).qtd = 3; //Corrige o problema das variáveis n inicializadas do valgrind, ele estava usando lixo em qtd
    for (int i = 0; i < 3; i++) {
        scanf("%d", &players[0]->v[i]);
    }


    // Player 1:
    scanf("%s", name);
    strcpy(players[1]->name, name); //Aqui é player1
    players[1]->qtd = 3;
    // Dados do player 1 são iguais aos dados do player 0
    players[1]->v = malloc(players[1]->qtd * sizeof(int));
    for (int i = 0; i < 3; i++) {                   //mesma estrutura do player0 para guardar os dados do p1(que são iguais aos do p0)
        players[1]->v[i] = players[0]->v[i];
    }

    if (players[0]->qtd > 4 || players[1]->qtd > 4) {
        printf("Melhor conferir esse Morango do Amor!\n");
    }

    printf("Placar inicial: %d vs %d\n", sum(players[0]), sum(players[1]));

    liberar(players[0]);
    liberar(players[1]);

    return 0;
}
