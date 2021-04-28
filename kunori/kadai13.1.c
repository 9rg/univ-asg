#include<stdio.h>
#include<stdlib.h>

/*
push関数の中で使われているheadと、main関数内で使われているheadは別物。
・push関数： **head つまりダブルポインタなので、ダブルポインタとして扱う
・main関数： *head　つまりただのポインタ。
push関数中で
 *head
 とすると、ダブルポインタheadが指し示すシングルポインタheadが保持しているアドレスが示される。
 つまりmain関数内のheadが保持している値、つまりheadが指し示そうとしてるやつのアドレスが手に入る。
 今回でいうと、構造体ポインタpに渡される予定のやつ、つまり構造体リストの先頭アドレスが、push関数中での「*head」によって得られる。
*/


//構造体の宣言
typedef struct element{
    int value;
    struct element *next;
} element_type;

void push(element_type **head){
    element_type *p;
    int i, num;

    printf("Input value:");
    scanf("%d", &num);
    
    i = 0;
    p = *head;//headの指し示す先、つまり*head自体のアドレスをセット。pは構造体ポインタなんだから、アドレスをいれるのは当たり前
    while(num != 0){
        //新しいノードの作成
        p = (element_type *)malloc(sizeof(element_type));
        p->value = num;

        if(i == 0){//スタックに最初のノードを追加
            *head = p;
        }
        else{
            //headの指し示す先を新しく追加されたノードにする
            p->next = *head;
            *head = p;

        }
        i++;
        printf("input value:");
        scanf("%d", &num);
    }
}

int main(){
    element_type *p, *p2, *head;

    push(&head);//pushにheadポインタ自体のアドレスを渡す

    p = head;//構造体ポインタに、headの指し示す場所(構造体リストの先頭)を設定→pが最初の構造体を指し示すようになる
    while(p!=NULL){
        printf("%d ", p->value);
        p = p->next;
    }
    puts("");

    while(p!=NULL){
        p2 = p->next;
        free(p);
        p = p2;
    }

    return 0;
}