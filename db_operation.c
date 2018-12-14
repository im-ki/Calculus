/**
  ******************************************************************************
    * @File:		db_operation.c
    * @Author:	    陈祈光
	* @Date:		2017-05-19
	* @Brief:		用户信息数据库管理源文件
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"db_operation.h"
#include<string.h>
#include<io.h>
#include<stdlib.h>

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/

/* 函数声明 -------------------------------------------------------------------*/
static int encode_write(struct user *,FILE *);
static int decode_read(struct user *,FILE *);
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len);
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len);

/* 函数定义 -------------------------------------------------------------------*/

/*******************************************************************************
  * @函数名称		add_to_db
  * @函数说明		将新的用户信息加入数据库
  * @输入参数       struct user *user_info
  * @返回参数       0(加入成功),-1(用户已存在)
  *****************************************************************************/
int add_to_db(struct user *user_info){
    FILE *fp;
	if(access("data.dat",0)==0){
		fp=fopen("data.dat","rb+");
	}else{
		fp=fopen("data.dat","wb+");
	}
	struct user temp;
	int state=0;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(temp.id[0]=='-'){
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(user_info,sizeof(struct user),1,fp);
			encode_write(user_info,fp);
			state=1;
			break;
		}else if(strcmp(temp.id,user_info->id)==0){
		    fclose(fp);
		    return -1;
		}
	}
	if(state==0){
		//fwrite(user_info,sizeof(struct user),1,fp);
		encode_write(user_info,fp);
	}
	fclose(fp);
	return 0;
}

/*******************************************************************************
  * @函数名称		del_from_db
  * @函数说明		从数据库中删除某个用户的数据
  * @输入参数       char *id(工号/学号)
  * @返回参数       0(删除成功),-1(删除失败)
  *****************************************************************************/
int del_from_db(char *id){
	FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	int state=0;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(temp.id,id)==0){
			temp.id[0]='-';
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			state=1;
			break;
		}
	}
	fclose(fp);
	if(state==0){
		return -1;
	}
	return 0;
}

/*******************************************************************************
  * @函数名称		in_db
  * @函数说明		查询某用户是否在数据库内
  * @输入参数       char *id(工号/学号)
  * @返回参数       0(该用户存在),-1(该用户不存在)
  *****************************************************************************/
