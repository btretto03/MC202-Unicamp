#include <stdio.h>
#include <stdlib.h>
//Oi, como a minha funcao proxima_geracao ficou meio enrolada acabei deixando meus comentarios pra me achar melhor, se fica ruim para correcao nas proximas vezes eu retiro antes de commitar, obrigado

void proxima_geracao(char **matrix, int i, int j) {
    char **new = malloc(i * sizeof(char *));   //Criei uma matriz temporaria para a "new" geracao
    for (int x = 0; x < i; x ++) {
        new[x] = malloc(j * sizeof(char));
    }

    for (int x = 0; x < i; x++) { //percorre as linhas da matriz orginal
        for (int y = 0; y < j; y++) {
            int live = 0;

            if (x == 0 || x == i - 1 || y == 0 || y == j - 1) { //Se esta nas bordas da matriz nao precisa verificar um dos lados
                for (int delta_x = -1; delta_x < 2; delta_x ++) {
                    for (int delta_y = -1; delta_y <= 1; delta_y ++) { //começa com -1 pra pegar a coluna anterior,(+1) pra pegar a mesma, (+1)pra pegar a prox
                        int vizinho_x = x + delta_x;
                        int vizinho_y = y + delta_y;

                        if (vizinho_x >= 0 && vizinho_x < i && vizinho_y >= 0 && vizinho_y < j) { //verifica se esta dentro da matriz e nao fora
                            if (delta_x != 0 || delta_y != 0) { //verifica se nao é a propria celula
                                if (matrix[vizinho_x][vizinho_y] == '#') {
                                    live ++;
                                }
                            }
                        }
                    }
                }
            } else {                //se está na parte interna da matriz
                for (int delta_x = -1; delta_x < 2; delta_x ++) { //quase igual, mas sem a verificacao das bordas
                    for (int delta_y = -1; delta_y <= 1; delta_y ++) {
                        if (delta_x != 0 || delta_y != 0) {
                            int vizinho_x = x + delta_x;
                            int vizinho_y = y + delta_y;
                            if (matrix[vizinho_x][vizinho_y] == '#') {
                                live ++;
                            }
                        }
                    }
                }
            }

            if (matrix[x][y] == '.') { //regras do jogo
                if (live == 3) {
                    new[x][y] = '#';
                } else {
                    new[x][y] = '.';
                } 
               
            } else {
                 if (live == 2 || live == 3) {
                    new[x][y] = '#';
                } else {
                    new[x][y] = '.';
                }
            }
        }
    }

    for (int x = 0; x < i; x ++) { //nova matriz
        for (int y = 0; y < j; y++) {
            matrix[x][y] = new[x][y];
        }
        free(new[x]);
    }
    free(new);
}

int main(){
    int i, j, n;
    scanf("%d %d %d", &i, &j, &n);
    char **matrix = malloc(i * sizeof(char *));

    for (int k = 0; k < i; k ++) {
        matrix[k] = malloc(j * sizeof(char));
    }
    for (int k = 0; k < i; k ++) {
        for (int z = 0; z < j; z++) {
            scanf(" %c", &matrix[k][z]);
        }
    }
    for(int k = 0; k <= n; k ++){ //printa a matriz
        printf("Geração %d\n", k);
        for (int k = 0; k < i; k ++) {
            for (int z = 0; z < j; z ++) {
                printf("%c ", matrix[k][z]);
        }
        printf("\n");
    }
        proxima_geracao(matrix, i, j);
    }

    for (int x = 0; x < i; x ++) {
        free(matrix[x]);
    }
    free(matrix);

    return 0;
}

