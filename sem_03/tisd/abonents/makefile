CC=gcc

INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func_tests/
UNITTESTSPATH=./unit_tests/

INC=-I$(INCPATH)
CFLAGS=-std=c99 -Wall -Werror -Wextra -Wpedantic --coverage -Wfloat-equal -Wvla -g3 -ggdb
LFLAGS=--coverage
CHECKFLAGS=-lcheck

OBJFILES=main.o abonent.o abonents_table.o

WINDOWS=WINDOWS_NT

.PHONY: clean release debug func unit
.NOTPARALLEL: release debug func

app.exe: $(OBJFILES)
	$(CC) $(LFLAGS) -o $@ $^

*.o: *.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe