#include<stdio.h>
#include<string.h>

typedef struct _score {
    int math;
    int engl;
    int prog;
    double mean;
    char scholar;
} score;

score check_score(int m, int e, int p);

int main(void){
    score s;
    int m, e, p;
    printf("Math = ");
    scanf("%d", &m);
    printf("Engl = ");
    scanf("%d", &e);
    printf("Prog = ");
    scanf("%d", &p);
    s = check_score(m, e, p);

    printf("Scholar: %c (Mean = %.2f)\n", s.scholar, s.mean);
}

score check_score(int m, int e, int p){
    score s;
    s.math = m;
    s.engl = e;
    s.prog = p;
    s.mean = ((double)s.math + (double)s.engl + (double)s.prog) / 3;
    if(s.mean >= 90){
        s.scholar = 'Y';
    }
    else{
        s.scholar = 'N';
    }

    return s;
}