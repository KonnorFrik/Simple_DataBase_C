#include "io.h"

#include <stdio.h>
#include <stdlib.h>

#include "settings.h"

char* get_sized_str(unsigned int size, int* status) {
    unsigned int curr_size = STR_LEN;
    char* res = calloc(curr_size, sizeof(char));
    unsigned int ind = 0;
    char* str_buf = NULL;
    char buf = 1;

    while (res != NULL && ind < size && buf != '\n' && !*status) {
        buf = getchar();
        res[ind] = buf;
        ind++;

        if (ind > curr_size) {
            curr_size += curr_size / 2;
            str_buf = realloc(res, curr_size);

            if (str_buf != NULL) {
                res = str_buf;
                free(str_buf);
                str_buf = NULL;

            } else {
                free(res);
                res = NULL;
                *status = NULL_PTR;
                continue;
            }
        }
    }

    if (res != NULL) {
        res[--ind] = '\0';
    }

    if (res == NULL) {
        *status = NULL_PTR;
    }

    return res;
}

char* get_str(int* status) {
    unsigned int curr_size = STR_LEN;
    char* res = calloc(curr_size, sizeof(char));
    unsigned int ind = 0;
    char* str_buf = NULL;
    char buf = 1;

    while (res != NULL && buf != '\n' && !*status) {
        buf = getchar();
        res[ind] = buf;
        ind++;

        if (ind > curr_size) {
            curr_size += curr_size / 2;
            str_buf = realloc(res, curr_size);

            if (str_buf != NULL) {
                res = str_buf;
                free(str_buf);
                str_buf = NULL;

            } else {
                free(res);
                res = NULL;
                *status = NULL_PTR;
                continue;
            }
        }
    }

    if (res != NULL) {
        res[--ind] = '\0';
    }

    if (res == NULL) {
        *status = NULL_PTR;
    }

    return res;
}

int get_number(int* status) {
    int res = 0;
    int scan_res = scanf("%d", &res);

    if (scan_res != 1) {
        *status = 1;
    }

    return res;
}

int is_eol() {
    int res = 0;

    if (getchar() == '\n') {
        res = 1;
    }

    return res;
}

void flush_stdin() {
    // if (!feof(stdin)) {
    while (getchar() != '\n') {
        ;
    }
    //}
}
