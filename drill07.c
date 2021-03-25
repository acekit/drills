//���͒l�Ɋւ���u�����炩�ȃG���[�v�Ƃ�����`�����Ȃ������߁B�S�ĂɑΏ��͒v���܂���B
//����́A��̏����ɂőz�肵�����͒l�ȊO���G���[�Ƃ݂Ȃ��܂����A�P����scanf�Ŏ�������ƁA�Ώ��d�؂�Ȃ����̓p�^�����c��܂��B
/*
7�l���Q�[��
�a��������͂���ƁA
�a���������j�����A
���܂�Ă��牽���o�߂�������
�\������
���a�����͈̔͂́A1900�N�ȍ~�Ƃ���B
�i���[�U�̒a��������͂���Ɖ��߂��A2021/03/09���݁A���E�ō����118�΂ł��邱�Ƃ�����Ȃ��j
*/
#include <errno.h>
#include <stdio.h> // ���o�͗p
#include <string.h> // ���͎��̕�����ː��l�ϊ��p
#include <time.h>   //�����̎擾�E�v�Z�p

//���l��` =====================
#define LEN_INPUT 9//8����+1 ���͉\�Ȑ����̌��� yyyymmdd �Ȃ̂�8���� + �I�[1����
#define REFERENCE_YEAR 1900 //�j���̊�Ƃ���N�i1900�N tm�\���̂�tm_year�̎d�l���j
#define TRUE    1
#define FALSE   0

// �֐��錾 =====================
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

// �֐���` ====================
// ���C��
int main( void )
{
    struct tm today;
    struct tm user_birthday;
    unsigned char birthday_mday;    // �a�����̗j��[0~6](��~�y)
    unsigned char is_function_succeeded = TRUE; // �G���[����p�t���O
    time_t current = time( NULL );  // current�ɍ����̎��ԏ����i�[
    double days_elapsed;            // �o�ߓ���
    today = *localtime( &current ); // �����̓��t��tm�\���̂Ɋi�[

    //�a���������[�U�����͂���----------
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

    //�j�����擾����----------
    is_function_succeeded = GetDayOfWeek( &user_birthday);
    if ( is_function_succeeded == FALSE )
    {
        printf("There is an error in the function that finds GetDayOfWeek function.\n");
        getchar(); //��ʂ��c���p
        return 0;
    }

    //�o�ߓ������擾----------
    GetDaysElapsed(user_birthday, today, &days_elapsed);

    //���ʂ��o�͂���----------
    if ( days_elapsed < 0 )//���͒l�����������������ƃG���[
    {
        printf( "Input value error. The birthday you entered is in the future.\n" );
    }else
    {
        PrintfDayOfTheWeek( user_birthday.tm_wday );//�j����\��
        PrintfDaysElapsed( (int)days_elapsed ) ;//�o�ߓ�����\��
    }

    printf( "Push enter keys." );
    getchar();//��ʂ��c���p

    return 0;
}


/*@brief ���[�U�[�̒a�����𓾂�֐�*/
/*@param [in] struct tm birthday    */
/*@param [in] unsigned char min_val �ŏ��l    */
/*@return unsigned char status         */
unsigned char GetUserBirthday(struct tm *birthday)
{
    //1.�܂��͕�����Ƃ��Ď󂯎��
    unsigned char status = FALSE; //�����̐���
    char s[LEN_INPUT];//���͗p�̃o�b�t�@
    printf( "Please enter your birthday in the format yyyymmdd. ex:1999�N10��10��=> 19991010\n") ;
    status = GetUserInputString(s, LEN_INPUT - 1); // �I�[�����p��1��������
    if ( status == FALSE )
    {
        printf("Error at function GetUserInputString()\n");
        return status;
    }    
    status = GetTmStructureFromYearMonthDay( s , birthday );
    return status;
}

