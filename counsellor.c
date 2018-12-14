/**
  ******************************************************************************
    * @File:		counsellor.c
    * @Author:	    ������
	* @Date:		2017-05-19
	* @Brief:		����Ա�û�Դ�ļ�
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

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		display_studentgrade
  * @����˵��		��ʾѧ���ɼ�
  * @�������       void
  * @���ز���       void
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
    printf("* ����Ա����ӭ����ѧ���ɼ���ѯ���棡\n");
    printf("  ��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  �� \t                   *   ѧ���ɼ���ѯ    *                            ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf("* �밴��Ҫ�����������ѧ������Ϣ��\n");
    printf("\n");
	printf("����������Ҫ���ҵ�ѧ����ѧ�Ų��Իس�����:\n");
	scanf("%s",temp.id);
	p2 = get_user_name(p1->id);
		printf("\n");
	printf("\n");
	printf("����������Ҫ���ҵ�ѧ�ڲ��Իس�����:\n");
	scanf("%d",&temp.term);
	temp.subject[0] = '-';
	head = get_mark(temp.id, p1);
		printf("\n");
	printf("\n");
	printf("%sͬѧ�ĳɼ����£�\n",p2);
	for(now=head;now!=NULL;now=now->next)
	{
		printf("\t%s\t\t%d\n",now->subject,now->mark);
		total_credit += now->credit;
		sum += ((float)now->mark - 50) / 10 * (now->credit);
    }
	gpa = sum/ total_credit;
	printf("��ѧ���ۺϼ���Ϊ��\t%.2f\n", gpa);
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
}
/*******************************************************************************
  * @��������		display_classtranscript
  * @����˵��		��ʾ�༶�ɼ���
  * @�������       char *identity(��ǰ�û��˺�)
  * @���ز���       void
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
    printf("* ����Ա����ӭ�����༶�ɼ���ѯ���棡\n");
    printf("  ��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  �� \t                   *   �༶�ɼ���ѯ    *                            ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf("* �밴��Ҫ��������������༶����Ϣ��\n");
    printf("\n");
	printf("��������ϣ�������ɼ���ѧ��:");
    scanf("%d",&temp2.term);
    temp2.subject[0]='-';
    	printf("\n");
	printf("\n");
	printf("��������Ҫ�����ɼ����רҵ:");
	scanf("%s",temp1.major);
		printf("\n");
	printf("\n");
	printf("��������Ҫ�����༶�İ༶���:");
	scanf("%d",&temp1.class_id);
    printf("\n");
	printf("\n");
	head1 = search_all_for_id(p0);
	head2 = get_mark(head1->id, p2);

	for(now2=head2;now2!=NULL;now2=now2->next)
	{
		printf("\t\t\t%s\t    ",now2->subject);
	}
	printf("��ѧ���ۺϼ���\n");
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
	printf("�ð༶��ƽ������Ϊ��%.2f\n", aver_gpa);
	for(num=1;per_gpa[num]!=0;num++)
	{
		vari_gpa += (pow(per_gpa[num],2) - pow(aver_gpa,2));
	}
	devi_gpa = sqrt(vari_gpa/(num-1));
	printf("�ð༶�ļ����׼��Ϊ��%.2f", devi_gpa);
}



/*******************************************************************************
  * @��������		display_underachiever
  * @����˵��		��ʾ�ҿ�ѧ�����ɼ���
  * @�������       char *identity(��ǰ�û��˺�)
  * @���ز���       void
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
    printf("* ����Ա����ӭ�����ҿ�ѧ������������棡\n");
    printf("  ��������������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  �� \t                   *   �ҿ�������ѯ    *                            ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf(" *  �밴��Ҫ�����������������Ϣ��\n");
    printf("\n");
	printf("��������ϣ���鿴��ѧ��:");
	scanf("%d",&temp2.term);
	temp2.subject[0]='-';
	head1 = search_all_for_id(p0);
    printf("\n");
	printf("\n");
	printf("�꼶�йҿ��������£�\n");
	for(now1=head1;now1!=NULL;now1=now1->next)
	{
	    head2 = get_mark(now1->id, p2);
        if(head2==NULL) continue;
		for(now2=head2;now2!=NULL;now2=now2->next)
		{
			if(now2->mark<60)
			{
				printf("%s\t%s\t%s\t%d��\t%s\t%d\n",now1->name,now1->id,now1->major,now1->class_id,now2->subject,now2->mark);
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
  * @��������		file_output
  * @����˵��		�����ɼ���
  * @�������       char *identity(��ǰ�û��˺�)
  * @���ز���       void
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
    printf("* ����Ա����ӭ�����ɼ����������棡\n");
    printf("  ��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  �� \t                   *   �ɼ�������    *                             ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf(" *  �밴��Ҫ�����������������Ϣ��\n");
    printf("\n");
    printf("\n");
	printf(" *  ��������ϣ�������ɼ���ѧ�� : ");
    scanf("%d",&temp2.term);
    temp2.subject[0]='-';
    printf("\n");
    printf("\n");
	printf(" *  ��������Ҫ�����ɼ����רҵ :");
	scanf("%s",temp1.major);
	printf("\n");
	printf("\n");
	printf("��������Ҫ�����༶�İ༶���:");
	scanf("%d",&temp1.class_id);

	head1 = search_all_for_id(p0);
	head2 = get_mark(head1->id, p2);

	fp = fopen("trsnscript.txt", "w");
	for(now2=head2;now2!=NULL;now2=now2->next)
	{
		fprintf(fp, "\t\t\t\t%s\t\t\t",now2->subject);
	}
	fprintf(fp, "��ѧ���ۺϼ���\n");
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
	fprintf(fp, "�ð༶��ƽ������Ϊ��%.2f\n", aver_gpa);
	for(num=1;per_gpa[num]!=0;num++)
	{
		vari_gpa += (pow(per_gpa[num],2) - pow(aver_gpa,2));
	}
	devi_gpa = sqrt(vari_gpa/(num-1));
	fprintf(fp, "�ð༶�ļ����׼��Ϊ��%.2f", devi_gpa);
	fclose(fp);
}
