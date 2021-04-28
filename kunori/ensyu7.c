#include<stdio.h>

void printBinary1(int num){
    int bit[8];
    int i, len = 4;
    for (i = len - 1; i >= 0; i--){
        bit[i] = num % 2;
        num /= 2;
    }
    for (i = 0; i < len; i++){
        printf("%d", bit[i]);
    }
    puts("");
}

void printBinary2(int num){
    int bit[8];
    int x, len = 4;
    for (int i = 0; i < len; i++){
        x = 1 << i;
        x = num & x;
        bit[len - i - 1] = x >> i;
    }
    for (int i = 0; i < len; i++){
        printf("%d", bit[i]);
    }
    puts("");
}

int main(void){
    int num1, num2, result, num1_r, num1_l;

    num1 = 0b0101;
    num2 = 0b0011;

    //下のコードの&を|,^ に変えて演算子を試す
    result = num1 ^ num2;
    
    printf("binary:\n");
    printBinary1(result);
    printBinary2(result);
    printf("decimal:%d\n", result);

    num1_r = num1 >> 1;
    num1_l = num1 << 1;
    printf("Right shifted:%d, Left shifted:%d\n", num1_r, num1_l);

    return 0;
}