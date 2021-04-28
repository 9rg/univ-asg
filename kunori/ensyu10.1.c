//単方向リストにおいて、リストの要素数を表示する処理を追加

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
    for (i = 1; i <= num; i++){
        cur_p = malloc(sizeof(element_type));
        if(i==1){
            head = cur_p;//最初の構造体変数をheadとする
        }
        else{//2回目以降は前回のものから連接
            pre_p->next = cur_p;
        }

        printf("Element %d:", i);
        scanf("%d", &cur_p->value);
        //構造体変数の「値」メンバの初期化
        cur_p->next = NULL;//「次の値へのポインタ」メンバの初期化
        pre_p = cur_p;//次のループの準備
    }

    //リストの内容を出力
    p = head;
    while(p != NULL){
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");

    ///////////////////////////////////////
    //         リストの要素数を出力         //
    ///////////////////////////////////////
    p = head;
    int cnt = 0;
    while (p != NULL){
        cnt++;
        p = p->next;
    }
    printf("num of Elements:%d\n", cnt);

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