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
#define LEN_EMPLOYEE_EXTENTION 4   //4�� �����ԍ�
#define TRUE 1
#define FALSE 0
//�\���̌^�錾
//�Ј����i�[�p
typedef struct {
    char employee_number[LEN_EMPLOYEE_NUMBER + 1];//null������
    char name[20];
    char employee_extention[LEN_EMPLOYEE_EXTENTION + 1]; //null������
}   T_EmployeeData;

// �֐��錾 =====================
unsigned char GetUserInput(T_EmployeeData *);
unsigned char SearchAndGetEmployeeInformationByEmployeeNumber(T_EmployeeData *);

void main(){
    T_EmployeeData user;//�Ј����
    unsigned char is_function_succeeded = FALSE;//�����̐���

    //�W�����͂���Ј��ԍ����擾����
    printf("Please, input employee's number.\n");
    printf("If you enter a number greater than %d digits, it will be recognized as a %d-digit number from the beginning.\n", LEN_EMPLOYEE_NUMBER, LEN_EMPLOYEE_NUMBER);
    is_function_succeeded = GetUserInput(&user);
    //���͕�����������Ȃ��������̏���
    if (is_function_succeeded == FALSE)
    {
        printf("Not enough characters to enter.\n");
        printf("Push enter keys.");
        getchar(); //��ʂ��c���p
        return;
    };

    //�Ј��ԍ�����Ј�������������
    is_function_succeeded = SearchAndGetEmployeeInformationByEmployeeNumber(&user);

    //�f�[�^�x�[�X��ɊY������Ј���񂪑��݂��Ȃ��ꍇ�̏���
    if(is_function_succeeded == FALSE){
        printf("There is no corresponding employee number in the database.\n");
        printf("Push enter keys.");
        getchar(); //��ʂ��c���p
        return;
    };

    //�Ј�������\������ 
    printf("This employee's name is %s.\n", user.name);
    //�����ԍ���\������
    printf("This employee's employee extention is %4s.\n", user.employee_extention);

    printf("Push enter keys.");
    getchar(); //��ʂ��c���p
    return ;
}

/*@brief ���[�U�[�̓��͂𓾂�֐�           */
/*@param [in] EmployeeData *input_employee_data                         */
/*@return unsigned char :�����̐���          */
unsigned char GetUserInput(T_EmployeeData *input_employee_data)
{
    unsigned char is_process_succeeded = FALSE;
    char input_val_char[LEN_EMPLOYEE_NUMBER + 1]; //null������
    scanf("%9s%*[^\n]", &input_val_char); // �����́A�Z�L�����e�B�ʂ�scanf�̊֌W����A�}�W�b�N�i���o�[�ł����A9�𒼓��ꂵ�Ă��܂��B
    while (getchar() != '\n'); // ���s�R�[�h�̓ǂݔ�΂�
    printf("Your input is %s.\n", input_val_char);
    if (strlen(input_val_char)  == LEN_EMPLOYEE_NUMBER){//+1��null������
        is_process_succeeded = TRUE;
    }
    strcpy(input_employee_data->employee_number, input_val_char);
    return is_process_succeeded;
}

/*@brief �Ј��ԍ�����Ј������������A�Ј������擾����֐�         */
/*@param [in] EmployeeData *input_employee_data    */
/*@return unsigned char :�����̐���                 */
unsigned char SearchAndGetEmployeeInformationByEmployeeNumber(T_EmployeeData *input_employee_data)
{
    unsigned char is_process_succeeded = FALSE;
    unsigned int i = 0;
    size_t size_of_database;
    //data base �̍쐬
    T_EmployeeData database_of_employee[] =
        {
            {"030164701", "��F�@�x", "0000"},
            {"030164702", "�ɓ��@�W�l", "1111"},
            {"030164703", "���V�@��", "2222"},
        };
    size_of_database = sizeof(database_of_employee) / sizeof(database_of_employee[0]);
    //�Y�����̒T��
    for (i = 0; i < size_of_database; i++)
    {
        //�Ј��ԍ�����v����f�[�^������΁A�l����
        if (strcmp(database_of_employee[i].employee_number,  input_employee_data->employee_number) == 0)
        {
            strcpy(input_employee_data->name, database_of_employee[i].name);
            strcpy(input_employee_data->employee_extention, database_of_employee[i].employee_extention);
            return is_process_succeeded = TRUE;
        }        
    }

    return is_process_succeeded;
}
