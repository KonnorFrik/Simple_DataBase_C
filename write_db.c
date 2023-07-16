#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

int main() {
    int status = 0;

    FILE* db = fopen(MODULES_PATH, "ab+");
    if (db == NULL) {
        status = NULL_PTR;
    }
    // else {
    // fseek(db, 0, SEEK_END);
    //}

    MODULES* record = init_module();

    printf("Now append: %s\n", MODULES_PATH);
    while (!status && db != NULL && record != NULL) {
        int offset;
        printf("\nEnter 1 for append, %d for exit\n>> ", EXIT_CODE);

        offset = get_number(&status);
        if (offset == EXIT_CODE) {
            status = USER_STOP;
            continue;
        }

        if (DEBUG) {
            printf("CURSOR: %ld\n", ftell(db));
        }

        fill_module(record, &status);

        write_module(db, record);

        printf("Writed record:\n");
        print_modules(record);
    }

    if (record != NULL) {
        // if (record->name != NULL) {
        // free(record->name);
        //}
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
