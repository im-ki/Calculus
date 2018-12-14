/**
  ******************************************************************************
    * @File:		login.c
    * @Author:	    ������
	* @Date:		2017-05-19
	* @Brief:		��¼����Դ�ļ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>	//C���ַ���������غ�����ͷ�ļ�
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include"db_operation.h"
#include"login.h"
#include"interface.h"

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		login
  * @����˵��		��¼
  * @�������       void
  * @���ز���       0(������һ��)
  *****************************************************************************/
int login(void){
	char password[30];	//���ڴ������
	char identity[30];		//���ڴ���˺�
	char *password_in_db;
	int user_type;

    while(1){
        system("CLS");
        printf("���ã��뿪ʼ��½\n");
        printf("*����������������\n");
        printf("\n\n\n\n");
        printf("�V============================================================================�Y");
        printf("�� \t\t           *  Calculus�ɼ�����ϵͳ  *                         ��");
        printf("��������������������������������������������������������������������������������");
        printf("  *��������Ӧ��ѧ��/���š���������ɵ�½*");
        printf("\n\n\n");
        printf("\t\t��*�˺�*�� ");
        scanf("%s", identity);
        printf("\n\n");
        printf("\t\t��*����*�� ");
        scanf("%s", password);
        printf("\n\n");

        password_in_db=get_password(identity);
        if(password_in_db==NULL){
            system("cls");
            printf("\n\n");
            printf("�V============================================================================�Y");
            printf("��                                                                            ��");
            printf("�� \t     �w �����棬���˺Ų����ڣ����������������ϵ����Ա �w             ��");
            printf("��                                                                            ��");
            printf("��������������������������������������������������������������������������������");
            printf("\n\n");
            system("pause");
            continue;
        }else if(strcmp(password_in_db, password)!=0){
            printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
            printf("\t\t                    *������󣬰����������*  \n");
            printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
            system("pause");
            continue;
        }
        system("cls");
        user_type=search_for_type(identity);
        switch(user_type){
            case 0:administrator_interface(identity);return 0;
            case 1:student_interface(identity);return 0;
            case 2:teacher_interface(identity);return 0;
            case 3:counselor_interface(identity);return 0;
        }
    }
}
