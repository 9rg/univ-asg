#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANGE 99

int  MakeQ(int *score, int size){
  if(size == 0) return 0;
  int ans, a, b, miss = 0;
  for (int i = 0; i < size; i++){
    a = rand() % RANGE;
    b = rand() % RANGE;
    printf(" Q%d : %d*%d=", i + 1, a, b);
    scanf("%d", &ans);
    if(a*b == ans) *(score + i) = 1;
    else{
      *(score + i) = 0;
      miss++;
    }
  }
  return miss;
}

void Score(int *score, int size, int miss){
  if(size == 0) return;
  double rate;
  printf("Finish!\nScore:");
  for (int i = 0; i < size; i++){
    if(*(score+i) == 1) printf("○ ");
    else printf("× ");
  }
  rate = (double)(size-miss) / (double)size;
  printf("\nValidity : %.1f%%\n", rate * 100);
}

int main(){
  int *score1, *score2;
  int questions, miss = 0;
  srand(time(NULL));
  questions = (rand() % 5) + 5;
  score1 = malloc(questions * sizeof(int));

  for (int i = 0; i < 2; i++){
    if(i == 1 && miss == 0) break;
    else if (i == 1 && miss > 0){
      questions = miss;
      score2 = malloc(miss * sizeof(int));
    }

    printf("\n\nRound%d : %d questions. Start!\n", i + 1, questions);

    if(i==0) miss = MakeQ(score1, questions);
    if(i==1) miss = MakeQ(score2, miss);

    if(i==0) Score(score1, questions, miss);
    if(i==1) Score(score2, questions, miss);
  }
  free(score1);
  free(score2);

  puts("\nCongratulations!");
}
