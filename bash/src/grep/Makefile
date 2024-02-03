CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -g
SOURCES=s21_grep.c
OBJECTS=$(SOURCES:.c=.o)
s21_grep:$(OBJECTS)
		$(CC) $(OBJECTS) -o s21_grep

s21_grep.o: s21_grep.c
		$(CC) $(CFLAGS) s21_grep.c

clean:
		rm -rf $(OBJECTS) 
rebuild: clean
