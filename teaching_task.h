/**
  ******************************************************************************
    * @File:		teaching_task.h
	* @Author:	    �����
	* @Date:		2017-05-19
	* @Brief:		��ʦ��ѧ��������ͷ�ļ�
  ******************************************************************************
  */

#ifndef __TEACHING_TASK_H
#define __TEACHING_TASK_H

/* Includes ------------------------------------------------------------------*/

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/
struct task{
    char id[20];    //�˺�
	char school[20];    //ѧԺ
	int grade;  //�꼶
	char major[25]; //רҵ
	int class_id;   //���
	int term;   //ѧ��
	char subject[20];   //ѧ��
	int task_state; //�ý�ѧ�����״̬
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
/* �������� -------------------------------------------------------------------*/
int add_teaching_task(struct task *);
struct task_linked *get_teaching_task(struct task *con);
int del_teaching_task(char *id);
int finish_task(struct task *con);
int in_teaching_task(struct task *new_task);
#endif
/**********************************END OF FILE***********************************/
