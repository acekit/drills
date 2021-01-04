#include <stdio.h>
#include <stdlib.h>
#define BUFF_LENGTH 2
#define N_INPUT 2
#define N_FUNCTION 4
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define ZERO 0

/*
1 四則演算
2つの数値を入力すると、加減乗除結果を表示する。
加減乗除専用の関数を作成すること。
*/

float CalFourArithmeticOperations(float , float , unsigned char , unsigned char );//四則演算する関数

int main(void)
{
  //input from stdin a,b
  float input[BUFF_LENGTH];
  float buff[3];
  int i = 0 ;
  float val = 0;
  for ( i = 0; i < N_INPUT; i++)
  {
    printf("%s%d%s\n", "Please, input ", N_INPUT - i, "numbers.");
    scanf("%f", &input[i]);
    printf("input is %f \n", input[i]);
  }
  (void)getchar(); //'¥n'の読み捨て

  //printf +,-,*,/
  for ( i = 0; i < N_FUNCTION; i++)
  {
    val = CalFourArithmeticOperations(input[0], input[1], i, 1);
    printf("%f \n", (float)val);
  }
  printf("%s \n", "Please, push Enter key.");
  (void)getchar();//画面を消さないため
  return 0;
}

/*
float a       :先方の入力値
float b       :後方の入力値
int mode      :ADD.+ , SUB.- , MUL.* , DIV./ 
int on_print  :printfあり、なし
*/
float CalFourArithmeticOperations(float a, float b, unsigned char mode, unsigned char on_print)
{
  float result = 0;
  unsigned char ope = 'E';
  switch (mode)
  {
  case ADD /* 足し算 */:
    result = a + b;
    ope = '+';
    break;
  case SUB /* 引き算 */:
    result = a - b;
    ope = '-';
    break;
  case MUL /* 掛け算 */:
    result = a * b;
    ope = '*';
    break;
  case DIV /* 割り算 */:
    if ((b > 0) || (b < 0))
    {
      result = a / b;
      ope = '/';
    }
    break;
  default:
    printf("Coding Error.\n");      
    on_print = 0;
    break;
  }
  if (on_print)
  {
    if (b == ZERO)
    {
      printf("The second number should be non-zero.\n");      
    }else
    {
      printf("A%cB=%f \n", ope, result);
    }
  }
  return result;
}
