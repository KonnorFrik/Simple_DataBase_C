#ifndef __DB_H__
#define __DB_H__

#include "struct.h"

MODULES* init_module();
void read_module(FILE* db, MODULES* obj, int offset);
void write_module(FILE* db, MODULES* obj);
void delete_module(char* filename, MODULES* record);
void update_module(FILE* db, MODULES* obj);
void fill_module(MODULES* obj, int* status);

int new_id(FILE* db);
void find_by_id(FILE* db, MODULES* record, int search_id);
int max_id(FILE* db, MODULES* obj);

char* get_tmp_filename(char* filename);
void print_modules(MODULES* obj);
void print_header();

/************************SUBMENU'S*************************/
void update_submenu(int* status, FILE* db, MODULES* record);
void delete_submenu(int* status, char* filename, MODULES* record);
void read_submenu(int* status, FILE* db, MODULES* record);
void write_submenu(int* status, FILE* db, MODULES* record);
/************************SUBMENU'S*************************/

#endif
