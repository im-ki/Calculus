/**
  ******************************************************************************
    * @File:		teaching_task.h
	* @Author:	    陈祈光
	* @Date:		2017-05-19
	* @Brief:		教师教学任务表管理头文件
  ******************************************************************************
  */

#ifndef __TEACHING_TASK_H
#define __TEACHING_TASK_H

/* Includes ------------------------------------------------------------------*/

/* 宏定义 --------------------------------------------------------------------*/

/* 变量及类型定义 -------------------------------------------------------------*/
struct task{
    char id[20];    //账号
	char school[20];    //学院
	int grade;  //年级
	char major[25]; //专业
	int class_id;   //班别
	int term;   //学期
	char subject[20];   //学科
	int task_state; //该教学任务的状态
};

struct task_linked{
    char id[20];
	char school[20];
	int grade;
	char major[25];
	int class_id;
	int term;
	char subject[20];
	int task_state;
	struct task_linked *next;
};
/* 函数声明 -------------------------------------------------------------------*/
int add_teaching_task(struct task *);
struct task_linked *get_teaching_task(struct task *con);
int del_teaching_task(char *id);
int finish_task(struct task *con);
int in_teaching_task(struct task *new_task);
#endif
/**********************************END OF FILE***********************************/
