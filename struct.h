#ifndef __STRUCT_DB_H__
#define __STRUCT_DB_H__

#define NAME_LEN 30

//#define MODULES_PATH "data/master_modules.db"
#define MODULES_PATH "data/new.db"

typedef struct modules {
    int id;
    char name[NAME_LEN];
    int mem_level;
    int cell;
    int flag;
} MODULES;

#endif
