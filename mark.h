/**
  ******************************************************************************
    * @File:		mark.h
	* @Author:	    陈祈光
	* @Date:		2017-05-19
	* @Brief:		学生成绩表管理头文件
  ******************************************************************************
  */

#ifndef __MARK_H
#define __MARK_H

/* Includes ------------------------------------------------------------------*/

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/
struct mark{
	char id[20];    //账号
	int term;   //学期
	char subject[20];   //学科
	int mark;   //成绩
	int credit; //学分
	char teacher_id[20];    //教师的账号
};

struct mark_linked{
	char id[20];
	int term;
	char subject[20];
	int mark;
	int credit;
	char teacher_id[20];
	struct mark_linked *next;
};

/* 函数声明 -------------------------------------------------------------------*/
int add_mark(struct mark *);
int del_mark(char *);
struct mark_linked *get_mark(char *id,struct mark *);


#endif
/**********************************END OF FILE***********************************/

