#include<stdio.h>

struct address_data{
    char name[81];
    char phone[20];
    int age;
};

int main(void){
    struct address_data alex, bobby;

    //alexの値設定
    printf("name:");
    scanf("%s", alex.name);
    printf("phone:");
    scanf("%s", alex.phone);
    printf("age:");
    scanf("%d", &alex.age);

    //bobbyの値設定
    printf("name:");
    scanf("%s", bobby.name);
    printf("phone:");
    scanf("%s", bobby.phone);
    printf("age:");
    scanf("%d", &bobby.age);

    //情報を表示する
    printf("%s\t[%s]\t%d\n", alex.name, alex.phone, alex.age);
    printf("%s\t[%s]\t%d\n", bobby.name, bobby.phone, bobby.age);

    if(alex.age<bobby.age){
        printf("bobby is larger than alex");
    }
    else if(alex.age==bobby.age){
        printf("same!");
    }
    else{
        printf("alex is larger than bobby");
    }
    return 0;
}
