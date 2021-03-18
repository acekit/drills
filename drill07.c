#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <math.h>
//入力値に関する「あきらかなエラー」という定義がかなり難しいため。全てに対処は致しません。
//今回は、後の処理にで想定した入力値以外をエラーとみなしますが、単純にscanfで実装すると、対処仕切れない入力パタンが残ります。
/*
7
人生ゲーム
誕生日を入力すると、
誕生日が何曜日か、
生まれてから何日経過したかを
表示する

誕生日の範囲は、1900年以降とする。
（ユーザの誕生日を入力すると解釈し、2021/03/09現在、世界最高齢は118歳であることから問題なし）
１誕生日をユーザが入力する関数
    8文字で入力
    4,2,2に区切る
    年月日にエラーがないか確認する
    それぞれをtm_year,tm_mon,tm_mdayに格納
2誕生日が何曜かを判定する関数
    tm構造体から、曜日を判定する
3誕生日から今日までが何日間か計算する関数
    入力した時刻現在のtm構造体を得る。
    誕生日との差分(difftime)から、経過日数を取得する。
4曜日を表示する関数
    曜日を表示
5経過日数を表示する関数
    経過時間を表示
*/

//数値定義
#define LEN_INPUT 9//8文字+1 入力可能な整数の桁数 yyyymmdd なので8文字 + 終端1文字
#define REFERENCE_YEAR 1900 //曜日の基準とする年（1900年）

typedef enum{ //エラー判定
        ERROR,
        SUCCESS
} enum_status;

//１誕生日をユーザが入力する
enum_status GetUserBirthday(struct tm*);//ユーザーの誕生日を得る
enum_status GetUserInputString(char *);//ユーザーの入力を文字列で得る
enum_status GetTmStructureFromYearMonthDay(char* , struct tm*);//yyyymmdd形式の日付からtm構造体を得る
unsigned char GetTheNumberOfDaysInThisMonth(unsigned int,unsigned char);//その月の日数を取得

//2誕生日が何曜かを判定する
enum_status GetDayOfWeek(struct tm * );//tm構造体の曜日を日付から再取得する関数

//3誕生日から今日までが何日間か計算する
float GetTheNumberOfDaysElapsed(struct tm  , struct tm  );//経過日数を求める関数

//4曜日を表示する
void PrintfDayOfTheWeek(unsigned char);//曜日をprintfする関数

//5経過日数を表示する
void PrintfTheNumberOfDaysElapsed(int);//経過日数をprintfする関数

int main( void )
{
    struct tm today;
    struct tm user_birthday;
    enum_status is_function_status = SUCCESS;//エラー判定用フラグ
    time_t current = time( NULL );//currentに今日の時間情報を格納
    char s[LEN_INPUT];//入力用のバッファ
    float days_elapsed;//経過日数
    today = *localtime( &current );//今日の日付をtm構造体に格納

    //誕生日をユーザが入力する
    while (1)
    {
        is_function_status = GetUserBirthday( &user_birthday );
        printf( "debug\n" );
        if ( is_function_status == SUCCESS )
        {
            break;          
        }else
        {
            printf( "There is some error. Please, try again.\n\n" );
        }
    }

    //曜日を取得する
    is_function_status = GetDayOfWeek( &user_birthday );

    //経過日数を取得
    days_elapsed = GetTheNumberOfDaysElapsed( user_birthday, today );  

    //結果を出力する
    if ( days_elapsed < 0 )//入力値が今日よりも未来だとエラー
    {
        printf( "Input value error. The birthday you entered is in the future.\n" );
    }else
    {
        PrintfDayOfTheWeek( user_birthday.tm_wday );//曜日を表示
        PrintfTheNumberOfDaysElapsed( (int)days_elapsed ) ;//経過日数を表示
    }
    printf( "%s", "Push enter keys." );
    getchar();//画面を残す用
    return 0;
}

/*@brief ユーザーの誕生日を得る関数*/
/*@param [in] struct tm birthday    */
/*@param [in] unsigned char min_val 最小値    */
/*@return enum_status status         */
enum_status GetUserBirthday(struct tm *birthday)
{
    //1.まずは文字列として受け取る
    enum_status status = SUCCESS ;//処理の成否
    char s[LEN_INPUT];//入力用のバッファ
    printf( "Please enter your birthday in the format yyyymmdd. ex:1999年10月10日=> 19991010\n") ;
    //scanfだと、桁溢れに対して対処しきれないため注意として表示。例：1000のときは100が入力されてしまう。
    status = GetUserInputString( s );
    status = GetTmStructureFromYearMonthDay( s , birthday );
    return status;
}

