//ある整数Nが素数か求める
#include<stdio.h>
#include<sys/time.h>
#define N 1000

double getETime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec * 1e-6;
}

void guchoku(){
    puts("Uses guchoku method:");
    double time_s, time_e;
    int flag = 0;
    time_s = getETime();
    for (int i = 2; i <= N; i++){
        for (int j = 2; j < i; j++){
            if(i%j==0){
                flag = 1;
                break;
            }
        }
        if(flag==0){
            printf("%5d", i);
        }
        flag = 0;
    }
    time_e = getETime();
    printf("\nSpended time:%lf\n", time_e - time_s);
}

int main(){
    puts("Uses Elatostenes method:");
    double time_s, time_e;
    time_s = getETime();
    int prime[N + 1];
    int i;
    int j;
    
    for (i = 2; i <= N; i++){
        prime[i] = 1;
    }
    for (i = 2; i <= N; i++){
        if(prime[i] == 1){
            for (j = 2 * i; j <= N; j++){
                if(j%i==0){
                    prime[j] = 0;
                }
            }
        }
    }

    for (i = 2; i <= N; i++){
        if (prime[i] == 1){
            printf("%5d", i);
        }
     }
    time_e = getETime();

    printf("\nSpended time:%lf\n", time_e - time_s);
    guchoku();
}