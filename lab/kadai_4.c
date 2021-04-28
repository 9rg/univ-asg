/*研究室課題4
端末数：固定
送受信可能なエリアの大きさ：可変
情報保持時間：可変
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define T_TERM 100
#define T_SIZE 1000
//T_TERM means the number of Total Terminals
//T_SIZE means a side length of Total area1

//================================================//
//                プロトタイプ宣言                //
//================================================//
int SetFirstPoint(int term[][7], int time);
int Check(int term[][7], int i, int data[], int area, int time);
int AreaCheck(int term[][7], int s, int area);
int SetPoint(int term[][7], int s);
int Move(int term[][7]);
int Prot(int term[][7], int num, int data1[], int data2[], int area1, int area2, int time1, int time2);


//================================================//
//                   メイン処理                   //
//================================================//
int main(void){
  int num,area1,area2,time1,time2;
  int *data1;// data of number of trial vs terminals's condition
  int *data2;// data of number of trial vs terminals's condition
  int term[T_TERM][7] = {0};// propaty of each terminals
  /*architect
  [i][0]:condition...when its value = 1, it has imformation
  [i][1]:x coordinate...current x coordinate
  [i][2]:y coordinate...current y coordinate
  [i][3]:x distance...distance from current x coordinate to destination
  [i][4]:y distance...distance from current y coordinate to destination
  [i][5]:x destination...ratio of x-direction component
  [i][6]:y destination...ratio of y-direction component*/
  srand((unsigned)time(NULL));

  printf("Current size of total area1 is %d*%d\n", T_SIZE, T_SIZE);
  printf("Current number of total terminals is %d\n", T_TERM);
  printf("Input number of trials:");
  scanf("%d", &num);
  printf("Input a side length of the area(1):");
  scanf("%d", &area1);
  printf("Input a side length of the area(2):");
  scanf("%d", &area2);
  printf("Input the time to keep the imformation(1):");
  scanf("%d", &time1);
  printf("Input the time to keep the imformation(2):");
  scanf("%d", &time2);
  data1 = (int *)malloc(num * sizeof(int));
  data2 = (int *)malloc(num * sizeof(int));

  SetFirstPoint(term, time1);
  for(int i=0;i<num;i++){
    Check(term, i, data1, area1, time1);
    Move(term);
  }

  SetFirstPoint(term, time2);
  for(int i=0;i<num;i++){
    Check(term, i, data2, area2, time2);
    Move(term);
  }

  printf("\n========== %d times later ==========\n\n", num);
  Prot(term, num, data1, data2, area1, area2, time1, time2);
  free(data1);
  free(data2);
  return 0;
}

//================================================//
//                 使用する関数                   //
//================================================//
int SetFirstPoint(int term[][7], int time){// function to set first destination to each terminals
  int t0 = rand()%T_TERM;
  for(int s=0;s<T_TERM;s++){
    term[s][1] = rand()%T_SIZE;
    term[s][2] = rand()%T_SIZE;
    term[s][3] = 0;
    term[s][4] = 0;
    term[s][5] = 0;
    term[s][6] = 0;
    if(s == t0){
      term[s][0] = time;
      continue;
    }
    term[s][0] = 0;
  }
}

int Check(int term[][7], int i, int data[], int area, int time){// function to judge that the terminal receives the imformation or not
  int judge=0;
  data[i]=0;
  for(int s=0;s<T_TERM;s++){
    if(term[s][3]==0 && term[s][4]==0){
      SetPoint(term, s);
    }
    if(term[s][0] > 0){
      data[i]++;
      if(AreaCheck(term, s, area)==1){
        judge=1;
      }
    }
  }
  if(judge==1){//if terminal that has imformation exist in the area
    data[i]=0;
    for(int s=0;s<T_TERM;s++){
      if(AreaCheck(term, s, area)==1){
        if(term[s][0] == 0){
          term[s][0] = time;
        }
      }
      if(term[s][0] > 1){
        data[i]++;
      }
    }
  }
}

int AreaCheck(int term[][7], int s, int area){// function to judje which two terminals are in the area1
  if((T_SIZE/2-area/2) <= term[s][1] && term[s][1] <= (T_SIZE/2+area/2) && (T_SIZE/2-area/2) <= term[s][2] && term[s][2] <= (T_SIZE/2+area/2)){
    return 1;
  }
  else{
    return 2;
  }
}

int SetPoint(int term[][7], int s){// function to set new destinaion of the terminal→おけ
  int tergetx = rand()%T_SIZE;
  int tergety = rand()%T_SIZE;
  term[s][3] = (tergetx - term[s][1]);
  term[s][4] = (tergety - term[s][2]);
  term[s][5] = abs(term[s][3]);
  term[s][6] = abs(term[s][4]);
}

int Move(int term[][7]){// function to move terminals to each destinations
  for(int s=0;s<T_TERM;s++){
    if(term[s][0] > 0){
      term[s][0]--;
    }
    if(term[s][3]==0){
      if(term[s][4] < 0){
        term[s][2]--;
        term[s][4]++;
      }
      else if(term[s][4] > 0){
        term[s][2]++;
        term[s][4]--;
      }
    }
    else if(term[s][4]==0){
      if(term[s][3] < 0){
        term[s][1]--;
        term[s][3]++;
      }
      else if(term[s][3] > 0){
        term[s][1]++;
        term[s][3]--;
      }
    }
    else{
      int direc = rand()%(term[s][5]+term[s][6]);
      if(direc < term[s][5]){
        if(term[s][3] < 0){
          term[s][1]--;
          term[s][3]++;
        }
        else if(term[s][3] > 0){
          term[s][1]++;
          term[s][3]--;
        }
      }
      if(direc >= term[s][5]){
        if(term[s][4] < 0){
          term[s][2]--;
          term[s][4]++;
        }
        else if(term[s][4] > 0){
          term[s][2]++;
          term[s][4]--;
        }
      }
    }
  }
}

int Prot(int term[][7], int num, int data1[], int data2[], int area1, int area2, int time1, int time2){// function to plot the data1 to gnuplot
  FILE *gp;
  gp = popen("gnuplot -persist","w");
  fprintf(gp, "set multiplot\n");
  fprintf(gp, "set xrange[0:%d]\n", num);
  fprintf(gp, "set yrange[-1.2:%d]\n", T_TERM+3);
  fprintf(gp, "set xlabel \"試行回数\"\n");
  fprintf(gp, "set ylabel \"情報を持つ端末数\"\n");
  fprintf(gp, "set key top title '総端末数%d 全体フィールド1辺%d'\n", T_TERM, T_SIZE);

  fprintf(gp, "set key left top\n");
  fprintf(gp, "plot '-' title 'エリア1辺:%d 保持時間:%d' lt rgb 'blue' with lines\n", area1, time1);
  for(int i=0;i<num;i++){
    fprintf(gp, "%d\n", data1[i]);
  }
  fprintf(gp, "e\n");

  fprintf(gp, "set key right top\n");
  fprintf(gp, "plot '-' title 'エリア1辺:%d 保持時間:%d' lt rgb 'red' with lines\n", area2, time2);
  for(int i=0;i<num;i++){
    fprintf(gp, "%d\n", data2[i]);
  }
  fprintf(gp, "e\n");

  fprintf(gp, "set nomultiplot\n");
  fprintf(gp, "exit\n");
  fflush(gp);
  pclose(gp);
}
