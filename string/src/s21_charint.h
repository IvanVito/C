#ifndef _S21_CHARINT_H
#define _S21_CHARINT_H

#include <stddef.h>

void s21_charint_clear(char *value, size_t v_size);
void s21_charint_div2(char *value, size_t v_size);
char s21_charint_mul2(char *value, size_t v_size);
void s21_charint_add(char *dest, const char *source, size_t v_size);
void s21_charint_rshift(char *value, size_t v_size, char rval);
void s21_charint_lshift(char *value, size_t v_size, char lval);

#endif