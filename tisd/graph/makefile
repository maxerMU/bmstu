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

OBJFILES=$(OUTPATH)main.o $(OUTPATH)graph.o

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

$(OUTPATH)graph.o: $(SRCPATH)graph.c $(INCPATH)graph.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH):
	mkdir $(OUTPATH)

clean:
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
