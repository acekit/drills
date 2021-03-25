//入力値に関する「あきらかなエラー」という定義がかなり難しいため。全てに対処は致しません。
//今回は、後の処理にで想定した入力値以外をエラーとみなしますが、単純にscanfで実装すると、対処仕切れない入力パタンが残ります。
/*
7人生ゲーム
誕生日を入力すると、
誕生日が何曜日か、
生まれてから何日経過したかを
表示する
※誕生日の範囲は、1900年以降とする。
（ユーザの誕生日を入力すると解釈し、2021/03/09現在、世界最高齢は118歳であることから問題なし）
*/
#include <errno.h>
#include <stdio.h> // 入出力用
#include <string.h> // 入力時の文字列⇒数値変換用
#include <time.h>   //日時の取得・計算用

//数値定義 =====================
#define LEN_INPUT 9//8文字+1 入力可能な整数の桁数 yyyymmdd なので8文字 + 終端1文字
#define REFERENCE_YEAR 1900 //曜日の基準とする年（1900年 tm構造体のtm_yearの仕様より）
#define TRUE    1
#define FALSE   0

// 関数宣言 =====================
unsigned char GetUserBirthday(struct tm *); 
unsigned char GetUserInputString(char *, unsigned int);
unsigned char GetTmStructureFromYearMonthDay(char* , struct tm*);
unsigned char GetDaysInThisMonth(unsigned int, unsigned char, unsigned char*);
unsigned char InitTmStructure(struct tm *, int , int , int);
unsigned char GetDaysFromJanFirst(unsigned int , unsigned char , unsigned int *);
unsigned char GetSerialDays(struct tm *, unsigned int *);
unsigned char GetDayOfWeek(struct tm *);
unsigned char GetDaysElapsed(struct tm, struct tm, double *);
unsigned char PrintfDayOfTheWeek(unsigned char);
void          PrintfDaysElapsed(int);

// 関数定義 ====================
// メイン
int main( void )
{
    struct tm today;
    struct tm user_birthday;
    unsigned char birthday_mday;    // 誕生日の曜日[0~6](日~土)
    unsigned char is_function_succeeded = TRUE; // エラー判定用フラグ
    time_t current = time( NULL );  // currentに今日の時間情報を格納
    double days_elapsed;            // 経過日数
    today = *localtime( &current ); // 今日の日付をtm構造体に格納

    //誕生日をユーザが入力する----------
    while (1)
    {
        is_function_succeeded = GetUserBirthday( &user_birthday );
        if ( is_function_succeeded == TRUE )
        {
            break;          
        }else
        {
            printf( "There is some error. Please, try again.\n\n" );
        }
    }

    //曜日を取得する----------
    is_function_succeeded = GetDayOfWeek( &user_birthday);
    if ( is_function_succeeded == FALSE )
    {
        printf("There is an error in the function that finds GetDayOfWeek function.\n");
        getchar(); //画面を残す用
        return 0;
    }

    //経過日数を取得----------
    GetDaysElapsed(user_birthday, today, &days_elapsed);

    //結果を出力する----------
    if ( days_elapsed < 0 )//入力値が今日よりも未来だとエラー
    {
        printf( "Input value error. The birthday you entered is in the future.\n" );
    }else
    {
        PrintfDayOfTheWeek( user_birthday.tm_wday );//曜日を表示
        PrintfDaysElapsed( (int)days_elapsed ) ;//経過日数を表示
    }

    printf( "Push enter keys." );
    getchar();//画面を残す用

    return 0;
}


/*@brief ユーザーの誕生日を得る関数*/
/*@param [in] struct tm birthday    */
/*@param [in] unsigned char min_val 最小値    */
/*@return unsigned char status         */
unsigned char GetUserBirthday(struct tm *birthday)
{
    //1.まずは文字列として受け取る
    unsigned char status = FALSE; //処理の成否
    char s[LEN_INPUT];//入力用のバッファ
    printf( "Please enter your birthday in the format yyyymmdd. ex:1999年10月10日=> 19991010\n") ;
    status = GetUserInputString(s, LEN_INPUT - 1); // 終端文字用の1桁を引く
    if ( status == FALSE )
    {
        printf("Error at function GetUserInputString()\n");
        return status;
    }    
    status = GetTmStructureFromYearMonthDay( s , birthday );
    return status;
}

/*@brief ユーザーの入力を文字列で得る関数*/
/*@param [in] char *s 入力用バッファ   */
/*@return char         */
unsigned char GetUserInputString(char *s , unsigned int s_len)// ユーザーの入力を文字列で得る
{
    //1.まずは文字列として受け取る
    unsigned char status = FALSE ;//処理の成否
    // scanfだと、桁溢れに対して対処しきれないため注意として表示。例：3文字制限で1000のときは100が入力されてしまう。
    printf("If you enter a number greater than %d digits, it will be recognized as a %d-digit number from the beginning.\n", s_len, s_len);
    scanf( "%8s%*[^\n]" , s );      // ここは、セキュリティ面とscanfの関係から、マジックナンバーですが、8を直入れしています。
    while ( getchar() != '\n' );    // 改行コードの読み飛ばし
    printf( "Your input is %s.\n" , s );

    status = TRUE;

    return status;
}

