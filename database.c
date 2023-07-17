#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

MODULES* init_module() {
    MODULES* obj = calloc(1, sizeof(MODULES));
    return obj;
}

void find_by_id(FILE* db, MODULES* record, int search_id) {
    int find = 0;
    int offset = 0;

    while (db != NULL && !feof(db) && !find) {
        read_module(db, record, offset);

        if (record != NULL && record->id == search_id) {
            find = 1;
            continue;
        }
        offset++;
    }
}

int max_id(FILE* db, MODULES* obj) {
    int res = -1;
    int offset = 0;

    while (db != NULL && !feof(db)) {
        read_module(db, obj, offset);

        if (obj != NULL && obj->id > res) {
            res = obj->id;
        }

        offset++;
    }

    return res;
}

int new_id(FILE* db) {
    MODULES* fake = calloc(1, sizeof(MODULES));
    int res = -1;

    if (fake != NULL) {
        res = max_id(db, fake);
        free(fake);
    }

    return res + 1;
}

void delete_module(char* filename, MODULES* record) {
    FILE* to_read = NULL;
    FILE* tmp = NULL;
    char* tmp_filename = NULL;

    if (filename != NULL) {
        to_read = fopen(filename, "rb");
        tmp_filename = get_tmp_filename(filename);

        if (DEBUG) {
            printf("\nfilename: %s\ttmp filename: %s\n", filename, tmp_filename);
        }
    }

    if (tmp_filename != NULL) {
        tmp = fopen(tmp_filename, "wb");
    }

    if (tmp != NULL && to_read != NULL) {
        MODULES* obj = calloc(1, sizeof(MODULES));

        while (!feof(to_read) && obj != NULL) {
            fread(obj, sizeof(MODULES), 1, to_read);

            if (obj->id != record->id) {
                fwrite(obj, sizeof(MODULES), 1, tmp);
            }
        }

        if (obj != NULL) {
            free(obj);
        }
    }

    if (to_read != NULL) {
        fclose(to_read);
    }

    if (tmp != NULL) {
        fclose(tmp);
    }

    if (filename != NULL && tmp_filename != NULL) {
        remove(filename);
        rename(tmp_filename, filename);
        free(tmp_filename);
    }
}

char* get_tmp_filename(char* filename) {
    char* new = NULL;

    if (filename != NULL) {
        int len;
        len = strlen(filename);
        len += 5;
        new = calloc(len, sizeof(char));
    }

    if (new != NULL) {
        strcat(new, filename);
        strcat(new, "_tmp");
    }

    return new;
}

void fill_module(MODULES* obj, int* status) {
    if (obj != NULL) {
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
        fseek(db, 0, SEEK_END);
        fwrite(obj, sizeof(MODULES), 1, db);
    }
}

void read_module(FILE* db, MODULES* obj, int offset) {
    if (obj != NULL && db != NULL) {
        fseek(db, sizeof(MODULES) * offset, SEEK_SET);
        fread(obj, sizeof(MODULES), 1, db);
    }
}

void print_header() { printf("id\tname\t\tmemory\tcell\tflag\n"); }

void print_modules(MODULES* obj) {
    if (obj != NULL) {
        printf("%d\t%s\t%d\t%d\t%d\n", obj->id, obj->name, obj->mem_level, obj->cell, obj->flag);

    } else {
        printf("\t--NULL--\n");
    }
}
