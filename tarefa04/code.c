#include "matriz.h"

void selection_sort(int **matrix, int i, int j){ 
    //Pra ordenar de forma crescente as linhas da matriz 
    for (int k = 0; k < j; k ++) { 
        int lower = k; 
        for (int z = k + 1; z < j; z ++) { 
            if (matrix[i][z] < matrix [i][lower]) { 
                lower = z; 
            } 
        } 
        int x = matrix[i][lower]; 
        matrix[i][lower] = matrix[i][k]; 
        matrix[i][k] = x; 
    } 
} 

void print_matrix(int **matrix, int i, int j) { 
    //funcao que printa a matriz 
    for (int k = 0; k < i; k++) { 
        for (int z = 0; z < j; z++) { 
            printf("%d ", matrix[k][z]); 
        } 
        printf("\n"); 
    } 
} 

int **double_matrix_lines(int **matrix, int i, int j) { 
    //funcao que dobra as linhas da matriz 
    int new_lines = i * 2; 
    int **doubled_matrix = malloc(new_lines * sizeof(int*)); 
    for (int k = 0; k < new_lines; k ++) { 
        doubled_matrix[k] = malloc(j * sizeof(int)); 
    } 
    for (int k = 0; k < i; k ++) { 
        for (int z = 0; z < j; z ++) { 
            doubled_matrix[k][z] = matrix[k][z];
        } 
    }
    return doubled_matrix; 
} 

int **double_matrix_columns(int **matrix, int i, int j) { 
    //funcao que dobra as colunas da matriz 
    int new_columns = j * 2; 
    int **doubled_matrix = malloc(i * sizeof(int*)); 
    for (int k = 0; k < i; k ++) { 
        doubled_matrix[k] = malloc(new_columns * sizeof(int)); 
    } 
    for (int k = 0; k < i; k ++) { 
        for (int z = 0; z < j; z ++) { 
            doubled_matrix[k][z] = matrix[k][z]; 
        }
    }
    return doubled_matrix; 
} 
