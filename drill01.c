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
float cal_four_arithmetic_operations(float a, float b, int mode)
{
  float result = 0;
  switch (mode)
  {
  case 0 /* value */:
    result = a + b;
    //printf("A+B=%f \n", result);
    break;
  case 1 /* value */:
    result = a - b;
    //printf("A-B=%f \n", result);
    break;
  case 2 /* value */:
    result = a * b;
    //printf("A*B=%f \n", result);
    break;
  case 3 /* value */:
    if (b == 0)
    {
      result = 0;
    }
    else
    {
      result = a / b;
    }
    //printf("A/B=%f \n", result);
    break;
  default:
    break;
  }
  return result;
}

int main(void)
{
  //input from stdin a,b
  float input[BUFF_LENGTH];
  float *p_input = input;
  float buff[3];
  for (int i = 0; i < N_INPUT; i++)
  {
    printf("%s\n", "Please, input 2 numbers.");
    scanf("%f", &input[i]);
    printf("input is %f \n", input[i]);
  }
  //printf +,-,*,/
  float val;
  for (int i = 0; i < N_FUNCTION; i++)
  {
    val = cal_four_arithmetic_operations(p_input[0], p_input[1], i);
  //  printf("%f \n", val);
  }
  printf("%s \n", "Please, push enter key.");
  scanf("%c", &buff[0]);

  return 0;
}
