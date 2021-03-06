#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
4
ビット演算
2つの数値x,yを入力すると、
xのyビット目を反転する。
ただし、基本的に桁数は0を最小値とする
*/
//
#define DECIMAL_NUMBER 10//10　strtoul()の基数に使用  
#define LEN_INPUT_X 9//8+1文字 入力可能な整数の桁数 int でオーバーフローしないように8桁に設定
#define ON 1
#define OFF 0
#define ERROR_VAL 100000000//入力可能桁数を8としているため、それより大きい数値をエラー判定値とした

unsigned int GetUserInputByUnsignedInt(unsigned char, unsigned char);//標準入力からunsigned int型で入力値を取得する
int InvertTheYBitOfTheX(int , int);//XのYビット目を反転させる

int main( void )
{
  unsigned int x;//入力値x
  unsigned char y;//入力値y
  unsigned char digits_binary_x=0;//xのビット桁数  
  unsigned char digits_decimal_x=0;//xの10進数の桁数  
  unsigned char len_input_y=0;//yの入力時の文字数
  unsigned int result_val;//反転後の値
  //input user's choice
  printf("Please, enter x and y. It will then display the value of the yth bit of x inverted.\n First, enter x(>0).\n");
  x=GetUserInputByUnsignedInt(LEN_INPUT_X,OFF); 
  if (x!=0)
  {
    digits_binary_x=log2(abs((int)x))+1;             //２進数での桁数を取得 桁数はlog2＋１となる
    digits_decimal_x=log10(digits_binary_x)+1;      //10進数での桁数を取得 桁数はlog10＋１となる　入力用関数における桁数指定のため    
  }else
  {//２進数での桁数を取得 x=0はエラーとなるため　個別処理
    digits_binary_x=1;             //２進数での桁数を取得 0は1桁
    digits_decimal_x=1;      //10進数での桁数を取得 0は1桁        
  }
  printf("２進数では%d桁です。\n",digits_binary_x); 
  printf("10進数では%d桁です。\n",digits_decimal_x);
  len_input_y=digits_decimal_x+1;//終端文字分1をたす

  while (1)//桁数以内の数字が入るまで繰り返す
  {
    printf("Next, enter (0<)y(<=%d). \n",digits_binary_x);
    y = (unsigned char)GetUserInputByUnsignedInt(len_input_y,OFF);//入力時の桁数指定 終端文字のため＋１
    if ((y>0)&&(y<=digits_binary_x))
    {
      break;
    }else
    {
      printf("Invalid value. Please, input again.\n");
    }
  }
  result_val=InvertTheYBitOfTheX(x,y);
  if (result_val==ERROR_VAL)
  {
    printf("Error (y=0).%d\n",result_val);
    printf("%s", "Push enter keys.");
    (void)getchar();        
  }else
  {
    printf("result is%d\n",result_val);
    printf("%s", "Push enter keys.");
    (void)getchar();    
  }
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
    }else if (fix_number_of_digits==1)//文字数を固定した場合の判定
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

/*@brief xのyビット目を反転させる演算     */
/*@param [in] int x 元の数    */
/*@param [in] int y 反転させるビット位置   */
/*@return result 演算後の値     */
int InvertTheYBitOfTheX(int x , int y)//XのYビット目を反転させる
{
  int result;
  if (y<1)
  {
    result =ERROR_VAL;//y-1がマイナスの時はエラーを返す。    
  }else
  {
    result = x ^ (0x01 << (y-1));//yビット目が1の数    
  }
  return result;
}


