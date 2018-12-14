/*
	*****************************************
		*@File:		cousellor.h
		*@Author:	陈天翼
		*Date:		2017-05-23
		*@brief:	辅导员模块功能实现头文件
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

/*	宏定义   ------------------------------------------------------------
----*/

/*	变量及类型定义	-----------------------------------------------------
----*/

/*	函数声明	---------------------------------------------------------
----*/
void display_studentgrade();
void display_classtranscript(char *identity);
void display_underachiever(char *identity);
void file_output(char *identity);

#endif // __COUNSELLOR_H

/**********************************END OF FILE***********************************/
