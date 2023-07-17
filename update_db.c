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
    FILE* db = NULL;

    printf("Enter DB path\n>> ");
    filename = get_str(&status);

    if (filename != NULL) {
        db = fopen(filename, "ab+");

    } else {
        status = NULL_PTR;
    }

    if (db == NULL) {
        status = NULL_PTR;
    }

    MODULES* record = init_module();
    if (record == NULL) {
        status = NULL_PTR;
    }

    printf("Now append: %s\n", filename == NULL ? "-NULL-" : filename);
    while (!status) {
    }

    return status;
}
