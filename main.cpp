#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "student.h"
#include "interface.h"
#pragma once

#pragma warning (disable : 4996)

int main(int argc, char* argv[]) {
	STACK_Init(MY_STUDENT_Free);
	size_t option = 0;
	while (option >= INTERF_PUSH && option <= INTERF_STOP)
	{
		menu();
		scanf("%d", &option);
		switch (option)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTERF_CLEAR: clear();
			break;
		case INTERF_FIND_LASTNAME: find_student();
			break;
		case SAVE_STACK: save_stack();
			break;
		case READ_STACK: read_stack();
			break;
		case PRINT_STACK: print_stack();
			break;
		case SAVE_STUDENT: save_student();
			break;
		case READ_STUDENT: read_student();
			break;
		case PUSH_STUDENT_FILE: push_student_from_file();
			break;
		case INTERF_STOP: clear();
			return 0;
		default:
			printf("Unknown option chosen.\n");
		};
	}
}