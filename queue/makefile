CC=gcc
LINTER=cppcheck

INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func_tests/
UNITTESTSPATH=./unit_tests/

INC=-I$(INCPATH)
CFLAGS=-std=c99 -Wall -Werror -Wextra -Wpedantic --coverage -Wfloat-equal -Wvla -g3 -ggdb
LFLAGS=--coverage
CHECKFLAGS=-lcheck

OBJFILES=$(OUTPATH)main.o $(OUTPATH)request.o $(OUTPATH)queue_vector.o $(OUTPATH)queue_list.o

WINDOWS=WINDOWS_NT

.PHONY: clean release debug func unit
.NOTPARALLEL: release debug func

ifneq ($(OS),$(WINDOWS))
	CHECKFLAGS+=-lpthread -lrt
endif

release: CFLAGS=-std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wvla -o3
release: LFLAGS=-o3
release: $(OUTPATH)release.lastbuildstate app.exe

debug: $(OUTPATH)debug.lastbuildstate app.exe

$(OUTPATH)release.lastbuildstate: | $(OUTPATH)
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
	touch $(OUTPATH)release.lastbuildstate

$(OUTPATH)debug.lastbuildstate: | $(OUTPATH)
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
	touch $(OUTPATH)debug.lastbuildstate

app.exe: $(OBJFILES)
	$(CC) $(LFLAGS) -o $@ $^

$(OUTPATH)main.o: $(SRCPATH)main.c | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)request.o: $(SRCPATH)request.c $(INCPATH)request.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)queue_vector.o: $(SRCPATH)queue_vector.c $(INCPATH)queue_vector.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)queue_list.o: $(SRCPATH)queue_list.c $(INCPATH)queue_list.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

func: $(OUTPATH)debug.lastbuildstate app.exe
	$(LINTER) $(SRCPATH)*.c
	cd $(FUNCTESTSPATH) && bash all_test.sh
	gcov $(OBJFILES)
	mv *.gcov $(OUTPATH)

$(OUTPATH):
	mkdir $(OUTPATH)

clean:
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
