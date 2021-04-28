#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSort(int data[], int size);

int main(){
    int i, n;
    int data[10];
    srand(time(NULL));
    for (i = 0; i < 10; i++){
        data[i] = rand() % 100;
    }
    insertSort(data, 10);
    for (i = 0; i < 10; i++)
        printf("%d\t", data[i]);
    return 0;
}

void insertSort(int data[], int size){
    int i, j, k, buf;

    for (i = 1; i < size; i++){
        if (data[i] > data[i - 1]){
            j = i - 1;
            while(j >= 0 && data[i] > data[j]){
                j--;
            }
            buf = data[i];
            for (k = i; k >= j + 2; k--){
                data[k] = data[k - 1];
            }
            data[j + 1] = buf;
        }
    }
}


/*
・5行目,7行目:関数定義において、使用配列が配列として宣言されていない
・10行目:すでに宣言済の変数iを再度宣言している
・7行目~23行目：5行目でinsertSort()についてのプロトタイプ宣言を行っているにもかかわらずmain()以前に関数の記述がなされているため、プロトタイプ宣言の意味がなくなっている
・13行目:比較演算子が逆
・13行目:while文の条件について、j>0のままだと、データの挿入時にdata[0]が比較されない
・20行目:bufを挿入する場所は[i+1]ではなく、while文中で調節したjが絡んだ[j+1]である
・(不適切ではないが)33行目:for文の記法において、29行目の記法と33行目の記法が統一されていない

*/

/*
・問2において、問題文中の「数値群」という言葉は、今回のプログラムではその要素数(サイズ)が10個と定まっているため、問題文中でも「数値群(10個)」と記述するのが適切であると感じる。
*/

