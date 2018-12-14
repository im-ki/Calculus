/**
  ******************************************************************************
    * @File:		db_operation.c
    * @Author:	    �����
	* @Date:		2017-05-19
	* @Brief:		�û���Ϣ���ݿ����Դ�ļ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include"db_operation.h"
#include<string.h>
#include<io.h>
#include<stdlib.h>

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/
static int encode_write(struct user *,FILE *);
static int decode_read(struct user *,FILE *);
static void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len);
static void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len);

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		add_to_db
  * @����˵��		���µ��û���Ϣ�������ݿ�
  * @�������       struct user *user_info
  * @���ز���       0(����ɹ�),-1(�û��Ѵ���)
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
  * @��������		del_from_db
  * @����˵��		�����ݿ���ɾ��ĳ���û�������
  * @�������       char *id(����/ѧ��)
  * @���ز���       0(ɾ���ɹ�),-1(ɾ��ʧ��)
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
  * @��������		in_db
  * @����˵��		��ѯĳ�û��Ƿ������ݿ���
  * @�������       char *id(����/ѧ��)
  * @���ز���       0(���û�����),-1(���û�������)
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
  * @��������		search_for_type
  * @����˵��		��ѯĳ�û�������
  * @�������       char *id(����/ѧ��)
  * @���ز���       0(����Ա),1(ѧ��),2(��ʦ),3(����Ա),-1(�Ҳ������û�)
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
  * @��������		search_all_for_id
  * @����˵��		�����з���������ѧ������Ϣ���������ʽ����,���øú����ĺ���Ҫע���ͷ��ڴ�
  * @�������       struct user *con(��ѯ����)
  * @���ز���       NULL(û�з����������û�),head(����ı�ͷ)
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
  * @��������		get_user_name
  * @����˵��		ͨ���˺Ż�ȡ����,���øú����ĺ���Ҫע���ͷ��ڴ�
  * @�������       char *id(����/ѧ��)
  * @���ز���       name(ָ�������ַ�����ָ��),NULL(�Ҳ������û�)
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
  * @��������		get_user_school
  * @����˵��		ͨ���˺Ż�ȡ����ѧԺ,���øú����ĺ���Ҫע���ͷ��ڴ�
  * @�������       char *id(����/ѧ��)
  * @���ز���       school(ָ�������ַ�����ָ��),NULL(�Ҳ������û�)
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
  * @��������		get_user_grade
  * @����˵��		ͨ���˺Ż�ȡ�����꼶,���øú����ĺ���Ҫע���ͷ��ڴ�
  * @�������       char *id(����/ѧ��)
  * @���ز���       grade(�꼶),-1(�Ҳ������û�)
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
  * @��������		mod_password
  * @����˵��		�޸�����
  * @�������       char *id(���޸ĵ��˺�),char *new_password
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		get_password
  * @����˵��		��ȡĳ�û�������,���øú����ĺ���Ҫע���ͷ��ڴ�
  * @�������       char *id(�˺�)
  * @���ز���       NULL(û�и��û�),password(ָ�������ַ�����ָ��)
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
  * @��������		mod_id
  * @����˵��		�޸��˺�
  * @�������       char *id(���޸ĵ��˺�),char *new_id
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		mod_name
  * @����˵��		�޸�����
  * @�������       char *id(���޸ĵ��˺�),char *new_name
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		mod_school
  * @����˵��		�޸�����ѧԺ
  * @�������       char *id(���޸ĵ��˺�),char *new_school
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		mod_major
  * @����˵��		�޸�רҵ
  * @�������       char *id(���޸ĵ��˺�),char *new_major
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		mod_type
  * @����˵��		�޸��û�����
  * @�������       char *id(���޸ĵ��˺�),char *new_type
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		mod_grade
  * @����˵��		�޸��꼶
  * @�������       char *id(���޸ĵ��˺�),char *new_grade
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @��������		mod_class_id
  * @����˵��		�޸İ��
  * @�������       char *id(���޸ĵ��˺�),char *new_class_id
  * @���ز���       0(�޸ĳɹ�),-1(�޸�ʧ��)
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
  * @����˵��		rc4��������,��д�����ݿ���
  * @�������       struct user *user_info(д�������),FILE *fp(�ļ�ָ��)
  * @���ز���       0(����д�����)
  *****************************************************************************/
static int encode_write(struct user *user_info,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct user));
    memcpy(pData,user_info,sizeof(struct user));
    unsigned long len = sizeof(struct user);

    rc4_init(s,(unsigned char *)key,strlen(key)); //�Ѿ�����˳�ʼ��
    rc4_crypt(s,(unsigned char *)pData,len);//����
    fwrite(pData,sizeof(struct user),1,fp);
    free(pData);
    return 0;
}

/*******************************************************************************
  * @��������		decode_read
  * @����˵��		�����ݿ��ж�������,��ʹ��rc4�����ݽ���
  * @�������       struct user *user_info(���ն������ݵı���),FILE *fp(�ļ�ָ��)
  * @���ز���       0(�����������)
  *****************************************************************************/
static int decode_read(struct user *user_info,FILE *fp){
    unsigned char s[256] = {0}; //S-box
    const char key[] = {"hjmchwcqgctycxl"};
    unsigned char *pData=(unsigned char *)malloc(sizeof(struct user));
    unsigned long len = sizeof(struct user);

    if(fread(pData,sizeof(struct user),1,fp)){
        rc4_init(s,(unsigned char *)key,strlen(key)); //�Ѿ�����˳�ʼ��
        rc4_crypt(s,(unsigned char *)pData,len);//����
        memcpy(user_info,pData,sizeof(struct user));
        free(pData);
        return 1;   //ʹ�ú�����Ч����freadһ��
    }
    return 0;
}
