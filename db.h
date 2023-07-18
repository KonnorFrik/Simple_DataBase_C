#ifndef __DB_H__
#define __DB_H__

#include "struct.h"

RECORD* init_module();
void read_module(FILE* db, RECORD* obj, int offset);
void write_module(FILE* db, RECORD* obj);
void delete_module(char* filename, RECORD* record);
void update_module(FILE* db, RECORD* obj);
void fill_module(RECORD* obj, int* status);

int new_id(FILE* db);
void find_by_id(FILE* db, RECORD* record, int search_id);
int max_id(FILE* db, RECORD* obj);

char* get_tmp_filename(char* filename);
void print_modules(RECORD* obj);
void print_header();

/************************SUBMENU'S*************************/
void update_submenu(int* status, FILE* db, RECORD* record);
void delete_submenu(int* status, char* filename, RECORD* record);
void read_submenu(int* status, FILE* db, RECORD* record);
void write_submenu(int* status, FILE* db, RECORD* record);
/************************SUBMENU'S*************************/

#endif
