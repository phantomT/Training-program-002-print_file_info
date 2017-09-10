#pragma warning(disable:4996) //VS 编译声明？

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <time.h>

struct _finddata_t;

char* get_name(void)											//不定长输入地址
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
	printf("$$$$$ 输入文件夹地址(./****/) $$$$$\n");								//文件地址
	file_loc = get_name();
	loc_len = strlen(file_loc);

	printf("$$$$$ 输入要查找的文件类型(*.xxxx) $$$$$\n");							//文件类型
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

	/*################### 建立输出文件"Output_file.txt" ###################*/

	FILE *fp;
	
	printf("##### Building Output_file.txt #####\n");					//状态标识  

	if ((fp = fopen("Output_file.txt", "wb")) == NULL)				// 打开输出文件并使fp指向此文件  
	{
		printf("##### Building failure ! #####\n");						// 如果打开时出错，就输出"打不开"的信息    
		exit(0);														// 终止程序  
	}

	//char headline[] = {"文件名\t\t\t\t文件大小\t\t创建日期\t\t修改日期\t\t访问日期\n"};
	//fprintf(fp, "%s\r\r\n", headline);
	//fprintf(fp, "\n");

	/*################### 将文件夹内文件信息加入到文件Output_file中 ###################*/
	struct _finddata_t fileinfo;							//文件存储信息结构体 
	long fHandle;											//保存文件句柄 
	int i = 0;												//文件数记录器		
	time_t Time_create, Time_write, Time_access;			//时间格式

	if ((fHandle = _findfirst(file_add, &fileinfo)) == -1L)
	{
		printf("当前目录下没有该类型的文件\n");
		exit(0);
	}
	else 
	{
		Time_create = time(&fileinfo.time_create);
		Time_write = time(&fileinfo.time_write);
		Time_access = time(&fileinfo.time_access);

		fprintf(fp, "找到文件:%-s\r\r\n 文件大小：%-6d KB, 创建日期：%s, 修改日期：%s, 访问日期：%s.\r\r\n", fileinfo.name, (fileinfo.size)/1000, ctime(&fileinfo.time_create), ctime(&fileinfo.time_write), ctime(&fileinfo.time_access));
		
		while (_findnext(fHandle, &fileinfo) == 0)
		{
			Time_create = time(&fileinfo.time_create);
			Time_write = time(&fileinfo.time_write);
			Time_access = time(&fileinfo.time_access);

			i++;
			fprintf(fp, "\r\r\n找到文件:%-s\r\r\n 文件大小：%-6d KB, 创建日期：%s, 修改日期：%s, 访问日期：%s.\r\r\n", fileinfo.name, (fileinfo.size)/1000, ctime(&fileinfo.time_create), ctime(&fileinfo.time_write), ctime(&fileinfo.time_access));
			
			//printf("找到文件:%30s,文件大小：%10d,创建日期：%10d,修改日期：%10d,访问日期：%10d\n", fileinfo.name, fileinfo.size,fileinfo.time_create,fileinfo.time_write,fileinfo.time_access);
		}
	}

	_findclose(fHandle);									//关闭文件 

	printf("文件数量：%d\n", i);

	/*################### 关闭文件Output_file ###################*/

	fclose(fp);
}

int main(void)
{
	printf("##### Program initiating #####\n");

	Output_info();

	system("pause");
}