CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)

ifeq ($(OS),Linux)
    det_OS = -lcheck -lrt -lpthread -lsubunit -lm
else
    det_OS = -lcheck
endif

all: clean decimal.a test gcov_report

check:
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h
	cppcheck --enable=all --suppress=MissingIncludeSystem *.c *.h

s21_decimal: 
	$(CC) $(CFLAGS) s21_decimal.c s21_decimal.h -o s21_decimal $(det_OS)

test: 
	$(CC) $(CFLAGS) -D TEST_RUN --coverage all_test.c s21_decimal.c s21_decimal_op.c -o test $(det_OS)
	./test

decimal.a: s21_decimal.o
	ar rcs s21_decimal.a *.o
	ranlib s21_decimal.a

s21_decimal.o: s21_decimal.h s21_decimal.c
	$(CC) $(CFLAGS) -D TEST_RUN s21_decimal.c -c 

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

clean:
	rm -rf report *.gc* *.o *.info *.a test.dSYM test s21_decimal.dSYM s21_decimal *.out

rebuild: clean all

.PHONY: all check test gcov_report clean rebuild