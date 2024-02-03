CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
SOURCES=s21_cat.c
OBJECTS=$(SOURCES:.c=.o)
s21_cat: s21_cat.o
		$(CC) s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c
		$(CC) $(CFLAGS) s21_cat.c

clean:
		rm -rf s21_cat.o s21_cat
rebuild: clean
