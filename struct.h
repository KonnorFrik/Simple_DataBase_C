#ifndef __STRUCT_DB_H__
#define __STRUCT_DB_H__

#define NAME_LEN 30

typedef struct modules {
    int id;
    char name[NAME_LEN];
    int mem_level;
    int cell;
    int flag;
} MODULES;

#endif
