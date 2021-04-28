#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct element{
    char name[SIZE];
    struct element *next;
} element_type;

void inputList(element_type **head);
int find(element_type **head, char *target);

int main(void){
    element_type *list = NULL;
    element_type *p;
    int index;
    char target[SIZE];

    inputList(&list);

    printf("Input target:");
    scanf("%s", target);
    index = find(&list, target);

    printf("#%d\n", index);

    while (list != NULL){
        p = list;
        printf("%s ", p->name);
        list = p->next;
        free(p);
    }
    printf("\n");
    return 0;
}

void inputList(element_type **head){
    int num;
    printf("Element num:");
    scanf("%d", &num);

    element_type *tail;
    element_type *p;
    p = *head;
    for (int i = 1; i <= num; i++){
        char name[SIZE];
        printf("Element %d:", i);
        scanf("%s", name);
        p = (element_type *)malloc(sizeof(element_type));
        strcpy(p->name, name);
        if(i == 1) *head = p;
        else tail->next = p;
        tail = p;
        tail->next = NULL;
    }
}

int find(element_type **head, char *target){
    element_type *p;
    int index = 1;

    p = *head;
    while(p != NULL){
        if (strcmp(p->name, target) == 0){
            return index;
        }
        else{
            p = p->next;
        }
        index++;
    }
    return -1;
}
