#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
3 カレンダー
年・月を入力すると、
月間カレンダーを表示する

①基準日から指定した日までの総日数を算出し
　指定月１日の曜日を判定
②各月の日数を取得、２月の場合は閏年判定も

*/
//西暦2000年1月1日以降を対象としています。
//ISO 8601で「2000年1月1日を土曜日とする」と定義 by wikipedia

#define LEN_INPUT_YEAR 5 //yyyy+1文字
#define LEN_INPUT_MONTH 3 //mm+1文字
#define DECIMAL_NUMBER 10//10　strtoul()の基数に使用 
#define REFERENCE_YEAR 2000 //基準とする年（2000年）
#define REFERENCE_MONTH 1 // 基準とする月（１月）
#define REFERENCE_DATE 1 // 基準とする日（１日）
#define NUMBER_AS_SATURDAY 5 //2000年1月1日を
#define NUMBER_OF_ONE_WEEK 7 //7日（１週間）
#define NUMBER_OF_MONTH_IN_A_YEAR 12//12月（１年間の月の数）
#define CORRECTION_VALUE_FOR_ONE_MONTH 1//調整用の１ヶ月を示す値

unsigned char GetDayOfTheWeek(unsigned int ,unsigned char);//曜日を取得
unsigned int GetTheNumberOfDaysInThisYear(unsigned int,unsigned char);//その年の日数を取得
unsigned char GetTheNumberOfDaysInThisMonth(unsigned int,unsigned char);//その月の日数を取得
unsigned int GetTotalDaysFromSpecifiedMonth(unsigned int ,unsigned char );//指定した年月までの基準日からの総日数を取得
void PrintCalendar(unsigned int ,unsigned char );//カレンダーを出力
void GetUserInput(unsigned char , char *);//ユーザーの入力を取得
unsigned int GetUserInputByUnsignedInt(unsigned char);//標準入力からunsigned int型で入力値を取得する
unsigned char FindInputErr(char);

int main( void )
{
  unsigned int input_year;
  unsigned char input_month;
  //input user's choice
  while (1)//2000以上の数が入力されるまで繰り返す。
  {
    printf("Please, input one year after 2000, within 9999 years. ex.2020\n");
    input_year=GetUserInputByUnsignedInt(LEN_INPUT_YEAR); 
    if (input_year>=REFERENCE_YEAR)//基準月以上か確認する。
    {
      break;
    }else
    {
      printf("Invalid value. Please, input again.\n");
    }
  }
  while (1)//０〜１２の間の数が入力されるまで繰り返す。
  {
    printf("Please, input month ex.02\n");
    input_month = (unsigned char)GetUserInputByUnsignedInt(LEN_INPUT_MONTH);
    if (input_month<=NUMBER_OF_MONTH_IN_A_YEAR)
    {
      break;
    }else
    {
      printf("Invalid value. Please, input again.\n");
    }
  }
  PrintCalendar(input_year,input_month);
//デバッグ用。最後に消す  printf("%d",GetTotalDaysFromSpecifiedMonth(input_year, input_month));
  printf("%s\n", "Push any keys.");
  (void)getchar();
  return 0;
}

/*
指定された年月のカレンダーを表示する
unsigned int    input_year     : 指定年
unsigned char   month          : 指定月
*/
void PrintCalendar(unsigned int year ,unsigned char month)
{
  //カレンダーの表示
  unsigned char this_month=GetTheNumberOfDaysInThisMonth(year,month);
  //年月欄表示
  printf("   %d 年 %d 月\n",year,month);
  //曜日欄表示
  printf("月 火 水 木 金 土 日\n");
  //曜日オフセット取得
  unsigned char offset_day=GetDayOfTheWeek(year,month);
  unsigned char cnt = 0;//表示個数のカウンタ
  unsigned char i=0;
  //始まりの曜日合わせ。
  for(i=1; i<=offset_day; i++,cnt++)
  {
    printf("   ");
  }
  //日付を順次表示
  for (i = 1; i <((this_month)+1); i++,cnt++)
  {
    //カウンタがNUMBER_OF_ONE_WEEKに達していたら折り返す
    if((cnt % NUMBER_OF_ONE_WEEK == 0)&&(cnt!=0)) //月曜始まりの月だと1日がcnt==0となるため
    {
      printf("\n");
    }
    printf("%2d ", i); //2桁で表示
  }
  printf("\n");
  return ;
}

