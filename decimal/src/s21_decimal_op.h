#ifndef _S21_DECIMAL_OP_H
#define _S21_DECIMAL_OP_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

// Bitwise methods
uint32_t s21_bit_get(uint32_t *bits, size_t index);
void s21_bit_set(uint32_t *bits, size_t index, uint32_t value);
void s21_bit_flip(uint32_t *bits, size_t index);

uint32_t s21_word_get(uint32_t *bits, size_t index, size_t bitsize);
void s21_word_set(uint32_t *bits, size_t index, size_t bitsize, uint32_t value);
uint32_t s21_word_lshift(uint32_t *bits, size_t index, size_t bitsize);

// Decimal operations
uint32_t s21_decimal_exp_get(s21_decimal *num);
void s21_decimal_exp_set(s21_decimal *num, uint32_t value);

// BCD operations
uint32_t s21_bcd_exp_get(s21_bcd *bcd_num);
void s21_bcd_exp_set(s21_bcd *bcd_num, uint32_t value);
uint32_t s21_bcd_num_get(s21_bcd *bcd_num, size_t n_index);
void s21_bcd_num_set(s21_bcd *bcd_num, size_t n_index, uint32_t value);
uint32_t s21_bcd_num_lshift(s21_bcd *bcd_num);
uint32_t s21_bcd_num_rshift(s21_bcd *bcd_num);
bool s21_bcd_not_null(s21_bcd *bcd_num);

// Conversion methods
void s21_dec2bcd(s21_decimal *number, s21_bcd *bcd);
int s21_bcd2dec(s21_bcd *bcd, s21_decimal *number);

// printing functions
char *s21_dec2str(s21_decimal *number);
char *s21_bcd2str(s21_bcd *number);
#define s21_num2str(x) \
  _Generic((x), s21_decimal * : s21_dec2str, s21_bcd * : s21_bcd2str)(x)

void s21_deciaml_bprint(s21_decimal *num);
void s21_bcd_bprint(s21_bcd *num);
#define s21_print_binary(x)                \
  _Generic((x), s21_decimal *              \
           : s21_deciaml_bprint, s21_bcd * \
           : s21_bcd_bprint)(x)

#endif