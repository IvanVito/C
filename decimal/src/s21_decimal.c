#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal_op.h"

// Internals

void s21_sprintf_write(char *str, s21_bcd *bcd, float *is_only_integer,
                       float *is_only_float, float src, int *degree) {
  int index_e = strcspn(str, "e");
  *degree = str[index_e + 3] - '0';
  *degree += (str[index_e + 2] - '0') * 10;
  *degree *= str[index_e + 1] == '-' ? -1 : 1;
  int i = 7;
  bool flag_of_zero = false;
  int temp_degree = *degree;
  if (src - *is_only_integer == 0.0F) {
    *is_only_integer = 1;
    flag_of_zero = true;
    i = temp_degree + 1;
  } else if (*is_only_integer == 0 && src - *is_only_integer != 0.0F) {
    *is_only_float = 1;
    if (*degree <= -23) {
      int width = 28 + *degree;
      sprintf(str, "%.*e", width, src);
      i = width + 1;
    }
  }
  for (uint32_t shift = 0; i >= 0 && shift < BCD_NUMSIZE; i--) {
    if (i == 1) continue;
    int number_from_str = str[i] - '0';
    if (*is_only_integer == 1 && temp_degree >= 7) {
      number_from_str = 0;
      temp_degree--;
    }
    if (number_from_str != 0) flag_of_zero = true;
    if (flag_of_zero) {
      s21_bcd_num_set(bcd, shift, number_from_str);
      ++shift;
    }
  }
}

// Arithmetic Operators

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int remaind = 0, error = 0;
  s21_bcd bcd_1 = {0}, bcd_2 = {0}, result_bcd = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  s21_bcd_normalize(&bcd_1, &bcd_2);
  s21_bcd_exp_set(&result_bcd, s21_bcd_exp_get(&bcd_1));
  if (s21_bcd_cmp_abs(&bcd_2, &bcd_1) > 0) {
    s21_bcd temp = bcd_1;
    bcd_1 = bcd_2, bcd_2 = temp;
  }
  remaind = s21_bcd_add(&bcd_1, &bcd_2, &result_bcd);
  if (remaind > 0 && s21_bcd_exp_get(&result_bcd) > 0)
    s21_bcd_round_bank_limited(&result_bcd, remaind);
  s21_bcd copy_result = result_bcd;
  s21_bit_range_set(result_bcd.bits, 0, BCD_BITSIZE, 0);
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  error = s21_bcd2dec(&copy_result, result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_bit_flip(value_2.bits, DEC_BITSIZE - 1);
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  int error = s21_add(value_1, value_2, result);
  return error;
}

// TODO: for removal

// int s21_check_rank(s21_bcd *bcd) {
//   int ranks = 0;
//   for (int shift = BCD_NUMSIZE; shift >= 0 && ranks == 0; shift -= 1)
//     if (s21_bcd_num_get(bcd, shift) != 0) ranks = shift + 1;
//   return ranks;
// }

