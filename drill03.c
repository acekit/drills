#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LEN_INPUT_YEAR 4
#define LEN_INPUT_MONTH 2 

/*
3 カレンダー
年・月を入力すると、
月間カレンダーを表示する
*/
//西暦2000年1月1日以降を対象としています。

int GetDayOfTheWeek(int ,int );//曜日を取得
int GetThisYearDays(int,int);//その年の日数を取得
int GetThisMonthDays(int,int);//その月の日数を取得
int GetTotalDays(int ,int );//指定した年月までの基準日からの総日数を取得
void PrintCalendar(int ,int );//カレンダーを出力
void GetUserInput(unsigned char , char *);
unsigned int GetUserInputByUnsignedInt(unsigned char);//標準入力からunsigned int型で入力値を取得する
unsigned char FindInputErr(char);

int main( void )
{
  unsigned int input_year[LEN_INPUT_YEAR];
  unsigned char input_month;
  //input user's choice
  printf("Please, input year ex.2020\n");
  GetUserInputByUnsignedInt(LEN_INPUT_YEAR);
  printf("Please, input month ex.02\n");

  PrintCalendar(input_year,input_month);
  printf("%s\n", "Push any keys.");
  (void)getchar();
  return 0;
}

/*
標準入力より、ユーザーの入力値を得る
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
*/
void PrintCalendar(int year ,int month)
{
  //カレンダーの表示　月始まりです。
  int this_month=GetThisMonthDays(year,month);
  //年表示
  printf("   %d 年 %d 月\n",year,month);
  //曜日表示
  printf("月 火 水 木 金 土 日\n");
  //曜日オフセット
  int offset_day=GetDayOfTheWeek(year,month);
  int cnt = 0;
  for(int i=1; i<=offset_day; i++,cnt++)
  {
    printf("   ");
  }
  for (int i = 1; i < (int)((this_month)+1); i++,cnt++)
  {
    if(cnt % 7 == 0) 
    {
      printf("\n");
    }
    if (i > 9) //桁合わせ
    {
      printf("%d ", i); //2桁
    }
    else
    {
      printf("%d  ", i);//1桁
    }
  }
  printf("\n");
  return ;
};

/*
標準入力より、ユーザーの入力値を得る
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
*/
int GetDayOfTheWeek(int year ,int month)
{
  //1日の曜日判定
  int day_of_week = 0;
  day_of_week = (GetTotalDays(year, month)+5) % 7; //ISO 8601で「2000年1月1日を土曜日とする」と定義 by wikipedia
  //printf("%d", (GetTotalDays(year, month)));
  return day_of_week;
};

/*
標準入力より、ユーザーの入力値を得る
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
*/
int GetTotalDays(int year,int month)
{
  //西暦2000年1月1日からの累積日数
  int total_day = 0;
  for (size_t i = 1999; i < year-1; i++)
  {
    total_day += GetThisYearDays(i,13);
  }
  total_day += GetThisYearDays(year,month);
  return total_day;
};

/*
標準入力より、ユーザーの入力値を得る
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
*/
int GetThisYearDays(int year,int month)
{
  //１月分の日数
  int pre_month = month-1;
  int this_year_day = 0;

  for (size_t i = 0; i < pre_month; i++)
  {
   this_year_day+=GetThisMonthDays(year,i+1); 
  }
  return this_year_day;
};

/*
標準入力より、ユーザーの入力値を得る
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
*/
int GetThisMonthDays(int year,int month)
{
  int month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  //うるう年処理
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
  {
    month_day[1]=29;
  }
  return month_day[month-1];
}

/*
標準入力より、ユーザーの入力値を得る
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
*/
void GetUserInput(unsigned char input_len, char *input_p)
{
  unsigned char is_under_digits=1;
  while(1){
    fgets(input_p,input_len,stdin);//get input number
    if (input_p[strlen(input_p) -1] != '\n')
    {
      is_under_digits = 1;
      while (getchar()!='\n')
        {//'¥n'まで読み捨て
          if (is_under_digits)
          {
            printf("There are too many characters to enter. Please, input again.\n");   
            is_under_digits = 0;     
          }
        }  
    }
    if (is_under_digits)
    {
      break;
    }
  }
  return ;
}

/*
標準入力から、任意の桁数の数字をIntで取得する


*/
unsigned int GetUserInputByUnsignedInt(unsigned char input_len)
{
  char input_buff[input_len]; 
  unsigned int input_val=0;
  unsigned char is_under_digits=1;
  char *endp =NULL;
  while(1){
    fgets(input_buff,input_len,stdin);//get input number
    if (input_buff[strlen(input_buff) -1] != '\n')
    {
      is_under_digits = 1;
      while (getchar()!='\n')
        {//'¥n'まで読み捨て
          if (is_under_digits)
          {
            printf("There are too many characters to enter. Please, input again.\n");   
            is_under_digits = 0;     
          }
        }  
    }
    input_val=strtoul(input_buff,&endp);
    printf("input is %d \n", input_val);
    
    if ( ( strlen(endp) != 0 ) && ( *endp != '\n' ) )
    {
      printf("input error %c \n", *endp);      
    }else
    {
      if ((is_under_digits))
      {
        break;
      }
    }
  }
  

  return (unsigned int)atoi(input_buff);
}