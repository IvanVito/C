CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
OS = $(shell uname)


ifeq ($(OS),Linux)
    det_OS = -lcheck  -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif


all: clean s21_math.a test gcov_report


test: 
	$(CC) $(CFLAGS) --coverage all_test.c  s21_math_c.c -o test $(det_OS)

s21_math.o:  s21_math.h s21_math_c.c
	$(CC) $(CFLAGS)  s21_math_c.c -c 

s21_math.a: s21_math.o

	ar rcs s21_math.a *.o
	ranlib s21_math.a



gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h
	
	rm .clang-format

clean:
	rm -rf report *.gc* *.o *.info *.a test.dSYM test

rebuild: clean all

	
