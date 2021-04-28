#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 10

//構造体の宣言
typedef struct cards{
    int num;
    int suit;
    struct cards *next;
} cards_type;

//関数プロトタイプ宣言
int check(char *select);//この中で確認用printfする
void getcard(cards_type **head, cards_type **tail, int *len);
void discard(cards_type **head, int *len);
void exchange(cards_type **head, cards_type **tail, int *len, int num);
void disp(cards_type **head, int i);
void finish(cards_type **head);

//メイン文
int main(void){
    cards_type *head, *tail;
    int len=0, num=5;
    char select[8];
    srand(time(NULL));

    exchange(&head, &tail, &len, num);
    for (int i = 1; i <= SIZE; i++){
        disp(&head, i);
        printf("What will you do next? [excange/check]:");
        scanf("%s", select);
        if(check(select) == 0) break;
        else{
            printf("How many cards to exchange?:");
            scanf("%d", &num);
            exchange(&head, &tail, &len, num);
        }
    }
    finish(&head);
}

////使用する関数
//check関数(入力された文字列を特定の文字列か判別する関数)
int check(char *select){
    if(strcmp(select, "check") == 0) return 0;
    else return 1;
}

//getcard関数(カード情報を生成し、リストの末尾に追加する関数)
void getcard(cards_type **head, cards_type **tail, int *len){
    cards_type *p, *new;
    int suit, num;
    suit = rand() % 4;
    num = (rand() % 13)+1;
    p = *tail;
    new = (cards_type *)malloc(sizeof(cards_type));
    new->suit = suit;
    new->num = num;
    *tail = new;
    if(*len == 0) *head = new;
    new->next = NULL;
    if (*len > 0) p->next = new;
    *len += 1;
}

//discard関数(リストの先頭のカートを削除する関数)
void discard(cards_type **head, int *len){
    cards_type *p;
    p = *head;
    if(*len > 0){
        *head = p->next;
        free(p);
        *len -= 1;
    }
}

void exchange(cards_type **head,cards_type **tail, int *len, int num){
    int i;
    for (i = 0; i < num; i++) discard(head, len);
    for (i = 0; i < num; i++) getcard(head, tail, len);
}

void disp(cards_type **head, int i){
    cards_type *p;
    p = *head;
    printf("\n[Turn %d]Current cards:\n", i);
    for (int i = 0; i < 5;i++){
        switch(p->suit){
            case 0:
                printf("  SPADE   ");
                break;
            case 1:
                printf("  DIAMOND ");
                break;
            case 2:
                printf("  HEART   ");
                break;
            case 3:
                printf("  CLUB    ");
                break;
        }
        printf("%d\n", p->num);
        if(i < 4) p = p->next;
    }
    puts("");
}

void finish(cards_type **head){
    cards_type *p, *p2;
    p = *head;
    do{
        p2 = p->next;
        free(p);
        p = p2;
    } while (p->next != NULL);
    puts("End of game.");
}
