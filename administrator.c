/**
  ******************************************************************************
    * @File:		administrator.c
    * @Author:	    �Ƽ���
	* @Date:		2017-05-19
	* @Brief:		����Ա�û�Դ�ļ�
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

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		add_user
  * @����˵��		�ֶ�����û�
  * @�������       void
  * @���ز���       0(����ɹ�),-1(�û��Ѵ���)
  *****************************************************************************/
int add_user(void){
    struct user temp;
    int state;
    system("cls");
    printf("* ����Ա����ӭ��������û����棡\n");
    printf("��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  ��    \t\t\t*   ����û�   * \t\t\t    ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf("*�밴��Ҫ����������ѧ�š�����������������Ϣ��\n");
    printf("\n");
    printf("\t   *1.ѧ��/���� *: ");
    scanf("%s",temp.id);
    printf("\n");
    printf("\t   *   2.����   *: ");
    scanf("%s",temp.name);
    printf("\n");
    printf("\t   *   3.����   *: ");
    scanf("%s",temp.password);
    printf("\n");
    printf("\t   *4 .����ѧԺ *: ");;
    scanf("%s",temp.school);
    printf("\n");
    printf("\t   *5.���û������� *:\n ");
    printf("ע��(1Ϊѧ��,2Ϊ��ʦ,3Ϊ����Ա)��");
    scanf("%d",&temp.type);
     if(temp.type==1){
        system("cls");
        printf("* �ѳɹ������û����û����ͣ�ѧ��\n");
        printf("��������������������������������\n");
        printf("\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��    \t\t\t*   ��Ϣ����   * \t\t\t    ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("* �밴��Ҫ��Ϊ��ѧ��������Ϣ����ǳ���Ҫ\n");
        printf("\n");
        printf("\t   *1.�����꼶  *: ");
        scanf("%d",&temp.grade);
        printf("\n");
        printf("\t   *2.����רҵ  *: ");
        scanf("%s",temp.major);
        printf("\n");
        printf("\t   *3.�������  *: ");
        scanf("%d",&temp.class_id);
        printf("\n\n");
        printf("* ��ϲ�㣡�ѳɹ��������û���\n");
        printf("* �û����ͣ�ѧ��\n");
        printf("* �ɷ�����\t*����΢��\t*����Ȧ        *QQ�ռ�\n");
        printf("\n");


    }else if(temp.type==3){
        system("cls");
        printf("* �ѳɹ������û����û����ͣ�����Ա\n");
        printf("��������������������������������\n");
        printf("\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��    \t\t\t*   ��Ϣ����   * \t\t\t    ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("* �밴��Ҫ��Ϊ�ø���Ա������Ϣ����ǳ���Ҫ\n");
        printf("\n");
        printf("\t   *1.�����꼶  *: ");
        scanf("%d",&temp.grade);
    }

    state=add_to_db(&temp);
    if(state==0){
        system("cls");
        printf("* ��ϲ�㣡�ѳɹ��������û���\n");
        printf("  ��������������������������\n");
        printf("�V============================================================================�Y");
        printf("�� \t                    *   �����û��ɹ�    *                           ��\n");
        printf("��������������������������������������������������������������������������������");
        printf("* �һ�������Щʲô��  \n");
        system("pause");
        printf("\n");
        printf("* �㻹���Խ�ͼ������\t*����΢��\t*����Ȧ        *QQ�ռ�\n");

        return 0;
    }else if(state==-1){
        system("cls");
        printf("* �ܱ�Ǹ�������˹���\n");
        printf("��������������������\n");
        printf("�V============================================================================�Y");
        printf("�� \t                    *  �������û�ʧ�� ��  *                           ��\n");
        printf("��������������������������������������������������������������������������������");
        printf("* �ܱ�Ǹ��������һЩ���󣨰�������鿴����ͽ��������  \n");
        system("pause");
        printf("  *  ����   �������������û���ѧ����������ǰ��ĳһ�û���ѧ�š������ظ���  \n");
        printf("\n\n");
        printf("  *�ҿ�����ô�죿��1.������ɾ�����ݿ������е���������û� \n");
        printf("  *                2.��Ҳ�����Ƿ��������ĸ��û������������󣬲�������������  \n");
        printf("  *                3.��������Ѱ�����ǵİ�����֧�����˻���123456  \n");
        return 0;
    }
    return -1;
}

/*******************************************************************************
  * @��������		add_student_csv
  * @����˵��		�������ѧ���û�
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int add_student_csv(void){  //ʹ��ansi����
    FILE *fp=fopen("student.csv","r");
    struct user temp;
    char s[256];
    char *c;
    char password[30];
    int state;
    while(1){
        system("cls");
        printf("* ����Ա����ӭ������������û����棡\n");
        printf("��������������������������������\n");
        printf("\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��    \t\t\t*   ��������û�   * \t\t\t    ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("* ����������Ԥ�����룺");
        scanf("%s",password);
        if(strlen(password)>16){
            system("cls");
            printf("* �ܱ�Ǹ�����޷�ִ�����ָ��\n");
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
            printf("* �ҿ�����ô�죿��1.�����Գ������������������룬����Ա���żȻ���������������� \n");
            printf("*                 2.��������Ѱ�����ǵİ�����֧�����˻���123456  \n");
            printf("\n");
            printf("\t                                                    ��������˳��ý���\n");
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
            printf("%s��ӳɹ�\n",temp.id);
        }else if(state==-1){
            printf("%s�Ѵ���\n",temp.id);
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @��������		add_teacher_csv
  * @����˵��		������ӽ�ʦ�û�
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int add_teacher_csv(void){
    FILE *fp=fopen("teacher.csv","r");
    struct user temp;
    char s[256];
    char *c;
    char password[30];
    int state;
    printf("������Ԥ������(С�ڵ���16λ�ַ�):");
    while(1){
        scanf("%s",password);
        if(strlen(password)>16){
            printf("����̫��������������:");
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
            printf("%s��ӳɹ�\n",temp.id);
        }else if(state==-1){
            printf("%s�Ѵ���\n",temp.id);
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @��������		add_counselor_csv
  * @����˵��		������Ӹ���Ա�û�
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int add_counselor_csv(void){
    FILE *fp=fopen("counselor.csv","r");
    struct user temp;
    char s[256];
    char *c;
    char password[30];
    int state;
    printf("������Ԥ������(С�ڵ���16λ�ַ�):");
    while(1){
        scanf("%s",password);
        if(strlen(password)>16){
            printf("����̫��������������:");
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
            printf("%s��ӳɹ�\n",temp.id);
        }else if(state==-1){
            printf("%s�Ѵ���\n",temp.id);
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @��������		view_all
  * @����˵��		�鿴�����û�
  * @�������       void
  * @���ز���       0(���)
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
    printf("* ����Ա����ӭ�����鿴�û����棡\n");
    printf("��������������������������������\n");
    printf("\n");
    printf("  ����������������������������������������������������������������������������\n");
    printf("  ��    \t\t\t*   �鿴�û�   * \t\t\t    ��\n");
    printf("  �ǩ������������������������������������������������������������������������� \n");
    printf("*ϵͳ�ֽ����е��û����±���ʾ��\n");
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
  * @��������		del_user_from_csv
  * @����˵��		����ɾ���û�
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int del_user_from_csv(void){
    FILE *fp=fopen("user_to_be_del.csv","r");
    char s[256];
    int state,user_type;
    while(fscanf(fp,"%s",s)!=-1){
        if(in_db(s)==-1){
            printf("%s������\n",s);
            continue;
        }
        user_type=search_for_type(s);
        state=!del_from_db(s);
        if(user_type==1){
            state=!del_mark(s)&&state;
        }else if(user_type==2){
            state=!del_teaching_task(s)&&state;
        }
        if(state)printf("%s�ѱ�ɾ��\n",s);
        else printf("%sɾ������\n",s);
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @��������		add_teaching_task_csv
  * @����˵��		��ӽ�ѧ����
  * @�������       void
  * @���ز���       0(���)
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
            printf("��ѧ�����������ͬ������\n");
            continue;
        }else if(state==-2){
            printf("�ļ��޷���\n");
            continue;
        }
        state=add_teaching_task(&temp);
        if(state==0){
            printf("��ӳɹ�\n");
        }else if(state==-1){
            printf("���ʧ��\n");
        }
    }
    fclose(fp);
    return 0;
}

/*******************************************************************************
  * @��������		del_user
  * @����˵��		ɾ���û�
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int del_user()
{
  char id[20];
  int r;
  printf("������Ҫɾ�����û��ʺ�:\n");
  scanf("%s",id);
  r=del_from_db(id);
  if(r==0)
    printf("ɾ���ɹ�\n");
  else
    printf("ɾ��ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		add_courses
  * @����˵��		�ֶ���ӽ�ѧ����
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int add_courses()
{
	struct task temp;
    int state;
    printf("�������ʦ����:");
    scanf("%s",temp.id);

    printf("�������ڿ�ѧԺ:");
    scanf("%s",temp.school);

    printf("�������ڿ��꼶:");
    scanf("%d",&temp.grade);

    printf("�������ڿ�רҵ:");
    scanf("%s",temp.major);

    printf("�������ڿΰ��:");
    scanf("%d",&temp.class_id);

    printf("�������ڿ�ѧ��:");
    scanf("%d",&temp.term);

    printf("������γ�����:");
    scanf("%s",temp.subject);

    temp.task_state=0;

    state=add_teaching_task(&temp);
    if(state==0){
        printf("��ӳɹ�\n");
    }else if(state==-1){
        printf("���ʧ��\n");
    }
    return 0;
}

/*******************************************************************************
  * @��������		mdfpassword
  * @����˵��		�޸��û�����
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfpassword()
{
    char id[20];
    char new_pass[20];
    char temp[20];
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    while(1)
    {
        printf("������������:\n");
        scanf("%s",temp);
        printf("�ٴ�����������:\n");
        scanf("%s",new_pass);
        if(strcmp(temp,new_pass)==0)
            break;
        else
            printf("���벻һ��!\n");
    }
    r=mod_password(id,new_pass);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdfschool
  * @����˵��		�޸��û�����ѧԺ
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfschool()
{
    char id[20];
    char new_school[20];
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("������������ѧԺ:\n");
    scanf("%s",new_school);
    r=mod_school(id,new_school);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdfmajor
  * @����˵��		�޸��û�����רҵ
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfmajor()
{
    char id[20];
    char new_major[20];
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("������������רҵ:\n");
    scanf("%s",new_major);
    r=mod_major(id,new_major);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdfgrade
  * @����˵��		�޸��û������꼶
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfgrade()
{
    char id[20];
    int new_grade;
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("�������������꼶:\n");
    scanf("%d",&new_grade);
    r=mod_grade(id,new_grade);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdfcls_id
  * @����˵��		�޸��û������༶
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfcls_id()
{
    char id[20];
    int newcls_id;
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("�������������༶:\n");
    scanf("%d",&newcls_id);
    r=mod_class_id(id,newcls_id);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdfname
  * @����˵��		�޸��û�����
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfname()
{
    char id[20];
    char newname[20];
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("������������:\n");
    scanf("%s",newname);
    r=mod_name(id,newname);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdftype
  * @����˵��		�޸��û�����
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdftype()
{
    char id[20];
    int newtype;
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("������������:\n");
    scanf("%d",&newtype);
    r=mod_type(id,newtype);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}

/*******************************************************************************
  * @��������		mdfid
  * @����˵��		�޸��û��˺�
  * @�������       void
  * @���ز���       0(���)
  *****************************************************************************/
int mdfid()
{
    char id[20];
    char newid[20];
    int r;
    printf("������Ҫ�޸ĵ��û�ID:\n");
    scanf("%s",id);
    printf("���������˺�:\n");
    scanf("%s",newid);
    r=mod_id(id,newid);
    if(r==0){
        printf("�޸ĳɹ�\n");}
    else
        printf("�޸�ʧ��\n");
    return 0;
}
