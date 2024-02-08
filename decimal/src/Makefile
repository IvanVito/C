.POSIX:
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

LFLAGS = -lcheck
ifeq ($(shell uname),Linux)
	LFLAGS += -lcheck -lrt -lpthread -lsubunit -lm
endif

TEST_C = all_test.c
LIB_C = s21_decimal.c s21_decimal_op.c
LIB_H = $(LIB_C:.c=.h)
LIB_O = $(LIB_C:.c=.o)
CODE_CH = $(TEST_C) $(LIB_C) $(LIB_H)

all: clean s21_decimal.a test gcov_report

check:
	clang-format -style=Google -n $(CODE_CH)
	clang-format -style=Google -i $(CODE_CH)
	cppcheck --enable=all --suppress=missingIncludeSystem $(CODE_CH)

test: 
	$(CC) $(CFLAGS) --coverage $(TEST_C) $(LIB_C) -o $@ $(LFLAGS)
	./test

s21_decimal.a: $(LIB_O)
	ar rcs $@ $(LIB_O)
	ranlib $@

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

clean:
	rm -rf *.out *.o *.a test *.gc* *.info report *.dSYM

rebuild: clean all

.PHONY: all check test gcov_report clean rebuild