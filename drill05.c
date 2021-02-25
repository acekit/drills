#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
5
昼休み判定
時間を入力すると、                  :HHmmの形式で入力
昼休みであるかを判定する。  　        :昼休み中　or 昼休み外　と表示
昼休み前であれば　昼休みまでの時間      :昼休みまでHHmm　と表示
昼休み中であれば　昼休み終了までの時間   :昼休み終了までHHmm　と表示
昼休み後であれば　昼休み終了から経過した時間:昼休み終了からHHmm　と表示
を表示する。
構造体を利用して実装すること        :昼休み関連情報を構造体として作成
*/

//
#define DECIMAL_NUMBER 10//10　strtoul()の基数に使用  
#define LEN_INPUT 7//6+1文字 入力可能な整数の桁数 DDHHmmなので6文字
#define ON 1
#define OFF 0

unsigned int GetUserInputByUnsignedInt(unsigned char, unsigned char);//標準入力からunsigned int型で入力値を取得する


//構造体の型宣言
struct lunch_break_information
{
    char start_time_of_lunch_break[4];    //昼休み開始時間
    char end_time_of_lunch_break[4];      //昼休み終了時間
};
//構造体の型宣言
struct current_situation_based_on_the_lunch_break
{
    char is_lunch_or_not;        //昼休み判定結果　
    char *comment;                  //状況説明文
    char time_difference_from_lunch_break[4];      //昼休み基準の時間差
};

int main( void )
{
    struct lunch_break_information lbi[1]=
    {
        {"1245","1330"}
    };
  //input user's choice
  printf("Please enter the date and time in the format DDHHmm. ex.050530 = 5th,05:30\n");
  x=GetUserInputByUnsignedInt(LEN_INPUT,ON); 
  printf("%s", "Push enter keys.");
  (void)getchar();
  return 0;
}

/*@brief 標準入力から、任意の桁数の数字をunsigned Intで取得する     */
/*@param [in] unsigned char input_len 入力する数字の文字数    */
/*@param [in] unsigned char fix_number_of_digits 入力する文字数を固定するか否か 1で指定文字数のみ可とし、0で指定文字未満でも可とする    */
/*@return unsigned int input_val 入力された数値        */
unsigned int GetUserInputByUnsignedInt(unsigned char input_len,unsigned char fix_number_of_digits)
{
  char input_buff[input_len]; //標準入力から取得するためのバッファ
  unsigned int input_val=0; //取得した文字列を数字化した値
  unsigned char is_over_digits=0;//桁数判定用　桁数が溢れていると１
  unsigned char is_correct_number_of_digits=0;//正しい桁数の以上の入力値が得られたら　１
  char *endp =NULL;
  while(1){//条件を満たすまでループ
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
    }else if (fix_number_of_digits==1)
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
      if ((fix_number_of_digits==0)||(is_correct_number_of_digits==1))
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

