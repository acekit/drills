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
グー：1,チョキ：2,パー：3 
*/
#define G 1
#define C 2
#define P 3

int main( void )
{
  //start jangkeng
  int count_all=0;
  int count_win=0;
  int on_loop=1;
  char user_input[2];//buffer user's choice ex) g,c,p or e:escape from loop
  int user;
  int pc;
  char pc_val[256];
  	srand(time(NULL));
  while(on_loop){
    printf("Please, select your key from '1' or '2' or '3' or '9'.\n 1=グー,2=チョキ,3=パー 9=終了\n");
    fgets(user_input,2,stdin);//input user's choice
      (void)getchar();
      printf("Your choice is :%s \n",user_input);      
      user=atoi(user_input);
    if ((user==9)) {
      break;
    }else {
     if(user!=G&&user!=C&&user!=P)    
     {
     	//NG 指定した手以外の場合
      printf("You selected an invalid key.%s\n",user_input);
     }else{
     		//OK 指定した手の場合
     	count_all++;
      srand((unsigned int)time(NULL));//初期化
      pc=(rand() % 3)+1;
      printf("%d\n",pc);
      //calculate cpu choice
      if(pc==G){
        strcat(pc_val,"グー");
      }else if(pc==C){
        strcat(pc_val,"チョキ");
      }else{
        strcat(pc_val,"パー");
      }
        printf("PC is :%s\n",pc_val );
      if(user==pc)
      {
        printf("結果:%s\n","あいこ");
      }else if(user<pc){
        printf("結果:%s\n","勝ち");      	        
        count_win++;
      	}else
      	{
        printf("結果:%s\n","負け");      	      		
      	}
      	printf("勝率（勝数/全数）=%f",(float)count_win/(float)count_all);
      }
    }
  }
printf("%s\n","Thank you for your playing!" );
printf("%s\n", "Push any keys.");
(void)getchar();
return 0;
}
