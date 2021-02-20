CC=gcc
LINTER=cppcheck

INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func_tests/
UNITTESTSPATH=./unit_tests/

INC=-I$(INCPATH)
CFLAGS=-std=c99 -Wall -Werror -Wpedantic --coverage -Wfloat-equal -Wvla -g3 -ggdb
LFLAGS=--coverage
CHECKFLAGS=-lcheck

OBJFILES=$(OUTPATH)main.o $(OUTPATH)elem.o $(OUTPATH)tree_node.o $(OUTPATH)binary_tree.o $(OUTPATH)balance_node.o $(OUTPATH)balance_tree.o $(OUTPATH)hash_table.o $(OUTPATH)statistic.o

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
	$(CC) $(LFLAGS) -o $@ $^ -lm

$(OUTPATH)main.o: $(SRCPATH)main.c | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)elem.o: $(SRCPATH)elem.c $(INCPATH)elem.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)tree_node.o: $(SRCPATH)tree_node.c $(INCPATH)tree_node.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)binary_tree.o: $(SRCPATH)binary_tree.c $(INCPATH)binary_tree.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)balance_node.o: $(SRCPATH)balance_node.c $(INCPATH)balance_node.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)balance_tree.o: $(SRCPATH)balance_tree.c $(INCPATH)balance_tree.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)hash_table.o: $(SRCPATH)hash_table.c $(INCPATH)hash_table.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)statistic.o: $(SRCPATH)statistic.c $(INCPATH)statistic.h | $(OUTPATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH):
	mkdir $(OUTPATH)

clean:
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
