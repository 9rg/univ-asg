#include<stdio.h>

void swap(int *first, int *second){
    int tmp;
    tmp = *first;
    *first = *second;
    *second = tmp;
}

void quickSort(int *data, int left, int right){
    int i, j, pivot, pivot_val;

    if(right-left <= 1){
        if(*(data+right) < *(data+left)){
            swap(data + right, data + left);
        }
        return;
    }

    pivot = (left + right) / 2;
    pivot_val = *(data + pivot);
    swap(data + pivot, data + right);

    i = left;

    for (j = left; j < right - 1;j++){
        if(*(data+j) < pivot_val){
            swap(data + i, data + j);
            i++;
        }
    }

    swap(data + i, data + right);

    quickSort(data, left, i);
    quickSort(data, i + 1, right); 
}

int main(){
    int i;
    int data[10] = {10, 8, 6, 3, 4, 2, 5, 7, 9, 1};
    quickSort(data, 0, 9);
    for (i = 0; i < 10;i++){
        printf("%d\t", data[i]);
    }
    puts("");

    return 0;
}