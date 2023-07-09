#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
#include "stack.h"
#include "interface.h"

#pragma warning (disable : 4996)

static char interftab[][52] =
{
	"0 - Push",
	"1 - Pop",			 
	"2 - Clear",		 
	"3 - Find student", 
	"4 - Save stack to file",
	"5 - Read stack from file (overwrites current stack)",
	"6 - Print whole stack",
	"7 - Save student to file",
	"8 - Read student from file",
	"9 - Push student from file",
	"10 - Quit"         
};

void menu()
{
	size_t it;
	printf("\n");
	for (it = 0; it < INTERF_TOT; ++it)
	{
		printf("%s\n", interftab[it]);
	}
}

void push()
{
	char lastname[512];
	int year, major;
	printf("\nInput lastname, year of birth and choose a major:\n");
	for (size_t i = 0; i < 8; i++)
	{
		printf("%d. %s\n", i, majorlist[i]);
	}
	printf("\nLastname: ");
	scanf("%s", lastname);
	printf("Year of birth: ");
	scanf("%d", &year);
	printf("Major: ");
	scanf("%d", &major);

	if (strlen(lastname) > 511 || year > 2021 || year < 1900 || major < ARCH || major > TRANS)
	{
		printf("Invalid input.\n");
		return;
	}

	void* pdat = MY_STUDENT_Push(lastname, year, (MAJOR)major);
	if (!STACK_Push(pdat))
		printf("Push error.\n");
}

void pop()
{
	STACK tmp = STACK_Pop();
	MY_STUDENT_Print(tmp.pData);
	MY_STUDENT_Free(tmp.pData);
}

void find_student()
{
	char str[512];
	printf("\nInput student data or choose a subject from list:\n");
	for (size_t i = 0; i < 8; i++)
	{
		printf("%d. %s\n", i, majorlist[i]);
	}
	printf("Data: ");
	scanf_s("%s", str, sizeof(str));

	int i = 0, isint = 1;
	while (str[i] != '\0')
	{
		isint = isdigit(str[i]);
		if (!isint) break;
		i++;
	}

	MY_STUDENT searchData;
	int dataType = 0;
	memset(&searchData, -1, sizeof(MY_STUDENT));
	if (isint)
	{
		int inputdat = atoi(str);
		if (inputdat >= ARCH && inputdat <= TRANS)
		{
			searchData.student_major = (MAJOR)inputdat;
			dataType = 1;
		}
		else if(inputdat >= 1900 && inputdat <= 2021)
		{
			searchData.year = inputdat;
			dataType = 2;
		}
	}
	if (!dataType)
	{
		searchData.lastname = (char*)malloc(strlen(str) + 1);
		if (!searchData.lastname)
		{
			printf("Memory allocation error.");
			exit(1);
		}
		memset(searchData.lastname, 0, strlen(str));
		memcpy(searchData.lastname, str, strlen(str) + 1);
	}

	void* pDat = STACK_Search(&searchData, MY_STUDENT_SearchData, 1, dataType);

	if (pDat)
	{
		MY_STUDENT_Print(pDat);
	}

	while (pDat)
	{
		pDat = STACK_Search(&searchData, MY_STUDENT_SearchData, 0, dataType);
		if (pDat)
		{
			MY_STUDENT_Print(pDat);
		}
	}

	if (searchData.lastname && dataType == 0) free(searchData.lastname);
}

void clear()
{
	STACK_Free();
}

void save_stack()
{
	STACK_Save(MY_STUDENT_SaveData);
}

void read_stack()
{
	clear();
	STACK_Read(MY_STUDENT_ReadData);
}

void print_stack()
{
	STACK_Print(MY_STUDENT_Print);
}

void save_student()
{
	int index;
	void* pData;
	printf("Input student index: ");
	scanf("%d", &index);
	if (index < 0)
	{
		printf("Invalid student index.\n");
		return;
	}
	FILE* file = fopen("student", "wb");
	if (file)
	{
		pData = STACK_FindByIndex(index);
		if (pData)
		{
			MY_STUDENT_SaveData(pData, file);
			printf("Student successfuly saved to file.\n");
		}
		else printf("Student not found.\n");
		fclose(file);
	}
	file = NULL;
}

void read_student()
{
	MY_STUDENT temp;
	memset(&temp, -1, sizeof(MY_STUDENT));
	FILE* file = fopen("student", "rb");
	if (!file)
	{
		printf("File error.");
		file = NULL;
		exit(1);
	}
	int namelen = 0;
	if (fread(&namelen, sizeof(int), 1, file)) {
		temp.lastname = (char*)malloc(namelen + 1);
		if (!temp.lastname)
		{
			printf("Memory allocation error.");
			exit(1);
		}
		memset(temp.lastname, 0, namelen);
		if (fread(temp.lastname, namelen + 1, 1, file) &&
			fread(&temp.year, sizeof(int), 1, file) &&
			fread(&temp.student_major, sizeof(int), 1, file))
			{
				MY_STUDENT_Print(&temp);
			}
		free(temp.lastname);
	}
	fclose(file);
	file = NULL;
}

void push_student_from_file()
{
	FILE* file = fopen("student", "rb");
	if (file)
	{
		STACK_Push(MY_STUDENT_ReadData(file));
		fclose(file);
	}
	else
	{
		printf("File not found");
	}
	file = NULL;
}