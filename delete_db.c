#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void printf_info_del();

void delete_submenu(int* status, char* filename, RECORD* record) {
    FILE* db = NULL;
    while (!*status) {
        printf_info_del();
        int user_inp = 0;
        printf("\nEnter id for find & del, %d for exit\n>> ", EXIT_CODE);

        user_inp = get_number(status);
        printf("\n");
        if (user_inp == EXIT_CODE) {
            *status = USER_STOP;
            continue;
        }

        if (*status) {
            *status = 0;
            if (!feof(stdin)) {
                flush_stdin();
            }
            continue;
        }

        db = fopen(filename, "rb");
        if (db == NULL) {
            *status = NULL_PTR;
            continue;
        }
        find_by_id(db, record, user_inp);
        fclose(db);
        db = NULL;

        printf("\nTo delete\n1. Yes\n2. No\n");
        print_header();
        print_modules(record);

        if (get_number(status) == 1) {
            printf("DELETE CONFIRMED\n");
            flush_stdin();
            delete_module(filename, record);
        }
    }

    if (db != NULL) {
        fclose(db);
    }

    printf("DELETE STATUS# %d\n", *status);
}

void printf_info_del() { printf("\n===Delete Module==="); }
