/**
  ******************************************************************************
    * @File:		mark.c
    * @Author:	    �����
	* @Date:		2017-05-19
	* @Brief:		ѧ���ɼ������Դ�ļ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"mark.h"
#include"db_operation.h"
#include<stdlib.h>
#include<string.h>
#include<io.h>

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/
static int encode_write(struct mark *user_mark,FILE *fp);
static int decode_read(struct mark *user_mark,FILE *fp);
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len);
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len);

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		add_mark
  * @����˵��		�����µĳɼ���Ϣ
  * @�������       struct mark *new_mark
  * @���ز���       0(����ɹ�),-1(����ʧ��)
  *****************************************************************************/
int add_mark(struct mark *new_mark){
	int type=search_for_type(new_mark->id);
	if(type==1){
		FILE *fp=fopen(new_mark->id,"ab");
		//fwrite(new_mark,sizeof(struct mark),1,fp);
		encode_write(new_mark,fp);
		fclose(fp);
		return 0;
	}
	return -1;
}

/*******************************************************************************
  * @��������		get_mark
  * @����˵��		��ȡѧ���ĳɼ���Ϣ,���øú����ĺ���Ҫע���ͷ��ڴ�
  * @�������       char *id(ѧ��),char *subject(��Ŀ����,��������)
  * @���ز���       temp(ѧ���ɼ��ṹ��),NULL(û�������Ŀ)
  *****************************************************************************/
struct mark_linked *get_mark(char *id,struct mark *con){
    struct mark temp;
    struct mark_linked *head=NULL,*now,*prev;
    FILE *fp;
    if(access(id,0)==0){
        fp=fopen(id,"rb");
        //fread(temp,sizeof(struct mark),1,fp);
        while(decode_read(&temp,fp)){
            if(con->subject[0]=='-'||strcmp(temp.subject,con->subject)==0){
                if(con->term==-1||temp.term==con->term){
                    now=(struct mark_linked *)malloc(sizeof(struct mark_linked));
                    if(head==NULL){
                        head=now;
                    }else{
                        prev->next=now;
                    }
                    prev=now;
                    memcpy(now,&temp,sizeof(struct mark));
                    //fseek(fp,0,SEEK_CUR);
                    prev->next=NULL;
                }
            }
        }
        fclose(fp);
    }
    return head;
}

/*******************************************************************************
  * @��������		del_mark
  * @����˵��		ɾ��ĳ��ѧ���������ɼ���
  * @�������       char *id(ѧ��)
  * @���ز���       0(ɾ���ɹ�)
  *****************************************************************************/
int del_mark(char *id){
	return remove(id);
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
  * @�������       struct mark *user_mark(д�������),FILE *fp(�ļ�ָ��)
  * @���ز���       0(����д�����)
  *****************************************************************************/
static int encode_write(struct mark *user_mark,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct mark));
    memcpy(pData,user_mark,sizeof(struct mark));
    unsigned long len = sizeof(struct mark);

    rc4_init(s,(unsigned char *)key,strlen(key)); //�Ѿ�����˳�ʼ��
    rc4_crypt(s,(unsigned char *)pData,len);//����
    fwrite(pData,sizeof(struct mark),1,fp);
    free(pData);
    return 0;
}

/*******************************************************************************
  * @��������		decode_read
  * @����˵��		�ӱ��ж�������,��ʹ��rc4�����ݽ���
  * @�������       struct mark *user_mark(���ն������ݵı���),FILE *fp(�ļ�ָ��)
  * @���ز���       0(�����������)
  *****************************************************************************/
static int decode_read(struct mark *user_mark,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct mark));
    unsigned long len = sizeof(struct mark);

    if(fread(pData,sizeof(struct mark),1,fp)){
        rc4_init(s,(unsigned char *)key,strlen(key)); //�Ѿ�����˳�ʼ��
        rc4_crypt(s,(unsigned char *)pData,len);//����
        memcpy(user_mark,pData,sizeof(struct mark));
        free(pData);
        return 1;   //ʹ�ú�����Ч����freadһ��
    }
    return 0;
}
