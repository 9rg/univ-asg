#include<stdio.h>
#include<sys/time.h>
#define N 40

int result[N + 1];

double getETime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec * 1e-6;
}

unsigned long int fib1(unsigned long int n){
    if(n == 0 || n == 1){
        return 1;
    }
    return (fib1(n - 1) + fib1(n - 2));
}

unsigned long int fib2(unsigned long int n){
    if(n == 0 || n == 1){
        return result[n];
    }
    result[n] = fib2(n - 1) + fib2(n - 2);
    return result[n];
}

int main(){
    double st, en;
    result[0] = 1;
    result[1] = 1;

    st = getETime();
    printf("%11d\n", fib1(N));
    en = getETime();
    printf("SAIKI:Elapsed Time=%.6f\n", en - st);

    st = getETime();
    printf("%11d\n", fib2(N));
    en = getETime();
    printf("DOUTEKI:Elapsed Time=%.6f\n", en - st);
    return 0;
}