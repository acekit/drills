#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_LENGTH 9//8桁+1桁（符号）
#define N_INPUT 2
#define N_FUNCTION 4
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define ZERO 0
#define ON_PRINT 1 //表示するか否か

/*
1 四則演算
2つの数値を入力すると、加減乗除結果を表示する。
加減乗除専用の関数を作成すること。
*/

double CalFourArithmeticOperations(double , double , unsigned char , unsigned char );//四則演算する関数

int main(void)
{
  //input from stdin a,b
  char input_buff[BUFF_LENGTH];//入力値のバッファ
  double input[N_INPUT];
  unsigned char i = 0 ;
  float val = 0;
  unsigned char is_over_digits = 1;//桁溢れ検出
  char *endp =NULL;

  while ( (int)i != N_INPUT)
  {
    printf("%s%d%s\n", "Please, input ", N_INPUT - i, "numbers.");
    printf("%s\n", "The maximum input value is 8 characters including the decimal point.");
    fgets(input_buff,sizeof(input_buff),stdin);//get input number
    if (input_buff[strlen(input_buff) - 1] != '\n')
    {
      is_over_digits = 1;
      while (getchar()!='\n')
        {//'¥n'まで読み捨て
          if (is_over_digits)
          {
            printf("There are too many characters to enter. Only the top eight apply.\n");   
            is_over_digits = 0;     
          }
        }  
    }
    input[i]=strtod(input_buff,&endp);
    printf("input is %lf \n", input[i]);
    if ( ( strlen(endp) != 0 ) && ( *endp != '\n' ) )
    {
      printf("input error %c \n", *endp);      
    }else
    {
      i=i+1;
    }
  }

  //printf +,-,*,/
  for ( i = 0; i < N_FUNCTION; i++)
  {
    val = CalFourArithmeticOperations(input[0], input[1], i, ON_PRINT);
  }
  printf("%s \n", "Please, push Enter key.");
  (void)getchar();//画面を消さないため
  return 0;
}

/*
double a       :先方の入力値
double b       :後方の入力値
int mode      :ADD.+ , SUB.- , MUL.* , DIV./ 
int on_print  :printfあり、なし
*/
double CalFourArithmeticOperations(double a, double b, unsigned char mode, unsigned char on_print)
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
    if ((b == ZERO) && ( mode == DIV ) )
    {
      printf("The second number should be non-zero.\n");      
    }else
    {
      printf("A%cB=%f \n", ope, result);
    }
  }
  return result;
}
