#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void show_all(FILE* db, MODULES* record);
void printf_info_read();

void read_submenu(int* status, FILE* db, MODULES* record) {
    //int status = 0;
    //char* filename = NULL;
    //FILE* db = NULL;

    //printf("Enter db path\n>> ");
    //filename = get_str(&status);

    //if (filename != NULL) {
        //db = fopen(filename, "rb+");
    //} else {
        //status = NULL_PTR;
    //}

    //if (db == NULL) {
        //status = NULL_PTR;
    //}

    //MODULES* record = init_module();
    //if (record == NULL) {
        //status = NULL_PTR;
    //}

    //printf("Now read: %s\n", filename == NULL ? "-NULL-" : filename);
    while (!*status) {
        printf_info_read();

        int user_inp;
        printf("\nEnter id for search\n%d For show all records\n(%d for exit)\n>> ", READ_ALL, EXIT_CODE);

        user_inp = get_number(status);
        printf("\n");
        if (user_inp == EXIT_CODE) {
            *status = USER_STOP;
            continue;
        }

        if (user_inp == READ_ALL) {
            show_all(db, record);
            fseek(db, 0, SEEK_SET);
            continue;
        }

        find_by_id(db, record, user_inp);

        if (DEBUG) {
            printf("[DEBUG] CURSOR: %ld\n", ftell(db));
        }

        print_header();
        print_modules(record);
    }

    //if (record != NULL) {
        //free(record);
    //}
    //if (filename != NULL) {
        //free(filename);
    //}
    //if (db != NULL) {
        //fclose(db);
    //}

    printf("STATUS# %d\n", *status);

    //return status;
}

void show_all(FILE* db, MODULES* record) {
    int offset = 0;
    fseek(db, 0, SEEK_SET);
    print_header();

    while (!feof(db)) {
        read_module(db, record, offset);
        offset++;

        if (!feof(db)) {
            print_modules(record);
        }
    }
}

void printf_info_read() {
    printf("\n===Read Module===");
}
