/**
  ******************************************************************************
    * @File:		interface.h
	* @Author:	    ������
	* @Date:		2017-05-19
	* @Brief:		�û�����ͷ�ļ�
  ******************************************************************************
  */
#ifndef __INTERFACE_H
#define __INTERFACE_H

/* Includes ------------------------------------------------------------------*/

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/
int administrator_interface(char *identity);
int student_interface(char *identity);
int teacher_interface(char *identity);
int counselor_interface(char *identity);

#endif // __INTERFACE_H

/**********************************END OF FILE***********************************/