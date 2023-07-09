#ifndef MY_INTERFACE___H
#define MY_INTERFACE___H

enum INTERF_OPT
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_FIND_LASTNAME,
	SAVE_STACK,
	READ_STACK,
	PRINT_STACK,
	SAVE_STUDENT,
	READ_STUDENT,
	PUSH_STUDENT_FILE,
	INTERF_STOP,
	INTERF_TOT
};

void push();
void pop();
void clear();
void menu();
void find_student();
void save_stack();
void read_stack();
void print_stack();
void save_student();
void read_student();
void push_student_from_file();
#endif