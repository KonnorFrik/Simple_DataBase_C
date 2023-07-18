#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void printf_info_upd();

void update_submenu(int* status, FILE* db, RECORD* record) {
    while (!*status) {
        printf_info_upd();
        int user_inp = 0;
        printf("\nEnter id for find & update, %d for exit\n>> ", EXIT_CODE);

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

        find_by_id(db, record, user_inp);

        /*vvvvvvvvvvvvFOR CHANGESvvvvvvvvvvvvvvvvvv*/
        printf("\nWhat to change\n1.Name\n2.Memory level\n3.Cell\n4.Flag\n%d. EXIT\n", EXIT_CODE);
        /*^^^^^^^^^^^^FOR CHANGES^^^^^^^^^^^^^^^^^^*/
        print_header();
        print_modules(record);

        user_inp = get_number(status);

        /*vvvvvvvvvvvvFOR CHANGESvvvvvvvvvvvvvvvvvv*/
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
            user_inp = 0;

        } else if (user_inp == 2) {
            printf("Enter new memory level\n>> ");
            record->mem_level = get_number(status);
            user_inp = 0;

        } else if (user_inp == 3) {
            printf("Enter new cell\n>> ");
            record->cell = get_number(status);
            user_inp = 0;

        } else if (user_inp == 4) {
            printf("Enter new flag\n>> ");
            record->flag = get_number(status);
            user_inp = 0;

        } else if (user_inp == EXIT_CODE) {
            user_inp = 0;
            continue;

        } else {
            printf("Unknown input\n");
            *status = 1;
            user_inp = 0;
        }
        /*^^^^^^^^^^^^FOR CHANGES^^^^^^^^^^^^^^^^^^*/

        if (!*status) {
            printf("\nUpdate confirm\n");
            update_module(db, record);

            printf("Updated module:\n");
            find_by_id(db, record, record->id);

            print_header();
            print_modules(record);
        }
    }

    printf("UPDATE STATUS# %d\n", *status);
}

void printf_info_upd() { printf("\n===Update Module==="); }
