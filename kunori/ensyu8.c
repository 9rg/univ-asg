#include<stdio.h>
#include<math.h>
#include "MT.h"

double rnd(void){
    return genrand_real3();
}

void monte1(int n){
    int i, hit=0;
    double x, y, p;
    for (i = 0; i < n; i++){
        x = rnd();
        y = rnd();
        if (x * x + y * y < 1){
            hit++;
        }
    }
    p = (double)hit / (double)n;
    printf("pi = %6.4f\n", 4 * p);
}

void monte2(int n){
    int i;
    double x, y, sum=0, sumsq, mean;
    for (i = 0; i < n; i++){
        x = rnd();
        y = sqrt(1 - x * x);
    }
    mean = sum / n;
    printf("pi = %6.4f\n", 4 * mean);
}

void monte3(int n){
    int i;
    const double a = (sqrt(5) - 1) / 2;
    double x = 0, sum = 0;
    for (i = 0; i < n; i++){
        if(x+=a >= 1){
            x--;
        }
        sum = sqrt(1 - x * x);
    }
    printf("pi = %6.4f", 4 * sum / n);
}

int main(){
    int n = 10000;
    monte1(n);
    monte2(n);
    monte3(n);
    puts("");
    return 0;
}