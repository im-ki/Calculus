/**
  ******************************************************************************
    * @File:		administrator.c
    * @Author:	    黄嘉敏
	* @Date:		2017-05-19
	* @Brief:		管理员用户源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include"db_operation.h"
#include"mark.h"
#include"teaching_task.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"administrator.h"

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		add_user
  * @函数说明		手动添加用户
  * @输入参数       void
  * @返回参数       0(加入成功),-1(用户已存在)
  *****************************************************************************/
int add_user(void){
    struct user temp;
    int state;
    system("cls");
    printf("* 管理员，欢迎来到添加用户界面！\n");
    printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  ┃    \t\t\t*   添加用户   * \t\t\t    ┃\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf("*请按照要求依次填入学号、姓名、密码等身份信息：\n");
    printf("\n");
    printf("\t   *1.学号/工号 *: ");
    scanf("%s",temp.id);
    printf("\n");
    printf("\t   *   2.姓名   *: ");
    scanf("%s",temp.name);
    printf("\n");
    printf("\t   *   3.密码   *: ");
    scanf("%s",temp.password);
    printf("\n");
    printf("\t   *4 .所属学院 *: ");;
    scanf("%s",temp.school);
    printf("\n");
    printf("\t   *5.新用户的类型 *:\n ");
    printf("注：(1为学生,2为老师,3为辅导员)：");
    scanf("%d",&temp.type);
     if(temp.type==1){
        system("cls");
        printf("* 已成功创建用户，用户类型：学生\n");
        printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃    \t\t\t*   信息完善   * \t\t\t    ┃\n");
        printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
        printf("* 请按照要求为该学生完善信息，这非常重要\n");
        printf("\n");
        printf("\t   *1.所属年级  *: ");
        scanf("%d",&temp.grade);
        printf("\n");
        printf("\t   *2.所属专业  *: ");
        scanf("%s",temp.major);
        printf("\n");
        printf("\t   *3.所属班别  *: ");
        scanf("%d",&temp.class_id);
        printf("\n\n");
        printf("* 恭喜你！已成功创建该用户！\n");
        printf("* 用户类型：学生\n");
        printf("* 可分享至\t*新浪微博\t*朋友圈        *QQ空间\n");
        printf("\n");


    }else if(temp.type==3){
        system("cls");
        printf("* 已成功创建用户，用户类型：辅导员\n");
        printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃    \t\t\t*   信息完善   * \t\t\t    ┃\n");
        printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
        printf("* 请按照要求为该辅导员完善信息，这非常重要\n");
        printf("\n");
        printf("\t   *1.管理年级  *: ");
        scanf("%d",&temp.grade);
    }

    state=add_to_db(&temp);
    if(state==0){
        system("cls");
        printf("* 恭喜你！已成功创建该用户！\n");
        printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("╒============================================================================╕");
        printf("│ \t                    *   创建用户成功    *                           │\n");
        printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
        printf("* 我还可以做些什么？  \n");
        system("pause");
        printf("\n");
        printf("* 你还可以截图分享至\t*新浪微博\t*朋友圈        *QQ空间\n");

        return 0;
    }else if(state==-1){
        system("cls");
        printf("* 很抱歉，发生了故障\n");
        printf("┅┅┅┅┅┅┅┅┅┅\n");
        printf("╒============================================================================╕");
        printf("│ \t                    *  ！创建用户失败 ！  *                           │\n");
        printf("┕┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┙");
        printf("* 很抱歉，发生了一些错误（按任意键查看问题和解决方法）  \n");
        system("pause");
        printf("  *  问题   ：您创建的新用户：学生与我们以前的某一用户的学号、工号重复了  \n");
        printf("\n\n");
        printf("  *我可以怎么办？：1.您可以删除数据库里面中的已有这个用户 \n");
        printf("  *                2.您也可以是否您创建的该用户工号输入有误，并尝试重新输入  \n");
        printf("  *                3.您还可以寻求我们的帮助，支付宝账户：123456  \n");
        return 0;
    }
    return -1;
}

