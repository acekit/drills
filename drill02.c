#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
2 じゃんけんゲーム
PCとじゃんけん対戦するゲーム。
人間はキーを押下し、PCはランダム値により手を決め、結果を判定・表示する。勝率も表示する。
グー：g,チョキ：c,パー：p
*/

int main( void )
{
  //start jangkeng
  int on_loop=1;
  char user[2];//buffer user's choice ex) g,c,p or e:escape from loop
  srand(time(NULL));
  while(on_loop){
    while(){

    }
    fgets(user,2,stdin);//input user's choice
    if ((user[0]=='e')) {
      printf("%s\n",user);
      /* code */
      break;
    }

    if(user[0]!='g'&&user[0]!='c'&&user[0]!='p'){

    }else{
      double v_rand;
      v_rand=(double)rand();
      printf("%f\n",v_rand);
      //calculate cpu choice
      if(v_rand>(float)2/3){
        printf("%c\n",'g' );
      }else if(v_rand>(float)1/3){
        printf("%c\n",'c' );
      }else{
        printf("%c\n",'p' );
      }
    }
    /*  switch (a) {
    case :
  }*/
}
printf("%s\n","Thank you for your playing!" );
//transfer values to float from char
//printf +,-,*,/
return 0;
}
