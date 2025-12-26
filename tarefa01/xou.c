#include <stdio.h>


int is_perfect_square(int num){ // Verifica se o número tem raíz quadrada
    for (int i = 0; i * i <= num; i++){
        if (i * i == num){
            return 1;
        }
    }
    return 0;
}

int perfect_square(int num){  // Calcula a raíz quadrada sabendo que ela existe
    for (int i = 0; i * i <= num; i++){
        if (i * i == num){
            return i;
        }
    }
    return 0;
}

int sequence(int list[10000], int tamanho){ // Determina a maior sequência crescente
    int bigger_seq = 1, now_seq = 1;
    int max_start = 0, now_start = 0;

    for (int i = 1; i < tamanho; i++){
        if (list[i] >= list[i - 1]){
            now_seq++;
            if (now_seq > bigger_seq){
                bigger_seq = now_seq;
                max_start = now_start;
            }
        } else {
            now_seq = 1;
            now_start = i;
        }
    }

    for (int i = max_start; i < max_start + bigger_seq; i++){
        printf("%d ", list[i]);
    }
    return bigger_seq;
}

int main(){
    int num;
    int numblist[10000], cont = 0;

    while(1){

        scanf("%d", &num);


        if (num == 0){
            sequence(numblist, cont);
            break;
        }

        numblist[cont] = num;
        cont ++;
        
        if (is_perfect_square(num) == 1){
            printf("%d\n", perfect_square(num)); 
        }
        else {
            printf("Que ");
            for (int i = 0; i < num; i++){     //não sei se tem um jeito de fazer esse print usando um só printf :/
                printf("x");
            }
            printf("ou da xuxa é esse?\n");
        }
    }
    return 0;
}