/*@brief ���[�U�[�̓��͂𕶎���œ���֐�*/
/*@param [in] char *s ���͗p�o�b�t�@   */
/*@return char         */
unsigned char GetUserInputString(char *s , unsigned int s_len)// ���[�U�[�̓��͂𕶎���œ���
{
    //1.�܂��͕�����Ƃ��Ď󂯎��
    unsigned char status = FALSE ;//�����̐���
    // scanf���ƁA�����ɑ΂��đΏ�������Ȃ����ߒ��ӂƂ��ĕ\���B��F3����������1000�̂Ƃ���100�����͂���Ă��܂��B
    printf("If you enter a number greater than %d digits, it will be recognized as a %d-digit number from the beginning.\n", s_len, s_len);
    scanf( "%8s%*[^\n]" , s );      // �����́A�Z�L�����e�B�ʂ�scanf�̊֌W����A�}�W�b�N�i���o�[�ł����A8�𒼓��ꂵ�Ă��܂��B
    while ( getchar() != '\n' );    // ���s�R�[�h�̓ǂݔ�΂�
    printf( "Your input is %s.\n" , s );

    status = TRUE;

    return status;
}

/*@brief yyyymmdd�̌`���̓��t��tm�\���̂Ɋi�[����*/
/*@param [in] unsigned int year_month_day : �w��N����yyyymmdd   */
/*@param [in] struct tm tm_time               :tm�\����*/
/*@return unsigned char status         */
unsigned char GetTmStructureFromYearMonthDay(char* year_month_day,struct tm *tm_time)//yyyymmdd�`���̓��t����tm�\���̂𓾂�
{
    unsigned char status = FALSE ;// �����̐���
    int year;
    int month;
    int day;
    unsigned char month_day;// 1���@�Q���E�E�E�P�Q�� �̓���

    sscanf( year_month_day ,"%04d%02d%02d" , &year , &month , &day) ;// yyyymmdd�̌`���ŕ��������
    // ���͒l�G���[����
    if ( ( year < REFERENCE_YEAR) ||// �N�̃G���[�F��N�ȑO�̓G���[
         ( (month < 1) || (month > 12)) ) // ���̃G���[�F1����菬�����A12�����傫���ꍇ�̓G���[
    {
        status = FALSE;
        return status;
    }
    status = GetDaysInThisMonth(year, month, &month_day); // �[�N�ɂ��Ή����錎�̓����擾
    if ( (day < 1) || (day > month_day)  )// ���̃G���[�F1����菬�����A���̓������傫���ꍇ�̓G���[
    {
        status = FALSE;
        return status;
    }

    status = InitTmStructure( tm_time, year, month, day);// ���͒l��������
    if ( status == FALSE)
    {
        return status;
    }

    status = TRUE;

    return status;
}

/*�w�肵���N������tm�\���̂�����������B*/
/*��{�I�ɂ͌o�ߓ����v�Z�̂��߁A������0:0:0�Ƃ���B*/
/*@param[in]    struct tm time_in           : tm�\����*/
/*@param[in]    unsigned char year          : �w��N*/
/*@param[in]    unsigned char month         : �w�茎*/
/*@param[in]    unsigned char day           : �w���*/
/*@return       unsigned char status        : �G���[����*/
unsigned char InitTmStructure(struct tm *time_in, int year, int month, int day)
{
    unsigned char status = FALSE; // �����̐���

    time_in->tm_year = year - REFERENCE_YEAR;   // tm�\���̂�tm_year�̎d�l���A[1900����̌o�ߔN��]�̌`���ɏC��
    time_in->tm_mon = month - 1;                // tm�\���̂�tm_mon�̎d�l���A��[0-11]
    time_in->tm_mday = day;                     // tm�\���̂�tm_mday�̎d�l���A�� [1-31]
    time_in->tm_hour = 0;                       // ��(���t�̑������������邽�߁A�����̊J�n�����ł���0:0:0����) 
    time_in->tm_min = 0;                        // ��(���t�̑������������邽�߁A�����̊J�n�����ł���0:0:0����) 
    time_in->tm_sec = 0;                        // �b(���t�̑������������邽�߁A�����̊J�n�����ł���0:0:0����) 
    time_in->tm_wday = 0;                       // �j��(�ꎞ�I��0����) 
    time_in->tm_yday = 0;                       // 1��1������̓��� (�ꎞ�I��0����) 
    time_in->tm_isdst = 0;                      // �Ď��Ԗ��� 

    status = TRUE;

    return status;
}

