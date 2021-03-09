#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <math.h>
//入力値に関する「あきらかなエラー」という定義がかなり難しいため。全てに対処は致しません。
//今回は、後の処理にで想定した入力値以外をエラーとみなしますが、単純にscanfで実装すると、対処仕切れない入力パタンが残ります。
/*
6 
数当てゲーム
PCがランダムに数値(1〜100)を決め、※入力値は整数としました。
人間が入力した数値と
同じであれば正解であることを表示、
異なれば数値の大小を表示する。
*/
//
#define LEN_INPUT 3//3文字 入力可能な整数の桁数 1~100 なので3文字
#define MAX_VAL 100//数値範囲の最大値　100
#define MIN_VAL 1//数値範囲の最小値　1

unsigned char GetRandomNumberInSpecifiedRange(unsigned char , unsigned char);

int main( void )
{
    char s[LEN_INPUT];//入力用のバッファ
    unsigned char user_val=0;//ユーザーの入力値
    unsigned char pc_val=0;//PCの指定値
    pc_val = GetRandomNumberInSpecifiedRange(MAX_VAL,MIN_VAL);

    while (1)
    {
        //ユーザーの数値を指定する
        printf("Guess the number chosen by the PC.\nPlease enter a single integer value between 1 and 100.\n");
        //scanfだと、桁溢れに対して対処しきれないため注意として表示。例：1000のときは100が入力されてしまう。
        printf("If you enter a number greater than %d digits, it will be recognized as a three-digit number from the beginning.\n",LEN_INPUT);
        scanf("%3s%*[^\n]" , s);//ここは、セキュリティ面とscanfの関係から、マジックナンバーですが、3を直入れしています。
        while (getchar() != '\n');//改行コードの読み飛ばし
        user_val = atoi(s);
        printf("Your answer is %d.\n" , user_val);
        if ((user_val < MIN_VAL) || (user_val > MAX_VAL))//入力値の範囲をチェック
        {
            printf("Input value is invalid.\n");
        }else
        {
            //printf("PC's number is %d\n",pc_val);
            if (pc_val == user_val)
            {
                printf("Correct answer.\n");            
                break;
            }else
            {
                printf("Incorrect answer.\n");                        
                if (pc_val < user_val)
                {
                    printf("Your number is greater than the correct answer.\n");
                }else
                {
                    printf("Your number is less than the correct answer.\n");                
                }
            }
        }
    }
    printf("%s", "Push enter keys.");
    getchar();//画面を残す用
    return 0;
}

/*@brief unsigned char の範囲内で、min_val=< x <=max_val　のランダムな数xを得る。*/
/*@param [in] unsigned char max_val 最大値    */
/*@param [in] unsigned char min_val 最小値    */
/*@return unsigned char x ランダムな数        */
unsigned char GetRandomNumberInSpecifiedRange(unsigned char max_val , unsigned char min_val)
{
    unsigned char x;//出力値
    unsigned char number_of_value_ranges;//[値の範囲の個数]は、最大値ー最小値＋１となる。
    number_of_value_ranges = (max_val - min_val + 1);
    srand(time(NULL)); //rand初期化
    //[値の範囲の個数]で割った余りは[値の範囲の個数]だけ存在する。また、あまりは0~max_val-1となるため、min_valを足す。
    x = (rand() % number_of_value_ranges) + min_val;  
    return x;
}