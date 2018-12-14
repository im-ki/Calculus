/**
  ******************************************************************************
    * @File:		interface.c
    * @Author:	    陈宣良
	* @Date:		2017-05-19
	* @Brief:		用户界面源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include"interface.h"
#include"student.h"
#include"teacher.h"
#include"administrator.h"
#include<stdio.h>
#include<windows.h>
#include"counsellor.h"

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		administrator_interface
  * @函数说明		管理员用户功能菜单
  * @输入参数       char *identity(当前账号)
  * @返回参数       0(退出)
  *****************************************************************************/
int administrator_interface(char *identity){
    int input;
    while(1){
        system("cls");
        printf("*欢迎您，管理员！\n");
        printf("┅┅┅┅┅┅┅┅\n");
        printf("*请按照菜单栏上的数字选择您需要的功能：\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃     \t\t\t*   菜单栏   * \t\t\t            ┃\n");
        printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
        printf("  ├┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┬┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┤ \n");
        printf("           * 1 手动添加用户 *                   *11 修改用户学院 *        \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("           * 2 批量导入学生 *                   *12 修改用户专业 *        \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("           * 3 批量导入老师 *                   *13 修改用户年级 *        \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("          * 4 批量导入辅导员 *                  *14 修改用户班别 *        \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("             * 5 删除用户 *                     *15 修改用户姓名*         \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("           * 7 查看所有用户 *                   *16 修改用户类型 *        \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("           * 8 手动添加课表 *                   *17 修改用户账号 *        \n");
        printf("  ┣─                              ─╋─                                ─┫ \n");
        printf("           * 9 批量添加课表 *                        * 18 退出 *          \n");
        printf("  ┗─────────────────┻──────────────────┛\n");
        printf(" * 请输入相应数字: ");
        scanf("%d",&input);
        switch(input){
            case 1:add_user();break;
            case 2:add_student_csv();break;
            case 3:add_teacher_csv();break;
            case 4:add_counselor_csv();break;
            case 5:del_user();break;
            case 6:del_user_from_csv();break;
            case 7:view_all();break;
            case 8:add_courses();break;
            case 9:add_teaching_task_csv();break;
            case 10:mdfpassword();break;
            case 11:mdfschool();break;
            case 12:mdfmajor();break;
            case 13:mdfgrade();break;
            case 14:mdfcls_id();break;
            case 15:mdfname();break;
            case 16:mdftype();break;
            case 17:mdfid();break;
            case 18:return 0;
            default:printf("输入错误,请重新输入.");system("pause");break;
        }
        system("pause");
    }
}

/*******************************************************************************
  * @函数名称		student_interface
  * @函数说明		学生用户功能菜单
  * @输入参数       char *identity(当前账号)
  * @返回参数       0(退出)
  *****************************************************************************/
int student_interface(char *identity){
    int input;
    char *name;
    while(1){
        name=get_user_name(identity);
        system("cls");
        printf("*欢迎您，%s同学！\n",name);
        free(name);
        printf("┅┅┅┅┅┅┅┅\n");
        printf("\n");
        printf("*请按照菜单栏上的数字选择您需要的功能：\n");
        printf("\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃     \t\t\t*   菜单栏   * \t\t\t            ┃\n");
        printf("  ┣────────────────────────────────────┫ \n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃         *  1 修改密码  *                    *  3 输出成绩单  *         ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃         *  2 查看成绩  *                       *  4 退出  *            ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┗────────────────────────────────────┛\n");
        scanf("%d",&input);
        switch(input){
            case 1:modify_my_password(identity);break;
            case 2:view_mark(identity);break;
            case 3:output_mark_csv(identity);break;
            case 4:return 0;
            default:printf("输入错误,请重新输入.");system("pause");break;
        }
        system("pause");
    }
}

/*******************************************************************************
  * @函数名称		teacher_interface
  * @函数说明		教师用户功能菜单
  * @输入参数       char *identity(当前账号)
  * @返回参数       0(退出)
  *****************************************************************************/
int teacher_interface(char *identity){
    int input;
    char *name;
    while(1){
        name=get_user_name(identity);
        system("cls");
        printf("*欢迎您，%s老师！\n",name);
        free(name);
        printf("┅┅┅┅┅┅┅┅\n");
        printf("\n");
        printf("*请按照菜单栏上的数字选择您需要的功能：\n");
        printf("\n");
         printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃     \t\t\t*   菜单栏   * \t\t\t            ┃\n");
        printf("  ┣────────────────────────────────────┫ \n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃     *  1 批量导入学生成绩  *                *  2 导出考勤表  *         ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃       *  3 查看学生成绩  *                  *  4 未完成任务  *         ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃        *  5 已完成任务  *                    *  6 修改密码  *          ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃           *  7 退出  *                                                 ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┗────────────────────────────────────┛\n");
        scanf("%d",&input);
        switch(input){
            case 1:input_mark_csv(identity);break;
            case 2:output_student_csv(identity);break;
            case 3:view_mark_of_student();break;
            case 4:search_for_task_with_state(identity,0);break;
            case 5:search_for_task_with_state(identity,1);break;
            case 6:modify_my_password(identity);break;
            case 7:return 0;
            default:printf("输入错误,请重新输入.");system("pause");break;
        }
        system("pause");
    }
}

/*******************************************************************************
  * @函数名称		counselor_interface
  * @函数说明		辅导员用户功能菜单
  * @输入参数       char *identity(当前账号)
  * @返回参数       0(退出)
  *****************************************************************************/
int counselor_interface(char *identity){
    int input;
    char *name;
    while(1){
        name=get_user_name(identity);
        system("cls");
        printf("您好，%s辅导员\n",name);
        printf("┅┅┅┅┅┅┅┅\n");
        printf("\n");
        free(name);
        printf("* 请按照菜单栏上的数字选择您需要的功能：\n");
        printf("\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃     \t\t\t*   菜单栏   * \t\t\t            ┃\n");
        printf("  ┣────────────────────────────────────┫ \n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃       *  1 查看学生成绩  *                *  4 导出班级成绩单  *       ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃       *  2 查看班级成绩  *                   *  5 修改密码  *          ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┃       *  3 查看挂科名单  *                     *  6 退出  *            ┃\n");
        printf("  ┃                                                                        ┃\n");
        printf("  ┗────────────────────────────────────┛\n");
        printf("\n");
        printf("* 请根据您想要的功能，输入相应的数字：\n");
        scanf("%d",&input);
        switch(input){
            case 1:display_studentgrade();break;
            case 2:display_classtranscript(identity);break;
            case 3:display_underachiever(identity);break;
            case 4:file_output(identity);break;
            case 5:modify_my_password(identity);break;
            case 6:return 0;
            default:printf("输入错误,请重新输入.");system("pause");break;
        }
        system("pause");
    }
}
