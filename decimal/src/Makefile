SHELL:=/bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LIBS=-lcheck
LINUX=-lsubunit -lrt -lpthread -lm
OS:=$(shell uname -s)
LFLAGS=-fprofile-arcs -ftest-coverage
all: s21_decimal.a test gcov_report

s21_decimal.a: s21_decimal_comparing_functions.o s21_decimal_convertors.o s21_decimal_default_operations.o s21_decimal_rounders.o s21_decimal_support_functions.o
	ar rcs s21_decimal.a s21_decimal_comparing_functions.o s21_decimal_convertors.o s21_decimal_default_operations.o s21_decimal_rounders.o s21_decimal_support_functions.o
	cp s21_decimal.a libs21_decimal.a
	cp s21_decimal.a ls21_decimal.a
	ranlib libs21_decimal.a
	ranlib ls21_decimal.a

s21_decimal_comparing_functions.o: 
	$(CC) $(CFLAGS) -c c_files/s21_decimal_comparing_functions.c -o s21_decimal_comparing_functions.o

s21_decimal_convertors.o:
	$(CC) $(CFLAGS) -c c_files/s21_decimal_convertors.c -o s21_decimal_convertors.o

s21_decimal_default_operations.o:
	$(CC) $(CFLAGS) -c c_files/s21_decimal_default_operations.c -o s21_decimal_default_operations.o

s21_decimal_rounders.o:
	$(CC) $(CFLAGS) -c c_files/s21_decimal_rounders.c -o s21_decimal_rounders.o

s21_decimal_support_functions.o:
	$(CC) $(CFLAGS) -c c_files/s21_decimal_support_functions.c -o s21_decimal_support_functions.o

test: s21_decimal.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_decimal_tests.c c_files/*.c -o test.out $(LIBS)
	./test.out
else
	$(CC) $(CFLAGS) s21_decimal_tests.c c_files/*.c -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: gcov_test.info test
	./test.out
	lcov -t "Tests coverage" -o test.info -c -d .
	genhtml -o report/ gcov_test.info
	open report/index.html 

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "Report" -o gcov_test.info --no-external -c -d .

gcov_test: s21_decimal.a

ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_decimal_tests.c c_files/*.c -o gcov_test $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_decimal_tests.c c_files/*.c -o gcov_test $(LIBS) $(LINUX)
endif

gcov_test.gcda: gcov_test
	chmod +x *
	./gcov_test

open: gcov_report
	open report/index.html

rebuild: clean all

check:
	cppcheck *.c
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf *.o *.a *.info test.out gcov_test
	rm -rf report
	rm *.gcno
	rm *.gcda
	
