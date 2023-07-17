#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

// TODO
// get db filepath from user
int main() {
    int status = 0;
    char* filename = NULL;
    FILE* db = NULL;

    printf("Enter db path\n>> ");
    filename = get_str(&status);

    if (filename != NULL) {
        db = fopen(filename, "rb+");

    } else {
        status = NULL_PTR;
    }

    if (db == NULL) {
        status = NULL_PTR;
    }

    // if (filename == NULL) {
    // status = NULL_PTR;
    //}

    MODULES* record = init_module();
    if (record == NULL) {
        status = NULL_PTR;
    }

    printf("Now read: %s\n", filename == NULL ? "-NULL-" : filename);
    while (!status) {
        int offset;
        printf("\nEnter offset of record (%d for exit)\n>> ", EXIT_CODE);

        offset = get_number(&status);
        if (offset == EXIT_CODE) {
            status = USER_STOP;
            continue;
        }

        read_module(db, record, offset);

        if (DEBUG) {
            printf("CURSOR: %ld\n", ftell(db));
        }

        print_header();
        print_modules(record);
    }

    if (record != NULL) {
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
