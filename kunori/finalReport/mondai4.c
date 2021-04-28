#include <stdio.h>
#define SIZE 5

int main(void){
    int i;
    int student[SIZE][4];

    puts("Input students data.");
    for (i = 0; i < SIZE; i++){
        printf("\nStudent[%d]\n", i);
        printf("勉強は好き？[y=1/n=0]:");
        scanf("%d", &student[i][0]);
        printf("自由研究では工作派？[y=1/n=0]:");
        scanf("%d", &student[i][1]);
        printf("アウトドア派？[y=1/n=0]:");
        scanf("%d", &student[i][2]);
        printf("読書は好き？[y=1/n=0]:");
        scanf("%d", &student[i][3]);
    }

    puts("\nClassifing...\n");
    for (i = 0; i < SIZE; i++){
        if(student[i][0] == 1){
            if(student[i][1] == 1) printf("student[%d] maybe likes science.\n", i);
            else printf("student[%d] maybe likes math.\n", i);
        }
        else{
            if(student[i][2] == 1) printf("student[%d] maybe likes physical education.\n", i);
            else{
                if(student[i][3] == 1) printf("student[%d] maybe likes japanese.\n", i);
                else printf("student[%d] maybe likes music.\n", i);
            }
        }
    }
}
