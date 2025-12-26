#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selection_sort(int **matrix, int i, int j);
//Pra ordenar de forma crescente as linhas da matriz

void print_matrix(int **matrix, int i, int j);
//funcao que printa a matriz 

int **double_matrix_lines(int **matrix, int i, int j);
//funcao que dobra as linhas da matriz

int **double_matrix_columns(int **matrix, int i, int j);
//funcao que dobra as colunas da matriz 

#endif