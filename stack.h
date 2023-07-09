#ifndef STACK___H
#define STACK___H

struct STACK
{
	void* pData;   
	STACK* under;	
};

typedef void (*FreeData)(void* pdat);
typedef void (PrintData)(void* pdat);
typedef void (SaveData)(void* ptr, FILE* fp);
typedef void* (ReadData)(FILE* fp);
typedef int (CompData)(void* pcurData, void* pSearchData, int dataType);
void STACK_Init(FreeData pFreeDat);
void STACK_Free();
void STACK_Print(PrintData print_data);
void STACK_Save(SaveData save_data);
void STACK_Read(ReadData read_data);
void STACK_Reverse();

void* STACK_FindByIndex(size_t index);
void* STACK_Search(void* pSearchData, CompData ptr_comp, int FirstEntry, int dataType);
STACK* STACK_Push(void* pDat);
STACK STACK_Pop();
#endif