/*@brief ユーザーの入力を文字列で得る関数*/
/*@param [in] char *s 入力用バッファ   */
/*@return char         */
enum_status GetUserInputString(char *s)//ユーザーの入力を文字列で得る
{
    //1.まずは文字列として受け取る
    enum_status status = SUCCESS ;//処理の成否
    unsigned char s_len =sizeof( s ); //入力文字数
    //scanfだと、桁溢れに対して対処しきれないため注意として表示。例：1000のときは100が入力されてしまう。
    printf( "If you enter a number greater than %d digits, it will be recognized as a %d-digit number from the beginning.\n", s_len,s_len );
    scanf( "%8s%*[^\n]" , s );//ここは、セキュリティ面とscanfの関係から、マジックナンバーですが、8を直入れしています。
    while ( getchar() != '\n' );//改行コードの読み飛ばし
    printf( "Your input is %s.\n" , s );
    if (sizeof( s ) < ( LEN_INPUT-1 ) )//終端文字を除く文字数との比較
    {
        status = ERROR;
    }
    return status;
}

/*@brief yyyymmddの形式の日付をtm構造体に格納する*/
/*@param [in] unsigned int    year_month_day : 指定年月日yyyymmdd   */
/*@param [in] struct tm tm_time               :tm構造体*/
/*@return enum_status status         */
enum_status GetTmStructureFromYearMonthDay(char* year_month_day,struct tm *tm_time)//yyyymmdd形式の日付からtm構造体を得る
{
    enum_status status = SUCCESS ;//処理の成否
    int year;
    int month;
    int day;
    unsigned char month_day;//1月　２月・・・１２月 の日数

    sscanf( year_month_day ,"%04d%02d%02d" , &year , &month , &day) ;//yyyymmddの形式で分割し代入
    //入力値エラー判定
    if ( (year < REFERENCE_YEAR) )//年のエラー：基準年以前はエラー
    {
        status = ERROR;
    }
    if ( (month < 1) || (month > 12)  )//月のエラー：1月より小さい、12月より大きい場合はエラー
    {
        status = ERROR;
    }
    month_day = GetTheNumberOfDaysInThisMonth(year , month);//閏年にも対応する月の日数取得
    if ( (day < 1) || (day > month_day)  )//日のエラー：1日より小さい、月の日数より大きい場合はエラー
    {
        status = ERROR;
    }
    if (status == SUCCESS)
    {
        tm_time->tm_year = year-REFERENCE_YEAR;//tm構造体のtm_yearの仕様より、[1900からの経過年数]の形式に修正
        tm_time->tm_mon  = month-1;//tm構造体のtm_monの仕様より、月[0-11]
        tm_time->tm_mday = day;//tm構造体のtm_mdayの仕様より、日 [1-31] 
        /* 時分秒曜日を適当に入力 */
        tm_time->tm_hour = 0; /* 時 (適当に入力)  */
        tm_time->tm_min  = 0; /* 分 (適当に入力)  */
        tm_time->tm_sec  = 0; /* 秒 (適当に入力)  */
        tm_time->tm_wday = 0; /* 曜日 (適当に入力) */
        tm_time->tm_yday = 0; /* 1月1日からの日数 (適当に入力) */        
    }
    return status;
}

/*
指定された年における、指定した月の一ヶ月の日数を取得する
unsigned int    input_year     : 指定年
unsigned char   month          : 指定月
*/
unsigned char GetTheNumberOfDaysInThisMonth(unsigned int year,unsigned char month)
{
  unsigned char month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//1月　２月・・・１２月 の日数
  //うるう年処理 　条件：「400で割り切れる年」もしくは、「4で割り切れる年かつ、100で割り切れない年」
  if (month==2)
  {
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
    {
      month_day[1] = 29;
    }    
  }
  return month_day[month-1];
}

/*曜日を求める(修正する)処理*/
/*@param[in] struct tm *time_in*/
/*@return status エラー判定*/
enum_status GetDayOfWeek(struct tm *time_in) {
    time_t t;//time_t型のバッファ
    enum_status status = SUCCESS;

    /* mktime 関数で変換 */
    if ( (t = mktime( time_in ) ) == (time_t)(-1) ) {
        status = ERROR;
    }
    /* 地方時に変換 */
    time_in = localtime( &t );

    return status;
}

/*経過日数を計算する*/
/*曜日を求める(修正する)処理*/
/*@param[in] struct tm *start_time */
/*@param[in] struct tm *end_time */
/*@return result 計算結果 */
float GetTheNumberOfDaysElapsed(struct tm start_time, struct tm end_time)
{
    float result;
    time_t start_serial_time = mktime( &start_time );
    time_t end_serial_time = mktime( &end_time );

    result = difftime( end_serial_time , start_serial_time ) / 60 / 60 / 24;//秒を分・時間・日で割る

    return result;
}

/*曜日を出力する*/
/*@param[in] unsigned char wday 曜日を表す数値　tm_wdayに準拠*/
/*@return  */
void PrintfDayOfTheWeek(unsigned char wday)
{
    char weeks[][10] = {//Wednesdayの文字数+1
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    printf("This day is %s.\n", weeks[wday]);
    
    return ;
}

/*経過日数を出力する*/
/*@param[in] unsigned int days_elapsed 経過日数*/
/*@return  */
void PrintfTheNumberOfDaysElapsed(int days_elapsed)
{
    printf("The number of days elapsed from the birthday is %d days.",days_elapsed);

    return;
}