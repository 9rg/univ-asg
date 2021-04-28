#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Member 6

typedef struct Pokemons{
    int id;
    char name[30];
    int type;
    int AP;
    int trainer;
    int flag;
} Pokemons;

int typeTranslate(char *typebuf){
    if(strcmp(typebuf,"ほのお")==0) return 1;
    else if(strcmp(typebuf,"みず")==0) return 2;
    else if(strcmp(typebuf,"くさ")==0) return 3;
    else return -1;
}

char typePrint(int typenum){
    if(typenum == 1) printf("ほのお ");
    if(typenum == 2) printf("みず   ");
    if(typenum == 3) printf("くさ   ");
    return -1;
}

void printPokemons(Pokemons p[], int num){
    printf("  No.%d ", num+1);
    printf("Name:%15s Type:", p[num].name);
    typePrint(p[num].type);
    printf("Attack Point:%d\n", p[num].AP);
}

int randChoose(Pokemons p[], int size){
    int randnum, count = 0;
    if(size == 1) randnum = 0;
    else randnum = rand() % (size / 2);
    for (int i = 0; i < Member; i++){
        if(p[i].trainer==1 && p[i].flag>0){
            if(count == randnum) return i;
            count++;
        }
    }
    return -1;
}

int Battle(Pokemons p[], int select, int rc){
    if(p[select].type-p[rc].type == 1 || p[select].type-p[rc].type == -2){
        p[select].AP = p[select].AP * 2;
    }
    if(p[select].AP > p[rc].AP){
        puts("You win!");
        return 1;
    }
    else if(p[select].AP < p[rc].AP){
        puts("You lose...");
        return -1;
    }
    else{
        puts("Drow!");
        return 0;
    }
}

int main(void){
    struct Pokemons datas[Member];
    int select, Distbuf0 = Member / 2, Distbuf1 = Member / 2, randnum, rc, score;
    int totalScore;
    char typebuf[6];
    srand(time(NULL));

    for (int i = 0; i < Member; i++){
        printf("\nPrease input information of Pokemon:[%d]\n", i+1);
        datas[i].id = i;
        datas[i].flag = 1;
        datas[i].trainer = 0;
        printf("Name:");
        scanf("%s", datas[i].name);
        printf("Type:");
        scanf("%s", typebuf);
        datas[i].type = typeTranslate(typebuf);
        printf("Attack Point:");
        scanf("%d", &datas[i].AP);
    }
    puts("\nInput completed. Now Distributing...");

    //Distribute
    for (int i = 0; i < Member; i++){
        if(Distbuf1 == 0) break;
        if(Distbuf0 == 0) datas[i].trainer=1;
        else if(rand()%2 == 1){
            datas[i].trainer = 1;
            Distbuf1--;
        }
        else Distbuf0--;
    }

        puts("Let's start Pokemon Battle!");
        totalScore = 0;
        for (int i = Member / 2; i > 0; i--)
        {
            printf("\n=== Round %d ===\n", Member/2 + 1 - i);
            puts(">>>Your Pokemons:");
            for (int j = 0; j < Member; j++)
            {
                if (datas[j].trainer == 0 && datas[j].flag > 0)
                {
                    printPokemons(datas, j);
                }
            }
            puts(">>>Enemy's Pokemons:");
            for (int j = 0; j < Member; j++)
            {
                if (datas[j].trainer == 1 && datas[j].flag > 0)
                {
                    printPokemons(datas, j);
                }
            }
            printf("Select Pokemon for battle:");
            scanf("%d", &select);
            printf("You:    ");
            printPokemons(datas, select - 1);
            printf("Enemy's:");
            rc = randChoose(datas, i);
            printPokemons(datas, rc);
            score = Battle(datas, select - 1, rc);
            totalScore = totalScore + score;
            datas[select - 1].flag = 0;
            datas[rc].flag = 0;
        }
    if(score > 0) puts("\nYou win the Battle!!");
    else if(score < 0) puts("\nYou lose the Battle...");
    else puts("\nThis Battle is drow!");
    return 0;
}