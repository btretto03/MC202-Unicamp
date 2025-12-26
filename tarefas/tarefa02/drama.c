#include "stdio.h"
#define MAX 20 //aumento no MAX
struct registro {
    char nome[MAX];
    char sobrenome[MAX];
    int qtd_peças;
};
void comemoracao(struct registro ator) {
    if (ator.qtd_peças >= 10) {   //Maior ou igual
        printf("Parabéns, %s %s, você completou %d peças conosco!\n", ator.nome,
               ator.sobrenome, ator.qtd_peças);
    }
}
int main() {
    int n;
    struct registro ator[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %s %s", &ator[i].qtd_peças, ator[i].sobrenome, ator[i].nome);
        comemoracao(ator[i]);
    }
}