// int reduce_rank(s21_bcd *bcd, int bcd_degree) {
//   int ranks = s21_check_rank(bcd);
//   while ((bcd_degree > 0) && (ranks > 29)) {
//     s21_bcd_round_bank_limited(bcd, 0);
//     bcd_degree--;
//     ranks--;
//   }
//   return bcd_degree;
// }

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  int error = CALC_OK;
  s21_bcd bcd_1 = {0}, bcd_2 = {0}, str_1 = {0}, str_2 = {0}, bcd_res = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  s21_bcd_shrink(&bcd_1);
  s21_bcd_shrink(&bcd_2);
  int degree_1 = s21_bcd_exp_get(&bcd_1);
  int degree_2 = s21_bcd_exp_get(&bcd_2);
  int bcd_degree = degree_1 + degree_2;
  for (size_t i = 0; i < BCD_NUMSIZE; i += 1) {
    int mask_1 = s21_bcd_num_get(&bcd_1, i);
    int remaind = 0;
    for (size_t j = 0; j < BCD_NUMSIZE; j += 1) {
      int mask_2 = s21_bcd_num_get(&bcd_2, j);
      int value = (mask_1 * mask_2 + remaind) % 10;
      remaind = (mask_1 * mask_2 + remaind) / 10;
      s21_bcd_num_set(&str_2, j, value);
    }
    for (size_t count = 0; count < i; count += 1) s21_bcd_num_lshift(&str_2);
    remaind = s21_bcd_add(&str_1, &str_2, &bcd_res);
    if (remaind != 0 && s21_bcd_num_get(&bcd_res, BCD_NUMSIZE) != 0 &&
        bcd_degree != 0) {
      s21_bcd_round_bank_limited(&bcd_res, remaind);
      bcd_degree--;
    }
    str_1 = bcd_res;
    s21_bit_range_set(str_2.bits, 0, BCD_BITSIZE, 0);
    s21_bit_range_set(bcd_res.bits, 0, BCD_BITSIZE, 0);
  }
  // bcd_degree = reduce_rank(&str_1, bcd_degree);
  // error = cmp_max_bcd(str_1);
  // if (bcd_degree > 28) error = 2;
  s21_bcd_exp_set(&str_1, bcd_degree);
  if (s21_bit_get(bcd_2.bits, 255) != (s21_bit_get(bcd_1.bits, 255)))
    s21_bit_set(str_1.bits, 255, 1);
  if (error == 0) {
    error = s21_bcd2dec(&str_1, result);
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
    return CALC_EDIVZ;
  if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0)
    return CALC_OK;

  int error = CALC_OK;
  s21_bcd bcd_1 = {0}, bcd_2 = {0}, bcd_result = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  int exp_ord = 0;
  while (s21_bcd_cmp_abs(&bcd_1, &bcd_2) < 0) {
    s21_bcd_mul10(&bcd_1);
    exp_ord++;
  }
  while (s21_bcd_cmp_abs(&bcd_1, &bcd_2) >= 0) {
    s21_bcd_mul10(&bcd_2);
    exp_ord--;
  }
  s21_bcd_div10(&bcd_2);
  s21_bit_set(bcd_1.bits, BCD_BITSIZE - 1, 0);
  s21_bit_set(bcd_2.bits, BCD_BITSIZE - 1, 1);
  for (size_t num_i = BCD_NUMSIZE; num_i > 0; --num_i) {
    uint32_t new_num = 0;
    while (s21_bcd_cmp_abs(&bcd_1, &bcd_2) >= 0) {
      s21_bcd_normalize(&bcd_1, &bcd_2);
      s21_bcd_add(&bcd_1, &bcd_2, &bcd_1);
      new_num++;
    }
    s21_bcd_num_set(&bcd_result, num_i - 1, new_num);
    s21_bcd_div10(&bcd_2);
    ++exp_ord;
  }
  uint32_t sign_1 = s21_bit_get(value_1.bits, DEC_BITSIZE - 1);
  uint32_t sign_2 = s21_bit_get(value_2.bits, DEC_BITSIZE - 1);
  uint32_t sign = sign_1 != sign_2 ? 1 : 0;
  if (exp_ord < 0) error = sign != 0 ? CALC_ESMALL : CALC_ELARGE;
  if (error == CALC_OK) {
    s21_bit_set(bcd_result.bits, BCD_BITSIZE - 1, sign);
    s21_bcd_exp_set(&bcd_result, exp_ord);
    s21_bcd_shrink(&bcd_result);
    error = s21_bcd2dec(&bcd_result, result);
  }
  return error;
}

// Comparison Operators

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_decimal_cmp(value_1, value_2) == 0 ? CMP_TRUE : CMP_FALSE;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_decimal_cmp(value_1, value_2) != 0 ? CMP_TRUE : CMP_FALSE;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_decimal_cmp(value_1, value_2) > 0 ? CMP_TRUE : CMP_FALSE;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_decimal_cmp(value_1, value_2) >= 0 ? CMP_TRUE : CMP_FALSE;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_decimal_cmp(value_1, value_2) < 0 ? CMP_TRUE : CMP_FALSE;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_decimal_cmp(value_1, value_2) <= 0 ? CMP_TRUE : CMP_FALSE;
}

