#include "s21_decimal_op.h"

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

// Bitwise get/set methods

// Gets bit from specified index
uint32_t s21_bit_get(uint32_t *bits, size_t index) {
  uint32_t bit_mask = (uint32_t)1 << (index % INT_BITSIZE);
  return bits[index / INT_BITSIZE] & bit_mask ? 1 : 0;
}

// Sets bit at specified index
void s21_bit_set(uint32_t *bits, size_t index, uint32_t value) {
  bits[index / INT_BITSIZE] &= ~((uint32_t)1 << (index % INT_BITSIZE));
  bits[index / INT_BITSIZE] |= (value ? 1 : 0) << (index % INT_BITSIZE);
}

// Flips bit at specified index
void s21_bit_flip(uint32_t *bits, size_t index) {
  bits[index / INT_BITSIZE] ^= (uint32_t)1 << (index % INT_BITSIZE);
}

// Sets bit range with given value
void s21_bit_range_set(uint32_t *bits, size_t index, size_t bitsize,
                       uint32_t value) {
  for (size_t i = index; i < index + bitsize; ++i) s21_bit_set(bits, i, value);
}

// Gets binary value from specified index with specified bitsize
uint32_t s21_word_get(uint32_t *bits, size_t index, size_t bitsize) {
  uint32_t result = bits[index / INT_BITSIZE] >> (index % INT_BITSIZE);
  result &= 0xFFFFFFFF >> (INT_BITSIZE - bitsize);
  return result;
}

// Sets binary value at specified index with specified bitsize
void s21_word_set(uint32_t *bits, size_t index, size_t bitsize,
                  uint32_t value) {
  uint32_t bit_mask = 0xFFFFFFFF >> (INT_BITSIZE - bitsize);
  value &= bit_mask;
  bits[index / INT_BITSIZE] &= ~(bit_mask << (index % INT_BITSIZE));
  bits[index / INT_BITSIZE] |= value << (index % INT_BITSIZE);
}

// Leftshifts binary value at specified index
uint32_t s21_word_lshift(uint32_t *bits, size_t index, size_t bitsize) {
  uint32_t overflow = 0;
  for (size_t i = index; i < index + bitsize; ++i) {
    uint32_t val = s21_bit_get(bits, i);
    s21_bit_set(bits, i, overflow);
    overflow = val;
  }
  return overflow;
}

// Decimal operations

uint32_t s21_decimal_exp_get(s21_decimal *num) {
  return s21_word_get(num->bits, 112U, 8U);
}

void s21_decimal_exp_set(s21_decimal *num, uint32_t value) {
  s21_word_set(num->bits, 112U, 8U, value);
}

// BCD operations

uint32_t s21_bcd_exp_get(s21_bcd *bcd_num) {
  uint32_t value = s21_word_get(bcd_num->bits, BCD_MANT_BITSIZE, 4U);
  value += 10U * s21_word_get(bcd_num->bits, BCD_MANT_BITSIZE + 4U, 4U);
  return value;
}

void s21_bcd_exp_set(s21_bcd *bcd_num, uint32_t value) {
  s21_word_set(bcd_num->bits, BCD_MANT_BITSIZE, 4U, value % 10);
  s21_word_set(bcd_num->bits, BCD_MANT_BITSIZE + 4U, 4U, value / 10);
}

uint32_t s21_bcd_num_get(s21_bcd *bcd_num, size_t n_index) {
  if (n_index >= BCD_NUMSIZE) return 0U;
  return s21_word_get(bcd_num->bits, n_index * 4U, 4U);
}

void s21_bcd_num_set(s21_bcd *bcd_num, size_t n_index, uint32_t value) {
  s21_word_set(bcd_num->bits, n_index * 4U, 4U, value);
}

// Works like the multiplication by 10, returns overflow
uint32_t s21_bcd_num_lshift(s21_bcd *bcd_num) {
  uint32_t overflow = s21_bcd_num_get(bcd_num, BCD_NUMSIZE - 1U);
  for (size_t n_index = BCD_NUMSIZE - 1U; n_index > 0U; --n_index) {
    uint32_t val = s21_bcd_num_get(bcd_num, n_index - 1U);
    s21_bcd_num_set(bcd_num, n_index, val);
  }
  s21_bcd_num_set(bcd_num, 0U, 0U);
  return overflow;
}

// Works like the division by 10, returns remainder
uint32_t s21_bcd_num_rshift(s21_bcd *bcd_num) {
  uint32_t underflow = s21_bcd_num_get(bcd_num, 0U);
  for (size_t n_index = 0U; n_index < BCD_NUMSIZE - 1U; ++n_index) {
    uint32_t val = s21_bcd_num_get(bcd_num, n_index + 1U);
    s21_bcd_num_set(bcd_num, n_index, val);
  }
  s21_bcd_num_set(bcd_num, BCD_NUMSIZE - 1U, 0U);
  return underflow;
}

bool s21_bcd_not_null(s21_bcd *bcd_num) {
  bool result = false;
  for (size_t i = 0; !result && i < 7U; ++i)
    if (bcd_num->bits[i] != 0U) result = true;
  if ((bcd_num->bits[7] & 0xfff) != 0) result = true;
  return result;
}

