/**
  ******************************************************************************
    * @File:		administrator.h
	* @Author:	    �Ƽ���
	* @Date:		2017-05-19
	* @Brief:		����Ա�û�ͷ�ļ�
  ******************************************************************************
  */
#ifndef __ADMINISTRATOR_H
#define __ADMINISTRATOR_H

/* Includes ------------------------------------------------------------------*/

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/
int add_user(void);
int add_student_csv(void);
int add_teacher_csv(void);
int add_counselor_csv(void);
int view_all(void);
int del_user_from_csv(void);
int add_teaching_task_csv(void);
int del_user();
int add_courses();
int mdfpassword();
int mdfschool();
int mdfmajor();
int mdfgrade();
int mdfcls_id();
int mdfname();
int mdftype();
int mdfid();
#endif // __ADMINISTRATOR_H

/**********************************END OF FILE***********************************/
