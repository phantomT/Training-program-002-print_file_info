#pragma warning(disable:4996) //VS ����������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>

struct _finddata_t;

char* get_name(void)											//�����������ַ
{
	char *name, *temp;
	int j = 1;

	name = (char*)malloc(sizeof(char)*(j + 1));
	if (NULL == name)
	{
		exit(1);
	}

	while ((name[j - 1] = getchar()) != '\n')
	{
		j++;
		temp = (char*)malloc(j + 1);
		if (NULL == temp)
		{
			exit(1);
		}
		name[j - 1] = '\0';
		strcpy(temp, name);
		free(name);

		name = (char*)malloc(sizeof(char)*(j + 1));
		if (NULL == name)
		{
			exit(1);
		}
		strcpy(name, temp);
		free(temp);
	}

	name[j - 1] = '\0';

	return(name);
}

void Output_info(void)
{	
	char * file_loc, *file_type, *file_add;										
	int loc_len, type_len;
	printf("$$$$$ �����ļ��е�ַ(./****/) $$$$$\n");								//�ļ���ַ
	file_loc = get_name();
	loc_len = strlen(file_loc);

	printf("$$$$$ ����Ҫ���ҵ��ļ�����(*.xxxx) $$$$$\n");							//�ļ�����
	file_type = get_name();
	type_len = strlen(file_type);

	file_add = (char*)malloc(loc_len+type_len+1);
	if (NULL == file_add)
	{
		exit(1);
	}

	strcpy(file_add, file_loc);
	strcat(file_add, file_type);
	printf("file_add test output: %s\n", file_add);

	/*################### ��������ļ�"Output_file.txt" ###################*/

	FILE *fp;
	
	printf("##### Building Output_file.txt #####\n");					//״̬��ʶ  

	if ((fp = fopen("Output_file.txt", "wb")) == NULL)				// ������ļ���ʹfpָ����ļ�  
	{
		printf("##### Building failure ! #####\n");						// �����ʱ���������"�򲻿�"����Ϣ    
		exit(0);														// ��ֹ����  
	}

	//char headline[] = {"�ļ���\t\t\t\t�ļ���С\t\t��������\t\t�޸�����\t\t��������\n"};
	//fprintf(fp, "%s\r\r\n", headline);
	//fprintf(fp, "\n");

	/*################### ���ļ������ļ���Ϣ���뵽�ļ�Output_file�� ###################*/
	struct _finddata_t fileinfo;							//�ļ��洢��Ϣ�ṹ�� 
	long fHandle;											//�����ļ���� 
	int i = 0;												//�ļ�����¼��		
	time_t Time_create, Time_write, Time_access;			//ʱ���ʽ

	if ((fHandle = _findfirst(file_add, &fileinfo)) == -1L)
	{
		printf("��ǰĿ¼��û�и����͵��ļ�\n");
		exit(0);
	}
	else 
	{
		Time_create = time(&fileinfo.time_create);
		Time_write = time(&fileinfo.time_write);
		Time_access = time(&fileinfo.time_access);

		fprintf(fp, "�ҵ��ļ�:%-s\r\r\n �ļ���С��%-6d KB, �������ڣ�%s, �޸����ڣ�%s, �������ڣ�%s.\r\r\n", fileinfo.name, (fileinfo.size)/1000, ctime(&fileinfo.time_create), ctime(&fileinfo.time_write), ctime(&fileinfo.time_access));
		
		while (_findnext(fHandle, &fileinfo) == 0)
		{
			Time_create = time(&fileinfo.time_create);
			Time_write = time(&fileinfo.time_write);
			Time_access = time(&fileinfo.time_access);

			i++;
			fprintf(fp, "\r\r\n�ҵ��ļ�:%-s\r\r\n �ļ���С��%-6d KB, �������ڣ�%s, �޸����ڣ�%s, �������ڣ�%s.\r\r\n", fileinfo.name, (fileinfo.size)/1000, ctime(&fileinfo.time_create), ctime(&fileinfo.time_write), ctime(&fileinfo.time_access));
			
			//printf("�ҵ��ļ�:%30s,�ļ���С��%10d,�������ڣ�%10d,�޸����ڣ�%10d,�������ڣ�%10d\n", fileinfo.name, fileinfo.size,fileinfo.time_create,fileinfo.time_write,fileinfo.time_access);
		}
	}

	_findclose(fHandle);									//�ر��ļ� 

	printf("�ļ�������%d\n", i);

	/*################### �ر��ļ�Output_file ###################*/

	fclose(fp);
}

int main(void)
{
	printf("##### Program initiating #####\n");

	Output_info();

	system("pause");
}