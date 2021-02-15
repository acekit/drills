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
  print_cal(input_year,input_month);
  printf("%s�_n", "Push any keys.");
  (void)getchar();
  return 0;
}

void print_cal(int year ,int month)
{
  //�J�����_�[�̕\���@���n�܂�ł��B
  int this_month=get_this_month_day(year,month);
  //�N�\��
  printf("   %d �N %d ���_n",year,month);
  //�j���\��
  printf("�� �� �� �� �� �y ���_n");
  //�j���I�t�Z�b�g
  int offset_day=get_day_of_week(year,month);
  int cnt = 0;
  for(int i=1; i<=offset_day; i++,cnt++)
  {
    printf("   ");
  }
  for (int i = 1; i < (int)((this_month)+1); i++,cnt++)
  {
    if(cnt % 7 == 0) 
    {
      printf("�_n");
    }
    if (i > 9) //�����킹
    {
      printf("%d ", i); //2��
    }
    else
    {
      printf("%d  ", i);//1��
    }
  }
  printf("�_n");
  return ;
};
int get_day_of_week(int year ,int month)
{
  //1���̗j������
  int day_of_week = 0;
  day_of_week = (get_total_day(year, month)+5) % 7; //ISO 8601�Łu2000�N1��1����y�j���Ƃ���v�ƒ�` by wikipedia
  //printf("%d", (get_total_day(year, month)));
  return day_of_week;
};
int get_total_day(int year,int month)
{
  //����2000�N1��1������̗ݐϓ���
  int total_day = 0;
  for (size_t i = 1999; i < year-1; i++)
  {
    total_day += get_this_year_day(i,13);
  }
  total_day += get_this_year_day(year,month);
  return total_day;
};
int get_this_year_day(int year,int month)
{
  //�P�����̓���
  int pre_month = month-1;
  int this_year_day = 0;

  for (size_t i = 0; i < pre_month; i++)
  {
   this_year_day+=get_this_month_day(year,i+1); 
  }
  return this_year_day;
};
int get_this_month_day(int year,int month)
{
  int month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  //���邤�N����
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
  {
    month_day[1]=29;
  }
  return month_day[month-1];
  }