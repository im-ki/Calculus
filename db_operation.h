/**
  ******************************************************************************
    * @File:		db_operation.h
	* @Author:	    �����
	* @Date:		2017-05-19
	* @Brief:		�û���Ϣ���ݿ����ͷ�ļ�
  ******************************************************************************
  */

#ifndef __DB_OPERATION_H
#define __DB_OPERATION_H

/* Includes ------------------------------------------------------------------*/
#include<stdio.h>

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/
struct user{
	char id[20];    //�˺�
	char name[20];  //����
	int type; //0(����Ա),1(ѧ��),2(��ʦ),3(����Ա)
	char school[25];    //ѧԺ
	int grade;  //�꼶
	char major[25]; //רҵ
	int class_id;   //���
	char password[17];  //����
};

struct user_linked{
	char id[20];
	char name[20];
	int type; //0 is administrator,1 is student,2 is teacher,3 is counselor
	char school[25];
	int grade;
	char major[25];
	int class_id;
	struct user_linked *next;
};

/* �������� -------------------------------------------------------------------*/
int add_to_db(struct user *);
int del_from_db(char *);
int in_db(char *);
int search_for_type(char *);
struct user_linked *search_all_for_id(struct user *);
char *get_password(char *);
char *get_user_name(char *id);
char *get_user_school(char *id);
int get_user_grade(char *id);
int mod_password(char *,char *);
int mod_id(char *id,char *new_id);
int mod_name(char *id,char *new_name);
int mod_school(char *id,char *new_school);
int mod_major(char *id,char *new_major);
int mod_type(char *id,int new_type);
int mod_grade(char *id,int new_grade);
int mod_class_id(char *id,int new_class_id);

#endif
/**********************************END OF FILE***********************************/

