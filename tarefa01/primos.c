#include<stdio.h>


int is_prime(int x){ // funcao que verifica se o número é primo
    for(int i = 2; i * i <= x; i ++){
        if (x % i == 0){
            return 0;
        }
    }
    return 1;
}

int palindromo(int x){ //funcao que verifica se o número é palíndromo
    int numb[100];
    int resto, size = 0;

    while (x > 0){
        resto = x % 10;
        numb[size] = resto;
        x = x / 10;
        size ++;
    }
    for (int i = 0; i < size / 2; i++){
        if (numb[i] != numb[size - 1 - i]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int x, count = 0, i = 2;
    scanf("%d", &x);
    while(count < x){
        if(palindromo(i) == 1 && is_prime(i) == 1){
            printf("%d\n", i);
            count ++;
        }
    i++;
    }
    return 0;
}