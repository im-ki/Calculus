/**
  ******************************************************************************
    * @File:		teaching_task.c
    * @Author:	    陈祈光
	* @Date:		2017-05-19
	* @Brief:		教师教学任务表管理源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"teaching_task.h"
#include"db_operation.h"
#include<stdlib.h>
#include<string.h>
#include<io.h>

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/
static int encode_write(struct task *user_task,FILE *fp);
static int decode_read(struct task *user_task,FILE *fp);
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len);
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len);

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		add_teaching_task
  * @函数说明		添加新的教学任务
  * @输入参数       struct task *new_task
  * @返回参数       0(添加成功),-1(添加失败)
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
  * @函数名称		in_teaching_task
  * @函数说明		查看要添加的教学任务是否在表中
  * @输入参数       struct task *new_task
  * @返回参数       0(不在),-1(表中有相同的任务),-2(无法打开文件)
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
  * @函数名称		get_teaching_task
  * @函数说明		获取符合条件的教学任务
  * @输入参数       struct task *con
  * @返回参数       head(链表表头),NULL(没有符合条件的教学任务)
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
  * @函数名称		del_teaching_task
  * @函数说明		删除教学任务表
  * @输入参数       char *id(被删除的用户账号)
  * @返回参数       0(删除完成),-1(删除失败)
  *****************************************************************************/
int del_teaching_task(char *id){
    return remove(id);
}

/*******************************************************************************
  * @函数名称		finish_task
  * @函数说明		修改教学任务的状态
  * @输入参数       struct task *con(搜索条件)
  * @返回参数       0(修改完成),-1(修改失败,找不到该教学任务)
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
  * @函数名称		rc4_init
  * @函数说明		rc4加密算法初始化
  * @输入参数       unsigned char *s(s-box), unsigned char *key(密钥), unsigned long Len(密钥长度)
  * @返回参数       无
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
        s[i] = s[j]; //交换s[i]和s[j]
        s[j] = tmp;
    }
}

/*******************************************************************************
  * @函数名称		rc4_crypt
  * @函数说明		rc4加密算法加密函数
  * @输入参数       unsigned char *s(s-box), unsigned char *Data(被加密的数据), unsigned long Len(数据长度)
  * @返回参数       无
  *****************************************************************************/
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len){
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for(k=0;k<Len;k++){
        i=(i+1)%256;
        j=(j+s[i])%256;
        tmp = s[i];
        s[i] = s[j]; //交换s[x]和s[y]
        s[j] = tmp;
        t=(s[i]+s[j])%256;
        Data[k] ^= s[t];
    }
}

/*******************************************************************************
  * @函数名称		encode_write
  * @函数说明		rc4加密数据,并写入表中
  * @输入参数       struct task *user_task(写入的内容),FILE *fp(文件指针)
  * @返回参数       0(加密写入完成)
  *****************************************************************************/
static int encode_write(struct task *user_task,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct task));
    memcpy(pData,user_task,sizeof(struct task));
    unsigned long len = sizeof(struct task);

    rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
    rc4_crypt(s,(unsigned char *)pData,len);//加密
    fwrite(pData,sizeof(struct task),1,fp);
    free(pData);
    return 0;
}

/*******************************************************************************
  * @函数名称		decode_read
  * @函数说明		从表中读出数据,并使用rc4对数据解密
  * @输入参数       struct task *user_task(接收读入数据的变量),FILE *fp(文件指针)
  * @返回参数       0(读出解密完成)
  *****************************************************************************/
static int decode_read(struct task *user_task,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct task));
    unsigned long len = sizeof(struct task);

    if(fread(pData,sizeof(struct task),1,fp)){
        rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
        rc4_crypt(s,(unsigned char *)pData,len);//加密
        memcpy(user_task,pData,sizeof(struct task));
        free(pData);
        return 1;
    }
    return 0;
}