// Conversion methods

/*
DECIMAL FORM
127                           96 95                            64
s0000000eeeeeeee0000000000000000 mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
63                            32 31                             0
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
BCD FORM
255                          224 223                          192
s0000000000000000000mmmmmmmmmmmm mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
191                          160 159                          128
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
127                           96 95                            64
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
63                            32 31                             0
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void s21_dec2bcd(s21_decimal *number, s21_bcd *bcd) {
  for (size_t i = 0; i < BCD_INTSIZE; ++i) bcd->bits[i] = 0;
  s21_decimal number_copy = *number;
  for (size_t shift = 0; shift < DEC_MANT_BITSIZE; shift++) {
    for (size_t value_i = 0; value_i < BCD_NUMSIZE; ++value_i) {
      uint32_t value = s21_bcd_num_get(bcd, value_i);
      if (value >= 5) s21_bcd_num_set(bcd, value_i, value + 3);
    }
    s21_word_lshift(bcd->bits, 0, BCD_MANT_BITSIZE);
    s21_bit_set(bcd->bits, 0,
                s21_bit_get(number_copy.bits, DEC_MANT_BITSIZE - 1));
    s21_word_lshift(number_copy.bits, 0, DEC_MANT_BITSIZE);
  }
  s21_bit_set(bcd->bits, 255U, s21_bit_get(number->bits, 127U));
  s21_bcd_exp_set(bcd, s21_decimal_exp_get(number));
}

int s21_bcd2dec(s21_bcd *bcd, s21_decimal *number) {
  int error = 0;
  s21_bcd bcd_copy = *bcd;
  for (size_t shift = 0; shift < DEC_MANT_BITSIZE; ++shift) {
    uint32_t remainder = 0;
    for (int value_i = BCD_NUMSIZE - 1; value_i >= 0; --value_i) {
      uint32_t value = s21_bcd_num_get(&bcd_copy, value_i);
      s21_bcd_num_set(&bcd_copy, value_i, (value >> 1) + remainder * 5);
      remainder = value & 1;
    }
    s21_bit_set(number->bits, shift, remainder);
  }
  if (s21_bcd_not_null(&bcd_copy)) {
    if (s21_bcd_exp_get(bcd) == 0)
      error = 1;
    else {
      bcd_copy = *bcd;
      s21_bcd_round_bank_limited(&bcd_copy, 0);
      error = s21_bcd2dec(&bcd_copy, number);
    }
  } else {
    s21_bit_set(number->bits, 127U, s21_bit_get(bcd->bits, 255U));
    s21_decimal_exp_set(number, s21_bcd_exp_get(bcd));
  }
  return error;
}

// printing functions

char *s21_dec2str(s21_decimal *number) {
  s21_bcd bcd = {0};
  s21_dec2bcd(number, &bcd);
  return s21_bcd2str(&bcd);
}

char *s21_bcd2str(s21_bcd *number) {
  static char result[100];
  char *result_cur = result;
  *(result_cur++) = s21_bit_get(number->bits, 255) ? '-' : '+';
  int num_end = 0;
  while (num_end < (int)BCD_NUMSIZE && s21_bcd_num_get(number, num_end) == 0)
    num_end++;
  int num_start = BCD_NUMSIZE - 1;
  while (num_start >= 0 && s21_bcd_num_get(number, num_start) == 0) num_start--;
  int exp = s21_bcd_exp_get(number);
  for (int i = num_start; i >= exp; --i)
    *(result_cur++) = s21_bcd_num_get(number, i) + '0';
  *(result_cur++) = ',';
  if (exp > 28) exp = 28;
  for (int i = exp - 1; i >= 0; --i)
    *(result_cur++) = s21_bcd_num_get(number, i) + '0';
  *result_cur = '\0';
  return result;
}

void s21_deciaml_bprint(s21_decimal *num) {
  for (int i = DEC_BITSIZE - 1; i >= 0; --i) {
    putchar(s21_bit_get(num->bits, i) ? '1' : '0');
    if (i != 0 && i % 4 == 0) printf(i % 32 == 0 ? " | " : " ");
  }
  putchar('\n');
}

void s21_bcd_bprint(s21_bcd *num) {
  for (int i = BCD_BITSIZE - 1; i >= 128; --i) {
    putchar(s21_bit_get(num->bits, i) ? '1' : '0');
    if (i != 128 && i % 4 == 0) printf(i % 32 == 0 ? " | " : " ");
  }
  putchar('\n');
  for (int i = 127; i >= 0; --i) {
    putchar(s21_bit_get(num->bits, i) ? '1' : '0');
    if (i != 0 && i % 4 == 0) printf(i % 32 == 0 ? " | " : " ");
  }
  putchar('\n');
}

#ifndef TEST_RUN

int main(void) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_bit_set(num_2.bits, 127, 1);
  s21_print_binary(&num_1);
  s21_print_binary(&num_2);
  s21_add(num_1, num_2, &res);
  s21_print_binary(&res);
  puts("");
  s21_dec2bcd(&res, &bcd);
  s21_print_binary(&bcd);
  puts(s21_bcd2str(&bcd));
  puts("-1152921498164396032,");
}

#endif