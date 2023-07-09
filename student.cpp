#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include <string.h>
#include <tchar.h>
#pragma warning (disable : 4996)

void* MY_STUDENT_Init(char* llastname, int yyear, MAJOR sstudent_major)
{
	MY_STUDENT* pdata = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (pdata)
	{
		pdata->lastname = (char*)malloc(strlen(llastname) + 1);
		if (!pdata->lastname)
		{
			printf("Memory allocation error.\n");
			exit(1);
		}
		strcpy(pdata->lastname, llastname);
		pdata->year = yyear;
		pdata->student_major = sstudent_major;
	}
	return (void*)(pdata);
}

void MY_STUDENT_Free(void* ptr)
{
	MY_STUDENT* pData = (MY_STUDENT*)ptr;
	if (pData)
		free(pData->lastname);
		free(pData);
		pData = NULL;
}

void* MY_STUDENT_Push(char* lastname, int year, MAJOR student_major)
{
	return MY_STUDENT_Init(lastname, year, student_major);
}

void MY_STUDENT_Print(void* ptr)
{
	MY_STUDENT* student = (MY_STUDENT*)ptr;
	if (student)
	{
		printf("\nLastname		: %s\n", student->lastname);
		printf("Year			: %d\n", student->year);
		printf("Major			: %s\n", majorlist[student->student_major]);
	}
}

int MY_STUDENT_SearchData(void* pCurData, void* pSearchData, int dataType)
{
	MY_STUDENT* pcur = (MY_STUDENT*)pCurData;
	MY_STUDENT* psearch = (MY_STUDENT*)pSearchData;

	switch (dataType)
	{
		case 0:
			if (strcmp(pcur->lastname, psearch->lastname) == 0)
				return 1;
			break;
		case 1:
			if (pcur->student_major == psearch->student_major)
				return 1;
			break;
		case 2:
			if (pcur->year == psearch->year)
				return 1;
			break;
	};
	return 0;
}

void MY_STUDENT_SaveData(void* ptr, FILE* fp)
{
	if (!fp)
	{
		printf("File error.");
		exit(1);
	}
	MY_STUDENT* pDat = (MY_STUDENT*)ptr;
	int namelen = strlen(pDat->lastname);
	if (fwrite((void*)&namelen, sizeof(int), 1, fp) &&
		fwrite((void*)pDat->lastname, namelen + 1, 1, fp) &&
		fwrite((void*)&(pDat->year), sizeof(int), 1, fp) &&
		fwrite((void*)&(pDat->student_major), sizeof(int), 1, fp));
	else
	{
		printf("File write error.");
		fclose(fp);
		exit(1);
	}
}

void* MY_STUDENT_ReadData(FILE* fp)
{
	MY_STUDENT temp;
	memset(&temp, -1, sizeof(MY_STUDENT));
	int namelen = 0;
	if (fread(&namelen, sizeof(int), 1, fp)) {
		temp.lastname = (char*)malloc(namelen + 1);
		if (!temp.lastname)
		{
			printf("Memory allocation error.");
			exit(1);
		}
		memset(temp.lastname, 0, namelen);
		if (fread(temp.lastname, namelen + 1, 1, fp) &&
			fread(&temp.year, sizeof(int), 1, fp) &&
			fread(&temp.student_major, sizeof(int), 1, fp))
		{
			void *ptr = MY_STUDENT_Push(temp.lastname, temp.year, temp.student_major);
			if (temp.lastname) free(temp.lastname);
			return ptr;
		}
		if (temp.lastname) free(temp.lastname);
	}
	return 0;
}