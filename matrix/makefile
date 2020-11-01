CC=gcc
LINTER=cppcheck

INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
FUNCTESTSPATH=./func_tests/
UNITTESTSPATH=./unit_tests/

INC=-I$(INCPATH)
CFLAGS=-std=c99 -Wall -Werror -Wextra -Wpedantic --coverage -Wfloat-equal -Wvla -g3 -ggdb
LFLAGS=--coverage -lm
CHECKFLAGS=-lcheck

OBJFILES=$(OUTPATH)main.o $(OUTPATH)matrix_create.o $(OUTPATH)matrix_utils.o $(OUTPATH)read_funcs.o $(OUTPATH)gen_matrix.o $(OUTPATH)pmatrix_create.o $(OUTPATH)pmatrix_utils.o

WINDOWS=WINDOWS_NT

.PHONY: clean release debug func unit
.NOTPARALLEL: release debug func

ifneq ($(OS),$(WINDOWS))
	CHECKFLAGS+=-lpthread -lrt
endif

release: CFLAGS=-std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wvla -o3
release: LFLAGS=-o3 -lm
release: $(OUTPATH)release.lastbuildstate app.exe

debug: $(OUTPATH)debug.lastbuildstate app.exe

$(OUTPATH)release.lastbuildstate:
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
	touch $(OUTPATH)release.lastbuildstate

$(OUTPATH)debug.lastbuildstate:
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
	touch $(OUTPATH)debug.lastbuildstate

app.exe: $(OBJFILES)
	$(CC) $^ $(LFLAGS) -o $@

$(OUTPATH)main.o: $(SRCPATH)main.c
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)matrix_create.o: $(SRCPATH)matrix_create.c $(INCPATH)matrix_create.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)matrix_utils.o: $(SRCPATH)matrix_utils.c $(INCPATH)matrix_utils.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)gen_matrix.o: $(SRCPATH)gen_matrix.c $(INCPATH)gen_matrix.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)read_funcs.o: $(SRCPATH)read_funcs.c $(INCPATH)read_funcs.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)pmatrix_create.o: $(SRCPATH)pmatrix_create.c $(INCPATH)pmatrix_create.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)pmatrix_utils.o: $(SRCPATH)pmatrix_utils.c $(INCPATH)pmatrix_utils.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

func: $(OUTPATH)debug.lastbuildstate app.exe
	$(LINTER) $(SRCPATH)*.c
	cd $(FUNCTESTSPATH) && cmd //C all_test.cmd
	gcov $(OBJFILES)
	mv *.gcov $(OUTPATH)

unit: unit_tests.exe
	drmemory -batch -lib_blacklist "*" -- ./unit_tests.exe
	
unit_tests.exe: $(OUTPATH)matrix_create.o $(OUTPATH)matrix_utils.o $(OUTPATH)check_matrix_create.o $(OUTPATH)check_matrix_utils.o $(OUTPATH)check_main.o
	$(CC) $(LFLAGS) $^ $(CHECKFLAGS) -o $@

$(OUTPATH)check_main.o: $(UNITTESTSPATH)check_main.c
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)check_matrix_create.o: $(UNITTESTSPATH)check_matrix_create.c $(INCPATH)check_matrix_create.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUTPATH)check_matrix_utils.o: $(UNITTESTSPATH)check_matrix_utils.c $(INCPATH)check_matrix_utils.h
	if [ ! -d $(OUTPATH) ]; then mkdir $(OUTPATH); fi
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OUTPATH)*.o $(OUTPATH)*.gcno $(OUTPATH)*.gcov $(OUTPATH)*.gcda $(OUTPATH)*.lastbuildstate *.exe