// Convertors and parsers

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return OP_ERR;
  s21_bit_range_set(dst->bits, 0, DEC_BITSIZE, 0);
  uint32_t val = (uint32_t)src;
  if (src < 0) {
    s21_bit_set(dst->bits, DEC_BITSIZE - 1, 1);
    val = ~val + 1;
  }
  dst->bits[0] = val;
  return OP_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst || isinf(src) || isnan(src) || fabsf(src) > 7.9228163E28F) {
    return OP_ERR;
  }
  s21_bit_range_set(dst->bits, 0, DEC_BITSIZE, 0);
  if (0 < fabsf(src) && fabsf(src) < 1e-28) {
    return OP_ERR;
  }
  char str[32] = {0};
  sprintf(str, "%.6e", src);
  int sign = str[0] == '-' ? -1 : 1;
  if (str[0] == '-') {
    src = -src;
    sprintf(str, "%.6e", src);
  }
  float is_only_integer = trunc(src);
  float is_only_float = 0;
  s21_bcd bcd = {0};
  int degree = 0;
  s21_sprintf_write(str, &bcd, &is_only_integer, &is_only_float, src, &degree);
  if (is_only_integer == 1)
    degree = 0;
  else {
    degree -= 6;
    for (int i = strcspn(str, "e") - 1; str[i] == '0'; i--) degree++;
  }
  if (degree < -28) degree = -28;
  s21_bcd2dec(&bcd, dst);
  if (degree < 0) degree = -degree;
  s21_decimal_exp_set(dst, degree);
  if (sign == -1) s21_bit_set(dst->bits, 127, 1);
  return OP_OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = OP_OK;
  s21_truncate(src, &src);
  for (size_t i = 31; error == OP_OK && i < DEC_MANT_BITSIZE; i++)
    if (s21_bit_get(src.bits, i)) error = OP_ERR;
  for (size_t i = 0; error == OP_OK && i < 31; i++)
    *dst |= s21_bit_get(src.bits, i) << i;
  if (s21_bit_get(src.bits, DEC_BITSIZE - 1)) *dst *= -1;
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = s21_word_get(src.bits, 0, 96);  // TODO: BETTER TO REWRITE THIS
  short unsigned int degree = s21_decimal_exp_get(&src);
  *dst /= pow(10, degree);
  if (s21_bit_get(src.bits, 127) != 0) *dst *= -1;
  return OP_OK;
}

// Another functions

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return OP_ERR;
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  if (s21_bit_get(value.bits, DEC_BITSIZE - 1) == 0)
    s21_truncate(value, result);
  else {
    s21_decimal one = {{1, 0, 0, 0}}, temp_result = {0};
    s21_truncate(value, &temp_result);
    s21_sub(temp_result, one, result);
  }
  return OP_OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = OP_OK;
  s21_bcd one = {0}, new_result = {0}, bcd = {0};
  int degree = s21_decimal_exp_get(&value), sign = s21_bit_get(value.bits, 127);
  if (sign) s21_bit_set(value.bits, 127, 0);
  if (degree > 28 || degree == 0) error = OP_ERR;
  s21_dec2bcd(&value, &bcd);
  while (degree != 0) {
    if ((s21_bcd_num_get(&bcd, 0) >= 5)) {
      one.bits[0] |= 1;
      s21_bcd_num_rshift(&bcd);
      s21_bcd_add(&bcd, &one, &new_result);
      bcd = new_result;
      degree--;
    } else {
      s21_bcd_num_rshift(&bcd);
      degree--;
    }
  }
  if (sign) s21_bit_set(bcd.bits, 255, 1);
  s21_bcd_exp_set(&bcd, degree);
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  s21_bcd2dec(&bcd, result);
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return OP_ERR;
  s21_bcd bcd = {0};
  s21_dec2bcd(&value, &bcd);
  int degree = s21_bcd_exp_get(&bcd);
  for (int i = 0; i < degree; i++) s21_bcd_num_rshift(&bcd);
  s21_bcd_exp_set(&bcd, 0);
  s21_bit_range_set(result->bits, 0, DEC_BITSIZE, 0);
  s21_bcd2dec(&bcd, result);
  return OP_OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return OP_ERR;
  *result = value;
  s21_bit_flip(result->bits, DEC_BITSIZE - 1);
  return OP_OK;
}