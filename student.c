/**
  ******************************************************************************
    * @File:		student.c
    * @Author:	    ����⡢������
	* @Date:		2017-05-19
	* @Brief:		ѧ���û�Դ�ļ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include"student.h"
#include<stdio.h>
#include<string.h>
#include"db_operation.h"
#include"mark.h"
#include<stdlib.h>

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		modify_my_password
  * @����˵��		�޸��Լ�������,�ú���Ҳ�ɱ������û�ʹ��
  * @�������       char *id
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
  *****************************************************************************/
int modify_my_password(char *id){
    char password[30];
    while(1){
        system("cls");
        printf("* ��ӭ�����޸�������棡\n");
        printf("������������������������\n");
        printf("\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��    \t\t\t*   �޸�����  * \t\t\t    ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("\n");
        printf("������������(С�ڵ���16λ�ַ�):");
        scanf("%s",password);
        if(strlen(password)>16){
            system("cls");
            printf("* �ܱ�Ǹ�������޷�ִ�����ָ��\n");
            printf("  ��������������������������\n");
            printf("\n\n");
            printf("�V============================================================================�Y");
            printf("��                                                                            ��");
            printf("�� \t                  ����������������������������� ��                   ��\n");
            printf("��                                                                            ��");
            printf("��������������������������������������������������������������������������������");
            printf("* ���׷�����ʲô��\n");
            printf("\n");
            system("pause");
            printf("* ���� ��        ����������볤�ȳ�����16����������������ϵͳ���趨�ǲ�ͬ�ġ�\n");
            printf("*                              ����������ֹ�����Ĳ�����\n");
            printf("\n");
            system("pause");
        }else{
            break;
        }
    }
    if(!mod_password(id,password)){
        system("cls");
        printf("* ��ϲ�㣡�ѳɹ��޸����룡\n");
        printf("  ��������������������������\n");
        printf("�V============================================================================�Y");
        printf("�� \t                    *   �޸�����ɹ�    *                             ��\n");
        printf("��������������������������������������������������������������������������������");

        return 0;
    }else{
        system("cls");
        printf("* ��Ǹ���޸�����ʧ�ܣ�\n");
        printf("  ��������������������������\n");
        printf("�V============================================================================�Y");
        printf("�� \t                    *   �޸�����ʧ��    *                             ��\n");
        printf("��������������������������������������������������������������������������������");
        system("pause");
        return -1;
    }
}

/*******************************************************************************
  * @��������		view_mark
  * @����˵��		�鿴�ɼ�
  * @�������       char *id
  * @���ز���       0(���)
  *****************************************************************************/
int view_mark(char *id){
    struct mark temp;
    struct mark_linked *head,*now,*prev;
    strcpy(temp.id,id);
    temp.subject[0]='-';
    temp.term=-1;
    head=get_mark(id,&temp);
    system("cls");
    printf("* ͬѧ����ӭ����鿴�ɼ�����\n");
    printf("  ��������������������������\n");
    printf("�V============================================================================�Y");
    printf("�� \t                    *   �ɼ���ѯ    *                                 ��\n");
    printf("��������������������������������������������������������������������������������");
    printf("* \n");
    printf("���޹��Ŀγ�:\n");
    for(now=head;now!=NULL;now=now->next){
        printf("    ѧ��:%s ѧ��:%d\n",now->subject,now->term);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    printf("��������Ҫ�鿴�Ŀγ�(Ҫ�鿴���гɼ������롮���С�):");
    scanf("%s",temp.subject);
    printf("��������Ҫ�鿴��ѧ��(Ҫ�鿴����ѧ�������롮-1��):");
    scanf("%d",&temp.term);
    if(strcmp(temp.subject,"����")==0){
        temp.subject[0]='-';
    }
    head=get_mark(id,&temp);
    for(now=head;now!=NULL;now=now->next){
        printf("    ѧ��:%s ѧ��:%d �ɼ�:%d ѧ��:%d\n",now->subject,now->term,now->mark,now->credit);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    return 0;
}

/*******************************************************************************
  * @��������		output_mark_csv
  * @����˵��		����ɼ���csv�ļ�
  * @�������       char *id
  * @���ز���       0(���)
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
    printf("* ͬѧ����ӭ����鿴�ɼ�����\n");
    printf("  ��������������������������\n");
     printf("�V============================================================================�Y");
    printf("�� \t                    *   �ɼ���ѯ    *                                 ��\n");
    printf("��������������������������������������������������������������������������������");
    printf("* \n");
    printf("���޹��Ŀγ�:\n");
    for(now=head;now!=NULL;now=now->next){
        printf("    subject:%s term:%d\n",now->subject,now->term);
    }
    for(now=head,prev=now;now!=NULL;prev=now){
        now=now->next;
        free(prev);
    }
    printf("��������Ҫ�����Ŀγ�(Ҫ�鿴���гɼ������롮���С�):");
    scanf("%s",temp.subject);
    printf("��������Ҫ�鿴��ѧ��(Ҫ�鿴����ѧ�������롮-1��):");
    scanf("%d",&temp.term);
    if(strcmp(temp.subject,"����")==0){
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
