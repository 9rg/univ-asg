#include<stdio.h>

struct address_data{
    char name[81];
    char phone[20];
    int age;
};

int main(void){
    struct address_data datas[5];

    //各データの値設定
    for (int i = 0; i < 5;i++){
        printf("name[%d]:", i);
        scanf("%s", datas[i].name);
        printf("phone[%d]:", i);
        scanf("%s", datas[i].phone);
        printf("age[%d]:", i);
        scanf("%d", &datas[i].age);
    }

    //情報を表示する
    int max = 0, max_num = 0;
    for (int i = 0; i < 5; i++){
        printf("%s\t[%s]\t%d\n", datas[i].name, datas[i].phone, datas[i].age);
        if(datas[i].age>=max){
            max = datas[i].age;
            max_num = i;
        }
    }

    printf("the most oldest is %d\n", max);

    return 0;
}
