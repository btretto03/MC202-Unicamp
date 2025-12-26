#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "matriz.h"

int main(){ 
    int i, j, free_i = 0, free_j = 0; 
    char command[3]; //O comando tera uma ou duas letras 
    scanf("%d %d", &i, &j); 
    int **matrix = malloc(i * sizeof(int *)); //cria a matriz inicial 
    for (int k = 0; k < i; k ++) { 
        matrix[k] = malloc(j * sizeof(int)); 
    } 
    for (int k = 0; k < i; k ++) { //inputs iniciais do usuario 
        for (int z = 0; z < j; z++) { 
            scanf(" %d", &matrix[k][z]); 
        } 
    } 
    for (int k = 0; k < i; k ++) { //ordena as linhas 
        selection_sort(matrix, k, j); 
    } 
    while(1){ //loop principal do código
        scanf("%s", command); 

        if (strcmp(command, "AP") == 0) { //Adicionar personagem
            int *new_line = malloc(j * sizeof(int)); //aloca um vetor temporario para guardar a nova linha
            for (int k = 0; k < j; k ++) { 
                int number; 
                scanf("%d", &number); 
                new_line[k] = number; 
            } 
            if (free_i == 0) { 
                printf("Tamanho da matriz: %d x %d\n", i + 1, j); 
                printf("Memória realocada: %d x %d -> %d x %d\n", i + free_i, j + free_j, i * 2, j + free_j);
                int **old_matrix = matrix; 
                int old_i = i; 
                matrix = double_matrix_lines(matrix, i, j + free_j); //dobra as linhas da matriz
                free_i = i;
                for (int k = 0; k < old_i; k ++) { 
                    free(old_matrix[k]); 
                } 
                free(old_matrix); 
            } 
            for (int k = 0; k < j; k ++) { 
                matrix[i][k] = new_line[k]; 
            }      
            selection_sort(matrix, i, j); //ordena a nova linha
            i++; 
            free_i--; 
            free(new_line); //libera a memoria do vetor temporario
        } 

        if (strcmp(command, "AH") == 0) { //Adicioanr habilidade
            int *new_column = malloc(i * sizeof(int)); //aloca um vetor temporario para guardar a nova coluna
            for (int k = 0; k < i; k ++) { 
                int number; 
                scanf("%d", &number); 
                new_column[k] = number; 
            } 
            if (free_j == 0) {  //Lógica similar ao comando AP
                printf("Tamanho da matriz: %d x %d\n", i, j + 1); 
                printf("Memória realocada: %d x %d -> %d x %d\n", i + free_i, j + free_j, i + free_i, j * 2);
                int **old_matrix = matrix; 
                matrix = double_matrix_columns(matrix, i + free_i, j); 
                free_j = j; 
                for (int k = 0; k < i + free_i; k ++) { 
                    free(old_matrix[k]); 
                } 
                free(old_matrix); 
            } 
            for (int k = 0; k < i; k ++) { 
                matrix[k][j] = new_column[k]; 
            }
            j++;
            for (int k = 0; k < i; k ++) { //como foi adicionado uma nova coluna, todas anteriores precisam ser reordenadas
                selection_sort(matrix, k, j);
            }
            free_j--; 
            free(new_column); 
        } 

        if (strcmp(command, "RP") == 0) { //Remover personagem
            int x = i + free_i; //total de linhas
            int remove_line; 
            scanf("%d", &remove_line); 

            free(matrix[remove_line]); //libera a memoria da linha que vai ser removida

            for (int k = remove_line; k < i - 1; k ++) { 
                matrix[k] = matrix[k + 1]; //muda os ponteiros das linhas abaixo da removida para cima
            } 

            matrix[i - 1] = malloc((j + free_j) * sizeof(int)); //nova linha vazia no final
            i--;
            free_i++; 

            if (i > 0 && i <= x/4) {  //Reduz a matriz
                int new_lines2 = x / 2;
                printf("Tamanho da matriz: %d x %d\n", i, j); 
                int total_cols = j + free_j;
                int **smaller_matrix = malloc(new_lines2 * sizeof(int*));

                for (int k = 0; k < new_lines2; k ++) {
                    smaller_matrix[k] = malloc(total_cols * sizeof(int));
                    for (int z = 0; z < total_cols; z ++) {
                        if (k < i) {
                            smaller_matrix[k][z] = matrix[k][z];
                        }
                    }
                }
                for (int k = 0; k < x; k ++) {
                    free(matrix[k]);
                }
                free(matrix);
                matrix = smaller_matrix; 
                free_i = new_lines2 - i; 
                printf("Memória realocada: %d x %d -> %d x %d\n", x, total_cols, new_lines2, total_cols); 
            } 
        } 

        if (strcmp(command, "RH") == 0) { //Remover habilidade
            int y = j + free_j;
            int remove_column; 
            scanf("%d", &remove_column); 

            for (int k = 0; k < i + free_i; k ++) { 
                for (int z = remove_column; z < j - 1; z ++) { 
                    matrix[k][z] = matrix[k][z+ 1]; 
                }
            } 
            j--; 
            free_j++;  
 
            for (int k = 0; k < i; k ++) {
                selection_sort(matrix, k, j);
            }
            if (j > 0 && j <= y / 4) { //reduz a matriz
                int new_columns2 = y / 2; 
                printf("Tamanho da matriz: %d x %d\n", i, j); 
                int total_rows = i + free_i;
                int **smaller_matrix = malloc(total_rows * sizeof(int*)); 

                for (int k = 0; k < total_rows; k ++) { 
                    smaller_matrix[k] = malloc(new_columns2 * sizeof(int)); 
                    for (int z = 0; z < new_columns2; z ++) { 
                        if (z < j) {
                            smaller_matrix[k][z] = matrix[k][z]; 
                        }
                    } 
                } 
                for (int k = 0; k < total_rows; k ++) {
                    free(matrix[k]);
                }
                free(matrix); 
                matrix = smaller_matrix; 
                free_j = new_columns2 - j; 
                printf("Memória realocada: %d x %d -> %d x %d\n", total_rows, y, total_rows, new_columns2); 
            } 
        } 
        if (strcmp(command, "V") == 0) { 
            printf("MATRIZ ATUAL:\n"); 
            print_matrix(matrix, i, j); 
        } 
        
        if (strcmp(command, "S") == 0) { 
            break; 
        } 
    } 

    for (int k = 0; k < i + free_i; k ++) { 
        free(matrix[k]); 
    } 
    free(matrix); 
    return 0; 
}