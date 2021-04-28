#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 100

int queue_data[QUEUE_SIZE]; //待ち行列データ本体(待ち客)
int queue_head;							//データ先頭
int queue_num;							//データ個数=待ち客数
int data[24];								//各時刻の客数をカウント
int *window;								//窓口データ


//================================================//
//                関数プロトタイプ宣言            //
//================================================//
int enqueue(int enq_data);
int dequeue(int *deq_data, int i, int window[]);
int Prot(int data[], int a, int b, int c);


//================================================//
//                   メイン処理                     //
//================================================//
int main(void)
{

	srand((unsigned)time(NULL));
	int a, b, c;	 //問題文で指定されている変数
	//a:新規顧客の来店間隔(秒)
	//b:サービスを受ける平均時間(秒)
	//c:店内の窓口の個数(個)
	int total = 0; //現在店にいる客数
	int d;         //dequeue時の排出データを格納
	queue_head = queue_num = 0; //キュー関連の変数の初期化

	printf("Input a (visit interval):");
	scanf("%d", &a);
	printf("Input b (time to spent):");
	scanf("%d", &b);
	printf("Input c (number of window):");
	scanf("%d", &c);
	int nexta = 0;
	window = (int *)malloc(c * sizeof(int));
	for(int i = 0; i < c; i++){ //窓口待機時間の初期化
		window[i] = 0;
	}

	for (int h = 0; h < 24; h++){
		for (int m = 0; m < 60; m++){
			for (int s = 0; s < 60; s++){
				if (nexta == 0){					 //新たな客来たとき！
					int enq_data = rand()%b; //新たな客のサービス対応時間を生成
					enqueue(enq_data);			 //待ち時間を持った新規客データをenqueue
					total++;						     //客数のカウント
					nexta = rand()%a;      //次に客が来るまでの時間を生成
				}
				for (int i = 0; i < c; i++){	//その秒での各窓口の操作
					if (window[i] > 0){					//窓口が客に対応していた場合
						window[i]--;
						if (window[i] == 0){			//客のサービス応対が終了した場合
							total--;								//退店処理
						}
					}
					else{
						if(queue_num > 0){
							dequeue(&d, i, window); //待ち客をdequeueして、windowに値を挿入
						}
					}
				}
				nexta--; //客来るまでの時間をカウントダウン
			}
		}
		data[h] = total;
	}
	free(window);
	Prot(data, a, b, c);
	return 0;
}

//================================================//
//                   使用する関数                   //
//================================================//
int enqueue(int enq_data){ //function to enter new data to the queue
	if (queue_num < QUEUE_SIZE){
		queue_data[(queue_head + queue_num) % QUEUE_SIZE] = enq_data;
		queue_num++;
		printf("enpueue success, queue_num=%d,component=%d\n", queue_num, enq_data);
		for(int i=0;i<queue_num;i++){
			printf("queue_data[%d]=")
		}
	}
	else{
		puts("enpueue failed.");
	}
}

int dequeue(int *deq_data, int i, int window[]){//function to delete head data of the queue
	if (queue_num > 0) {
		*deq_data = queue_data[queue_head];
		queue_head = (queue_head + 1) % QUEUE_SIZE;
		queue_num--;
		window[i] = deq_data;
		printf("dequeue success, queue_num=%d\n", queue_num);
	}
	else{
		puts("dequeue failed.");
	}
}

int Prot(int data[], int a, int b, int c){// function to plot the data to gnuplot
	FILE *gp;
	gp = popen("gnuplot -persist","w");
	fprintf(gp, "set xrange[0:24]\n");
	fprintf(gp, "set yrange[-2:200]\n");
	fprintf(gp, "set xlabel \"時刻\"\n");
	fprintf(gp, "set ylabel \"店内の客数\"\n");
	fprintf(gp, "set key top title 'a:%d b:%d c:%d'\n", a, b, c);

	fprintf(gp, "set key left top\n");
	fprintf(gp, "plot '-' lt rgb 'blue' with lines\n");
	for(int i=0;i<24;i++){
		fprintf(gp, "%d\n", data[i]);
	}
	fprintf(gp, "e\n");

	fprintf(gp, "exit\n");
	fflush(gp);
	pclose(gp);
}
