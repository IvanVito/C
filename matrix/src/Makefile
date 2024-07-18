CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)
NAME = $(shell date)

ifeq ($(OS),Linux)
    det_OS = -lcheck -lrt -lpthread -lsubunit -lm
else
    det_OS = -lcheck -lpthread
endif

all: clean s21_matrix.a test gcov_report

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h
	rm .clang-format
	cppcheck --enable=all --suppress=MissingIncludeSystem *.c *.h

s21_matrix: 
	$(CC) $(CFLAGS) s21_matrix.c  s21_matrix.h  s21_matrix_extend.h s21_matrix_extend.c -o s21_matrix $(det_OS)

test: 
	$(CC) $(CFLAGS) --coverage all_test.c s21_matrix.c s21_matrix_extend.c -o test $(det_OS)

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a *.o
	ranlib s21_matrix.a

s21_matrix.o: s21_matrix.h s21_matrix.c s21_matrix_extend.h s21_matrix_extend.c
	$(CC) $(CFLAGS) s21_matrix.c  s21_matrix_extend.c -c 

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

clean:
	rm -rf report *.gc* *.o *.info *.a test.dSYM test s21_matrix.dSYM s21_matrix a.out

rebuild: clean all

push:
	git add s21_matrix.c s21_matrix.h all_test.c Makefile s21_matrix_extend.c s21_matrix_extend.h
	git commit -m "$(NAME)"
	git push origin main

.PHONY: all check test gcov_report clean rebuild