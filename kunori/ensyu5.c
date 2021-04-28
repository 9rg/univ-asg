#include<stdio.h>
int extgcd(int a, int b, int *x, int *y){
    int d;
    
    if(b==0){
        *x = 1;
        *y = 0;
    }
    else{
        d = extgcd(b, a % b, y, x);
        *y = *y - a / b * *x;
    }

    return d;
}

int main(){
    int x, y;
    int a, b, d;

    printf("Input integer 1st:\n");
    scanf("%d", &a);
    printf("Input integer 2nd:\n");
    scanf("%d", &b);

    d = extgcd(a, b, &x, &y);
    printf("x:%d y:%d\n", x, y);
}