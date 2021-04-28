#include <stdio.h>

int search(int data[], int size, int key){
    int i;
    for (i = 0; i < size - 1; i++){
        if(data[i] == key){
            return i;
        }
    }
    return -1;
}


int binary_search(int data[], int size, int key){
    int left = 0;
    int right = size - 1;
    int mid;
    while (right >= left){
        mid = left + (right - left) / 2;
        if(data[mid] == key){
            return mid;
        }
        else if(data[mid] > key){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return -1;
}

int main(){
    int data[11] = {1, 3, 5, 11, 12, 13, 17, 22, 23, 25, 28};
    int key = 25;
    int index;

    index = search(data, 11, key);
    printf("index:%d\n", index);

    index = binary_search(data, 11, key);
    printf("index:%d\n", index);


    return 0;
}