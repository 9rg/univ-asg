#include<stdio.h>

void swap(int *first, int *second){
    int tmp;
    tmp = *first;
    *first = *second;
    *second = tmp;
}

void bubbleSort(int *data, int size){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size-i; j++){
            if(*(data+j) > *(data+j+1)){
                swap(data+j, data+j+1);
            }
        }
    }
}

int main(){
    int i;
    int data[10] = {10, 8, 6, 3, 4, 2, 5, 7, 9, 1};
    bubbleSort(data, 10);
    for (i = 0; i < 10;i++){
        printf("%d\t", data[i]);
    }

    return 0;
}