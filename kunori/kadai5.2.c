#include<stdio.h>

void swap(int *first, int *second){
    int tmp;
    tmp = *first;
    *first = *second;
    *second = tmp;
}

void selectSort(int *data, int size){
    int i, j, minidx;
    for (i = 0; i < size; i++){
        minidx = i;
        for (j = i; j < size - i; j++){
            if(*(data+minidx) > *(data+j)){
                minidx = j;
            }
        }
        swap(data + i, data + minidx);
    }
}

int main(){
    int i;
    int data[10] = {10, 8, 6, 3, 4, 2, 5, 7, 9, 1};
    selectSort(data, 10);
    for (i = 0; i < 10;i++){
        printf("%d\t", data[i]);
    }
    return 0;
}