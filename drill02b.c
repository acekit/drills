#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
2 じゃんけんゲーム
PCとじゃんけん対戦するゲーム。
人間はキーを押下し、
PCはランダム値により手を決め、
結果を判定・表示する。
勝率も表示する。
*/
#define G 1 //ぐー
#define C 2 //チョキ
#define P 3 //パー
#define Q 9 //終了

int main(void)
{
  //start jangkeng
  int count_all = 0;
  int count_win = 0;
  int on_loop = 1;
  char user_input[2]; //buffer user's choice ex) g,c,p or e:escape from loop
  char user_input_char=0;
  int user;
  int pc;
  char pc_val[256];
  srand(time(NULL)); //rand初期化

  while (on_loop)
  { //終了するまで継続してじゃんけん
    printf("Please, select your key from '%d' or '%d' or '%d' or '%d'.\n 1=グー,2=チョキ,3=パー 9=終了\n", G, C, P, Q);
    fgets(user_input, 2, stdin); //input user's choice
    (void)getchar();             //¥nの読み飛ばし
    printf("Your choice is :%s \n", user_input);
    user = atoi(user_input);
    if ((user == Q))
    { //終了処理の場合
      break;
    }
    else
    {
      if (user != G && user != C && user != P)
      {
        //NG 指定した手以外の場合
        printf("You selected an invalid key.%s\n", user_input);
      }
      else
      {
        //OK 指定した手の場合
        count_all++;
        srand((unsigned int)time(NULL)); //初期化
        pc = (rand() % 3) + 1;
        printf("%d\n", pc);
        //calculate cpu choice
        memset(pc_val, '\0', sizeof(pc_val));
        if (pc == G)
        {
          strcat(pc_val, "グー");
        }
        else if (pc == C)
        {
          strcat(pc_val, "チョキ");
        }
        else
        {
          strcat(pc_val, "パー");
        }
        printf("PC is :%s\n", pc_val);
        if (user == pc)
        {
          printf("結果:%s\n", "あいこ");
        }
        else if (user < pc)
        {
          printf("結果:%s\n", "勝ち");
          count_win++;
        }
        else
        {
          printf("結果:%s\n", "負け");
        }
        printf("勝率（勝数/全数）=%f", (float)count_win / (float)count_all);
      }
    }
  }
  //終了時の処理
  printf("%s\n", "Thank you for your playing!");
  printf("%s\n", "Push any keys.");
  (void)getchar();
  return 0;
}
