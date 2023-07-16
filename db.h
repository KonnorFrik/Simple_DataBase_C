#ifndef __DB_H__
#define __DB_H__

#include "struct.h"

void print_modules(MODULES* obj);
void read_module(FILE* db, MODULES* obj, int offset, int* status);
void write_module(FILE* db, MODULES* obj);
void fill_module(MODULES* obj, int* status);
MODULES* init_module();

#endif
