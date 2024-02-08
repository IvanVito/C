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
uint32_t s21_bit_get(const uint32_t *bits, size_t index);
void s21_bit_set(uint32_t *bits, size_t index, uint32_t value);
void s21_bit_flip(uint32_t *bits, size_t index);
void s21_bit_range_set(uint32_t *bits, size_t index, size_t bitsize,
                       uint32_t value);

uint32_t s21_word_get(const uint32_t *bits, size_t index, size_t bitsize);
void s21_word_set(uint32_t *bits, size_t index, size_t bitsize, uint32_t value);
uint32_t s21_word_lshift(uint32_t *bits, size_t index, size_t bitsize);

// Decimal operations
uint32_t s21_decimal_exp_get(s21_decimal *num);
void s21_decimal_exp_set(s21_decimal *num, uint32_t value);
int s21_decimal_cmp(s21_decimal value_1, s21_decimal value_2);

// BCD operations
uint32_t s21_bcd_exp_get(s21_bcd *bcd_num);
void s21_bcd_exp_set(s21_bcd *bcd_num, uint32_t value);
uint32_t s21_bcd_num_get(s21_bcd *bcd_num, size_t n_index);
void s21_bcd_num_set(s21_bcd *bcd_num, size_t n_index, uint32_t value);
uint32_t s21_bcd_num_lshift(s21_bcd *bcd_num);
uint32_t s21_bcd_num_rshift(s21_bcd *bcd_num);
void s21_bcd_mul10(s21_bcd *bcd_num);
void s21_bcd_div10(s21_bcd *bcd_num);
void s21_bcd_shrink(s21_bcd *bcd_num);
bool s21_bcd_not_null(s21_bcd *bcd_num);
int s21_bcd_cmp(s21_bcd *bcd_1, s21_bcd *bcd_2);
int s21_bcd_cmp_abs(const s21_bcd *bcd_1, const s21_bcd *bcd_2);
int s21_bcd_add(s21_bcd *bcd_1, s21_bcd *bcd_2, s21_bcd *result);
void s21_bcd_normalize(s21_bcd *value_1, s21_bcd *value_2);
void s21_bcd_round_bank_limited(s21_bcd *bcd_num, int overflow);
int cmp_max_bcd(s21_bcd bcd_res);
int s21_check_rank(s21_bcd *bcd);
int reduce_rank(s21_bcd *bcd, int bcd_degree);

// Conversion methods
void s21_dec2bcd(s21_decimal *number, s21_bcd *bcd);
int s21_bcd2dec(const s21_bcd *bcd, s21_decimal *number);

// printing functions
char *s21_dec2str(s21_decimal *number);
char *s21_bcd2str(s21_bcd *number);
#define s21_num2str(x) \
  _Generic((x), s21_decimal * : s21_dec2str, s21_bcd * : s21_bcd2str)(x)

void s21_decimal_bprint(s21_decimal *num);
void s21_bcd_bprint(s21_bcd *num);
#define s21_print_binary(x)                \
  _Generic((x), s21_decimal *              \
           : s21_decimal_bprint, s21_bcd * \
           : s21_bcd_bprint)(x)

#endif