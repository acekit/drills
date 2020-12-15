﻿#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
3 カレンダー
年・月を入力すると、
月間カレンダーを表示する
*/
//西暦0年1月1日以降を対象としています。

int get_day_of_week(int ,int );
int get_this_year_day(int,int);
int get_this_month_day(int,int);
int get_total_day(int ,int );
void print_cal(int ,int );


int main( void )
{
  int input_year,input_month;
  //input user's choice
  printf("Please, input year and month ex.2020 2\n");
  scanf("%d", &input_year);
  scanf("%d", &input_month);
  (void)getchar();
  print_cal(input_year,input_month);
  printf("%s\n", "Push any keys.");
  (void)getchar();
  return 0;
}

void print_cal(int year ,int month)
{
  //カレンダーの表示　月始まりです。
  int this_month=get_this_month_day(year,month);
  //年表示
  printf("    %d \n",year);
  //曜日表示
  printf("月 火 水 木 金 土 日\n");
  //曜日オフセット
  int offset_day=get_day_of_week(year,month);
  int cnt = 0;
  for(int i=1; i<=offset_day; i++,cnt++)
  {
    printf("   ");
  }
  for (int i = 0; i < (int)((this_month+offset_day)/7); i++,cnt++)
  {
    if(cnt % 7 == 0) 
    {
      printf("\n");
    }
    printf("%d",i);
  }
  //
  return ;
};
int get_day_of_week(int year ,int month)
{
  //1日の曜日判定
  int day_of_week = 0;
  day_of_week = get_total_day(year,month) % 7;
  return day_of_week;
};
int get_total_day(int year,int month)
{
  //西暦0年1月1日からの累積日数
  int total_day = 0;
  for (size_t i = 0; i < year-1; i++)
  {
    total_day += get_this_year_day(i,12);
  }
  total_day += get_this_year_day(year,month);
  return total_day;
};
int get_this_year_day(int year,int month)
{
  //１月分の日数 閏年判定
  int pre_month = month - 1 ;
  int this_year_day = 0;

  for (size_t i = 0; i < pre_month; i++)
  {
   this_year_day+=get_this_month_day(year,month); 
  }
  return this_year_day;
};
int get_this_month_day(int year,int month)
{
  int month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
  {
    month_day[1]=29;
  }
  return month_day[month-1];
}