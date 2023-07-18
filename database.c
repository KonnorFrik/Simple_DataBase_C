#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

RECORD* init_module() {
    RECORD* obj = calloc(1, sizeof(RECORD));
    return obj;
}

void find_by_id(FILE* db, RECORD* record, int search_id) {
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

int max_id(FILE* db, RECORD* obj) {
    int res = 0;
    int offset = 0;

    while (db != NULL && !feof(db)) {
        read_module(db, obj, offset);

        if (DEBUG) {
            printf("[DEBUG] %d %s\n", obj->id, obj->name);
        }

        if (obj != NULL && obj->id > res) {
            res = obj->id;
            if (DEBUG) {
                printf("[DEBUG]\tMax changed: %d\n", res);
            }
        }

        offset++;
    }

    return res;
}

int new_id(FILE* db) {
    RECORD* fake = init_module();
    int res = -2;

    if (fake != NULL) {
        res = max_id(db, fake);
        free(fake);
    }

    if (DEBUG) {
        printf("[DEBUG] GOT max id: %d to return: %d\n", res, res + 1);
    }

    return res + 1;
}

void delete_module(char* filename, RECORD* record) {
    FILE* to_read = NULL;
    FILE* tmp = NULL;
    char* tmp_filename = NULL;

    if (filename != NULL) {
        to_read = fopen(filename, "rb");
        tmp_filename = get_tmp_filename(filename);
    }

    if (tmp_filename != NULL) {
        tmp = fopen(tmp_filename, "wb");
    }

    if (tmp != NULL && to_read != NULL) {
        RECORD* obj = calloc(1, sizeof(RECORD));
        int offset = 0;

        while (!feof(to_read) && obj != NULL) {
            read_module(to_read, obj, offset);

            if (obj->id != record->id) {
                fwrite(obj, sizeof(RECORD), 1, tmp);
            }

            offset++;
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

    if (DEBUG) {
        printf("[DEBUG]\n");
        printf("IN get_tmp_filename filename is:\n");
        print_raw_str(filename);
        printf("[DEBUG]\n");
    }

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

void fill_module(RECORD* obj, int* status) {
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

void write_module(FILE* db, RECORD* obj) {
    if (db != NULL && obj != NULL) {
        fseek(db, 0, SEEK_END);
        fwrite(obj, sizeof(RECORD), 1, db);
    }
}

void read_module(FILE* db, RECORD* obj, int offset) {
    if (obj != NULL && db != NULL) {
        fseek(db, sizeof(RECORD) * offset, SEEK_SET);
        fread(obj, sizeof(RECORD), 1, db);
    }
}

void update_module(FILE* db, RECORD* obj) {
    fseek(db, ftell(db) - sizeof(RECORD), SEEK_SET);
    if (DEBUG) {
        printf("[DEBUG] cursor for update: %ld\n", ftell(db));
    }
    fwrite(obj, sizeof(RECORD), 1, db);
}

void print_header() { printf("id\tname\t\tmemory\tcell\tflag\n"); }

void print_modules(RECORD* obj) {
    if (obj != NULL) {
        printf("%d\t%s\t%d\t%d\t%d\n", obj->id, obj->name, obj->mem_level, obj->cell, obj->flag);

    } else {
        printf("\t--NULL--\n");
    }
}
