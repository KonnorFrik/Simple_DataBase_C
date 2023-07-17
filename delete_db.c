#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

int main() {
    int status = 0;
    char* filename = NULL;

    printf("Enter DB path\n>> ");
    filename = get_str(&status);
    // FILE* db = fopen(filename, "rb");
    FILE* db = NULL;

    if (filename == NULL) {
        status = NULL_PTR;
    }

    // if (db == NULL) {
    // status = NULL_PTR;
    //}

    MODULES* record = init_module();
    if (record == NULL) {
        status = NULL_PTR;
    }

    printf("Now delete in: %s\n", filename == NULL ? "-NULL-" : filename);
    while (!status) {
        int user_inp;
        printf("\nEnter id for find & del, %d for exit\n>> ", EXIT_CODE);

        user_inp = get_number(&status);
        if (user_inp == EXIT_CODE) {
            status = USER_STOP;
            continue;
        }

        // printf("Enter id for search\n>> ");
        // int search_id = get_number(&status);

        db = fopen(filename, "rb");
        if (db == NULL) {
            status = NULL_PTR;
            continue;
        }
        find_by_id(db, record, user_inp);
        fclose(db);
        db = NULL;

        printf("\nTo delete\n1. Yes\n2. No\n");
        print_header();
        print_modules(record);

        if (get_number(&status) == 1) {
            printf("DELETE CONFIRMED\n");
            flush_stdin();
            delete_module(filename, record);
        }
    }

    if (record != NULL) {
        // if (record->name != NULL) {
        // free(record->name);
        //}
        free(record);
    }

    if (filename != NULL) {
        free(filename);
    }

    if (db != NULL) {
        fclose(db);
    }

    printf("STATUS# %d\n", status);

    return status;
}
