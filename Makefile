.RECIPEPREFIX = >
cc=gcc
flags=-Wall -Werror -Wextra
build_dir=bin
default_db_name=default.db

### USER ====================
all: check_dirs main clean
rebuild: clean_all all

main: main.o io.o database.o write_db.o read_db.o update_db.o delete_db.o
> $(cc) $(flags) $? -o $(build_dir)/$@

new_db:
> rm -f data/$(default_db_name)
> touch data/$(default_db_name)

del_db:
> rm -rf data/*

shared_lib: libdb_interface.so main.c
> $(cc) $(flags) main.c -o $(build_dir)/main -L./bin -Wl,-rpath=./bin -l:libdb_interface.so

libdb_interface.so: io.c database.c write_db.c read_db.c update_db.c delete_db.c
> $(cc) $(flags) -c -fpic $?
> $(cc) $(flags) -shared *.o -o $(build_dir)/$@
### USER ====================

### STUFF ===================
debug: check_dirs debug_main clean

debug_main: main.c io.c database.c write_db.c read_db.c update_db.c delete_db.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

clean:
> rm -f *.o

check_dirs:
> chmod +x check_dirs.sh
> ./check_dirs.sh

clean_all: clean
> rm -rf bin/*

%.o: %.c
> $(cc) $(flags) -c $? -o $@
### STUFF ===================
