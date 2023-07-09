#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#pragma warning(disable : 4996)

static STACK* top = NULL;
FreeData ptr_free_dat;

void STACK_Init(FreeData pFreeDat)
{
	top = NULL;
	ptr_free_dat = pFreeDat;
}

void STACK_Free()
{
	STACK* p = top, * ptmp = NULL;
	while (p)
	{
		(*ptr_free_dat)(p->pData);
		ptmp = p;
		p = p->under;
		free(ptmp);
		ptmp = NULL;
	}

	top = NULL;
}

STACK *STACK_Push(void* pDat)
{
	STACK *newstack = (STACK *)malloc(sizeof(STACK));
	if (!newstack)
	{
		printf("Memory allocation error.");
		exit(1);
	}

	if (top)
	{
		newstack->under = top;
		top = newstack;
	}
	else
	{
		top = newstack;
		newstack->under = NULL;
	}

	newstack->pData = pDat;
	return newstack;
}

void* STACK_Search(void* pSearchDat, CompData ptr_comp, int FirstEntry, int dataType)
{
	static STACK* elementptr;
	STACK* ptmp = NULL;

	if (FirstEntry)
		elementptr = top;

	while (elementptr)
	{
		if (!(*ptr_comp)(elementptr->pData, pSearchDat, dataType))
		{
			elementptr = elementptr->under;
		}
		else
		{
			ptmp = elementptr;
			elementptr = elementptr->under;
			return ptmp->pData;
		}
	}

	return NULL;
}

STACK STACK_Pop()
{
	STACK stack;
	if (!top)
	{
		stack.pData = NULL;
		stack.under = NULL;
	}
	else
	{
		STACK* next = top->under;

		stack.pData = top->pData;
		stack.under = NULL;
		free(top);
		top = next;
	}

	return stack;
}

void STACK_Save(SaveData save_data)
{
	FILE* file = fopen("stack", "wb");
	STACK* ptr = top;
	if (file)
	{
		while (ptr)
		{
			(*save_data)(ptr->pData, file);
			ptr = ptr->under;
		}
		fclose(file);
	}
	file = NULL;
}

void STACK_Read(ReadData read_data)
{
	FILE* file = fopen("stack", "rb");
	if (file)
	{
		void* pDat = (*read_data)(file);
		while(pDat)
		{
			STACK_Push(pDat);
			pDat = (*read_data)(file);
		}
		fclose(file);
		STACK_Reverse();
	}
	file = NULL;
}

void STACK_Print(PrintData print_data)
{
	STACK* p = top;
	size_t i = 0;
	while (p)
	{
		printf("\nIndex: %d\n", i);
		(*print_data)(p->pData);
		p = p->under;
		i++;
	}
}

void* STACK_FindByIndex(size_t index)
{
	STACK* ptr = top;
	if (ptr)
	{
		while (index--)
		{
			if (ptr)	ptr = ptr->under;
			else return 0;
		}
		return ptr->pData;
	}
	else return 0;
}

void STACK_Reverse()
{
	if (!top) return;
	STACK* tmptop = top;
	STACK* previous = top;
	STACK* current = top;
	STACK* next;
	current = current->under;
	
	while (current)
	{
		next = current->under;
		current->under = previous;
		previous = current;
		current = next;
	}
	top = previous;
	tmptop->under = NULL;
}