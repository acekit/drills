#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <math.h>
//入力値に関する「あきらかなエラー」という定義がかなり難しいため。全てに対処は致しません。
//今回は、後の処理にで想定した入力値以外をエラーとみなしますが、単純にscanfで実装すると、対処仕切れない入力パタンが残ります。
/*
5
昼休み判定
時間を入力すると、                  :HHmmの形式で入力
昼休みであるかを判定する。  　        :昼休み中　or 昼休み外　と表示
昼休み前であれば　昼休みまでの時間      :昼休みまでHHmm　と表示
昼休み中であれば　昼休み終了までの時間   :昼休み終了までHHmm　と表示
昼休み後であれば　昼休み終了から経過した時間:昼休み終了からHHmm　と表示
を表示する。
構造体を利用して実装すること        :time.h のtm構造体を使用
時分を分のみに変換する関数を自作
分を時分に変換する関数を自作
*/
//
#define DECIMAL_NUMBER 10//10　strtoul()の基数に使用  
#define LEN_INPUT 2//2文字 入力可能な整数の桁数 DD HH mm ずつ入力するので2文字
#define ON 1
#define OFF 0
#define LUNCH_BREAK_START_TIME_HOUR 12//昼休み開始[時]
#define LUNCH_BREAK_START_TIME_MINUTES 45//昼休み開始[分]
#define LUNCH_BREAK_END_TIME_HOUR 13//昼休み終了[時]
#define LUNCH_BREAK_END_TIME_MINUTES 30//昼休み終了[分]
unsigned int GetSerialMinutes(struct tm);//時刻を分に変換する
struct tm GetTimeFromSerialMinutes(unsigned int);//分をtmに時と分で格納する

int main( void )
{
    //time.h のtm構造体を使用
    struct tm start_time;
    struct tm end_time;
    struct tm input_time;
    struct tm print_time;
    char s[LEN_INPUT];//入力用のバッファ
    start_time.tm_hour = LUNCH_BREAK_START_TIME_HOUR;
    start_time.tm_min = LUNCH_BREAK_START_TIME_MINUTES;
    end_time.tm_hour = LUNCH_BREAK_END_TIME_HOUR;
    end_time.tm_min = LUNCH_BREAK_END_TIME_MINUTES;
    unsigned int input_time_serial_minutes;//入力値のシリアル分
    unsigned int start_time_serial_minutes;//入力値のシリアル分
    unsigned int end_time_serial_minutes;//入力値のシリアル分

    //時刻を指定する
    printf("Please enter the date and time in the format HH. ex.14 = 14:xx\n");
    scanf("%2s%*[^\n]" , s);//ここは、セキュリティ面とscanfの関係から、マジックナンバーですが、2を直入れしています。
    while (getchar() != '\n');//改行コードの読み飛ばし
    input_time.tm_hour = atoi(s);
    printf("Please enter the date and time in the format MM. ex.30 = xx:30\n");
    scanf("%2s%*[^\n]" , s);//ここは、セキュリティ面とscanfの関係から、マジックナンバーですが、2を直入れしています。
    while (getchar() != '\n');//改行コードの読み飛ばし
    input_time.tm_min = atoi(s);
    if (((input_time.tm_hour <= 0) || (input_time.tm_hour > 24)) || ((input_time.tm_min <= 0) || (input_time.tm_min > 59)))
    {
        printf("Input value is invalid.Exit the program.");
    }else
    {
        //昼休みか否かを判定する
        // ①昼休みより前か否かを判定する
        // ②昼休みより後か否かを判定する
        // ①でも②でもないと昼休みである。
        input_time_serial_minutes = GetSerialMinutes(input_time);
        start_time_serial_minutes = GetSerialMinutes(start_time);
        end_time_serial_minutes = GetSerialMinutes(end_time);
        if (input_time_serial_minutes < start_time_serial_minutes)//①
        {
            print_time = GetTimeFromSerialMinutes(start_time_serial_minutes - input_time_serial_minutes);
            printf("It is now before lunch break. The lunch break will start in %2d [hour] %2d [min].\n",print_time.tm_hour,print_time.tm_min);
        }else if (input_time_serial_minutes > end_time_serial_minutes)//②
        {
            print_time = GetTimeFromSerialMinutes(input_time_serial_minutes - end_time_serial_minutes);
            printf("It is now after lunch break.  %2d [hour] and %2d [min] have passed since the lunch break.\n",print_time.tm_hour,print_time.tm_min);        
        }else
        {
            print_time = GetTimeFromSerialMinutes(end_time_serial_minutes - input_time_serial_minutes);
            printf("It is now lunch time. The lunch break will end in %2d [hour] %2d [min].\n" , print_time.tm_hour , print_time.tm_min);                
        }
    }
    printf("%s", "Push enter keys.");
    getchar();//画面を残す用
    return 0;
}


/*@brief HH時MM分の時刻情報を格納したtm構造体を、分のみで表した形式に変換する。例：01時00分 => 60     */
/*@param [in] struct tm input_time 変換元の時間    */
/*@return unsigned int minutes 変換後の分        */
unsigned int GetSerialMinutes(struct tm input_time){
    unsigned int minutes;
    minutes = input_time.tm_hour * 60 + input_time.tm_min;//1時間は60分
    return minutes;
}

/*@brief 分のみで表された時刻情報を、X時Y分の形式でtm構造体に格納する。例： 90 => tm_hour=1  tm_min=30    */
/*@param [in] unsigned int minutes 変換元の分    */
/*@return struct tm converted_time 変換後の時間情報         */
struct tm GetTimeFromSerialMinutes(unsigned int minutes){
    struct tm converted_time;
    converted_time.tm_hour = (unsigned char)(minutes / 60);//1時間は60分
    converted_time.tm_min = (unsigned char)(minutes % 60);//60分で割ったあまりが表示分
    return converted_time;
}

