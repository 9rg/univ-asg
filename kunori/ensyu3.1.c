#include<stdio.h>
#include<string.h>

#define NAME_LEN 21

typedef struct _run {
    double first;
    double second;
    double third;
} run;

typedef struct _fitness {
    char name[NAME_LEN];
    run run_sec;
} fitness;

int main(void){
    fitness f;
    
    strcpy(f.name, "Andy");
    f.run_sec.first = 8.0;
    f.run_sec.second = 7.5;
    f.run_sec.third = 7.8;
    printf("%s: 1st=%.1lf, 2nd=%.1lf, 3rd=%.1lf\n",
          f.name, f.run_sec.first, f.run_sec.second, f.run_sec.third);
}