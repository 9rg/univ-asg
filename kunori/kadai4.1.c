#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int n, i;
    int min = INT_MAX;
    int *data;
    scanf("%d", &n);
    data = malloc(n * sizeof(int));
    for (i = 0; i < n; i++){
        printf("data[%d]:", i);
        scanf("%d", data + i);
    }
    for (i = 0; i < n;i++){
        if(min >= *(data+i)){
            min = *(data + i);
        }
    }
    free(data);
    printf("min=%d\n", min);
    return 0;
}