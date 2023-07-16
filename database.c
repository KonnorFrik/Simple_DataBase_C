#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

MODULES* init_module() {
    MODULES* obj = malloc(sizeof(MODULES));
    return obj;
}

void fill_module(MODULES* obj, int* status) {
    if (obj != NULL) {
        printf("ID\n>> ");
        obj->id = get_number(status);
        flush_stdin();

        printf("Name\n>> ");
        char* buf = get_sized_str(NAME_LEN, status);
        if (buf != NULL) {
            strcpy(obj->name, buf);
            free(buf);
        }

        printf("Memory Level\n>> ");
        obj->mem_level = get_number(status);

        printf("Cell\n>> ");
        obj->cell = get_number(status);

        printf("Flag\n>> ");
        obj->flag = get_number(status);
    }
}

void write_module(FILE* db, MODULES* obj) {
    if (db != NULL && obj != NULL) {
        fwrite(obj, sizeof(MODULES), 1, db);
    }
}

void read_module(FILE* db, MODULES* obj, int offset, int* status) {
    if (obj != NULL && db != NULL && !*status) {
        fseek(db, sizeof(MODULES) * offset, SEEK_SET);
        fread(obj, sizeof(MODULES), 1, db);
    }

    if (*status && obj != NULL) {
        free(obj);
    }
}

void print_modules(MODULES* obj) {
    if (obj != NULL) {
        printf("id\tname\t\tmemory\tcell\tflag\n");
        printf("%d\t%s\t\t%d\t%d\t%d\n", obj->id, obj->name, obj->mem_level, obj->cell, obj->flag);

    } else {
        printf("\t--NULL--\n");
    }
}
