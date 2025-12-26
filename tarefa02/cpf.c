#include <stdio.h>
#include <stdlib.h>
#define MAX 10000 //fui aumentando o max ate todos os testes passarem

struct person{
    char name[100];
    char birth[11];
    char place[50];
    char cpf[12];
};

int main(){
    int n;
    char cpf[12];
    struct person data[MAX];

    scanf("%d ", &n);
    for(int i = 0; i < n; i++){
        fgets(data[i].name, 100 , stdin);
        scanf("%s ", data[i].birth);
        fgets(data[i].place, 50, stdin);
        scanf("%s ", data[i].cpf);
    }

    scanf("%s ", cpf);
       for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < 11; j++) {
            if (cpf[j] != data[i].cpf[j]) {
                break;
            }
        }
        if (j == 11) {
            printf("Nome: %s", data[i].name);
            printf("Nascimento: %s\n", data[i].birth);
            printf("Local: %s", data[i].place);
            printf("CPF: ");
            for (int j = 0; j < 11; j++) {
                printf("%c", data[i].cpf[j]);
                if (j == 2 || j == 5) {
                    printf(".");
                }
                if (j == 8) {
                    printf("-");
                }
            }
            printf("\n");
            return 0; 
        }
    }
    printf("CPF nao encontrado.\n");
    return 0;
}