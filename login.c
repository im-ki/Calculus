/**
  ******************************************************************************
    * @File:		login.c
    * @Author:	    陈宣良
	* @Date:		2017-05-19
	* @Brief:		登录界面源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>	//C中字符串处理相关函数的头文件
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include"db_operation.h"
#include"login.h"
#include"interface.h"

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		login
  * @函数说明		登录
  * @输入参数       void
  * @返回参数       0(返回上一级)
  *****************************************************************************/
int login(void){
	char password[30];	//用于存放密码
	char identity[30];		//用于存放账号
	char *password_in_db;
	int user_type;

    while(1){
        system("CLS");
        printf("您好，请开始登陆\n");
        printf("*┅┅┅┅┅┅┅┅\n");
        printf("\n\n\n\n");
        printf("╒============================================================================╕");
        printf("│ \t\t           *  Calculus成绩管理系统  *                         │");
        printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
        printf("  *请输入相应的学号/工号、密码以完成登陆*");
        printf("\n\n\n");
        printf("\t\t┃*账号*┃ ");
        scanf("%s", identity);
        printf("\n\n");
        printf("\t\t┃*密码*┃ ");
        scanf("%s", password);
        printf("\n\n");

        password_in_db=get_password(identity);
        if(password_in_db==NULL){
            system("cls");
            printf("\n\n");
            printf("╒============================================================================╕");
            printf("│                                                                            │");
            printf("│ \t     ╳ ！警告，该账号不存在，请重新输入或者联系管理员 ╳             │");
            printf("│                                                                            │");
            printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
            printf("\n\n");
            system("pause");
            continue;
        }else if(strcmp(password_in_db, password)!=0){
            printf("════════════════════════════════════════");
            printf("\t\t                    *密码错误，按任意键继续*  \n");
            printf("════════════════════════════════════════\n");
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