/*@brief yyyymmddの形式の日付をtm構造体に格納する*/
/*@param [in] unsigned int year_month_day : 指定年月日yyyymmdd   */
/*@param [in] struct tm tm_time               :tm構造体*/
/*@return unsigned char status         */
unsigned char GetTmStructureFromYearMonthDay(char* year_month_day,struct tm *tm_time)//yyyymmdd形式の日付からtm構造体を得る
{
    unsigned char status = FALSE ;// 処理の成否
    int year;
    int month;
    int day;
    unsigned char month_day;// 1月　２月・・・１２月 の日数

    sscanf( year_month_day ,"%04d%02d%02d" , &year , &month , &day) ;// yyyymmddの形式で分割し代入
    // 入力値エラー判定
    if ( ( year < REFERENCE_YEAR) ||// 年のエラー：基準年以前はエラー
         ( (month < 1) || (month > 12)) ) // 月のエラー：1月より小さい、12月より大きい場合はエラー
    {
        status = FALSE;
        return status;
    }
    status = GetDaysInThisMonth(year, month, &month_day); // 閏年にも対応する月の日数取得
    if ( (day < 1) || (day > month_day)  )// 日のエラー：1日より小さい、月の日数より大きい場合はエラー
    {
        status = FALSE;
        return status;
    }

    status = InitTmStructure( tm_time, year, month, day);// 入力値を初期化
    if ( status == FALSE)
    {
        return status;
    }

    status = TRUE;

    return status;
}

/*指定した年月日でtm構造体を初期化する。*/
/*基本的には経過日時計算のため、時刻は0:0:0とする。*/
/*@param[in]    struct tm time_in           : tm構造体*/
/*@param[in]    unsigned char year          : 指定年*/
/*@param[in]    unsigned char month         : 指定月*/
/*@param[in]    unsigned char day           : 指定日*/
/*@return       unsigned char status        : エラー判定*/
unsigned char InitTmStructure(struct tm *time_in, int year, int month, int day)
{
    unsigned char status = FALSE; // 処理の成否

    time_in->tm_year = year - REFERENCE_YEAR;   // tm構造体のtm_yearの仕様より、[1900からの経過年数]の形式に修正
    time_in->tm_mon = month - 1;                // tm構造体のtm_monの仕様より、月[0-11]
    time_in->tm_mday = day;                     // tm構造体のtm_mdayの仕様より、日 [1-31]
    time_in->tm_hour = 0;                       // 時(日付の足し引きをするため、日時の開始時刻である0:0:0を代入) 
    time_in->tm_min = 0;                        // 分(日付の足し引きをするため、日時の開始時刻である0:0:0を代入) 
    time_in->tm_sec = 0;                        // 秒(日付の足し引きをするため、日時の開始時刻である0:0:0を代入) 
    time_in->tm_wday = 0;                       // 曜日(一時的に0を代入) 
    time_in->tm_yday = 0;                       // 1月1日からの日数 (一時的に0を代入) 
    time_in->tm_isdst = 0;                      // 夏時間無効 

    status = TRUE;

    return status;
}

/*基準日から指定された年・月・日までの総日数(シリアル日数)を取得する*/ 
/*@param[in]    unsigned int    input_year     : 指定年*/
/*@param[in]    unsigned char   month          : 指定月*/
/*@param[in]    unsigned char   day            : 指定日*/
/*@param[in]    unsigned int *total_day        : 総日数のバッファ*/
/*@return       unsigned char status           : エラー判定*/
unsigned char GetSerialDays(struct tm *input_time, unsigned int *total_day)
{
    unsigned int year = input_time->tm_year + REFERENCE_YEAR;
    unsigned char month = input_time->tm_mon;
    unsigned char day = input_time->tm_mday;
    unsigned char input_month ;         // 指定年の月総数 
    unsigned int i;                     // 基準日からの累積日数
    total_day[0] = 0;                   // 初期化
    unsigned char status = FALSE;
    unsigned int number_of_days_in_this_year = 0;

    //経過年数分の日数を足し合わせる
    for (i = REFERENCE_YEAR; i <= year - 1; i++)
    {
        status = GetDaysFromJanFirst(i, 12, &number_of_days_in_this_year); //12か月
        if ( status == FALSE)
        {
            return status;
        }

        total_day[0] += number_of_days_in_this_year;
    }

    // 指定年内の指定月までの日数を取得し、足し合わせる
    if (month > 0) //指定月が1月の場合は日数は０
    {
        input_month = month - 1; // 指定月の１月前の月末までなので、1ヶ月分調整
        status = GetDaysFromJanFirst(year, input_month, &number_of_days_in_this_year);
        if (status == FALSE)
        {
            return status;
        }
    }else
    {
        number_of_days_in_this_year = 0;
    }
    total_day[0] += number_of_days_in_this_year;

    // 指定年内の指定日までの日数を足し合わせる
    total_day[0] += day;

    status = TRUE;

    return status;
}