/*�������w�肳�ꂽ�N�E���E���܂ł̑�����(�V���A������)���擾����*/ 
/*@param[in]    unsigned int    input_year     : �w��N*/
/*@param[in]    unsigned char   month          : �w�茎*/
/*@param[in]    unsigned char   day            : �w���*/
/*@param[in]    unsigned int *total_day        : �������̃o�b�t�@*/
/*@return       unsigned char status           : �G���[����*/
unsigned char GetSerialDays(struct tm *input_time, unsigned int *total_day)
{
    unsigned int year = input_time->tm_year + REFERENCE_YEAR;
    unsigned char month = input_time->tm_mon;
    unsigned char day = input_time->tm_mday;
    unsigned char input_month ;         // �w��N�̌����� 
    unsigned int i;                     // �������̗ݐϓ���
    total_day[0] = 0;                   // ������
    unsigned char status = FALSE;
    unsigned int number_of_days_in_this_year = 0;

    //�o�ߔN�����̓����𑫂����킹��
    for (i = REFERENCE_YEAR; i <= year - 1; i++)
    {
        status = GetDaysFromJanFirst(i, 12, &number_of_days_in_this_year); //12����
        if ( status == FALSE)
        {
            return status;
        }

        total_day[0] += number_of_days_in_this_year;
    }

    // �w��N���̎w�茎�܂ł̓������擾���A�������킹��
    if (month > 0) //�w�茎��1���̏ꍇ�͓����͂O
    {
        input_month = month - 1; // �w�茎�̂P���O�̌����܂łȂ̂ŁA1����������
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

    // �w��N���̎w����܂ł̓����𑫂����킹��
    total_day[0] += day;

    status = TRUE;

    return status;
}

/*
�w�肳�ꂽ�N�ɂ�����A1������w�肵�����̌����܂ł̑��������擾����
/*@param[in]    unsigned int    input_year     : �w��N*/
/*@param[in]    unsigned char   month          : �w�茎*/
/*@param[in]    unsigned int *this_year_day    : �������̃o�b�t�@*/
/*@return       unsigned char status           : �G���[����*/
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

/*�w�肳�ꂽ�N�ɂ�����A�w�肵�����̈ꃖ���̓������擾����*/
/*@param[in]    unsigned int    input_year     : �w��N*/
/*@return       unsigned char   month          : �w�茎*/
unsigned char GetDaysInThisMonth(unsigned int year, unsigned char month, unsigned char *month_day)
{
    unsigned char status = FALSE;
    unsigned char month_day_array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //1���@�Q���E�E�E�P�Q�� �̓���
    // ���邤�N���� �����F�u400�Ŋ���؂��N�v�������́A�u4�Ŋ���؂��N���A100�Ŋ���؂�Ȃ��N�v
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

/*�j�������߂�(�C������)����*/
/*@param[in]    struct tm *time_in  :�w���*/
/*@return       status              :�G���[����*/
unsigned char GetDayOfWeek(struct tm *time_in)
{
    struct tm time_reference;        //���
    unsigned int t_time_reference;   //����̃V���A������
    unsigned int t_time_in;         //�w����̃V���A������
    unsigned int t_difference;      //�������̍���
    unsigned char status = FALSE;
    
    //����̏�����
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

    /* ����Ƃ̍�����j���𔻒� */
    t_difference =( t_time_in - t_time_reference);
    time_in->tm_wday = t_difference % 7 + 1; //1900/01/01�͌��j���i1�j
    if ( time_in->tm_wday == 7)
    {
        time_in->tm_wday = 0;
    }

    status = TRUE;

    return status;
}

/*�o�ߓ������v�Z����*/
/*@param[in] struct tm *start_time */
/*@param[in] struct tm *end_time */
/*@param[in] double *days_elapsed �o�ߎ���*/
/*@return status �G���[���� */
unsigned char GetDaysElapsed(struct tm start_time, struct tm end_time, double *days_elapsed)
{
    unsigned char status = FALSE;
    unsigned int start_serial_time;//�V���A�������@�J�n��
    unsigned int end_serial_time;  //�V���A�������@�I����
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

/*�j�����o�͂���*/
/*@param[in] unsigned char wday �j����\�����l�@tm_wday�ɏ���*/
/*@return  */
unsigned char PrintfDayOfTheWeek(unsigned char wday)
{
    unsigned char status = FALSE;
    if ( ( wday < 0) || ( wday > 6 ) )
    {
        return status;
    }
    char weeks[][10] = {//Wednesday�̕�����+1
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

/*�o�ߓ������o�͂���*/
/*@param[in] unsigned int days_elapsed �o�ߓ���*/
/*@return  */
void PrintfDaysElapsed(int days_elapsed)
{
    printf("The number of days elapsed from the birthday is %d days.\n",days_elapsed);

    return;
}