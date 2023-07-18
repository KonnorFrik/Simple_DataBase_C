#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void printf_info_write();

void write_submenu(int* status, FILE* db, MODULES* record) {
    // int status = 0;
    // char* filename = NULL;
    // FILE* db = NULL;

    // printf("Enter DB path\n>> ");
    // filename = get_str(&status);

    // if (filename != NULL) {
    // db = fopen(filename, "ab+");
    //} else {
    // status = NULL_PTR;
    //}

    // if (db == NULL) {
    // status = NULL_PTR;
    //}

    // MODULES* record = init_module();
    // if (record == NULL) {
    // status = NULL_PTR;
    //}

    // printf("Now append: %s\n", filename == NULL ? "-NULL-" : filename);
    while (!*status) {
        printf_info_write();
        int menu;
        printf("\nEnter 1 for append, %d for exit\n>> ", EXIT_CODE);

        menu = get_number(status);
        printf("\n");
        if (menu == EXIT_CODE) {
            *status = USER_STOP;
            continue;
        }

        fill_module(record, status);
        record->id = new_id(db);

        printf("Writed record:\n");
        print_header();
        print_modules(record);

        write_module(db, record);
    }

    // if (record != NULL) {
    // free(record);
    //}
    // if (filename != NULL) {
    // free(filename);
    //}
    // if (db != NULL) {
    // fclose(db);
    //}

    printf("STATUS# %d\n", *status);

    // return status;
}

void printf_info_write() { printf("\n===Write Module==="); }
