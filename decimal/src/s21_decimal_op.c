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
uint32_t s21_bit_get(const uint32_t *bits, size_t index) {
  uint32_t bit_mask = 1U << (index % INT_BITSIZE);
  return (bits[index / INT_BITSIZE] & bit_mask) ? 1U : 0U;
}

// Sets bit at specified index
void s21_bit_set(uint32_t *bits, size_t index, uint32_t value) {
  bits[index / INT_BITSIZE] &= ~(1U << (index % INT_BITSIZE));
  bits[index / INT_BITSIZE] |= (value ? 1 : 0) << (index % INT_BITSIZE);
}

// Flips bit at specified index
void s21_bit_flip(uint32_t *bits, size_t index) {
  bits[index / INT_BITSIZE] ^= 1U << (index % INT_BITSIZE);
}

// Sets bit range with given value
void s21_bit_range_set(uint32_t *bits, size_t index, size_t bitsize,
                       uint32_t value) {
  for (size_t i = index; i < index + bitsize; ++i) s21_bit_set(bits, i, value);
}

// Gets binary value from specified index with specified bitsize
uint32_t s21_word_get(const uint32_t *bits, size_t index, size_t bitsize) {
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

int s21_decimal_cmp(s21_decimal value_1, s21_decimal value_2) {
  s21_bcd bcd_1 = {0}, bcd_2 = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  return s21_bcd_cmp(&bcd_1, &bcd_2);
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

void s21_bcd_mul10(s21_bcd *bcd_num) {
  s21_bcd_shrink(bcd_num);
  uint32_t exp = s21_bcd_exp_get(bcd_num);
  if (exp != 0)
    s21_bcd_exp_set(bcd_num, exp - 1);
  else
    s21_bcd_num_lshift(bcd_num);
}

void s21_bcd_div10(s21_bcd *bcd_num) {
  s21_bcd_shrink(bcd_num);
  uint32_t exp = s21_bcd_exp_get(bcd_num);
  if (s21_bcd_num_get(bcd_num, 0) != 0)
    s21_bcd_exp_set(bcd_num, exp + 1);
  else
    s21_bcd_num_rshift(bcd_num);
}

// remove trailing zeroes
void s21_bcd_shrink(s21_bcd *bcd_num) {
  uint32_t exp = s21_bcd_exp_get(bcd_num);
  while (exp != 0 && s21_bcd_num_get(bcd_num, 0) == 0) {
    s21_bcd_num_rshift(bcd_num);
    exp--;
  }
  s21_bcd_exp_set(bcd_num, exp);
}

bool s21_bcd_not_null(s21_bcd *bcd_num) {
  bool result = false;
  for (size_t n_index = 0U; !result && n_index < BCD_NUMSIZE; ++n_index)
    result = s21_bcd_num_get(bcd_num, n_index) != 0;
  return result;
}

int s21_bcd_cmp(s21_bcd *bcd_1, s21_bcd *bcd_2) {
  s21_bcd_normalize(bcd_1, bcd_2);
  int result = 0;
  int sign_1 = s21_bit_get(bcd_1->bits, BCD_BITSIZE - 1) != 0 ? -1 : 1;
  int sign_2 = s21_bit_get(bcd_2->bits, BCD_BITSIZE - 1) != 0 ? -1 : 1;
  for (size_t num_i = BCD_NUMSIZE; result == 0 && num_i > 0; --num_i) {
    int num_1 = (int)s21_bcd_num_get(bcd_1, num_i - 1) * sign_1;
    int num_2 = (int)s21_bcd_num_get(bcd_2, num_i - 1) * sign_2;
    if (num_1 != num_2) result = num_1 > num_2 ? 1 : -1;
  }
  return result;
}

int s21_bcd_cmp_abs(const s21_bcd *bcd_1, const s21_bcd *bcd_2) {
  s21_bcd abcd_1 = *bcd_1, abcd_2 = *bcd_2;
  s21_bit_set(abcd_1.bits, BCD_BITSIZE - 1, 0);
  s21_bit_set(abcd_2.bits, BCD_BITSIZE - 1, 0);
  return s21_bcd_cmp(&abcd_1, &abcd_2);
}

int s21_bcd_add(s21_bcd *bcd_1, s21_bcd *bcd_2, s21_bcd *result) {
  s21_bcd result_new = {0};
  s21_bcd_exp_set(&result_new, s21_bcd_exp_get(bcd_1));
  int remainder = 0, sign_remainder = 1;
  int sign_1 = s21_bit_get(bcd_1->bits, BCD_BITSIZE - 1) ? -1 : 1;
  int sign_2 = s21_bit_get(bcd_2->bits, BCD_BITSIZE - 1) ? -1 : 1;
  if (sign_1 == -1) {
    if (sign_2 == -1)
      sign_1 = 1, sign_2 = 1;
    else
      sign_remainder = -1;
    s21_bit_set(result_new.bits, BCD_BITSIZE - 1, 1);
  }
  for (size_t num_i = 0; num_i < BCD_NUMSIZE; ++num_i) {
    int number_1 = s21_bcd_num_get(bcd_1, num_i);
    int number_2 = s21_bcd_num_get(bcd_2, num_i);
    int add = number_2 * sign_2 + remainder * sign_remainder;
    remainder = 0;
    if (abs(add) > number_1) {
      add += sign_remainder == -1 ? -10 : (sign_2 == -1 ? 10 : 0);
      remainder = sign_remainder == -1 || sign_2 == -1 ? -1 : 0;
    }
    add = abs(add + number_1 * sign_1);
    if (add > 9) remainder = add / 10, add = add % 10;
    s21_bcd_num_set(&result_new, num_i, add);
  }
  *result = result_new;
  return remainder;
}

void s21_bcd_normalize(s21_bcd *value_1, s21_bcd *value_2) {
  s21_bcd_shrink(value_1);
  s21_bcd_shrink(value_2);
  uint32_t exp_1 = s21_bcd_exp_get(value_1);
  uint32_t exp_2 = s21_bcd_exp_get(value_2);

  while (exp_1 > exp_2) {
    s21_bcd_num_lshift(value_2);
    exp_2++;
  }
  s21_bcd_exp_set(value_2, exp_2);
  while (exp_1 < exp_2) {
    s21_bcd_num_lshift(value_1);
    exp_1++;
  }
  s21_bcd_exp_set(value_1, exp_1);
}

void s21_bcd_round_bank_limited(s21_bcd *bcd_num, int overflow) {
  s21_bcd one = {0}, new_result = {0};
  one.bits[0] |= 1;
  if (s21_bcd_num_get(bcd_num, 0) % 2 == 0) {
    if (s21_bcd_num_get(bcd_num, 0) > 5) {
      s21_bcd_num_rshift(bcd_num);
      s21_bcd_add(bcd_num, &one, &new_result);
      *bcd_num = new_result;
    } else {
      s21_bcd_num_rshift(bcd_num);
    }
  } else {
    if (s21_bcd_num_get(bcd_num, 0) > 4) {
      s21_bcd_num_rshift(bcd_num);
      s21_bcd_add(bcd_num, &one, &new_result);
      *bcd_num = new_result;
    } else {
      s21_bcd_num_rshift(bcd_num);
    }
  }
  s21_bcd_num_set(bcd_num, BCD_NUMSIZE - 1, overflow);
  int32_t exp = s21_bcd_exp_get(bcd_num);
  if (exp > 0) exp--;
  s21_bcd_exp_set(bcd_num, exp);
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
  s21_bit_range_set(bcd->bits, 0, BCD_BITSIZE, 0);
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
  s21_bcd_shrink(bcd);
}

int s21_bcd2dec(const s21_bcd *bcd, s21_decimal *number) {
  int error = CALC_OK;
  s21_bit_range_set(number->bits, 0, DEC_BITSIZE, 0);
  s21_bcd bcd_cut = *bcd;
  if (s21_bcd_not_null(&bcd_cut)) {
    uint32_t exp = 0;
    while ((exp = s21_bcd_exp_get(&bcd_cut)) > 28U)
      s21_bcd_round_bank_limited(&bcd_cut, 0);
    if (!s21_bcd_not_null(&bcd_cut)) error = CALC_ESMALL;
  }
  s21_bcd_shrink(&bcd_cut);
  s21_bcd bcd_copy = bcd_cut;

  for (size_t shift = 0; error == CALC_OK && shift < DEC_MANT_BITSIZE;
       ++shift) {
    uint32_t remainder = 0;
    for (size_t value_i = BCD_NUMSIZE; value_i > 0; --value_i) {
      uint32_t value = s21_bcd_num_get(&bcd_copy, value_i - 1);
      s21_bcd_num_set(&bcd_copy, value_i - 1, (value >> 1) + remainder * 5);
      remainder = value & 1;
    }
    s21_bit_set(number->bits, shift, remainder);
  }
  if (s21_bcd_not_null(&bcd_copy)) {
    if (s21_bcd_exp_get(&bcd_cut) == 0)
      error = CALC_ELARGE;
    else {
      bcd_copy = bcd_cut;
      s21_bcd_round_bank_limited(&bcd_copy, 0);
      error = s21_bcd2dec(&bcd_copy, number);
    }
  } else {
    s21_bit_set(number->bits, 127U, s21_bit_get(bcd_cut.bits, 255U));
    s21_decimal_exp_set(number, s21_bcd_exp_get(&bcd_cut));
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
  for (int i = exp - 1; i >= 0; --i)
    *(result_cur++) = s21_bcd_num_get(number, i) + '0';
  *result_cur = '\0';
  return result;
}

// void s21_decimal_bprint(s21_decimal *num) {
//   for (int i = DEC_BITSIZE - 1; i >= 0; --i) {
//     putchar(s21_bit_get(num->bits, i) ? '1' : '0');
//     if (i != 0 && i % 4 == 0) printf(i % 32 == 0 ? " | " : " ");
//   }
//   putchar('\n');
// }

// void s21_bcd_bprint(s21_bcd *num) {
//   for (int i = BCD_BITSIZE - 1; i >= 128; --i) {
//     putchar(s21_bit_get(num->bits, i) ? '1' : '0');
//     if (i != 128 && i % 4 == 0) printf(i % 32 == 0 ? " | " : " ");
//   }
//   putchar('\n');
//   for (int i = 127; i >= 0; --i) {
//     putchar(s21_bit_get(num->bits, i) ? '1' : '0');
//     if (i != 0 && i % 4 == 0) printf(i % 32 == 0 ? " | " : " ");
//   }
//   putchar('\n');
// }
