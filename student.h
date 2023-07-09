#ifndef STUDENT__H
#define STUDENT__H

enum MAJOR
{
	ARCH,
	BUD,
	ENERG,
	FIZ,
	INF,
	MAT,
	NANO,
	TRANS
};

static char majorlist[][16] =
{
	"Architektura",
	"Budownictwo",
	"Energetyka",
	"Fizyka",
	"Informatyka",
	"Matematyka",
	"Nanotechnologia",
	"Transport"
};

struct MY_STUDENT
{
	char *lastname;
	int year;
	enum MAJOR student_major;
};

void MY_STUDENT_Free(void* ptr);
void* MY_STUDENT_Push(char* lastname, int year, MAJOR student_major);
void MY_STUDENT_Print(void* ptr);
void MY_STUDENT_SaveData(void* ptr, FILE* fp);
void* MY_STUDENT_ReadData(FILE* fp);
int MY_STUDENT_SearchData(void* pCurData, void* pSearchData, int dataType);
#endif
