/*
	*****************************************
		*@File:		cousellor.h
		*@Author:	������
		*Date:		2017-05-23
		*@brief:	����Աģ�鹦��ʵ��ͷ�ļ�
	*****************************************
	*/

#ifndef __COUNSELLOR_H
#define __COUNSELLOR_H

/*	Includes ------------------------------------------------------------
---*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"mark.h"
#include"db_operation.h"

/*	�궨��   ------------------------------------------------------------
----*/

/*	���������Ͷ���	-----------------------------------------------------
----*/

/*	��������	---------------------------------------------------------
----*/
void display_studentgrade();
void display_classtranscript(char *identity);
void display_underachiever(char *identity);
void file_output(char *identity);

#endif // __COUNSELLOR_H

/**********************************END OF FILE***********************************/
