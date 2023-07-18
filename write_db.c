#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void printf_info_write();

void write_submenu(int* status, FILE* db, RECORD* record) {
    while (!*status) {
        printf_info_write();
        int menu = 0;
        printf("\nEnter 1 for append, %d for exit\n>> ", EXIT_CODE);

        menu = get_number(status);
        printf("\n");
        if (menu == EXIT_CODE) {
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

        fill_module(record, status);
        record->id = new_id(db);

        printf("Writed record:\n");
        print_header();
        print_modules(record);

        write_module(db, record);
    }

    printf("STATUS# %d\n", *status);
}

void printf_info_write() { printf("\n===Write Module==="); }
