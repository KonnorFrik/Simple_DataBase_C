#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "db.h"
#include "io.h"
#include "settings.h"
#include "struct.h"

void print_menu();
void print_status(char* filename, FILE* db, int status);
void print_hello();
FILE* connect(char* filename);
FILE* disconnect(FILE* file);

int main() {
    int status = 0;
    char* filename = NULL;
    FILE* db = NULL;

    RECORD* record = init_module();
    if (record == NULL) {
        status = NULL_PTR;
    }

    print_hello();

    int menu = 0;
    while (menu != EXIT_CODE) {
        printf("\n");
        print_status(filename, db, status);
        print_menu();

        if (status) {
            status = 0;
        }

        menu = get_number(&status);
        printf("\n");
        if (!feof(stdin)) {
            flush_stdin();
        }

        if (menu == CONNECT_ACTION) {
            if (filename != NULL) {
                free(filename);
                filename = NULL;
            }
            printf("Enter DB path\n>> ");

            filename = get_str(&status);
            db = connect(filename);
            menu = 0;

        } else if (menu == WRITE_ACTION) {
            if (db != NULL && record != NULL) {
                write_submenu(&status, db, record);
            } else {
                status = NULL_PTR;
            }
            menu = 0;
            if (status == EXIT_CODE) {
                status = 0;
            }

        } else if (menu == READ_ACTION) {
            if (db != NULL && record != NULL) {
                read_submenu(&status, db, record);
            } else {
                status = NULL_PTR;
            }
            menu = 0;
            if (status == EXIT_CODE) {
                status = 0;
            }

        } else if (menu == UPDATE_ACTION) {
            if (db != NULL && record != NULL) {
                update_submenu(&status, db, record);
            } else {
                status = NULL_PTR;
            }
            menu = 0;
            if (status == EXIT_CODE) {
                status = 0;
            }

        } else if (menu == DELETE_ACTION) {
            db = disconnect(db);

            if (filename != NULL && record != NULL) {
                delete_submenu(&status, filename, record);
            } else {
                status = NULL_PTR;
            }
            if (status == EXIT_CODE) {
                status = 0;
            }
            menu = 0;
            db = connect(filename);

        } else if (menu == DISCONNECT_ACTION) {
            if (filename != NULL) {
                free(filename);
                filename = NULL;
            }

            db = disconnect(db);

        } else if (menu == EXIT_CODE) {
            printf("Bye\n");

        } else {
            printf("Unknown command\n");
        }
    }

    if (record != NULL) {
        free(record);
    }

    if (filename != NULL) {
        if (DEBUG) {
            printf("[DEBUG] 'filename' NOT null in main\n");
        }
        free(filename);
    }

    if (db != NULL) {
        if (DEBUG) {
            printf("[DEBUG] 'db' NOT null in main\n");
        }
        fclose(db);
    }

    printf("Status# %d\n", status);
    return status;
}

FILE* connect(char* filename) {
    FILE* file = NULL;
    if (filename != NULL) {
        file = fopen(filename, FILEMODE);
    }
    return file;
}

FILE* disconnect(FILE* file) {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
    return file;
}

void print_menu() {
    printf("%d. Disconnect DB\n", DISCONNECT_ACTION);
    printf("%d. Connect to DB\n", CONNECT_ACTION);
    printf("%d. Read from DB\n", READ_ACTION);
    printf("%d. Update record in DB\n", UPDATE_ACTION);
    printf("%d. Write New into DB\n", WRITE_ACTION);
    printf("%d. Delete from DB\n", DELETE_ACTION);
    printf("%d. EXIT\n", EXIT_CODE);
    printf(">> ");
}

void print_status(char* filename, FILE* db, int status) {
    printf("\n");
    printf("--------Status------\n");
    printf("| Sys status:  '%d'\n", status);
    printf("| DB file:     '%s'\n", filename == NULL ? "-NULL-" : filename);
    printf("| DB connect:   %s \n", db == NULL ? "NO" : "YES");
    printf("--------Status------\n");
    printf("\n");
}

void print_hello() {
    printf("=========================\n");
    printf("| Welcome to C DataBase |\n");
    printf("| Author: KonnorFrik    |\n");
    printf("=========================\n");
    printf("\n");
}
