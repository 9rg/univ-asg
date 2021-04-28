#include <stdio.h>

void func(int n, int y){
  int x, rem, frac=0; //x:2の辺の数 y:3の辺の数 rem:余り frac:yが0より大きい場合の計算用端数
  rem = n - y * 3;
  if(rem == 1){
    y--;
    rem = rem + 3;
  }
  x = rem / 2;
  if(rem % 2 != 1){
    if(y > 0){
      frac++;
    }
    printf("マッチング辺数:%d 最小の色数:%d\n", x + y, x + frac);
  }
  if(y > 0){
    func(n, y - 1);
  }
}

int main(void){
  int n;
  printf("Input number n=");
  scanf("%d", &n);
  func(n, n/3);
  return 0;
}
