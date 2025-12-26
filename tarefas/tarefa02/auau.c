#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

struct name{
    char name[50];
    char first_surname[50];
    char sec_surname[50];
};

char upper(char a){ //transforma a letra minuscula em maiuscula
    return a - 32;
}

void unscramble1(char emb[], struct name dogs[], int i){
    char first, sec, third;
    first = upper(emb[0]);
    sec = upper(emb[1]);
    third = upper(emb[2]);

    for(int x = 0; x <= i; x ++){
        if(first == dogs[x].name[0] && sec == dogs[x].first_surname[0] && third == dogs[x].sec_surname[0]){
            int k = 0;
            while(dogs[x].first_surname[k] != '\0'){
                dogs[i + 1].first_surname[k] = dogs[x].first_surname[k];
                k++;
            }
            dogs[i + 1].first_surname[k] = '\0'; 
        }
    }
}

void unscramble2(char emb[], struct name dogs[], int i){
    char first, sec, third;
    first = upper(emb[0]);
    sec = upper(emb[1]);
    third = upper(emb[2]);

    for(int x = 0; x <= i; x ++){
        if(first == dogs[x].name[0] && sec == dogs[x].first_surname[0] && third == dogs[x].sec_surname[0]){
            int k = 0;
            while(dogs[x].sec_surname[k] != '\0'){
                dogs[i + 1].sec_surname[k] = dogs[x].sec_surname[k];
                k++;
            }
            dogs[i + 1].sec_surname[k] = '\0';
        }
    }
}


int main(){
    int n, m, i = 0, j = 0;
    struct name dogs[MAX];
    char emb1[4], emb2[4];

    scanf("%d", &n);
    while(i < n){                   //Usei while ao inves de for pra guardar a variável i e utiliza-la no prox loop pra guardar os filhotes
        scanf("%s %s %s", dogs[i].name, dogs[i].first_surname, dogs[i].sec_surname);
        i ++;
    }
    scanf("%d", &m);
    while(j < m){
        scanf("%s %s %s", emb1, emb2 , dogs[i].name);
        unscramble1(emb1, dogs, i - 1);
        unscramble2(emb2, dogs, i - 1);
        i++;
        j++;
    }
    for(int x = 0; x < i; x++){
        printf("%s %s %s\n", dogs[x].name, dogs[x].first_surname, dogs[x].sec_surname);
    }
    return 0;
}
