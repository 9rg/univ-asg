#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
  int i=0,j,k,num;
  int *data;// data of number of trial vs terminals's condition
  int field[100][100]={0};// just position of terminals
  int term[20][7]={0};// propaty of each terminals
  /*architect
  [i][0]:condition...when its value = 1, it has imformation
  [i][1]:x coordinate...current x coordinate
  [i][2]:y coordinate...current y coordinate
  [i][3]:x distance...distance from current x coordinate to destination
  [i][4]:y distance...distance from current y coordinate to destination
  [i][5]:x destination...ratio of x-direction component
  [i][6]:y destination...ratio of y-direction component
  */

  //================================================//
  //                 メイン処理                     //
  //================================================//
  printf("Input number of trials:");
  scanf("%d", &num);

  data = (int *)malloc(num * sizeof(int));

  SetFirstPoint(field, term);
  puts("========== first condition ==========");
  Show(field, term);
  for(i=0;i<num;i++){
    Search(field, term, i, data);
    Move(field, term);
  }
  printf("\n========== %d times later ==========\n", num);
  Show(field, term);
  Prot(term, num, data);
  return 0;
}

//================================================//
//                 使用する関数                   //
//================================================//
int Show(field[][100], term[][7]){// function to show the condition of field
  int count=0;
  for(int j=0;j<100;j++){
    for(int k=0;k<100;k++){
      if(field[j][k]==0){
        printf("-");
      }
      else{
        printf("%d",field[j][k]);
      }
    }
    puts(" ");
  }
  for(int j=0;j<20;j++){
    if(term[j][0]==1){
      count++;
    }
  }
  printf("current number of imformations:%d\n", count);
}

int SetFirstPoint(field[][100], term[][7]){// function to set first destination to each terminals
  int t0 = rand()%20;
  for(int s=0;s<20;s++){
    term[s][1] = rand()%100;
    term[s][2] = rand()%100;
    if(s == t0){
      term[s][0] = 1;
      field[term[s][1]][term[s][2]] = 2;
    }
    else{
      field[term[s][1]][term[s][2]] = 1;
    }
  }
}

int Search(field[][100], term[][7], i, data[i]){// function to judge that the terminal receives the imformation or not
  int s,t;
  double dis;
  data[i]=0;
  for(s=0;s<20;s++){
    if(term[s][3]==0 && term[s][4]==0){
      SetPoint(s,term);
    }
    else{
      for(t=0;t<20;t++){
        if(term[s][0]==1){
          continue;
        }
        if(term[t][0]==1){
          dis = sqrt((term[s][1]-term[t][1])*(term[s][1]-term[t][1])+(term[s][2]-term[t][2])*(term[s][2]-term[t][2]));
          if(dis<=10){
            term[s][0]=1;
            field[term[s][1]][term[s][2]] = 1;
            break;
          }
        }
      }
    }
    if(term[s][0]==1){
      data[i]++;
    }
  }
}

int SetPoint(int d, term[][7]){// function to set new destinaion of the terminal
  int tergetx = rand()%100;
  int tergety = rand()%100;
  term[d][3] = (tergetx - term[d][1]);
  term[d][4] = (tergety - term[d][2]);
  term[d][5] = abs(term[d][3]);
  term[d][6] = abs(term[d][4]);
}

int Move(field[][100], term[][7]){// function to move terminals to each destinations
  for(int s=0;s<20;s++){
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
      field[term[s][1]][term[s][2]]=7;
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
    if(term[s][0]==1){
      field[term[s][1]][term[s][2]]=2;
    }
    else if(term[s][0]==0){
      field[term[s][1]][term[s][2]]=1;
    }
  }
}

int Prot(term[][7], num, data[num]){// function to plot the data to gnuplot
  FILE *gp;
  gp = popen("gnuplot -persist","w");
  fprintf(gp, "set xrange[0:%d]\n", num);
  fprintf(gp, "set yrange[-1.2:22]\n");
  fprintf(gp, "set xlabel \"試行回数\"\n");
  fprintf(gp, "set ylabel \"情報を持つ端末数\"\n");

  fprintf(gp, "plot '-' with points pointtype 1\n");
  for(int i=0;i<num;i++){
    fprintf(gp, "%d\n", data[i]);
  }
  fprintf(gp, "e\n");

  fprintf(gp, "exit\n");
  fflush(gp);
  pclose(gp);
}
