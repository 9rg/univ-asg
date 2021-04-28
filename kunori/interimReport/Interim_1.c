#include <stdio.h>
#include <stdlib.h>

int  find(int *data, int size, int target){
    int count = 0;
    for (int i = 0; i < size; i++){
        if(*(data+i) == target){
            count++;
        }
    }
    return count;
}

int main(){
    int *data;
    int target;
    int i, n;
    int count;

    printf("array size:");
    scanf("%d", &n);
    data = malloc(n * sizeof(int));
    printf("target:");
    scanf("%d", &target);

    for (i = 0; i < n; i++){
        scanf("%d", data + i);
    }

    count = find(data, n, target);
    printf("count: %d\n", count);
    free(data);

    return 0;
}

/*
・4行目:戻り値が設定されている関数なのに、関数がvoid型で宣言されている
・4行目:data配列はアドレス渡しをするべきだが、値渡しと同じ記法になっている
・7行目:アドレスと値を比較してしまっている。
・9行目:find()内において、全てのdataの中身を見終わる前のタイミングでreturnしている。
・20行目:scanf関数の第一引数はアドレスである必要があるが、&演算子がついていない
・21行目:malloc関数の引数において、サイズが考慮されていない
・23行目:scanf関数の第一引数はアドレスである必要があるが、&演算子がついていない
・29行目:戻り値がある関数に対して、代入先を指定していない
・38行目:main()内において、未宣言の変数countを使用している。→18行目に追加する必要がある
*/