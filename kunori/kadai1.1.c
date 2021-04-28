//演習問題1-1
#include <stdio.h>

int main(void){
    int n;
    char s[10];
    
    printf("Input:");
    scanf("%d", &n);
    printf("Your input: %d\n", n);

    printf("Input:");
    scanf("%s", &s[0]);
    printf("Your input: %s\n", s);
}