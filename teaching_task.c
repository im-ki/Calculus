/**
  ******************************************************************************
    * @File:		teaching_task.c
    * @Author:	    �����
	* @Date:		2017-05-19
	* @Brief:		��ʦ��ѧ��������Դ�ļ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"teaching_task.h"
#include"db_operation.h"
#include<stdlib.h>
#include<string.h>
#include<io.h>

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/
static int encode_write(struct task *user_task,FILE *fp);
static int decode_read(struct task *user_task,FILE *fp);
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len);
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len);

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		add_teaching_task
  * @����˵��		����µĽ�ѧ����
  * @�������       struct task *new_task
  * @���ز���       0(��ӳɹ�),-1(���ʧ��)
  *****************************************************************************/
int add_teaching_task(struct task *new_task){
	int type=search_for_type(new_task->id);
	if(type==2){
		FILE *fp=fopen(new_task->id,"ab");
		//fwrite(new_task,sizeof(struct task),1,fp);
		encode_write(new_task,fp);
		fclose(fp);
		return 0;
	}
	return -1;
}

/*******************************************************************************
  * @��������		in_teaching_task
  * @����˵��		�鿴Ҫ��ӵĽ�ѧ�����Ƿ��ڱ���
  * @�������       struct task *new_task
  * @���ز���       0(����),-1(��������ͬ������),-2(�޷����ļ�)
  *****************************************************************************/
int in_teaching_task(struct task *new_task){
	struct task temp;
    FILE *fp;
    if(access(new_task->id,0)==0){
        fp=fopen(new_task->id,"rb");
        while(decode_read(&temp,fp)){
            //fread(&temp,sizeof(struct user),1,fp);
            if(strcmp(temp.subject,new_task->subject)==0){
                if(temp.term==new_task->term){
                    if(strcmp(temp.school,new_task->school)==0){
                        if(temp.grade==new_task->grade){
                            if(strcmp(temp.major,new_task->major)==0){
                                if(temp.class_id==new_task->class_id){
                                    fclose(fp);
                                    return -1;
                                }
                            }
                        }
                    }
                }
            }
        }
        fclose(fp);
        return 0;
    }
    return 0;
}
/*******************************************************************************
  * @��������		get_teaching_task
  * @����˵��		��ȡ���������Ľ�ѧ����
  * @�������       struct task *con
  * @���ز���       head(�����ͷ),NULL(û�з��������Ľ�ѧ����)
  *****************************************************************************/
