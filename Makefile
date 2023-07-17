.RECIPEPREFIX = >
cc=gcc
flags=-Wall -Werror -Wextra
build_dir=bin

### USER ====================
all: check_dirs reader writer deleter clean
debug: check_dirs debug_reader debug_writer debug_deleter clean
rebuild: clean_all all

writer: write_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

reader: read_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

deleter: delete_db.o io.o database.o
> $(cc) $(flags) $? -o $(build_dir)/$@

debug_reader: read_db.c io.c database.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

debug_writer: write_db.c io.c database.c
> $(cc) $(flags) -g $? -o $(build_dir)/$@

debug_deleter: delete_db.c io.c database.c
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