/*
指定された年・月からその月の１日における曜日を判定する
unsigned int    input_year     : 指定年
unsigned char   month          : 指定月
*/
unsigned char GetDayOfTheWeek(unsigned int year ,unsigned char month)
{
  //1日の曜日判定
  unsigned char day_of_week = 0;
  day_of_week = (GetTotalDaysFromSpecifiedMonth(year, month)+NUMBER_AS_SATURDAY) % NUMBER_OF_ONE_WEEK; 
  return day_of_week;
}

/*
基準日から指定された年・月までの総日数を取得する
unsigned int    input_year     : 指定年
unsigned char   month          : 指定月
*/
unsigned int GetTotalDaysFromSpecifiedMonth(unsigned int year,unsigned char month)
{
  unsigned int i;
  //基準日からの累積日数
  unsigned int total_day = 0;
  //指定年の前年(year-1)までの総数
    for (i = REFERENCE_YEAR; i <= year-1; i++)
    {
      total_day += GetTheNumberOfDaysInThisYear(i,NUMBER_OF_MONTH_IN_A_YEAR);
    }
  //指定年の総数 ただし、指定月の１月前の月末までなので、1ヶ月分調整が必要
  unsigned char input_month= month-CORRECTION_VALUE_FOR_ONE_MONTH;
  total_day += GetTheNumberOfDaysInThisYear(year,input_month);
  return total_day;
}

/*
指定された年における、1月から指定した月の月末までの総日数を取得する
unsigned int    input_year     : 指定年
unsigned char   month          : 指定月
*/
unsigned int GetTheNumberOfDaysInThisYear(unsigned int year,unsigned char month)
{
  unsigned int this_year_day = 0;
  unsigned char i = 0;
  for (i = 1; i <= month; i++)
  {
   this_year_day+=GetTheNumberOfDaysInThisMonth(year,i); 
  }
  return this_year_day;
}

/*
指定された年における、指定した月の一ヶ月の日数を取得する
unsigned int    input_year     : 指定年
unsigned char   month          : 指定月
*/
unsigned char GetTheNumberOfDaysInThisMonth(unsigned int year,unsigned char month)
{
  unsigned char month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//1月　２月・・・１２月 の日数
  //うるう年処理 　条件：「400で割り切れる年」もしくは、「4で割り切れる年かつ、100で割り切れない年」
  if (month==2)
  {
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
    {
      month_day[1]=29;
    }    
  }
  return month_day[month-1];
}

/*
標準入力から、任意の桁数の数字をunsigned Intで取得する
*/
unsigned int GetUserInputByUnsignedInt(unsigned char input_len)
{
  char input_buff[input_len]; //標準入力から取得するためのバッファ
  unsigned int input_val=0; //取得した文字列を数字化した値
  unsigned char is_over_digits=0;//桁数判定用　桁数が溢れていると１
  unsigned char is_correct_number_of_digits=0;//正しい桁数の以上の入力値が得られたら　１
  char *endp =NULL;
  while(1){
    fgets(input_buff,input_len,stdin);//get input number
    if (input_buff[strlen(input_buff) -1] != '\n')
    {
      is_over_digits = 1;//入力文字数が規定値を超えている
      is_correct_number_of_digits=1;//必要桁数に足りている
      while (getchar()!='\n')
        {//'¥n'まで読み捨て
          if (is_over_digits)//桁溢れしているか　溢れている場合、溢れた分を削除する
          {
            printf("There are too many characters to enter.Overflowing characters are thrown away.\n");   
            is_over_digits = 0;     
          }
        }  
    }else
    {
      is_correct_number_of_digits = 0;
    }
    input_val=strtoul(input_buff,&endp,DECIMAL_NUMBER);
    printf("input is %d \n", input_val);
    
    if ( ( strlen(endp) != 0 ) && ( *endp != '\n' ) )
    {
      printf("input error %c \n", *endp);            
    }else
    { 
      if (is_correct_number_of_digits)
      {
        break;        
      }else
      {
        printf("You have entered too few characters. Please, Input again.\n");   
      }
    }
  }
  return input_val;
}

