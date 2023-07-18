#ifndef __IO_H__
#define __IO_H__

#define STR_LEN 256

char* get_str(int* status);
char* get_sized_str(unsigned int size, int* status);
int get_number(int* status);
char* get_str();
void flush_stdin();
void print_raw_str(char* str);

#endif