/*
指定された年における、1月から指定した月の月末までの総日数を取得する
/*@param[in]    unsigned int    input_year     : 指定年*/
/*@param[in]    unsigned char   month          : 指定月*/
/*@param[in]    unsigned int *this_year_day    : 総日数のバッファ*/
/*@return       unsigned char status           : エラー判定*/
unsigned char GetDaysFromJanFirst(unsigned int year, unsigned char month, unsigned int *this_year_day)
{
    this_year_day[0] = 0;
    unsigned char number_of_days_in_this_month = 0;
    unsigned char status = FALSE;
    unsigned char i;

    for (i = 1; i <= month; i++)
    {
        status = GetDaysInThisMonth(year, i, &number_of_days_in_this_month);
        if ( status == 0)
        {
            return status;
        }

        this_year_day[0] += number_of_days_in_this_month;
    }
    status = TRUE;

    return status;
}

/*指定された年における、指定した月の一ヶ月の日数を取得する*/
/*@param[in]    unsigned int    input_year     : 指定年*/
/*@return       unsigned char   month          : 指定月*/
unsigned char GetDaysInThisMonth(unsigned int year, unsigned char month, unsigned char *month_day)
{
    unsigned char status = FALSE;
    unsigned char month_day_array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //1月　２月・・・１２月 の日数
    // うるう年処理 条件：「400で割り切れる年」もしくは、「4で割り切れる年かつ、100で割り切れない年」
    if( (month > 0) || (month < 13) )
    {    
        if (month == 2)
        {
            if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
            {
                month_day_array[1] = 29;
            }  
        }
        month_day[0] = ( unsigned char ) month_day_array[ month - 1 ];
        status = TRUE;
    }

    return status;
}

/*曜日を求める(修正する)処理*/
/*@param[in]    struct tm *time_in  :指定日*/
/*@return       status              :エラー判定*/
unsigned char GetDayOfWeek(struct tm *time_in)
{
    struct tm time_reference;        //基準日
    unsigned int t_time_reference;   //基準日のシリアル日数
    unsigned int t_time_in;         //指定日のシリアル日数
    unsigned int t_difference;      //基準日からの差分
    unsigned char status = FALSE;
    
    //基準日の初期化
    status = InitTmStructure( &time_reference, REFERENCE_YEAR, 1, 1);
    if ( status == FALSE)
    {
        return status;
    }
    
    status = GetSerialDays( &time_reference, &t_time_reference);
    if (status == FALSE)
    {
        return status;
    }

    status = GetSerialDays(time_in, &t_time_in);
    if (status == FALSE)
    {
        return status;
    }

    /* 基準日との差から曜日を判定 */
    t_difference =( t_time_in - t_time_reference);
    time_in->tm_wday = t_difference % 7 + 1; //1900/01/01は月曜日（1）
    if ( time_in->tm_wday == 7)
    {
        time_in->tm_wday = 0;
    }

    status = TRUE;

    return status;
}

/*経過日数を計算する*/
/*@param[in] struct tm *start_time */
/*@param[in] struct tm *end_time */
/*@param[in] double *days_elapsed 経過時間*/
/*@return status エラー判定 */
unsigned char GetDaysElapsed(struct tm start_time, struct tm end_time, double *days_elapsed)
{
    unsigned char status = FALSE;
    unsigned int start_serial_time;//シリアル日数　開始日
    unsigned int end_serial_time;  //シリアル日数　終了日
    status = GetSerialDays( &start_time, &start_serial_time);
    if (status == FALSE)
    {
        return status;
    }

    status = GetSerialDays( &end_time, &end_serial_time);
    if (status == FALSE)
    {
        return status;
    }

    days_elapsed[0] = (end_serial_time - start_serial_time) ; 

    status = TRUE;

    return status;
}

/*曜日を出力する*/
/*@param[in] unsigned char wday 曜日を表す数値　tm_wdayに準拠*/
/*@return  */
unsigned char PrintfDayOfTheWeek(unsigned char wday)
{
    unsigned char status = FALSE;
    if ( ( wday < 0) || ( wday > 6 ) )
    {
        return status;
    }
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

    status = TRUE;

    return status;
}

/*経過日数を出力する*/
/*@param[in] unsigned int days_elapsed 経過日数*/
/*@return  */
void PrintfDaysElapsed(int days_elapsed)
{
    printf("The number of days elapsed from the birthday is %d days.\n",days_elapsed);

    return;
}