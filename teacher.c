/**
  ******************************************************************************
    * @File:		teacher.c
    * @Author:	    �»���
	* @Date:		2017-05-22
	* @Brief:		��ʦ�û�����Դ�ļ�
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

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		int input_mark_csv(void)
  * @����˵��		��ʦ�����Ͻ��ɼ�����CSV�ļ��Ͻ�
  * @�������      ��
  * @���ز���      ����0��ʾ�ɹ�����
  *****************************************************************************/
int input_mark_csv(char *id){  //ʹ��ansi����
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
    printf("* ��ʦ����ӭ��������ɼ����棡\n");
    printf("��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  ��                         *   ��������ѧ���ɼ�   *                       ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf("\n");
    printf("δ�ύ�ɼ����Ľ�ѧ����:\n");
    for(now=head,i=1;now!=NULL;now=now->next,i++){
        printf("    %d subject:%s term:%d school:%s major:%s grade:%d class_id:%d\n",i,now->subject,now->term,now->school,now->major,now->grade,now->class_id);
    }
    printf("\n");
    printf("������Ҫ�ύ�ĳɼ����ı��:");
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
            printf("%s ���ڳɼ�����\n",user_now->id);
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
                printf("%s ���ڸð���\n",id_in_file);
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
        printf("���ڳɼ�����༶������ƥ��,�޷�����\n");
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
  * @��������		int search_for_task_with_state(void)
  * @����˵��		�鿴��ѧ����״̬
  * @�������      char *id(��ǰ�˺�),int state(Ҫ�鿴��״̬)
  * @���ز���      ����0��ʾ���
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
        printf("�޼�¼\n");
        return 0;
    }
    for(now=head,i=1;now!=NULL;now=now->next,i++){
        printf("    %d ѧ��:%s ѧ��:%d ѧԺ:%s רҵ:%s �꼶:%d ���:%d\n",i,now->subject,now->term,now->school,now->major,now->grade,now->class_id);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}


/*******************************************************************************
  * @��������	   int view_mark_of_student(void)
  * @����˵��	   �鿴ѧ���ɼ�
  * @�������      id(ѧ��ѧ�ţ�
  * @���ز���      ����0��ʾ�ɹ���ѯ
  *****************************************************************************/
int view_mark_of_student(void){

    struct mark temp;
    struct mark_linked *head,*now,*prev;
    system("cls");
    printf("* ��ʦ����ӭ����ѧ���ɼ���ѯ���棡\n");
    printf("  ��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  �� \t                   *   ѧ���ɼ���ѯ    *                            ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf(" * �밴��Ҫ�����������ѧ������Ϣ��\n");
    printf("\n");
    printf("\n");
	printf("����������Ҫ��ѯ��ѧ�ţ�");
	scanf("%s",temp.id);
    //strcpy(temp.id,id);
    temp.subject[0]='-';
    temp.term=-1;
    head=get_mark(temp.id,&temp);
    printf("��ѧ���޹��Ŀγ�:\n");
    for(now=head;now!=NULL;now=now->next){
        printf("    �γ�:%s ѧ��:%d\n",now->subject,now->term);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    printf("\n");
    printf("\n");
    printf("��������Ҫ�鿴�Ŀγ�(Ҫ�鿴���гɼ������롮���С�):");
    scanf("%s",temp.subject);
    printf("\n");
    printf("\n");
    printf("��������Ҫ�鿴��ѧ��(Ҫ�鿴����ѧ�������롮-1��):");
    scanf("%d",&temp.term);
    if(strcmp(temp.subject,"����")==0){
        temp.subject[0]='-';
    }
    head=get_mark(temp.id,&temp);
    for(now=head;now!=NULL;now=now->next){
        printf("    �γ�:%s ѧ��:%d �ɼ�:%d ѧ��:%d\n",now->subject,now->term,now->mark,now->credit);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}

/*******************************************************************************
  * @��������	   int output_student_csv(char *id)
  * @����˵��	   ����ѧ���ɼ�
  * @�������      id(ѧ��ѧ�ţ�
  * @���ز���      ����0��ʾ�ɹ���ѯ���ɹ���������������;���������û���ҵ���Ӧ�γ̣�
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
    printf("* ��ʦ����ӭ�������ڱ������棡\n");
    printf("  ��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  �� \t                    *   �������ڱ�    *                             ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf("\n");
    printf(" * �밴��Ҫ�����������������Ϣ��\n");
    printf("\n");
    printf("\n");
    printf("������Ҫ������������ѧԺ:");
    scanf("%s",con.school);
    printf("\n");
    printf("\n");
    printf("������Ҫ�������������꼶:");
    scanf("%d",&con.grade);
    printf("\n");
    printf("\n");
    printf("������Ҫ������������רҵ:");
    scanf("%s",con.major);
    printf("\n");
    printf("\n");
    printf("������Ҫ�����������İ��:");
    scanf("%d",&con.class_id);
    printf("\n");
    printf("\n");
    printf("������Ҫ������������ѧ��:");
    scanf("%d",&con.term);
    printf("\n");
    printf("\n");
    printf("������Ҫ�����������Ŀγ�����:");
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
        printf("�������\n");
    }else{
        printf("û���ҵ���Ӧ�γ�\n");
    }
    return 0;
}
