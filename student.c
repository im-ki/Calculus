/**
  ******************************************************************************
    * @File:		student.c
    * @Author:	    陈祈光、陈宣良
	* @Date:		2017-05-19
	* @Brief:		学生用户源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include"student.h"
#include<stdio.h>
#include<string.h>
#include"db_operation.h"
#include"mark.h"
#include<stdlib.h>

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		modify_my_password
  * @函数说明		修改自己的密码,该函数也可被其他用户使用
  * @输入参数       char *id
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int modify_my_password(char *id){
    char password[30];
    while(1){
        system("cls");
        printf("* 欢迎来到修改密码界面！\n");
        printf("┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃    \t\t\t*   修改密码  * \t\t\t    ┃\n");
        printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
        printf("\n");
        printf("请输入新密码(小于等于16位字符):");
        scanf("%s",password);
        if(strlen(password)>16){
            system("cls");
            printf("* 很抱歉，我们无法执行这个指令\n");
            printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
            printf("\n\n");
            printf("╒============================================================================╕");
            printf("│                                                                            │");
            printf("│ \t                  ！密码过长，请重新输入您的密码 ！                   │\n");
            printf("│                                                                            │");
            printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
            printf("* 到底发生了什么？\n");
            printf("\n");
            system("pause");
            printf("* 问题 ：        您输入的密码长度超过了16个，这明显与我们系统的设定是不同的。\n");
            printf("*                              所以我们终止了您的操作。\n");
            printf("\n");
            system("pause");
        }else{
            break;
        }
    }
    if(!mod_password(id,password)){
        system("cls");
        printf("* 恭喜你！已成功修改密码！\n");
        printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("╒============================================================================╕");
        printf("│ \t                    *   修改密码成功    *                             │\n");
        printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");

        return 0;
    }else{
        system("cls");
        printf("* 抱歉！修改密码失败！\n");
        printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("╒============================================================================╕");
        printf("│ \t                    *   修改密码失败    *                             │\n");
        printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
        system("pause");
        return -1;
    }
}

/*******************************************************************************
  * @函数名称		view_mark
  * @函数说明		查看成绩
  * @输入参数       char *id
  * @返回参数       0(完成)
  *****************************************************************************/
int view_mark(char *id){
    struct mark temp;
    struct mark_linked *head,*now,*prev;
    strcpy(temp.id,id);
    temp.subject[0]='-';
    temp.term=-1;
    head=get_mark(id,&temp);
    system("cls");
    printf("* 同学，欢迎进入查看成绩界面\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("╒============================================================================╕");
    printf("│ \t                    *   成绩查询    *                                 │\n");
    printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
    printf("* \n");
    printf("您修过的课程:\n");
    for(now=head;now!=NULL;now=now->next){
        printf("    学科:%s 学期:%d\n",now->subject,now->term);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    printf("请输入您要查看的课程(要查看所有成绩请输入‘所有’):");
    scanf("%s",temp.subject);
    printf("请输入您要查看的学期(要查看所有学期请输入‘-1’):");
    scanf("%d",&temp.term);
    if(strcmp(temp.subject,"所有")==0){
        temp.subject[0]='-';
    }
    head=get_mark(id,&temp);
    for(now=head;now!=NULL;now=now->next){
        printf("    学科:%s 学期:%d 成绩:%d 学分:%d\n",now->subject,now->term,now->mark,now->credit);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}

/*******************************************************************************
  * @函数名称		output_mark_csv
  * @函数说明		输出成绩到csv文件
  * @输入参数       char *id
  * @返回参数       0(完成)
  *****************************************************************************/
int output_mark_csv(char *id){
    struct mark temp;
    struct mark_linked *head,*now,*prev;
    FILE *fp=fopen("my_mark.csv","w");
    strcpy(temp.id,id);
    temp.subject[0]='-';
    temp.term=-1;
    head=get_mark(id,&temp);
    system("cls");
    printf("* 同学，欢迎进入查看成绩界面\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
     printf("╒============================================================================╕");
    printf("│ \t                    *   成绩查询    *                                 │\n");
    printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
    printf("* \n");
    printf("您修过的课程:\n");
    for(now=head;now!=NULL;now=now->next){
        printf("    subject:%s term:%d\n",now->subject,now->term);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    printf("请输入您要导出的课程(要查看所有成绩请输入‘所有’):");
    scanf("%s",temp.subject);
    printf("请输入您要查看的学期(要查看所有学期请输入‘-1’):");
    scanf("%d",&temp.term);
    if(strcmp(temp.subject,"所有")==0){
        temp.subject[0]='-';
    }
    head=get_mark(id,&temp);

    for(now=head;now!=NULL;now=now->next){
        fprintf(fp,"%s,%d,%d,%d\n",now->subject,now->term,now->mark,now->credit);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    fclose(fp);
    return 0;
}
