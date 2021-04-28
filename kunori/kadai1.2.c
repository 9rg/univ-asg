//演習問題1-2
#include <stdio.h>

#define PI 3.14
#define SIZE 10

int main(void){
    double cir[SIZE];
    double *dp;
    dp = cir;

    for (int i = 0  ; i < SIZE; i++){
        *(cir + i) = (i+1) * (i+1) * PI;
    }

    printf("SIZE:%d\n", SIZE);
    for (int i = 0; i < SIZE; i++){
        printf("Area of cir(rad:%dcm) = %.2f[cm^2]\n", i+1, *(cir + i));
    }
}