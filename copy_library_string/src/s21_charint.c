#include "s21_charint.h"

#include <stddef.h>

#include "s21_string.h"

void s21_charint_clear(char *value, size_t v_size) {
  for (size_t i = 0; i < v_size; ++i) value[i] = '\0';
}

void s21_charint_div2(char *value, size_t v_size) {
  for (int i = v_size - 1; i >= 0; --i) {
    if (i != 0 && value[i - 1] & 1) value[i] += 10;
    value[i] >>= 1;
  }
}

char s21_charint_mul2(char *value, size_t v_size) {
  value[v_size - 1] <<= 1;
  for (int i = v_size - 1; i > 0; --i) {
    value[i - 1] <<= 1;
    if (value[i] >= 10) {
      value[i - 1] += value[i] / 10;
      value[i] %= 10;
    }
  }
  char overflow = value[0] / 10;
  value[0] %= 10;
  return overflow;
}

void s21_charint_add(char *dest, const char *source, size_t v_size) {
  for (int i = v_size - 1; i >= 0; --i) {
    dest[i] += source[i];
    if (i != 0 && dest[i] >= 10) {
      dest[i - 1] += dest[i] / 10;
      dest[i] %= 10;
    }
  }
}

void s21_charint_rshift(char *value, size_t v_size, char rval) {
  for (int i = v_size - 1; i > 0; --i) value[i] = value[i - 1];
  value[0] = rval;
}

void s21_charint_lshift(char *value, size_t v_size, char lval) {
  for (int i = 1; i < (int)v_size - 1; ++i)
    if (i != 0) value[i - 1] = value[i];
  value[v_size - 1] = lval;
}