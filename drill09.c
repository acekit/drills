//���͒l�Ɋւ���u�����炩�ȃG���[�v�Ƃ�����`�����Ȃ������߁B�S�ĂɑΏ��͒v���܂���B
//����́A��̏����őz�肵�����͒l�ȊO���G���[�Ƃ݂Ȃ��܂����A�P����scanf�Ŏ�������ƁA�Ώ��d�؂�Ȃ����̓p�^�����c��܂��B
/*
No .9 �d�b��
    �Ј��ԍ�����͂���ƁA
    �����A�����ԍ����\�������B 
    �f�[�^�͍\���̂ŃA�N�Z�X���邱�ƁB �f�[�^��`���@�͎��R�B
*/
#include <errno.h>
#include <stdio.h>  // ���o�͗p
#include <stdlib.h> //atoi�p
#include <string.h> // ���͎��̕�����ː��l�ϊ��p

//���l��` =====================
#define LEN_EMPLOYEE_NUMBER 9  //9�� ���͉\�Ȑ����̌��� 030xxxxxx �Ȃ̂�9����
#define LEN_DATABASE 3         //�Ј����f�[�^�x�[�X���̓o�^�Ј���
#define TRUE 1
#define FALSE 0
//�\���̌^�錾
//�Ј����i�[�p
typedef struct {
    unsigned int employee_number;
    char name[20];
    unsigned int employee_extention;
}   T_EmployeeData;

// �֐��錾 =====================
unsigned int GetUserInput();
unsigned char InitEmployeeInformation( T_EmployeeData* );
void PrintfTheNameOfEmployee( T_EmployeeData );
void PrintfEmployeeExtention( T_EmployeeData );

void main(){
    T_EmployeeData user;//�Ј����
    unsigned char is_function_succeeded = FALSE;//�����̐���

    //�W�����͂���Ј��ԍ����擾����
    printf("Please, input employee's number.\n");
    printf("If you enter a number greater than %d digits, it will be recognized as a %d-digit number from the beginning.\n", LEN_EMPLOYEE_NUMBER, LEN_EMPLOYEE_NUMBER);
    user.employee_number = GetUserInput();

    //�Ј��ԍ�����Ј���������������
    is_function_succeeded = InitEmployeeInformation( &user );

    //�f�[�^�x�[�X��ɊY������Ј���񂪑��݂��Ȃ��ꍇ�̏���
    if(is_function_succeeded == FALSE){
        printf("There is no corresponding employee number in the database.\n");
        printf("Push enter keys.");
        getchar(); //��ʂ��c���p
        return;
    };

    //�Ј�������\������
    PrintfTheNameOfEmployee( user );
    //�����ԍ���\������
    PrintfEmployeeExtention( user );

    printf("Push enter keys.");
    getchar(); //��ʂ��c���p
    return ;
}

/*@brief ���[�U�[�̓��͂𓾂�֐�           */
/*@param [in]                           */
/*@return unsigned int :���͒l          */
unsigned int GetUserInput(){
    char input_val_char[LEN_EMPLOYEE_NUMBER + 1];
    unsigned int input_val;
    scanf("%9s%*[^\n]", &input_val_char); // �����́A�Z�L�����e�B�ʂ�scanf�̊֌W����A�}�W�b�N�i���o�[�ł����A8�𒼓��ꂵ�Ă��܂��B
    while (getchar() != '\n'); // ���s�R�[�h�̓ǂݔ�΂�
    input_val = atoi(input_val_char);
    printf("Your input is %09d.\n", input_val);
    return input_val;
}

/*@brief �Ј��ԍ�����Ј���������������֐�         */
/*@param [in]_EmployeeData *input_employee_data    */
/*@return unsigned char :�����̐���                 */
unsigned char InitEmployeeInformation(T_EmployeeData *input_employee_data){
    unsigned char is_process_succeeded = FALSE;
    unsigned int tmp_employee_number = input_employee_data->employee_number ;
    unsigned int i = 0;
    //data base �̍쐬
    T_EmployeeData database_of_employee[LEN_DATABASE] =
        {
            {30164701, "��F�@�x", 0000},
            {30164702, "�ɓ��@�W�l", 1111},
            {30164703, "���V�@��", 2222},
        };

    //�Y�����̒T��
    for (i = 0; i < LEN_DATABASE; i++)
    {
        //�Ј��ԍ�����v����f�[�^������΁A�l����
        if (database_of_employee[i].employee_number == input_employee_data->employee_number)
        {
            strcpy(input_employee_data->name, database_of_employee[i].name);
            input_employee_data->employee_extention = database_of_employee[i].employee_extention;
            return is_process_succeeded = TRUE;
        }        
    }

    return is_process_succeeded;
}

/*@brief �Ј�������\������֐�           */
/*@param [in] T_EmployeeData input_employee_data :�Ј����*/
/*@return           */
void PrintfTheNameOfEmployee(T_EmployeeData input_employee_data)
{
    printf("This employee's name is %s.\n" , input_employee_data.name);
    return;
}

/*@brief �����ԍ���\������֐�           */
/*@param [in] T_EmployeeData input_employee_data :�Ј����*/
/*@return           */
void PrintfEmployeeExtention(T_EmployeeData input_employee_data)
{
    printf("This employee's employee extention is %4d.\n" , input_employee_data.employee_extention);
    return;
}