struct task_linked *get_teaching_task(struct task *con){
    struct task temp;
    struct task_linked *head=NULL,*now,*prev;
    FILE *fp;
    if(access(con->id,0)==0){
        fp=fopen(con->id,"rb");
        while(decode_read(&temp,fp)){
            //fread(&temp,sizeof(struct user),1,fp);
            if(con->subject[0]=='-'||strcmp(temp.subject,con->subject)==0){
                if(con->term==-1||temp.term==con->term){
                    if(con->school[0]=='-'||strcmp(temp.school,con->school)==0){
                        if(con->grade==-1||temp.grade==con->grade){
                            if(con->major[0]=='-'||strcmp(temp.major,con->major)==0){
                                if(con->class_id==-1||temp.class_id==con->class_id){
                                    if(con->task_state==-1||temp.task_state==con->task_state){
                                        now=(struct task_linked*)malloc(sizeof(struct task_linked));
                                        if(head==NULL){
                                            head=now;
                                        }else{
                                            prev->next=now;
                                        }
                                        prev=now;
                                        memcpy(now,&temp,sizeof(struct task));
                                        //fseek(fp,0,SEEK_CUR);
                                        prev->next=NULL;

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        fclose(fp);
    }
    return head;
}

/*******************************************************************************
  * @��������		del_teaching_task
  * @����˵��		ɾ����ѧ�����
  * @�������       char *id(��ɾ�����û��˺�)
  * @���ز���       0(ɾ�����),-1(ɾ��ʧ��)
  *****************************************************************************/
int del_teaching_task(char *id){
    return remove(id);
}

/*******************************************************************************
  * @��������		finish_task
  * @����˵��		�޸Ľ�ѧ�����״̬
  * @�������       struct task *con(��������)
  * @���ز���       0(�޸����),-1(�޸�ʧ��,�Ҳ����ý�ѧ����)
  *****************************************************************************/
int finish_task(struct task *con){
    FILE *fp=fopen(con->id,"rb+");
    struct task temp;
    while(decode_read(&temp,fp)){
        //fread(&temp,sizeof(struct user),1,fp);
        if(strcmp(temp.subject,con->subject)==0){
            if(temp.term==con->term){
                if(strcmp(temp.school,con->school)==0){
                    if(temp.grade==con->grade){
                        if(strcmp(temp.major,con->major)==0){
                            if(temp.class_id==con->class_id){
                                if(temp.task_state==con->task_state){
                                    temp.task_state=1;
                                    fseek(fp,-1*(int)sizeof(struct task),SEEK_CUR);
                                    encode_write(&temp,fp);
                                    fclose(fp);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}
/*******************************************************************************
  * @��������		rc4_init
  * @����˵��		rc4�����㷨��ʼ��
  * @�������       unsigned char *s(s-box), unsigned char *key(��Կ), unsigned long Len(��Կ����)
  * @���ز���       ��
  *****************************************************************************/
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len){
    int i =0, j = 0;
    char k[256] = {0};
    unsigned char tmp = 0;
    for (i=0;i<256;i++) {
        s[i] = i;
        k[i] = key[i%Len];
    }
    for (i=0; i<256; i++) {
        j=(j+s[i]+k[i])%256;
        tmp = s[i];
        s[i] = s[j]; //����s[i]��s[j]
        s[j] = tmp;
    }
}

/*******************************************************************************
  * @��������		rc4_crypt
  * @����˵��		rc4�����㷨���ܺ���
  * @�������       unsigned char *s(s-box), unsigned char *Data(�����ܵ�����), unsigned long Len(���ݳ���)
  * @���ز���       ��
  *****************************************************************************/
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len){
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for(k=0;k<Len;k++){
        i=(i+1)%256;
        j=(j+s[i])%256;
        tmp = s[i];
        s[i] = s[j]; //����s[x]��s[y]
        s[j] = tmp;
        t=(s[i]+s[j])%256;
        Data[k] ^= s[t];
    }
}

/*******************************************************************************
  * @��������		encode_write
  * @����˵��		rc4��������,��д�����
  * @�������       struct task *user_task(д�������),FILE *fp(�ļ�ָ��)
  * @���ز���       0(����д�����)
  *****************************************************************************/
static int encode_write(struct task *user_task,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct task));
    memcpy(pData,user_task,sizeof(struct task));
    unsigned long len = sizeof(struct task);

    rc4_init(s,(unsigned char *)key,strlen(key)); //�Ѿ�����˳�ʼ��
    rc4_crypt(s,(unsigned char *)pData,len);//����
    fwrite(pData,sizeof(struct task),1,fp);
    free(pData);
    return 0;
}

/*******************************************************************************
  * @��������		decode_read
  * @����˵��		�ӱ��ж�������,��ʹ��rc4�����ݽ���
  * @�������       struct task *user_task(���ն������ݵı���),FILE *fp(�ļ�ָ��)
  * @���ز���       0(�����������)
  *****************************************************************************/
static int decode_read(struct task *user_task,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct task));
    unsigned long len = sizeof(struct task);

    if(fread(pData,sizeof(struct task),1,fp)){
        rc4_init(s,(unsigned char *)key,strlen(key)); //�Ѿ�����˳�ʼ��
        rc4_crypt(s,(unsigned char *)pData,len);//����
        memcpy(user_task,pData,sizeof(struct task));
        free(pData);
        return 1;
    }
    return 0;
}
