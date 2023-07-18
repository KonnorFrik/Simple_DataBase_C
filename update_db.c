#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void printf_info_upd();

void update_submenu(int* status, FILE* db, MODULES* record) {
    //char* filename = NULL;
    //FILE* db = NULL;

    //printf("Enter DB path\n>> ");
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

    //if (db != NULL) {
        //printf("Now update: ");
    //} else {
        //printf("Can't open ");
    //}

    //printf("'%s'\n", filename == NULL ? "-NULL-" : filename);

    while (!*status) {
        printf_info_upd();
        int user_inp;
        printf("\nEnter id for find & update, %d for exit\n>> ", EXIT_CODE);

        user_inp = get_number(status);
        printf("\n");
        if (user_inp == EXIT_CODE) {
            *status = USER_STOP;
            continue;
        }

        find_by_id(db, record, user_inp);

        printf("\nWhat to change\n1.Name\n2.Memory level\n3.Cell\n4.Flag\n\n");
        print_header();
        print_modules(record);

        user_inp = get_number(status);

        if (user_inp == 1) {
            printf("Enter new name\n>> ");
            flush_stdin();
            char* buf = get_str(status);
            if (buf != NULL) {
                strcpy(record->name, buf);
                free(buf);

            } else { 
                *status = NULL_PTR;
            }

        } else if (user_inp == 2) {
            printf("Enter new memory level\n>> ");
            record->mem_level = get_number(status);

        } else if (user_inp == 3) {
            printf("Enter new cell\n>> ");
            record->cell = get_number(status);

        } else if (user_inp == 4) {
            printf("Enter new flag\n>> ");
            record->flag = get_number(status);

        } else {
            printf("Unknown input\n");
            *status = 1;
        }

        if (!*status) {
            printf("\nUpdate confirm\n");
            update_module(db, record);

            printf("Updated module:\n");
            find_by_id(db, record, record->id);

            print_header();
            print_modules(record);
        }

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

    printf("UPDATE STATUS# %d\n", *status);

    //return status;
}

void printf_info_upd() {
    printf("\n===Update Module===");
}
