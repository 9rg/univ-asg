#include<stdio.h>
#include<stdlib.h>

void showProcess(int *data, int size){
    for (int i = 0; i < size; i++){
        printf("%d ", *(data+i));
    }
    puts("");
}

void insertSort(int *data, int size){
    int i, j, tmp, flag=0;
    for (i = 1; i < size; i++){
        tmp = *(data + i);
        for (j = i; j >= 0; j--){
            if (tmp < *(data + j-1)){
                *(data + j) = *(data + j - 1);
                flag = 1;
            }
            else break;
        }
        *(data + j) = tmp;
        if(flag == 1){
            showProcess(data, size);
            flag = 0;
        }
    }
}

int main(){
    int i, n;
    int *data;
    printf("input array size:");
    scanf("%d", &n);
    data = malloc(n * sizeof(int));
    puts("input data:");
    for (i = 0; i < n; i++){
        printf("data[%d]:", i);
        scanf("%d", data + i);
    }

    insertSort(data, n);
    
    for (i = 0; i < n; i++){
        printf("%d\t", data[i]);
    }
    puts("");

    free(data);
    return 0;
}