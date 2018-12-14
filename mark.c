/**
  ******************************************************************************
    * @File:		mark.c
    * @Author:	    陈祈光
	* @Date:		2017-05-19
	* @Brief:		学生成绩表管理源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"mark.h"
#include"db_operation.h"
#include<stdlib.h>
#include<string.h>
#include<io.h>

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/
static int encode_write(struct mark *user_mark,FILE *fp);
static int decode_read(struct mark *user_mark,FILE *fp);
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len);
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len);

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		add_mark
  * @函数说明		加入新的成绩信息
  * @输入参数       struct mark *new_mark
  * @返回参数       0(加入成功),-1(加入失败)
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
  * @函数名称		get_mark
  * @函数说明		获取学生的成绩信息,调用该函数的函数要注意释放内存
  * @输入参数       char *id(学号),char *subject(科目名称,搜索条件)
  * @返回参数       temp(学生成绩结构体),NULL(没有这个科目)
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
  * @函数名称		del_mark
  * @函数说明		删除某个学生的整个成绩表
  * @输入参数       char *id(学号)
  * @返回参数       0(删除成功)
  *****************************************************************************/
int del_mark(char *id){
	return remove(id);
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
  * @输入参数       struct mark *user_mark(写入的内容),FILE *fp(文件指针)
  * @返回参数       0(加密写入完成)
  *****************************************************************************/
static int encode_write(struct mark *user_mark,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct mark));
    memcpy(pData,user_mark,sizeof(struct mark));
    unsigned long len = sizeof(struct mark);

    rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
    rc4_crypt(s,(unsigned char *)pData,len);//加密
    fwrite(pData,sizeof(struct mark),1,fp);
    free(pData);
    return 0;
}

/*******************************************************************************
  * @函数名称		decode_read
  * @函数说明		从表中读出数据,并使用rc4对数据解密
  * @输入参数       struct mark *user_mark(接收读入数据的变量),FILE *fp(文件指针)
  * @返回参数       0(读出解密完成)
  *****************************************************************************/
static int decode_read(struct mark *user_mark,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct mark));
    unsigned long len = sizeof(struct mark);

    if(fread(pData,sizeof(struct mark),1,fp)){
        rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
        rc4_crypt(s,(unsigned char *)pData,len);//加密
        memcpy(user_mark,pData,sizeof(struct mark));
        free(pData);
        return 1;   //使得函数的效果与fread一致
    }
    return 0;
}
