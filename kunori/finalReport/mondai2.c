#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

//構造体の宣言
typedef struct element{
    char word[SIZE];
    struct element *next;
    struct element *pre;
} element_type;

//関数プロトタイプ宣言
int check(char *word);
void push(element_type **head, char *word, int *len);
void pop(element_type **head, int *len);
void disp(element_type **head, int *len);
void finish(element_type **head, int *len);

//メイン文
int main(void){
    element_type *head;
    int len = 0; //現在の文章の長さ(入力された単語の数)
    char word[SIZE];

    while(1){
        printf("\nInput word:");
        scanf("%s", word);
        switch (check(word)){
            case 1: goto loopout;
            case 2:
                if (len > 0) pop(&head, &len);
                else puts("There is no sentence.");
                break;
            case 3:
                push(&head, word, &len);
                break;
        }
        disp(&head, &len);
    }
    loopout:
        finish(&head, &len);
    return 0;
}

//使用する関数
//check関数(入力された文字列を特定の文字列か判別する関数)
int check(char *word){
    if(strcmp(word, "finishprocess") == 0) return 1;
    else if(strcmp(word, "deleteword") == 0) return 2;
    else return 3;
}

//push関数(スタックに要素を追加する関数)
void push(element_type **head, char *word, int *len){
    element_type *p, *new;
    p = *head;
    new = (element_type *)malloc(sizeof(element_type));
    strcpy(new->word, word);
    *head = new;
    if(*len == 0){
        new->next = NULL;
        new->pre = NULL;
    }
    else{
        new->next = p;
        p->pre = new;
    }
    *len += 1;
}

//pop関数(スタックに最後に追加された要素を削除する関数)
void pop(element_type **head, int *len){
    element_type *p;
    p = *head;
    *head = p->next;
    free(p);
    *len -= 1;
    if(*len > 0){
        p = *head;
        p->pre = NULL;
    }
}

//disp関数(現在のスタックの中身を表示する関数)
void disp(element_type **head, int *len){
    element_type *p;
    p = *head;
    for (int i = 0; i < *len; i++){
        if(p->next != NULL) p = p->next;
    }
    for (int i = 0; i < *len; i++){
        printf("%s ", p->word);
        if(p->pre != NULL) p = p->pre;
    }
    puts("");
}

//finish関数(メモリを解放する関数)
void finish(element_type **head, int *len){
    element_type *p, *p2;
    p = *head;
    for (int i = 0; i < *len ; i++){
        p2 = p->next;
        free(p);
        p = p2;
    }
    puts("\nEnd of process.");
}
