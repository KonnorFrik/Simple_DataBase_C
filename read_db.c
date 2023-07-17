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

    printf("Enter db path\n>> ");
    char* filename = get_str(&status);
    FILE* db = fopen(filename, "rb+");
    //flush_stdin();

    if (filename == NULL) {
        status = NULL_PTR;
    }

    if (db == NULL) {
        status = NULL_PTR;
    }

    MODULES* record = init_module();
    if (record == NULL) {
        status = NULL_PTR;
    }

    printf("Now read: %s\n", filename);
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

    if (status) {
        printf("STATUS# %d\n", status);
    }

    return status;
}
