#include <stdio.h>


double expo(double x, int exp){ //funcao para calcular a potencia de um número;
    double result = 1.0;
    for(int i = 1; i <= exp; i++){
        result *= x;
    }
    return result;
}

double factorial(double x){ //funcao para calcular o fatorial de um numero positivo diferente de 1;
    double  resultado = 1.0;
    for (int i = x; i > 0; i--){
        resultado *= i;
    }
    return resultado;
}

double sin_Taylor(double x){ // funcao que calcula o valor do sinx
    double term, sinx = 0.0;
    int count = 1;
    for(int i = 1; i > 0 ; i ++){
        term = (expo(x, 2*i - 1) / factorial(2*i - 1));
        if (term >= 0.000001 || term <= - 0.000001){
            if(count % 2 != 0){  
                sinx += term;
            }else{            
                sinx -= term;
            }
            count ++;
        }else{
            break;
        }
    }
    return sinx;
}

double cos_Taylor(double x){ // funcao que calcula o valor do cosx
    double term, cosx = 1.0;
    int count = 1;
    for(int i = 1; i > 0 ; i++){
        term = expo(x, 2*i) / factorial(2*i);
        if (term >= 0.000001|| term <= -0.000001 ){
            if(count % 2 != 0){   
                cosx -= term;     
            }else{
                cosx += term;   
            }
            count++;
        }else{
            break;
        }
    }
    return cosx;
}

int main(){
    double x;
    scanf("%lf", &x);
    printf("%.6lf\n", sin_Taylor(x));
    printf("%.6lf\n", cos_Taylor(x));

    return 0;
}
