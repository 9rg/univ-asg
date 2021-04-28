#include<stdio.h>
int cnt1 = 0, cnt2 = 0;

int gcd_subtract(int m,int n){
    while (m != n){
        cnt1++;
        if(m > n){
            m = m - n;
        }
        else{
            n = n - m;
        }
    }
    return m;
}

int gcd_rec(int m,int n){
    cnt2++;
    if (m % n == 0){
        return n;
    }
    else{
        return (gcd_rec(n, m % n));
    }
}

int main(){
    int x, y;

    printf("Input positive integer 1st:");
    scanf("%d", &x);
    printf("Input positive integer 2st:");
    scanf("%d", &y);

    printf("(1)The greatest common divisor is %d\ncount=%d\n", gcd_subtract(x, y),cnt1);
    printf("(2)The greatest common divisor is %d\ncount=%d\n", gcd_rec(x, y),cnt2);
    return 0;
}