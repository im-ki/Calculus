/**
  ******************************************************************************
    * @File:		counsellor.c
    * @Author:	    陈天翼
	* @Date:		2017-05-19
	* @Brief:		辅导员用户源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"mark.h"
#include"db_operation.h"
#include<windows.h>
#include"counsellor.h"

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		display_studentgrade
  * @函数说明		显示学生成绩
  * @输入参数       void
  * @返回参数       void
  *****************************************************************************/
void display_studentgrade()
{
	struct mark temp;
	struct mark *p1=&temp;
	struct mark_linked* now, *head, *prev;
	char* p2;
	int total_credit =0 ;
	float sum = 0, gpa;
		system("cls");
    printf("* 辅导员，欢迎来到学生成绩查询界面！\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  │ \t                   *   学生成绩查询    *                            │\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf("* 请按照要求依次填入该学生的信息：\n");
    printf("\n");
	printf("请输入您需要查找的学生的学号并以回车结束:\n");
	scanf("%s",temp.id);
	p2 = get_user_name(p1->id);
		printf("\n");
	printf("\n");
	printf("请输入您需要查找的学期并以回车结束:\n");
	scanf("%d",&temp.term);
	temp.subject[0] = '-';
	head = get_mark(temp.id, p1);
		printf("\n");
	printf("\n");
	printf("%s同学的成绩如下：\n",p2);
	for(now=head;now!=NULL;now=now->next)
	{
		printf("\t%s\t\t%d\n",now->subject,now->mark);
		total_credit += now->credit;
		sum += ((float)now->mark - 50) / 10 * (now->credit);
    }
	gpa = sum/ total_credit;
	printf("该学期综合绩点为：\t%.2f\n", gpa);
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
}
/*******************************************************************************
  * @函数名称		display_classtranscript
  * @函数说明		显示班级成绩单
  * @输入参数       char *identity(当前用户账号)
  * @返回参数       void
  *****************************************************************************/
void display_classtranscript(char *identity)
{
	struct user temp1;
	struct user *p0=&temp1;
	struct user_linked *now1, *head1, *prev1;
	struct mark temp2;
	struct mark *p2=&temp2;
	struct mark_linked *now2, *head2, *prev2;
	int total_credit =0, num=1;
	double sum = 0, total_gpa=0, aver_gpa, vari_gpa=0, devi_gpa;
	double per_gpa[100]={0};
	char *box;

	temp1.type=1;

	box=get_user_school(identity);
	strcpy(temp1.school,box);
	free(box);

	temp1.grade=get_user_grade(identity);
		system("cls");
    printf("* 辅导员，欢迎来到班级成绩查询界面！\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  │ \t                   *   班级成绩查询    *                            │\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf("* 请按照要求依次填入所需班级的信息：\n");
    printf("\n");
	printf("请输入您希望导出成绩的学期:");
    scanf("%d",&temp2.term);
    temp2.subject[0]='-';
    	printf("\n");
	printf("\n");
	printf("请输入需要导出成绩表的专业:");
	scanf("%s",temp1.major);
		printf("\n");
	printf("\n");
	printf("请输入需要导出班级的班级编号:");
	scanf("%d",&temp1.class_id);
    printf("\n");
	printf("\n");
	head1 = search_all_for_id(p0);
	head2 = get_mark(head1->id, p2);

	for(now2=head2;now2!=NULL;now2=now2->next)
	{
		printf("\t\t\t%s\t    ",now2->subject);
	}
	printf("该学期综合绩点\n");
	for(now1=head1;now1!=NULL;now1=now1->next,sum=0,total_credit=0,num++)
	{
	    head2 = get_mark(now1->id, p2);
	    if(head2==NULL) continue;
		printf("%s\t%s", now1->id,now1->name);
		for(now2=head2;now2!=NULL;now2=now2->next)
		{
			printf("\t\t%d\t\t", now2->mark);
			total_credit += now2->credit;
			sum += ((float)now2->mark - 50.0) / 10.0 * (now2->credit);
		}
		per_gpa[num] = sum/ total_credit;
		printf("%.2f\n", per_gpa[num]);
		for(now2=head2,prev2=now2;now2!=NULL;prev2=now2)
		{
			now2=now2->next;
			free(prev2);
		}
	}
	for(now1=head1,prev1=now1;now1!=NULL;prev1=now1)
	{
		now1=now1->next;
		free(prev1);
	}
	printf("\n");
	for(num=1;per_gpa[num]!=0;num++)
	{
		total_gpa += per_gpa[num] ;
	}
	aver_gpa = total_gpa / (num-1);
	printf("该班级的平均绩点为：%.2f\n", aver_gpa);
	for(num=1;per_gpa[num]!=0;num++)
	{
		vari_gpa += (pow(per_gpa[num],2) - pow(aver_gpa,2));
	}
	devi_gpa = sqrt(vari_gpa/(num-1));
	printf("该班级的绩点标准差为：%.2f", devi_gpa);
}



/*******************************************************************************
  * @函数名称		display_underachiever
  * @函数说明		显示挂科学生及成绩单
  * @输入参数       char *identity(当前用户账号)
  * @返回参数       void
  *****************************************************************************/
void display_underachiever(char *identity)
{
	struct user temp1;
	struct user *p0=&temp1;
	struct user_linked *now1, *head1, *prev1;
	struct mark temp2;
	struct mark *p2=&temp2;
	struct mark_linked *now2, *head2, *prev2;
	char *p;
	p = get_user_school(identity);
	strcpy(temp1.school,p);
	free(p);
	temp1.type=1;
	temp1.grade = get_user_grade(identity);
	temp1.major[0]='-';
	temp1.class_id=-1;
    system("cls");
    printf("* 辅导员，欢迎来到挂科学生名单输出界面！\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  │ \t                   *   挂科名单查询    *                            │\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf(" *  请按照要求依次填入所需的信息：\n");
    printf("\n");
	printf("请输入您希望查看的学期:");
	scanf("%d",&temp2.term);
	temp2.subject[0]='-';
	head1 = search_all_for_id(p0);
    printf("\n");
	printf("\n");
	printf("年级中挂科人数如下：\n");
	for(now1=head1;now1!=NULL;now1=now1->next)
	{
	    head2 = get_mark(now1->id, p2);
        if(head2==NULL) continue;
		for(now2=head2;now2!=NULL;now2=now2->next)
		{
			if(now2->mark<60)
			{
				printf("%s\t%s\t%s\t%d班\t%s\t%d\n",now1->name,now1->id,now1->major,now1->class_id,now2->subject,now2->mark);
                break;
			}
		}

		for(now2=head2,prev2=now2;now2!=NULL;prev2=now2)
		{
			now2=now2->next;
			free(prev2);
		}
	}
	for(now1=head1,prev1=now1;now1!=NULL;prev1=now1)
	{
		now1=now1->next;
		free(prev1);
	}
}



/*******************************************************************************
  * @函数名称		file_output
  * @函数说明		导出成绩单
  * @输入参数       char *identity(当前用户账号)
  * @返回参数       void
  *****************************************************************************/
void file_output(char *identity)
{
	struct user temp1;
	struct user *p0=&temp1;
	struct user_linked *now1, *head1, *prev1;
	struct mark temp2;
	struct mark *p2=&temp2;
	struct mark_linked *now2, *head2, *prev2;
	int total_credit =0, num=1;
	double sum = 0, total_gpa=0, aver_gpa, vari_gpa=0, devi_gpa;
	double per_gpa[100]={0};
	FILE *fp;
	char *box;

	temp1.type=1;

	box=get_user_school(identity);
	strcpy(temp1.school,box);
	free(box);

	temp1.grade=get_user_grade(identity);
		system("cls");
    printf("* 辅导员，欢迎来到成绩单导出界面！\n");
    printf("  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅\n");
    printf("\n");
    printf("  ┏────────────────────────────────────┓\n");
    printf("  │ \t                   *   成绩单导出    *                             │\n");
    printf("  ┣┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┫ \n");
    printf(" *  请按照要求依次填入所需的信息：\n");
    printf("\n");
    printf("\n");
	printf(" *  请输入您希望导出成绩的学期 : ");
    scanf("%d",&temp2.term);
    temp2.subject[0]='-';
    printf("\n");
    printf("\n");
	printf(" *  请输入需要导出成绩表的专业 :");
	scanf("%s",temp1.major);
	printf("\n");
	printf("\n");
	printf("请输入需要导出班级的班级编号:");
	scanf("%d",&temp1.class_id);

	head1 = search_all_for_id(p0);
	head2 = get_mark(head1->id, p2);

	fp = fopen("trsnscript.txt", "w");
	for(now2=head2;now2!=NULL;now2=now2->next)
	{
		fprintf(fp, "\t\t\t\t%s\t\t\t",now2->subject);
	}
	fprintf(fp, "该学期综合绩点\n");
	for(now1=head1;now1!=NULL;now1=now1->next,sum=0,total_credit=0,num++)
	{
	    head2 = get_mark(now1->id, p2);
	    if(head2==NULL) continue;
		fprintf(fp, "%s\t%s", now1->id,now1->name);
		for(now2=head2;now2!=NULL;now2=now2->next)
		{
			fprintf(fp, "\t\t\t\t%d\t\t\t\t\t", now2->mark);
			total_credit += now2->credit;
			sum += ((float)now2->mark - 50.0) / 10.0 * (now2->credit);
		}
		per_gpa[num] = sum/ total_credit;
		fprintf(fp, "\t\t%.2f\n", per_gpa[num]);
		for(now2=head2,prev2=now2;now2!=NULL;prev2=now2)
		{
			now2=now2->next;
			free(prev2);
		}
	}
	for(now1=head1,prev1=now1;now1!=NULL;prev1=now1)
	{
		now1=now1->next;
		free(prev1);
	}
	fprintf(fp,"\n");
	for(num=1;per_gpa[num]!=0;num++)
	{
		total_gpa += per_gpa[num] ;
	}
	aver_gpa = total_gpa / (num-1);
	fprintf(fp, "该班级的平均绩点为：%.2f\n", aver_gpa);
	for(num=1;per_gpa[num]!=0;num++)
	{
		vari_gpa += (pow(per_gpa[num],2) - pow(aver_gpa,2));
	}
	devi_gpa = sqrt(vari_gpa/(num-1));
	fprintf(fp, "该班级的绩点标准差为：%.2f", devi_gpa);
	fclose(fp);
}
