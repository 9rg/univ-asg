//単方向リストにおいて整数を読み込み、リストの先頭にその整数を保持したノードを挿入する処理を追加

#include<stdio.h>
#include<stdlib.h>

typedef struct element{
    int value;
    struct element *next;
} element_type;

int main(void){
    element_type *cur_p, *head, *pre_p, *p, *tmp;
    int i, num, val;
    head = NULL;

    printf("Element num:");
    scanf("%d", &num);

    ///////////////////////////////////////
    //              変更箇所              //
    ///////////////////////////////////////
    for (i = 1; i <= num; i++){
        cur_p = malloc(sizeof(element_type));
        head = cur_p;
        if(i != 1){ //2回目以降は前回のものに連接
            cur_p->next = pre_p;
        }
        printf("Element %d:", i);
        scanf("%d", &cur_p->value);
        pre_p = cur_p;//次のループの準備
    }

    //リストの内容を出力
    p = head;
    while(p != NULL){
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");

    //リスト内容を出力しながら、malloc()で確保したメモリを解放
    while(head != NULL){
        p = head;
        head = p->next;
        printf("%d ", p->value);
        free(p);
    }
    printf("\n");

    return 0;
}