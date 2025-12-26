#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

int** zero_squared_matrix(int size_kernel) {
    //funcao que cria a matiz de kernel com todos seus elementos iguais a 0
    int **kernel_matrix = malloc(size_kernel * sizeof(int *));
        for (int i = 0; i < size_kernel; i++) {
            kernel_matrix[i] = malloc(size_kernel* sizeof(int));
            for (int k = 0; k < size_kernel; k++){
                kernel_matrix[i][k] = 0;
            }
        }
    return kernel_matrix;
}

int ** new_image(int lines, int columns, int size_kernel) {
    int new_lines = lines - size_kernel + 1;
    int new_columns = columns - size_kernel + 1;

    int **new_image = malloc(new_lines * sizeof(int *));
    for (int i = 0; i < new_lines; i ++) {
        new_image[i] = malloc(new_columns * sizeof(int));
    }
    return new_image;
}

void new_matrix(int **matrix, int lines, int columns, int size_kernel, int **kernel, int **new_image_matrix, int q) {
    int new_lines = lines - size_kernel + 1;
    int new_columns = columns - size_kernel + 1;

    for (int i = 0; i < new_lines; i++) {
        for (int j = 0; j < new_columns; j++) {
            new_image_matrix[i][j] = 0;
        }
    }

    for (int x = 0; x < lines; x ++) {
        for (int y = 0; y < columns; y ++) {
            if ( x < (size_kernel - 1)/2                               //Verifica cima
                || (lines - 1 - x) * 2 < size_kernel - 1               //Veririca baixo
                || y < (size_kernel - 1)/2                             //Veririca esquerda
                ||  (columns - 1 - y) * 2 < size_kernel - 1) {         //Veririca direita
                continue; //se o pixel é valido pula
            } else {
                int sum_kernel = 0;
                for (int i = -(size_kernel - 1) / 2; i <= (size_kernel - 1) / 2; i++) {
                    for (int j = -(size_kernel - 1) / 2; j <= (size_kernel - 1) / 2; j++) {
                        sum_kernel += matrix[x + i][y + j] * kernel[i + (size_kernel - 1) / 2][j + (size_kernel - 1) / 2];
                    }
                }
                int value = sum_kernel / q;

                if (value < 0) { 
                    value = 0;
                }
                if (value > 255) {
                    value = 255;
                }
                int out_x = x - (size_kernel - 1) / 2;
                int out_y = y - (size_kernel - 1) / 2;
                if (out_x >= 0 && out_x < new_lines && out_y >= 0 && out_y < new_columns) {
                    new_image_matrix[out_x][out_y] = value;
                }
            }
        }
    }
}

int main(){
    image_p image;
    char path[100];
    int size_kernel, q;

    scanf("%s", path);        //recebe a imagem origianl e guarda espaço pra ela
    image = read_image(path);
    int lines = (*image).n;
    int columns = (*image).m;

    scanf("%d %d", &size_kernel, &q);  //recebe o que o enunciado define como l e q
    int **kernel_matrix = zero_squared_matrix(size_kernel);
    for (int i = 0; i < size_kernel; i++) {
        for (int j = 0; j < size_kernel; j++) {
            scanf("%d", &kernel_matrix[i][j]);
        }
    }
    int **new_image_matrix = new_image(lines, columns, size_kernel);
    new_matrix((*image).matrix, lines, columns, size_kernel, kernel_matrix, new_image_matrix, q);

    image_p new_image = create_image(lines - size_kernel + 1, columns - size_kernel + 1);  //cria um novo elemento na sruct(a imagem que vai ser printada)
    for (int i = 0; i < (*new_image).n; i++) {
        for (int j = 0; j < (*new_image).m; j++) {
            (*new_image).matrix[i][j] = new_image_matrix[i][j];
        }
    }
    print_image(new_image);

    for (int i = 0; i < size_kernel; i++) {                     //Libera a memoria
        free(kernel_matrix[i]);
    }
    free(kernel_matrix);
    for (int i = 0; i < lines - size_kernel + 1; i++) {
        free(new_image_matrix[i]);
    }
    free(new_image_matrix);
    free_image(image);
    free_image(new_image);

    return 0;
}





