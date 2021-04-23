//入力値に関する「あきらかなエラー」という定義がかなり難しいため。全てに対処は致しません。
//今回は、後の処理で想定した入力値以外をエラーとみなしますが、単純にscanfで実装すると、対処仕切れない入力パタンが残ります。
/*
No .9 電話帳
    社員番号を入力すると、
    氏名、内線番号が表示される。 
    データは構造体でアクセスすること。 データ定義方法は自由。
*/
#include <errno.h>
#include <stdio.h>  // 入出力用
#include <stdlib.h> //atoi用
#include <string.h> // 入力時の文字列⇒数値変換用

//数値定義 =====================
#define LEN_EMPLOYEE_NUMBER 9  //9桁 入力可能な整数の桁数 030xxxxxx なので9文字
#define LEN_EMPLOYEE_EXTENTION 4   //4桁 内線番号
#define TRUE 1
#define FALSE 0
//構造体型宣言
//社員情報格納用
typedef struct {
    char employee_number[LEN_EMPLOYEE_NUMBER + 1];//null文字分
    char name[20];
    char employee_extention[LEN_EMPLOYEE_EXTENTION + 1]; //null文字分
}   T_EmployeeData;

// 関数宣言 =====================
unsigned char GetUserInput(T_EmployeeData *);
unsigned char SearchAndGetEmployeeInformationByEmployeeNumber(T_EmployeeData *);

void main(){
    T_EmployeeData user;//社員情報
    unsigned char is_function_succeeded = FALSE;//処理の成否

    //標準入力から社員番号を取得する
    printf("Please, input employee's number.\n");
    printf("If you enter a number greater than %d digits, it will be recognized as a %d-digit number from the beginning.\n", LEN_EMPLOYEE_NUMBER, LEN_EMPLOYEE_NUMBER);
    is_function_succeeded = GetUserInput(&user);
    //入力文字数が足りなかった時の処理
    if (is_function_succeeded == FALSE)
    {
        printf("Not enough characters to enter.\n");
        printf("Push enter keys.");
        getchar(); //画面を残す用
        return;
    };

    //社員番号から社員情報を検索する
    is_function_succeeded = SearchAndGetEmployeeInformationByEmployeeNumber(&user);

    //データベース上に該当する社員情報が存在しない場合の処理
    if(is_function_succeeded == FALSE){
        printf("There is no corresponding employee number in the database.\n");
        printf("Push enter keys.");
        getchar(); //画面を残す用
        return;
    };

    //社員氏名を表示する 
    printf("This employee's name is %s.\n", user.name);
    //内線番号を表示する
    printf("This employee's employee extention is %4s.\n", user.employee_extention);

    printf("Push enter keys.");
    getchar(); //画面を残す用
    return ;
}

/*@brief ユーザーの入力を得る関数           */
/*@param [in] EmployeeData *input_employee_data                         */
/*@return unsigned char :処理の成否          */
unsigned char GetUserInput(T_EmployeeData *input_employee_data)
{
    unsigned char is_process_succeeded = FALSE;
    char input_val_char[LEN_EMPLOYEE_NUMBER + 1]; //null文字分
    scanf("%9s%*[^\n]", &input_val_char); // ここは、セキュリティ面とscanfの関係から、マジックナンバーですが、9を直入れしています。
    while (getchar() != '\n'); // 改行コードの読み飛ばし
    printf("Your input is %s.\n", input_val_char);
    if (strlen(input_val_char)  == LEN_EMPLOYEE_NUMBER){//+1はnull文字分
        is_process_succeeded = TRUE;
    }
    strcpy(input_employee_data->employee_number, input_val_char);
    return is_process_succeeded;
}

/*@brief 社員番号から社員情報を検索し、社員情報を取得する関数         */
/*@param [in] EmployeeData *input_employee_data    */
/*@return unsigned char :処理の成否                 */
unsigned char SearchAndGetEmployeeInformationByEmployeeNumber(T_EmployeeData *input_employee_data)
{
    unsigned char is_process_succeeded = FALSE;
    unsigned int i = 0;
    size_t size_of_database;
    //data base の作成
    T_EmployeeData database_of_employee[] =
        {
            {"030164701", "井熊　駿", "0000"},
            {"030164702", "伊藤　晃人", "1111"},
            {"030164703", "寺澤　翔", "2222"},
        };
    size_of_database = sizeof(database_of_employee) / sizeof(database_of_employee[0]);
    //該当情報の探索
    for (i = 0; i < size_of_database; i++)
    {
        //社員番号が一致するデータがあれば、値を代入
        if (strcmp(database_of_employee[i].employee_number,  input_employee_data->employee_number) == 0)
        {
            strcpy(input_employee_data->name, database_of_employee[i].name);
            strcpy(input_employee_data->employee_extention, database_of_employee[i].employee_extention);
            return is_process_succeeded = TRUE;
        }        
    }

    return is_process_succeeded;
}