/*******************************************************************************
  * @函数名称		add_student_csv
  * @函数说明		批量添加学生用户
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int add_student_csv(void){  //使用ansi编码
    FILE *fp=fopen("student.csv","r");
    struct user temp;
    char s[256];
    char *c;
    char password[30];
    int state;
    while(1){
        system("cls");
        printf("* 管理员，欢迎来到批量添加用户界面！\n");
        printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
        printf("\n");
        printf("  ┏────────────────────────────────────┓\n");
        printf("  ┃    \t\t\t*   批量添加用户   * \t\t\t    ┃\n");
        printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
        printf("* 请输入您的预置密码：");
        scanf("%s",password);
        if(strlen(password)>16){
            system("cls");
            printf("* 很抱歉，您无法执行这个指令\n");
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
            printf("* 我可以怎么办？：1.您可以尝试重新输入您的密码，这可以避免偶然输入错误带来的问题 \n");
            printf("*                 2.您还可以寻求我们的帮助：支付宝账户：123456  \n");
            printf("\n");
            printf("\t                                                    按任意键退出该界面\n");
            system("pause");
        }else{
            break;
        }
    }
    while(fscanf(fp,"%s",s)==1){
        c=strtok(s,",");
        sscanf(c,"%s",temp.id);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.name);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.type);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.school);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.major);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.grade);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.class_id);

        strcpy(temp.password,password);

        state=add_to_db(&temp);
        if(state==0){
            printf("%s添加成功\n",temp.id);
        }else if(state==-1){
            printf("%s已存在\n",temp.id);
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @函数名称		add_teacher_csv
  * @函数说明		批量添加教师用户
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int add_teacher_csv(void){
    FILE *fp=fopen("teacher.csv","r");
    struct user temp;
    char s[256];
    char *c;
    char password[30];
    int state;
    printf("请输入预置密码(小于等于16位字符):");
    while(1){
        scanf("%s",password);
        if(strlen(password)>16){
            printf("密码太长，请重新输入:");
        }else{
            break;
        }
    }
    while(fscanf(fp,"%s",s)==1){
        c=strtok(s,",");
        sscanf(c,"%s",temp.id);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.name);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.type);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.school);

        strcpy(temp.password,password);

        state=add_to_db(&temp);
        if(state==0){
            printf("%s添加成功\n",temp.id);
        }else if(state==-1){
            printf("%s已存在\n",temp.id);
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @函数名称		add_counselor_csv
  * @函数说明		批量添加辅导员用户
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int add_counselor_csv(void){
    FILE *fp=fopen("counselor.csv","r");
    struct user temp;
    char s[256];
    char *c;
    char password[30];
    int state;
    printf("请输入预置密码(小于等于16位字符):");
    while(1){
        scanf("%s",password);
        if(strlen(password)>16){
            printf("密码太长，请重新输入:");
        }else{
            break;
        }
    }
    while(fscanf(fp,"%s",s)!=-1){
        c=strtok(s,",");
        sscanf(c,"%s",temp.id);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.name);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.type);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.school);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.grade);

        strcpy(temp.password,password);

        state=add_to_db(&temp);
        if(state==0){
            printf("%s添加成功\n",temp.id);
        }else if(state==-1){
            printf("%s已存在\n",temp.id);
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @函数名称		view_all
  * @函数说明		查看所有用户
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int view_all(void){
    struct user temp;
    struct user_linked *head,*now,*prev;
    temp.type=-1;
    temp.school[0]='-';
    temp.major[0]='-';
    temp.grade=-1;
    temp.class_id=-1;
    head=search_all_for_id(&temp);
    system("cls");
    printf("* 管理员，欢迎来到查看用户界面！\n");
    printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  ┃    \t\t\t*   查看用户   * \t\t\t    ┃\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf("*系统现今已有的用户如下表所示：\n");
    printf("\n");
    for(now=head;now!=NULL;now=now->next){
        if(now->type==1){
            printf("%s %s %d %s %s %d %d\n",now->id,now->name,now->type,now->school,now->major,now->grade,now->class_id);
        }else if(now->type==2){
            printf("%s %s %d %s\n",now->id,now->name,now->type,now->school);
        }else{
            printf("%s %s %d %s %d\n",now->id,now->name,now->type,now->school,now->grade);
        }
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}

/*******************************************************************************
  * @函数名称		del_user_from_csv
  * @函数说明		批量删除用户
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int del_user_from_csv(void){
    FILE *fp=fopen("user_to_be_del.csv","r");
    char s[256];
    int state,user_type;
    while(fscanf(fp,"%s",s)!=-1){
        if(in_db(s)==-1){
            printf("%s不存在\n",s);
            continue;
        }
        user_type=search_for_type(s);
        state=!del_from_db(s);
        if(user_type==1){
            state=!del_mark(s)&&state;
        }else if(user_type==2){
            state=!del_teaching_task(s)&&state;
        }
        if(state)printf("%s已被删除\n",s);
        else printf("%s删除出错\n",s);
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @函数名称		add_teaching_task_csv
  * @函数说明		添加教学任务
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int add_teaching_task_csv(void){
    FILE *fp=fopen("teaching_task.csv","r");
    struct task temp;
    char s[256];
    char *c;
    int state;
    while(fscanf(fp,"%s",s)!=-1){
        c=strtok(s,",");
        sscanf(c,"%s",temp.id);
        printf("%s\n",temp.id);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.school);
        printf("%s\n",temp.school);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.grade);
        printf("%d\n",temp.grade);

        c=strtok(NULL,",");
        sscanf(c,"%s",temp.major);
        printf("%s\n",temp.major);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.class_id);
        printf("%d\n",temp.class_id);

        c=strtok(NULL,",");
        sscanf(c,"%d",&temp.term);
        printf("%d\n",temp.term);


        c=strtok(NULL,",");
        sscanf(c,"%s",temp.subject);
        printf("%s\n",temp.subject);

        temp.task_state=0;

        state=in_teaching_task(&temp);
        if(state==-1){
            printf("教学任务表中有相同的任务\n");
            continue;
        }else if(state==-2){
            printf("文件无法打开\n");
            continue;
        }
        state=add_teaching_task(&temp);
        if(state==0){
            printf("添加成功\n");
        }else if(state==-1){
            printf("添加失败\n");
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @函数名称		del_user
  * @函数说明		删除用户
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int del_user()
{
  char id[20];
  int r;
  printf("请输入要删除的用户帐号:\n");
  scanf("%s",id);
  r=del_from_db(id);
  if(r==0)
    printf("删除成功\n");
  else
    printf("删除失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		add_courses
  * @函数说明		手动添加教学任务
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int add_courses()
{
	struct task temp;
    int state;
    printf("请输入教师工号:");
    scanf("%s",temp.id);

    printf("请输入授课学院:");
    scanf("%s",temp.school);

    printf("请输入授课年级:");
    scanf("%d",&temp.grade);

    printf("请输入授课专业:");
    scanf("%s",temp.major);

    printf("请输入授课班别:");
    scanf("%d",&temp.class_id);

    printf("请输入授课学期:");
    scanf("%d",&temp.term);

    printf("请输入课程名称:");
    scanf("%s",temp.subject);

    temp.task_state=0;

    state=add_teaching_task(&temp);
    if(state==0){
        printf("添加成功\n");
    }else if(state==-1){
        printf("添加失败\n");
    }
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfpassword
  * @函数说明		修改用户密码
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfpassword()
{
    char id[20];
    char new_pass[20];
    char temp[20];
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    while(1)
    {
        printf("请输入新密码:\n");
        scanf("%s",temp);
        printf("再次输入新密码:\n");
        scanf("%s",new_pass);
        if(strcmp(temp,new_pass)==0)
            break;
        else
            printf("密码不一致!\n");
    }
    r=mod_password(id,new_pass);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfschool
  * @函数说明		修改用户所属学院
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfschool()
{
    char id[20];
    char new_school[20];
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新所属学院:\n");
    scanf("%s",new_school);
    r=mod_school(id,new_school);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfmajor
  * @函数说明		修改用户所属专业
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfmajor()
{
    char id[20];
    char new_major[20];
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新所属专业:\n");
    scanf("%s",new_major);
    r=mod_major(id,new_major);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfgrade
  * @函数说明		修改用户所属年级
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfgrade()
{
    char id[20];
    int new_grade;
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新所属年级:\n");
    scanf("%d",&new_grade);
    r=mod_grade(id,new_grade);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfcls_id
  * @函数说明		修改用户所属班级
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfcls_id()
{
    char id[20];
    int newcls_id;
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新所属班级:\n");
    scanf("%d",&newcls_id);
    r=mod_class_id(id,newcls_id);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfname
  * @函数说明		修改用户姓名
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfname()
{
    char id[20];
    char newname[20];
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新姓名:\n");
    scanf("%s",newname);
    r=mod_name(id,newname);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdftype
  * @函数说明		修改用户类型
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdftype()
{
    char id[20];
    int newtype;
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新类型:\n");
    scanf("%d",&newtype);
    r=mod_type(id,newtype);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}

/*******************************************************************************
  * @函数名称		mdfid
  * @函数说明		修改用户账号
  * @输入参数       void
  * @返回参数       0(完成)
  *****************************************************************************/
int mdfid()
{
    char id[20];
    char newid[20];
    int r;
    printf("请输入要修改的用户ID:\n");
    scanf("%s",id);
    printf("请输入新账号:\n");
    scanf("%s",newid);
    r=mod_id(id,newid);
    if(r==0){
        printf("修改成功\n");}
    else
        printf("修改失败\n");
    return 0;
}
