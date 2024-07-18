CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)
SRC_C = $(shell find . -name 's21_*.c')
SRC_O = $(SRC_C:.c=.o)
SRC_H = $(shell find . -name 's21_*.h')

TEST_C = $(shell find test_src -name 'test_*.c')
TEST_h = $(shell find test_src -name 'test_*.h')
ifeq ($(OS),Linux)
	TEST_LIBS = -lcheck -lm -lsubunit
else
	TEST_LIBS = -lcheck
endif

all: clean s21_string.a test gcov_report

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n $(SRC_C) $(SRC_H) $(TEST_C) $(TEST_H)
	clang-format -style=Google -i $(SRC_C) $(SRC_H) $(TEST_C) $(TEST_H)
	rm .clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem \
	                      --suppress=useStandardLibrary \
	                      --suppress=invalidPrintfArgType_uint \
	                        $(SRC_C)  $(SRC_H) \
	                        $(TEST_C) $(TEST_H)


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

s21_string.a: $(SRC_O)
	ar rcs s21_string.a $(SRC_O)
	ranlib s21_string.a

test: 
	$(CC) $(CFLAGS) --coverage $(TEST_C) $(SRC_C) -o test $(TEST_LIBS)

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info

clean:
	rm -rf report *.gcno *.gcda *.o *.info *.a test.dSYM test s21_string.dSYM \
	       vgcore.*

rebuild: clean all

.PHONY: all check test gcov_report clean rebuild
