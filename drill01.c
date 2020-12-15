#include <stdio.h>
#include <stdlib.h>
int BUFF_LENGTH = 2;
int N_INPUT = 2;
int N_FUNCTION = 4;
/*
1 四則演算
2つの数値を入力すると、加減乗除結果を表示する。
加減乗除専用の関数を作成すること。
*/

/*
float a       :先方の入力値
float b       :後方の入力値
int mode      :1.+ , 2.- , 3.* , 4./ 
int on_print  :printfあり、なし
*/
float cal_four_arithmetic_operations(float a, float b, int mode, int on_print)
{
  float result = 0;
  char ope;
  switch (mode)
  {
  case 0 /* value */:
    result = a + b;
    ope = '+';
    //printf("A+B=%f \n", result);
    break;
  case 1 /* value */:
    result = a - b;
    ope = '-';
    //printf("A-B=%f \n", result);
    break;
  case 2 /* value */:
    result = a * b;
    ope = '*';
    //printf("A*B=%f \n", result);
    break;
  case 3 /* value */:
    if (b == 0)
    {
      result = 0;
      ope = 'E';
    }
    else
    {
      result = a / b;
      ope = '/';
    }
    break;
  default:
    ope = 'E';
    break;
  }
  if (on_print)
  {
    printf("A%cB=%f \n", ope, result);
  }
  return result;
}

int main(void)
{
  //input from stdin a,b
  float input[BUFF_LENGTH];
  float buff[3];
  for (int i = 0; i < N_INPUT; i++)
  {
    printf("%s%d%s\n", "Please, input ", N_INPUT - i, "numbers.");
    scanf("%f", &input[i]);
    printf("input is %f \n", input[i]);
  }
  (void)getchar(); //'¥n'の読み捨て

  //printf +,-,*,/
  float val = 0;
  for (int i = 0; i < N_FUNCTION; i++)
  {
    val = cal_four_arithmetic_operations(input[0], input[1], i, 1);
    printf("%f \n", (float)val);
  }
  printf("%s \n", "Please, push any key.");
  // scanf("%c", &buff[0]);
  (void)getchar();
  return 0;
}
