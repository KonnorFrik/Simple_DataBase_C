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

    FILE* db = fopen(MODULES_PATH, "rb");
    if (db == NULL) {
        status = NULL_PTR;
    }

    MODULES* record = init_module();

    printf("Now read: %s\n", MODULES_PATH);
    while (!status && db != NULL && record != NULL) {
        int offset;
        printf("Enter offset of record (%d for exit)\n>> ", EXIT_CODE);

        offset = get_number(&status);
        if (offset == EXIT_CODE) {
            status = USER_STOP;
            continue;
        }

        read_module(db, record, offset, &status);

        if (DEBUG) {
            printf("CURSOR: %ld\n", ftell(db));
        }

        print_modules(record);
    }

    // if (modules_record == NULL) {
    // status = NULL_PTR;
    //}

    // if (modules_record != NULL) {
    // free(modules_record);
    //}

    if (record != NULL) {
        free(record);
    }

    if (db != NULL) {
        fclose(db);
    }

    if (status) {
        printf("STATUS# %d\n", status);
    }

    return status;
}
