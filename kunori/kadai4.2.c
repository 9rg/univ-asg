#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, i, cnt = 0;
    int *data;
    float avg = 0;

    printf("input n:");
    scanf("%d", &n);
    data = malloc(n * sizeof(int));
    
    for (i = 0; i < n; i++){
        printf("data[%d]:", i);
        scanf("%d", data + i);
        avg += *(data + i);
    }
    avg /= n;
    for (i = 0; i < n; i++){
        if(avg <= *(data+i)){
            cnt++;
        }
    }
    free(data);
    printf("amount=%d\n", cnt);
    return 0;
}