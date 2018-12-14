/**
  ******************************************************************************
    * @File:		interface.c
    * @Author:	    ������
	* @Date:		2017-05-19
	* @Brief:		�û�����Դ�ļ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include"interface.h"
#include"student.h"
#include"teacher.h"
#include"administrator.h"
#include<stdio.h>
#include<windows.h>
#include"counsellor.h"

/* �궨�� --------------------------------------------------------------------*/

/* ���������Ͷ��� -------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/* �������� -------------------------------------------------------------------*/

/*******************************************************************************
  * @��������		administrator_interface
  * @����˵��		����Ա�û����ܲ˵�
  * @�������       char *identity(��ǰ�˺�)
  * @���ز���       0(�˳�)
  *****************************************************************************/
int administrator_interface(char *identity){
    int input;
    while(1){
        system("cls");
        printf("*��ӭ��������Ա��\n");
        printf("����������������\n");
        printf("*�밴�ղ˵����ϵ�����ѡ������Ҫ�Ĺ��ܣ�\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��     \t\t\t*   �˵���   * \t\t\t            ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("  �������������������������������������Щ������������������������������������� \n");
        printf("           * 1 �ֶ�����û� *                   *11 �޸��û�ѧԺ *        \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("           * 2 ��������ѧ�� *                   *12 �޸��û�רҵ *        \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("           * 3 ����������ʦ *                   *13 �޸��û��꼶 *        \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("          * 4 �������븨��Ա *                  *14 �޸��û���� *        \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("             * 5 ɾ���û� *                     *15 �޸��û�����*         \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("           * 7 �鿴�����û� *                   *16 �޸��û����� *        \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("           * 8 �ֶ���ӿα� *                   *17 �޸��û��˺� *        \n");
        printf("  �ǩ�                              ���賓                                ���� \n");
        printf("           * 9 ������ӿα� *                        * 18 �˳� *          \n");
        printf("  �������������������������������������ߩ�������������������������������������\n");
        printf(" * ��������Ӧ����: ");
        scanf("%d",&input);
        switch(input){
            case 1:add_user();break;
            case 2:add_student_csv();break;
            case 3:add_teacher_csv();break;
            case 4:add_counselor_csv();break;
            case 5:del_user();break;
            case 6:del_user_from_csv();break;
            case 7:view_all();break;
            case 8:add_courses();break;
            case 9:add_teaching_task_csv();break;
            case 10:mdfpassword();break;
            case 11:mdfschool();break;
            case 12:mdfmajor();break;
            case 13:mdfgrade();break;
            case 14:mdfcls_id();break;
            case 15:mdfname();break;
            case 16:mdftype();break;
            case 17:mdfid();break;
            case 18:return 0;
            default:printf("�������,����������.");system("pause");break;
        }
        system("pause");
    }
}

/*******************************************************************************
  * @��������		student_interface
  * @����˵��		ѧ���û����ܲ˵�
  * @�������       char *identity(��ǰ�˺�)
  * @���ز���       0(�˳�)
  *****************************************************************************/
int student_interface(char *identity){
    int input;
    char *name;
    while(1){
        name=get_user_name(identity);
        system("cls");
        printf("*��ӭ����%sͬѧ��\n",name);
        free(name);
        printf("����������������\n");
        printf("\n");
        printf("*�밴�ղ˵����ϵ�����ѡ������Ҫ�Ĺ��ܣ�\n");
        printf("\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��     \t\t\t*   �˵���   * \t\t\t            ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("  ��                                                                        ��\n");
        printf("  ��         *  1 �޸�����  *                    *  3 ����ɼ���  *         ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��         *  2 �鿴�ɼ�  *                       *  4 �˳�  *            ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ����������������������������������������������������������������������������\n");
        scanf("%d",&input);
        switch(input){
            case 1:modify_my_password(identity);break;
            case 2:view_mark(identity);break;
            case 3:output_mark_csv(identity);break;
            case 4:return 0;
            default:printf("�������,����������.");system("pause");break;
        }
        system("pause");
    }
}

/*******************************************************************************
  * @��������		teacher_interface
  * @����˵��		��ʦ�û����ܲ˵�
  * @�������       char *identity(��ǰ�˺�)
  * @���ز���       0(�˳�)
  *****************************************************************************/
int teacher_interface(char *identity){
    int input;
    char *name;
    while(1){
        name=get_user_name(identity);
        system("cls");
        printf("*��ӭ����%s��ʦ��\n",name);
        free(name);
        printf("����������������\n");
        printf("\n");
        printf("*�밴�ղ˵����ϵ�����ѡ������Ҫ�Ĺ��ܣ�\n");
        printf("\n");
         printf("  ����������������������������������������������������������������������������\n");
        printf("  ��     \t\t\t*   �˵���   * \t\t\t            ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("  ��                                                                        ��\n");
        printf("  ��     *  1 ��������ѧ���ɼ�  *                *  2 �������ڱ�  *         ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��       *  3 �鿴ѧ���ɼ�  *                  *  4 δ�������  *         ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��        *  5 ���������  *                    *  6 �޸�����  *          ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��           *  7 �˳�  *                                                 ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ����������������������������������������������������������������������������\n");
        scanf("%d",&input);
        switch(input){
            case 1:input_mark_csv(identity);break;
            case 2:output_student_csv(identity);break;
            case 3:view_mark_of_student();break;
            case 4:search_for_task_with_state(identity,0);break;
            case 5:search_for_task_with_state(identity,1);break;
            case 6:modify_my_password(identity);break;
            case 7:return 0;
            default:printf("�������,����������.");system("pause");break;
        }
        system("pause");
    }
}

/*******************************************************************************
  * @��������		counselor_interface
  * @����˵��		����Ա�û����ܲ˵�
  * @�������       char *identity(��ǰ�˺�)
  * @���ز���       0(�˳�)
  *****************************************************************************/
int counselor_interface(char *identity){
    int input;
    char *name;
    while(1){
        name=get_user_name(identity);
        system("cls");
        printf("���ã�%s����Ա\n",name);
        printf("����������������\n");
        printf("\n");
        free(name);
        printf("* �밴�ղ˵����ϵ�����ѡ������Ҫ�Ĺ��ܣ�\n");
        printf("\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("  ��     \t\t\t*   �˵���   * \t\t\t            ��\n");
        printf("  �ǩ������������������������������������������������������������������������� \n");
        printf("  ��                                                                        ��\n");
        printf("  ��       *  1 �鿴ѧ���ɼ�  *                *  4 �����༶�ɼ���  *       ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��       *  2 �鿴�༶�ɼ�  *                   *  5 �޸�����  *          ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ��       *  3 �鿴�ҿ�����  *                     *  6 �˳�  *            ��\n");
        printf("  ��                                                                        ��\n");
        printf("  ����������������������������������������������������������������������������\n");
        printf("\n");
        printf("* ���������Ҫ�Ĺ��ܣ�������Ӧ�����֣�\n");
        scanf("%d",&input);
        switch(input){
            case 1:display_studentgrade();break;
            case 2:display_classtranscript(identity);break;
            case 3:display_underachiever(identity);break;
            case 4:file_output(identity);break;
            case 5:modify_my_password(identity);break;
            case 6:return 0;
            default:printf("�������,����������.");system("pause");break;
        }
        system("pause");
    }
}
