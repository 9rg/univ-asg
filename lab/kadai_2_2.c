/*研究室課題2.2
端末数：可変
送受信可能なエリアの大きさ：固定
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define T_SIZE 1000
#define T_AREA 500
//T_SIZE means a side length of Total Area
//T_AREA means a side length of send and receive Area

//================================================//
//                プロトタイプ宣言                //
//================================================//
int SetFirstPoint(int term[][7], int amount);
int Check(int term[][7], int i, int data[], int amount);
int AreaCheck(int term[][7], int s);
int SetPoint(int term[][7], int s);
int Move(int term[][7], int amount);
int Prot(int term[][7], int num, int data1[], int data2[], int amount1, int amount2);

//================================================//
//                 メイン処理                     //
//================================================//
int main(void){
  int i=0,j,k,num,amount1,amount2;
  int *data1;// data of number of trial vs terminals's condition
  int *data2;// data of number of trial vs terminals's condition
  int (*term1)[7];// propaty of each terminals(1)
  int (*term2)[7];// propaty of each terminals(2)
  /*architect
  [i][0]:condition...when its value = 1, it has imformation
  [i][1]:x coordinate...current x coordinate
  [i][2]:y coordinate...current y coordinate
  [i][3]:x distance...distance from current x coordinate to destination
  [i][4]:y distance...distance from current y coordinate to destination
  [i][5]:x destination...ratio of x-direction component
  [i][6]:y destination...ratio of y-direction component*/


  printf("Current size of total area is %d*%d\n", T_SIZE, T_SIZE);
  printf("Current size of send and receive area is %d*%d\n", T_AREA, T_AREA);
  printf("Input number of trials:");
  scanf("%d", &num);
  printf("Input number of terminals (1):");
  scanf("%d", &amount1);
  printf("Input number of terminals (2):");
  scanf("%d", &amount2);

  data1 = (int *)malloc(num * sizeof(int));
  data2 = (int *)malloc(num * sizeof(int));
  term1 = malloc(sizeof(int) * amount1 * 7);
  term2 = malloc(sizeof(int) * amount2 * 7);

  SetFirstPoint(term1, amount1);
  for(i=0;i<num;i++){
    Check(term1, i, data1, amount1);
    Move(term1, amount1);
  }
  SetFirstPoint(term2, amount2);
  for(i=0;i<num;i++){
    Check(term2, i, data2, amount2);
    Move(term2, amount2);
  }
  printf("\n========== %d times later ==========\n\n", num);
  Prot(term1, num, data1, data2, amount1, amount2);
  free(data1);
  free(data2);
  free(term1);
  free(term2);
  return 0;
}

//================================================//
//                 使用する関数                   //
//================================================//
int SetFirstPoint(int term[][7], int amount){// function to set first destination to each terminals
  int t0 = rand()%amount;
  for(int s=0;s<amount;s++){
    term[s][1] = rand()%T_SIZE;
    term[s][2] = rand()%T_SIZE;
    term[s][3] = 0;
    term[s][4] = 0;
    term[s][5] = 0;
    term[s][6] = 0;
    if(s == t0){
      term[s][0] = 1;
    }
    else{
      term[s][0] = 0;
    }
  }
}

int Check(int term[][7], int i, int data[], int amount){// function to judge that the terminal receives the imformation or not
  int judge=0;
  data[i]=0;
  for(int s=0;s<amount;s++){
    if(term[s][3]==0 && term[s][4]==0){
      SetPoint(term, s);
    }
    if(term[s][0]==1){
      data[i]++;
      if(AreaCheck(term, s)==1){
        judge=1;
      }
    }
  }
  if(judge==1){//if terminal that has imformation exist in the area
    data[i]=0;
    for(int s=0;s<amount;s++){
      if(AreaCheck(term, s)==1){
        term[s][0]=1;
      }
      if(term[s][0]==1){
        data[i]++;
      }
    }
  }
}

int AreaCheck(int term[][7], int s){// function to judje which two terminals are in the area1
  if((T_SIZE/2-T_AREA/2) <= term[s][1] && term[s][1] <= (T_SIZE/2+T_AREA/2) && (T_SIZE/2-T_AREA/2) <= term[s][2] && term[s][2] <= (T_SIZE/2+T_AREA/2)){
    return 1;
  }
  else{
    return 2;
  }
}

int SetPoint(int term[][7], int s){// function to set new destinaion of the terminal
  int tergetx = rand()%T_SIZE;
  int tergety = rand()%T_SIZE;
  term[s][3] = (tergetx - term[s][1]);
  term[s][4] = (tergety - term[s][2]);
  term[s][5] = abs(term[s][3]);
  term[s][6] = abs(term[s][4]);
}

int Move(int term[][7], int amount){// function to move terminals to each destinations
  for(int s=0;s<amount;s++){
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

int Prot(int term[][7], int num, int data1[], int data2[], int amount1, int amount2){// function to plot the data1 to gnuplot
  int amo;
  FILE *gp;
  gp = popen("gnuplot -persist","w");
  fprintf(gp, "set multiplot\n");
  fprintf(gp, "set xrange[0:%d]\n", num);
  if(amount1<amount2){
    amo = amount2;
  }
  else{
    amo = amount1;
  }
  fprintf(gp, "set yrange[-1.2:%d]\n", amo+3);
  fprintf(gp, "set xlabel \"試行回数\"\n");
  fprintf(gp, "set ylabel \"情報を持つ端末数\"\n");
  fprintf(gp, "set key top title '全体フィールド1辺:%d  送受信エリア1辺:%d'\n", T_SIZE, T_AREA);

  fprintf(gp, "set key left top\n");
  fprintf(gp, "plot '-' title '端末数%dの場合' lt rgb 'blue' with lines\n", amount1);
  for(int i=0;i<num;i++){
    fprintf(gp, "%d\n", data1[i]);
  }
  fprintf(gp, "e\n");

  fprintf(gp, "set key right top\n");
  fprintf(gp, "plot '-' title '端末数%dの場合' lt rgb 'red' with lines\n", amount2);
  for(int i=0;i<num;i++){
    fprintf(gp, "%d\n", data2[i]);
  }
  fprintf(gp, "e\n");

  fprintf(gp, "set nomultiplot\n");
  fprintf(gp, "exit\n");
  fflush(gp);
  pclose(gp);
}
