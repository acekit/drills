#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
4
ビット演算
2つの数値x,yを入力すると、
xのyビット目を反転する。
*/
//

void GetUserInputByInt(int ,int );//int型で数値を取得する
int InvertTheYBitOfTheX(int , int);//XのYビット目を反転させる

int main( void )
{
  int input_year,input_month;
  //input user's choice
  printf("Please, input year and month ex.2020 2�_n");
  scanf("%d", &input_year);
  scanf("%d", &input_month);
  (void)getchar();
  printf("%s�_n", "Push any keys.");
  (void)getchar();
  return 0;
}
