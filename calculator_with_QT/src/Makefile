CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)
TEST = s21_calculation.c s21_dijkstra.c s21_other_functions.c s21_parser.c s21_stack.c s21_validator.c all_test.c
NAME = $(shell date)

ifeq ($(OS),Linux)
    det_OS = -lcheck -lrt -lpthread -lsubunit -lm
    project = calculator
	inst = cd ui && qmake && make && make clean && rm Makefile && mkdir -p ../build && mv $(project) ../build/
else
    det_OS = -lcheck -lpthread
    project = calculator.app
	inst = cd ui && qmake && make && make clean && rm Makefile && mkdir -p ../build && mv $(project)/$(UI_BIN) ../build/
endif

all: dist gcov_report dvi

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h
	rm .clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	cp ../materials/linters/.clang-format ./ui
	clang-format -style=Google -n ./ui/*.cpp ./ui/*.h
	clang-format -style=Google -i ./ui/*.cpp ./ui/*.h
	rm ./ui/.clang-format

test: clean
	$(CC) $(CFLAGS) --coverage $(TEST) -o test $(det_OS)

install:
	$(inst)
	
gcc:
	$(CC) $(CFLAGS) -D GCC	s21*.c s21*.h -g $(det_OS)
	./a.out

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	make clean

clean:
	rm -rf *.gc* *.o *.info *.a test.dSYM test s21_smart_calc.dSYM s21_smart_calc.h.gch a.out build-calculator-Desktop_x86_darwin_generic_mach_o_64bit-Debug

reboot: clean 
	rm -rf report dist build

dvi:
	nano ./documentation.md

dist: reboot install
	mkdir -p dist
	cp -R ./build/$(project) ./dist/$(project)
	cp ./documentation.md ./dist/documentation.md
	cd ./dist && tar cvzf calculator.tgz *
	cd ./dist && rm -R $(project) documentation.md
	make clean	

unistall:
	rm -rf build

rebuild: reboot all

valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s ./test

push:
	git add *.c *.h Makefile
	git commit -m "$(NAME)"
	git push origin develop
