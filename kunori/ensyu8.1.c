#include<stdio.h>
#define SIZE 10
void mergeSort(int *data, int left, int right){
    int i, mid, index_left, index_right;
    int buf[SIZE];

    if(right <= left){
        return;
    }

    mid = (left + right) / 2; //中点を取る

    mergeSort(data, left, mid);      //左半分をソート
    mergeSort(data, mid + 1, right); //右半分をソート

    //外部配列にコピー
    for (i = left; i <= mid; i++){ //左半分のコピー
        buf[i] = *(data + i);
    }
    for (i = mid + 1; i <= right; i++){//右半分をコピー
        buf[right - (i -(mid+1))] = *(data + i);
    }

    //併合処理
    index_left = left;//左側の添え字
    index_right = right;//右側の添え字

    for (i = left; i <= right; i++){
        if(buf[index_left] < buf[index_right]){
            *(data + i) = buf[index_left]; //左側を採用
            index_left++;
        }
        else{
            *(data + i) = buf[index_right]; //右側を採用
            index_right--;
        }
    }
}

int main(){
    int i;
    int data[10] = {10, 8, 6, 3, 4, 2, 5, 7, 9, 1};
    mergeSort(data, 0, 9);
    for (i = 0; i < SIZE; i++){
        printf("%d\t", data[i]);
    }
    puts("");
}