int in_db(char *id){
	FILE *fp=fopen("data.dat","rb");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(temp.id,id)==0){
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		search_for_type
  * @函数说明		查询某用户的类型
  * @输入参数       char *id(工号/学号)
  * @返回参数       0(管理员),1(学生),2(老师),3(辅导员),-1(找不到该用户)
  *****************************************************************************/
int search_for_type(char *id){
	FILE *fp=fopen("data.dat","rb");
	struct user temp;
    while(decode_read(&temp,fp)){
        //fread(&temp,sizeof(struct user),1,fp);
        if(strcmp(temp.id,id)==0){
            fclose(fp);
            return temp.type;
        }
    }
    fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		search_all_for_id
  * @函数说明		将所有符合条件的学生的信息以链表的形式返回,调用该函数的函数要注意释放内存
  * @输入参数       struct user *con(查询条件)
  * @返回参数       NULL(没有符合条件的用户),head(链表的表头)
  *****************************************************************************/
struct user_linked *search_all_for_id(struct user *con){    //Please free the memory after using this function
    FILE *fp=fopen("data.dat","rb");
    struct user temp;
    struct user_linked *head=NULL,*now,*prev;
    while(decode_read(&temp,fp)){
        //fread(&temp,sizeof(struct user),1,fp);
        if(strcmp(temp.id,"0")!=0&&temp.id[0]!='-'){
            if(con->type==-1||temp.type==con->type){
                if(con->school[0]=='-'||strcmp(temp.school,con->school)==0){
                    if(con->grade==-1||temp.grade==con->grade){
                        if(con->major[0]=='-'||strcmp(temp.major,con->major)==0){
                            if(con->class_id==-1||temp.class_id==con->class_id){
                                now=(struct user_linked *)malloc(sizeof(struct user_linked));
                                if(head==NULL){
                                    head=now;
                                }else{
                                    prev->next=now;
                                }
                                prev=now;
                                memcpy(now,&temp,sizeof(struct user)-sizeof(temp.password));
                                //fseek(fp,0,SEEK_CUR);
                                prev->next=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    return head;
}

/*******************************************************************************
  * @函数名称		get_user_name
  * @函数说明		通过账号获取姓名,调用该函数的函数要注意释放内存
  * @输入参数       char *id(工号/学号)
  * @返回参数       name(指向姓名字符串的指针),NULL(找不到该用户)
  *****************************************************************************/
char *get_user_name(char *id){
    char *name=NULL;
    FILE *fp=fopen("data.dat","rb");
    struct user temp;
    while(decode_read(&temp,fp)){
        if(strcmp(temp.id,id)==0){
            name=(char *)malloc(20*sizeof(char));
            strcpy(name,temp.name);
            fclose(fp);
            return name;
        }
    }
    fclose(fp);
    return name;
}

/*******************************************************************************
  * @函数名称		get_user_school
  * @函数说明		通过账号获取所属学院,调用该函数的函数要注意释放内存
  * @输入参数       char *id(工号/学号)
  * @返回参数       school(指向姓名字符串的指针),NULL(找不到该用户)
  *****************************************************************************/
char *get_user_school(char *id){
    char *school=NULL;
    FILE *fp=fopen("data.dat","rb");
    struct user temp;
    while(decode_read(&temp,fp)){
        if(strcmp(temp.id,id)==0){
            school=(char *)malloc(25*sizeof(char));
            strcpy(school,temp.school);
            fclose(fp);
            return school;
        }
    }
    fclose(fp);
    return school;
}

/*******************************************************************************
  * @函数名称		get_user_grade
  * @函数说明		通过账号获取所属年级,调用该函数的函数要注意释放内存
  * @输入参数       char *id(工号/学号)
  * @返回参数       grade(年级),-1(找不到该用户)
  *****************************************************************************/
int get_user_grade(char *id){
    int grade=-1;
    FILE *fp=fopen("data.dat","rb");
    struct user temp;
    while(decode_read(&temp,fp)){
        if(strcmp(temp.id,id)==0){
            grade=temp.grade;
            fclose(fp);
            return grade;
        }
    }
    fclose(fp);
    return grade;
}
/*******************************************************************************
  * @函数名称		mod_password
  * @函数说明		修改密码
  * @输入参数       char *id(被修改的账号),char *new_password
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_password(char *id,char *new_password){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            strcpy(temp.password,new_password);
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		get_password
  * @函数说明		获取某用户的密码,调用该函数的函数要注意释放内存
  * @输入参数       char *id(账号)
  * @返回参数       NULL(没有该用户),password(指向密码字符串的指针)
  *****************************************************************************/
char *get_password(char *id){   //Please free the memory after using this function
    FILE *fp=fopen("data.dat","rb");
    struct user temp;
    char *password;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            password=(char *)malloc(17*sizeof(char));
            strcpy(password,temp.password);
			fclose(fp);
			return password;
		}
	}
	fclose(fp);
	return NULL;
}

/*******************************************************************************
  * @函数名称		mod_id
  * @函数说明		修改账号
  * @输入参数       char *id(被修改的账号),char *new_id
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_id(char *id,char *new_id){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            strcpy(temp.id,new_id);
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		mod_name
  * @函数说明		修改姓名
  * @输入参数       char *id(被修改的账号),char *new_name
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_name(char *id,char *new_name){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            strcpy(temp.name,new_name);
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		mod_school
  * @函数说明		修改所属学院
  * @输入参数       char *id(被修改的账号),char *new_school
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_school(char *id,char *new_school){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            strcpy(temp.school,new_school);
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		mod_major
  * @函数说明		修改专业
  * @输入参数       char *id(被修改的账号),char *new_major
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_major(char *id,char *new_major){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            strcpy(temp.major,new_major);
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		mod_type
  * @函数说明		修改用户类型
  * @输入参数       char *id(被修改的账号),char *new_type
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_type(char *id,int new_type){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            temp.type=new_type;
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		mod_grade
  * @函数说明		修改年级
  * @输入参数       char *id(被修改的账号),char *new_grade
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_grade(char *id,int new_grade){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            temp.grade=new_grade;
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return -1;
}

/*******************************************************************************
  * @函数名称		mod_class_id
  * @函数说明		修改班别
  * @输入参数       char *id(被修改的账号),char *new_class_id
  * @返回参数       0(修改成功),-1(修改失败)
  *****************************************************************************/
int mod_class_id(char *id,int new_class_id){
    FILE *fp=fopen("data.dat","rb+");
	struct user temp;
	while(decode_read(&temp,fp)){
		//fread(&temp,sizeof(struct user),1,fp);
		if(strcmp(id,temp.id)==0){
            temp.class_id=new_class_id;
			fseek(fp,-1*(int)sizeof(struct user),SEEK_CUR);
			//fwrite(&temp,sizeof(struct user),1,fp);
			encode_write(&temp,fp);
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
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
  * @函数说明		rc4加密数据,并写入数据库中
  * @输入参数       struct user *user_info(写入的内容),FILE *fp(文件指针)
  * @返回参数       0(加密写入完成)
  *****************************************************************************/
static int encode_write(struct user *user_info,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct user));
    memcpy(pData,user_info,sizeof(struct user));
    unsigned long len = sizeof(struct user);

    rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
    rc4_crypt(s,(unsigned char *)pData,len);//加密
    fwrite(pData,sizeof(struct user),1,fp);
    free(pData);
    return 0;
}

/*******************************************************************************
  * @函数名称		decode_read
  * @函数说明		从数据库中读出数据,并使用rc4对数据解密
  * @输入参数       struct user *user_info(接收读入数据的变量),FILE *fp(文件指针)
  * @返回参数       0(读出解密完成)
  *****************************************************************************/
static int decode_read(struct user *user_info,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct user));
    unsigned long len = sizeof(struct user);

    if(fread(pData,sizeof(struct user),1,fp)){
        rc4_init(s,(unsigned char *)key,strlen(key)); //已经完成了初始化
        rc4_crypt(s,(unsigned char *)pData,len);//加密
        memcpy(user_info,pData,sizeof(struct user));
        free(pData);
        return 1;   //使得函数的效果与fread一致
    }
    return 0;
}
