#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
2 じゃんけんゲーム
PCとじゃんけん対戦するゲーム。
1.人間はキーを押下し、
2.PCはランダム値により手を決め、
3.結果を判定・表示する。
4.勝率も表示する。
*/
#define G 1 //ぐー
#define C 2 //チョキ
#define P 3 //パー
#define Q 9 //終了
#define INPUT_LENGTH 2//1文字+終端文字
#define N_MAX 255//最大対戦回数　カウンタがunsigned charのためこれより小さい数
#define USER_LOSE 0 //勝ち負け判定結果　負け
#define USER_WIN 1 //勝ち負け判定結果　勝ち
#define USER_EVEN 2 //勝ち負け判定結果　あいこ
#define VAL_WIN1 -1 //勝ち負け判定における(ユーザーの手-PCの手)の勝ちの値１
#define VAL_WIN2 2  //勝ち負け判定における(ユーザーの手-PCの手)の勝ちの値２
#define VAL_LOSE1 -2 //勝ち負け判定における(ユーザーの手-PCの手)の負けの値１
#define VAL_LOSE2 1  //勝ち負け判定における(ユーザーの手-PCの手)の負けの値２
#define VAL_EVEN 0   //勝ち負け判定における(ユーザーの手-PCの手)のあいこの値

void GetUserInput(unsigned char, char *);//標準入力から文字列を得る関数
unsigned char GetUserChoiseByNum(unsigned char,char * );//ユーザーの入力を取得する関数
unsigned char GetCpuChoiseByNum(void); //PCの手を決定する関数
unsigned char JudgeWinOrLose(unsigned char, unsigned char); //勝敗を判定する関数
float CalculateTheWinningPercentage(unsigned char,unsigned char); //勝率を計算する関数

int main(void)
{
  //start jangkeng
  unsigned char count_all = 0;//全対戦回数
  unsigned char count_win = 0;//全勝利数
  char user_input[INPUT_LENGTH]; //buffer user's choice ex) g,c,p or e:escape from loop
  char user_input_char=0;
  unsigned char user;
  unsigned char pc;
  char pc_val[256];
  unsigned char win_lose_val = 0;
  float win_ratio=0;
  srand(time(NULL)); //rand初期化

  while (1)
  { //終了するまで継続してじゃんけん
  
    //対戦最大数と、現在の対戦数/最大数を表示
    printf("The maximum number of times you can play rock-paper-scissors is %d. Now:%d/%d\n",N_MAX,count_all,N_MAX);
  
    //入力すべき内容を指示
    printf("Please, select your key from '%d' or '%d' or '%d' or '%d'.\n 1=グー,2=チョキ,3=パー 9=終了\n", G, C, P, Q);

    //ユーザーの手を取得
    user = GetUserChoiseByNum(sizeof(user_input),user_input);
    if((user==Q)||(count_all==N_MAX))//終了する場合
    {
      break;
    }
    //試行回数の更新
    count_all++;

    //PCの手を取得
    pc = GetCpuChoiseByNum();

    //勝敗の判定
    win_lose_val = JudgeWinOrLose(user,pc);

    //勝敗の表示
    switch (win_lose_val)
    {
      case 1:
      printf("結果:勝ち\n");
      count_win++;
      break;
      case 2:
      printf("結果:あいこ\n");
      break;
      case 0:
      printf("結果:負け\n");
      break;
    }

    //勝率の算出
    win_ratio=CalculateTheWinningPercentage(count_win,count_all);

    //勝率の表示
    printf("勝率（勝数/全数）=%f\n", win_ratio);
  }
  //終了時の処理
  printf("%s\n", "Thank you for your playing!");
  printf("%s\n", "Push Enter keys.");
  (void)getchar();
  return 0;
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
//ユーザーの入力を取得する関数
unsigned char input_len   : 入力する文字数
         char *input_p    : 入力した値を格納する配列のポインタ
unsigned char user        : 数字に変化した後のユーザの選択         
*/
unsigned char GetUserChoiseByNum(unsigned char input_len,char *input_p )
{
  unsigned char user;
  unsigned char not_get_user_input=1;//ユーザーの入力を受け取っていないと1
  while (not_get_user_input)
  {
    GetUserInput(input_len,input_p);
    user = (unsigned char)atoi(input_p);
    switch (user)
    {
      case G:
        printf("Your choice is %d=グー \n",G);
        not_get_user_input=0;
        break;
      case C:
        printf("Your choice is %d=チョキ \n",C);
        not_get_user_input=0;
        break;
      case P:
        printf("Your choice is %d=パー \n",P);
        not_get_user_input=0;
        break;
      case Q://終了処理の場合
        printf("Your choice is %d=終了 \n",Q);
        not_get_user_input=0;
        break;
    default:
      //NG 指定した手以外の場合
      printf("You selected an invalid key. ->%s\n", input_p);
      printf("Please, input again.\n");
      break;
    }
  }
  return user;
}
unsigned char GetCpuChoiseByNum(void) //PCの手を決定する関数
{
  char pc_val[256];
  unsigned char pc;
  srand(time(NULL)); //rand初期化
  pc = (rand() % 3) + 1;//G,C,Pの３パタン
     //calculate cpu choice
    memset(pc_val, '\0', sizeof(pc_val));
    switch (pc)
    {
    case G:
      strcat(pc_val, "グー");
      break;
    case C:
      strcat(pc_val, "チョキ");
      break;
    case P:
      strcat(pc_val, "パー");
      break;
    default:
      break;
    }
    printf("PC is %c:%s\n",pc, pc_val);
  return pc;
}

//勝敗を判定する関数
/*
  unsigned char user: G or C or P;
  unsigned char PC: G or C or P;
*/
unsigned char JudgeWinOrLose(unsigned char user, unsigned char pc)
{
  char win_lose_val=user - pc;
  switch (win_lose_val)
  {
  case VAL_EVEN://あいこの場合
    win_lose_val = USER_EVEN;
    break;
  case VAL_WIN1: //勝ちの場合
  case VAL_WIN2: //勝ちの場合
    win_lose_val = USER_WIN;
    break;
  case VAL_LOSE1: //負けの場合
  case VAL_LOSE2: //負けの場合
    win_lose_val = USER_LOSE;
    break;
  default:
    break;
  }
  return win_lose_val;
} 
float CalculateTheWinningPercentage(unsigned char count_win,unsigned char count_all)
{
  return (float)count_win/(float)count_all;
}