.RECIPEPREFIX = >
cc=gcc
flags=-Wall -Werror -Wextra
build_dir=bin

### USER ====================
all: reader writer deleter clean
debug: debug_reader debug_writer debug_deleter clean

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
rebuild: clean_all all

clean:
> rm -f *.o

clean_all: clean
> rm -rf bin/*
### STUFF ===================


%.o: %.c
> $(cc) $(flags) -c $? -o $@
