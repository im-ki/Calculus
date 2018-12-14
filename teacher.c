/**
  ******************************************************************************
    * @File:		teacher.c
    * @Author:	    陈火旺
	* @Date:		2017-05-22
	* @Brief:		教师用户管理源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"teacher.h"
#include"mark.h"
#include"db_operation.h"
#include<stdlib.h>
#include<string.h>
#include"teaching_task.h"

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		int input_mark_csv(void)
  * @函数说明		老师批量上交成绩，用CSV文件上交
  * @输入参数      空
  * @返回参数      返回0表示成功导入
  *****************************************************************************/
int input_mark_csv(char *id){  //使用ansi编码
    struct task con;
    struct task_linked *head,*prev,*now;
    struct user temp;
    struct user_linked *user_head,*user_now,*user_prev;
    struct mark new_mark;
    char id_in_file[20];
    FILE *fp;
    int input,check=1,stop=0;
    int i;
    char s[256];
    char *c;

    con.class_id=-1;
    con.grade=-1;
    strcpy(con.id,id);
    con.major[0]='-';
    con.school[0]='-';
    con.subject[0]='-';
    con.task_state=0;
    con.term=-1;
    head=get_teaching_task(&con);
    system("cls");
    printf("* 老师，欢迎来到导入成绩界面！\n");
    printf("┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  ┃                         *   批量导入学生成绩   *                       ┃\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf("\n");
    printf("未提交成绩单的教学任务:\n");
    for(now=head,i=1;now!=NULL;now=now->next,i++){
        printf("    %d subject:%s term:%d school:%s major:%s grade:%d class_id:%d\n",i,now->subject,now->term,now->school,now->major,now->grade,now->class_id);
    }
    printf("\n");
    printf("请输入要提交的成绩单的编号:");
    scanf("%d",&input);
    for(i=1,now=head;now!=NULL;now=now->next,i++){
        if(i==input){
            memcpy(&con,now,sizeof(struct task));
            break;
        }
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }

    temp.class_id=con.class_id;
    temp.grade=con.grade;
    strcpy(temp.major,con.major);
    strcpy(temp.school,con.school);
    temp.type=1;
    user_head=search_all_for_id(&temp);

    fp=fopen("mark.csv","r");
    for(user_now=user_head;user_now!=NULL;user_now=user_now->next){
        fseek(fp,0,SEEK_SET);
        while(fscanf(fp,"%s",s)==1){
            c=strtok(s,",");
            sscanf(c,"%s",id_in_file);
            if(strcmp(user_now->id,id_in_file)==0){
                check=0;
                break;
            }
        }
        if(check==1){
            printf("%s 不在成绩表内\n",user_now->id);
            stop=1;
        }else{
            check=1;
        }
    }

    if(stop==0){
        fseek(fp,0,SEEK_SET);
        while(fscanf(fp,"%s",s)==1){
            c=strtok(s,",");
            sscanf(c,"%s",id_in_file);
            for(user_now=user_head;user_now!=NULL;user_now=user_now->next){
                if(strcmp(user_now->id,id_in_file)==0){
                    check=0;
                    break;
                }
            }
            if(check==1){
                printf("%s 不在该班内\n",id_in_file);
                stop=1;
            }else{
                check=1;
            }
        }
    }

    fclose(fp);
    for(user_now=user_head,user_prev=user_now;user_now!=NULL;user_prev=user_now){
        user_now=user_now->next;
        free(user_prev);
    }
    if(stop==1){
        printf("由于成绩表与班级名单不匹配,无法导入\n");
        return -1;
    }else{
        finish_task(&con);
        fp=fopen("mark.csv","r");
        while(fscanf(fp,"%s",s)==1){
            c=strtok(s,",");
            sscanf(c,"%s",new_mark.id);

            c=strtok(NULL,",");
            sscanf(c,"%d",&new_mark.term);

            c=strtok(NULL,",");
            sscanf(c,"%s",new_mark.subject);

            c=strtok(NULL,",");
            sscanf(c,"%d",&new_mark.mark);

            c=strtok(NULL,",");
            sscanf(c,"%d",&new_mark.credit);

            add_mark(&new_mark);
        }
        fclose(fp);
    }
    return 0;
}

/*******************************************************************************
  * @函数名称		int search_for_task_with_state(void)
  * @函数说明		查看教学任务状态
  * @输入参数      char *id(当前账号),int state(要查看的状态)
  * @返回参数      返回0表示完成
  *****************************************************************************/
int search_for_task_with_state(char *id,int state){
    struct task con;
    struct task_linked *head,*prev,*now;
    int i;

    con.class_id=-1;
    con.grade=-1;
    strcpy(con.id,id);
    con.major[0]='-';
    con.school[0]='-';
    con.subject[0]='-';
    con.task_state=state;
    con.term=-1;
    head=get_teaching_task(&con);

    if(head==NULL){
        printf("无记录\n");
        return 0;
    }
    for(now=head,i=1;now!=NULL;now=now->next,i++){
        printf("    %d 学科:%s 学期:%d 学院:%s 专业:%s 年级:%d 班别:%d\n",i,now->subject,now->term,now->school,now->major,now->grade,now->class_id);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}


/*******************************************************************************
  * @函数名称	   int view_mark_of_student(void)
  * @函数说明	   查看学生成绩
  * @输入参数      id(学生学号）
  * @返回参数      返回0表示成功查询
  *****************************************************************************/
int view_mark_of_student(void){

    struct mark temp;
    struct mark_linked *head,*now,*prev;
    system("cls");
    printf("* 老师，欢迎来到学生成绩查询界面！\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  │ \t                   *   学生成绩查询    *                            │\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf(" * 请按照要求依次填入该学生的信息：\n");
    printf("\n");
    printf("\n");
	printf("请输入您想要查询的学号：");
	scanf("%s",temp.id);
    //strcpy(temp.id,id);
    temp.subject[0]='-';
    temp.term=-1;
    head=get_mark(temp.id,&temp);
    printf("该学生修过的课程:\n");
    for(now=head;now!=NULL;now=now->next){
        printf("    课程:%s 学期:%d\n",now->subject,now->term);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    printf("\n");
    printf("\n");
    printf("请输入您要查看的课程(要查看所有成绩请输入‘所有’):");
    scanf("%s",temp.subject);
    printf("\n");
    printf("\n");
    printf("请输入您要查看的学期(要查看所有学期请输入‘-1’):");
    scanf("%d",&temp.term);
    if(strcmp(temp.subject,"所有")==0){
        temp.subject[0]='-';
    }
    head=get_mark(temp.id,&temp);
    for(now=head;now!=NULL;now=now->next){
        printf("    课程:%s 学期:%d 成绩:%d 学分:%d\n",now->subject,now->term,now->mark,now->credit);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}

/*******************************************************************************
  * @函数名称	   int output_student_csv(char *id)
  * @函数说明	   导出学生成绩
  * @输入参数      id(学生学号）
  * @返回参数      返回0表示成功查询（成功则输出：导出完成;否则输出：没有找到相应课程）
  *****************************************************************************/
int output_student_csv(char *id)
{
    struct task con;
    struct task_linked *head;
    struct user temp;
    struct user_linked *student_list,*prev,*now;
    FILE *fp;
    strcpy(con.id,id);
    system("cls");
    printf("* 老师，欢迎来到考勤表导出界面！\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  │ \t                    *   导出考勤表    *                             │\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf("\n");
    printf(" * 请按照要求依次填入所需的信息：\n");
    printf("\n");
    printf("\n");
    printf("请输入要导出的名单的学院:");
    scanf("%s",con.school);
    printf("\n");
    printf("\n");
    printf("请输入要导出的名单的年级:");
    scanf("%d",&con.grade);
    printf("\n");
    printf("\n");
    printf("请输入要导出的名单的专业:");
    scanf("%s",con.major);
    printf("\n");
    printf("\n");
    printf("请输入要导出的名单的班别:");
    scanf("%d",&con.class_id);
    printf("\n");
    printf("\n");
    printf("请输入要导出的名单的学期:");
    scanf("%d",&con.term);
    printf("\n");
    printf("\n");
    printf("请输入要导出的名单的课程名称:");
    scanf("%s",con.subject);
    con.task_state=-1;
    head=get_teaching_task(&con);
    if(head!=NULL){
        temp.type=1;
        strcpy(temp.school,head->school);
        strcpy(temp.major,head->major);
        temp.grade=head->grade;
        temp.class_id=head->class_id;
        free(head);
        student_list=search_all_for_id(&temp);
        fp=fopen("student_list.csv","w");
        for(now=student_list;now!=NULL;now=now->next){
            fprintf(fp,"%s,%s\n",now->id,now->name);
        }
        fseek(fp,-1*(int)sizeof(char),SEEK_END);
        putchar(EOF);
        for(now=student_list,prev=now;now!=NULL;prev=now){
            now=now->next;
            free(prev);
        }
        printf("导出完成\n");
    }else{
        printf("没有找到相应课程\n");
    }
    return 0;
}
