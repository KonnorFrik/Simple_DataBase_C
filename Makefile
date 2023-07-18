.RECIPEPREFIX = >
cc=gcc
flags=-Wall -Werror -Wextra
build_dir=bin

### USER ====================
all: check_dirs reader writer deleter updater main clean
debug: check_dirs debug_reader debug_writer debug_deleter clean
rebuild: clean_all all

main: main.o io.o database.o write_db.o read_db.o update_db.o delete_db.o
> $(cc) $(flags) $? -o $(build_dir)/$@
> make clean

writer: write_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

reader: read_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

deleter: delete_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

updater: update_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

debug_reader: read_db.c io.c database.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

debug_writer: write_db.c io.c database.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

debug_deleter: delete_db.c io.c database.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

debug_updater: update_db.c io.c database.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

new_db:
> rm -f data/new.db
> touch data/new.db
### USER ====================

### STUFF ===================

clean:
> rm -f *.o

check_dirs:
> chmod +x check_dirs.sh
> ./check_dirs.sh

clean_all: clean
> rm -rf bin/*
### STUFF ===================


%.o: %.c
> $(cc) $(flags) -c $? -o $@
