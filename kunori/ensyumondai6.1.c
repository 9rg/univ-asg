#include<stdio.h>

void insertSort(int *data, int size){
    int i, j, tmp;
    for (i = 1; i < size; i++){
        tmp = *(data + i);
        for (j = i; j >= 0; j--){
            if (tmp < *(data + j-1)){
                *(data + j) = *(data + j - 1);
            }
            else break;
        }
        *(data + j) = tmp;
    }
}

int main(){
    int i;
    int data[10] = {10, 8, 6, 3, 4, 2, 5, 7, 9, 1};
    insertSort(data, 10);
    for (i = 0; i < 10; i++){
        printf("%d\t", data[i]);
    }
    puts("");

    return 0;
}