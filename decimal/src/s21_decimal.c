#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal_op.h"

// CODE TRASHCAN

/* who tf did this????? */
// int check_sign(s21_decimal bcd_1, s21_decimal bcd_2) {
//   int count_sig = 0;
//   if (!(s21_is_set_bit(&bcd_2, 127) && s21_is_set_bit(&bcd_1, 127)) &&
//       (s21_is_set_bit(&bcd_2, 127) || s21_is_set_bit(&bcd_1, 127))) {
//     s21_is_set_bit(&bcd_2, 127) ? s21_unset_bit(&bcd_2, 127)
//                                 : s21_unset_bit(&bcd_1, 127);
//     count_sig++;
//   }
//   return count_sig;
// }

// int mask_full(s21_decimal copy_res) {
//   s21_decimal string = {0}, max_bcd = {0};
//   int res = 0;
//   for (int i = 0; i < DECIMAL_MANT; i++) s21_set_bit(&string, i);
//   s21_from_dec_to_bcd(&string, &max_bcd);
//   res = s21_is_greater_mod(copy_res, max_bcd);
//   return res;
// }

// is this method so needful???
size_t s21_bcd_rank_get(s21_bcd *bcd) {
  size_t number_i = BCD_NUMSIZE;
  while (number_i > 0 && s21_bcd_num_get(bcd, number_i - 1)) number_i--;
  return number_i;
}

// this one looks too overloaded
void examination(s21_bcd *bcd_1, s21_bcd *bcd_2, int *reduction, int *degree_1,
                 int *degree_2) {
  if (*degree_1 > *degree_2 && *degree_1 > 0 && *degree_2 > 0) {
    while (*degree_1 >= 0 && *reduction > 0 && *degree_1 != *degree_2) {
      // s21_bank_rounding(0, bcd_1);
      s21_bcd_round_bank_limited(bcd_1, 0);
      (*degree_1)--;
      (*reduction)--;
    }
  } else if (*degree_1<*degree_2 && * degree_1> 0 && *degree_2 > 0) {
    while (*degree_2 >= 0 && *reduction > 0 && *degree_1 != *degree_2) {
      // s21_bank_rounding(0, bcd_2);
      s21_bcd_round_bank_limited(bcd_2, 0);
      (*degree_2)--;
      (*reduction)--;
    }
  } else {
    while (*degree_1 > 1 && *degree_2 > 1 && *reduction > 2) {
      // s21_bank_rounding(0, bcd_1);
      s21_bcd_round_bank_limited(bcd_1, 0);
      (*degree_1)--;
      // s21_bank_rounding(0, bcd_2);
      s21_bcd_round_bank_limited(bcd_2, 0);
      (*degree_2)--;
      *reduction -= 2;
    }
  }
  if (*reduction == 1 && (bcd_1->bits[0] & 15) >= (bcd_2->bits[0] & 15)) {
    // s21_bank_rounding(0, bcd_2);
    s21_bcd_round_bank_limited(bcd_2, 0);
    (*degree_2)--;
  } else {
    // s21_bank_rounding(0, bcd_1);
    s21_bcd_round_bank_limited(bcd_1, 0);
    (*degree_1)--;
  }
}

/* REWRITE IT FROM SCRATCH PLS */
// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int error = 2, count_sig = 0, degree_1 = 0, remaind = 0, value = 0,
//       degree_2 = 0, reduction = 0, ranks_1 = 0, ranks_2 = 0;
//   s21_decimal str_1 = {0}, str_2 = {0}, copy_res = {0};
//   s21_bcd bcd_1 = {0}, bcd_2 = {0}, bcd_remaind = {0};
//   copy_res = *result;
//   s21_dec2bcd(&value_1, &bcd_1);
//   s21_dec2bcd(&value_2, &bcd_2);
//   ranks_1 = s21_bcd_rank_get(&bcd_1);
//   ranks_2 = s21_bcd_rank_get(&bcd_2);
//   count_sig = s21_bit_get(bcd_1.bits, 255) != s21_bit_get(bcd_2.bits, 255);
//   reduction = (ranks_1 + ranks_2) - BCD_NUMSIZE;
//   degree_1 = s21_take_degree(&bcd_1);
//   degree_2 = s21_take_degree(&bcd_2);
//   if (reduction > 1)
//     examination(&bcd_1, &bcd_2, &reduction, &degree_1, &degree_2);
//   if (reduction <= 1) {
//     int bcd_degree = degree_1 + degree_2;
//     if (bcd_degree < BCD_NUMSIZE) {
//       for (int i = 0; i < DECIMAL_MANT_BCD; i += 4) {
//         int mask_1 = (bcd_1.bits[i / BITS_IN_INT] >> (i % BITS_IN_INT)) & 15;
//         remaind = 0;
//         for (int j = 0; j < DECIMAL_MANT_BCD; j += 4) {
//           int mask_2 = (bcd_2.bits[j / BITS_IN_INT] >> (j % BITS_IN_INT)) &
//           15; value = (mask_1 * mask_2 + remaind) % 10; remaind = (mask_1 *
//           mask_2 + remaind) / 10; str_2.bits[j / BITS_IN_INT] |= (value <<
//           j); if ((((remaind != 0) && (str_2.bits[3] >> 16) & 15) != 0)) {
//             // s21_bank_rounding(remaind, &str_2);
//             s21_bcd_round_bank_limited(&str_2, remaind);
//             bcd_degree--;
//             remaind = 0;
//           }
//         }
//         for (int count = 0; count < i; count += 4) s21_mult_10(&str_2);
//         remaind = s21_add_without_bcd(&str_1, &str_2, &copy_res);
//         if (((remaind != 0) && (copy_res.bits[3] >> 16) & 15) != 0) {
//           // s21_bank_rounding(remaind, &copy_res);
//           s21_bcd_round_bank_limited(&copy_res, remaind);
//           bcd_degree--;
//         }
//         str_1 = copy_res;
//         for (int z = 0; z < 4; z++) {
//           str_2.bits[z] = 0;
//           copy_res.bits[z] = 0;
//         }
//         error = mask_full(str_1);
//         s21_give_degree(bcd_degree, &str_1);
//         if (count_sig == 1) s21_set_bit(&str_1, 127);
//       }

//       s21_from_bcd_to_dec(&str_1, result);
//     }
//   } else
//     error = 1;
//   return error;
// }

// BAD
// int s21_floor(s21_decimal value, s21_decimal *result) {
//   if (!result) return 1;
//   // s21_print_binary(&value);
//   if (s21_is_set_bit(&value, 127) == 0) {
//     s21_truncate(value, result);
//   } else {
//     s21_decimal bcd_value = {0}, bcd_minus = {1}, bcd_result = {0};
//     s21_truncate(value, result);
//     // s21_print_binary(result);
//     // s21_print_binary(&bcd_value);
//     s21_add_without_bcd(&bcd_value, &bcd_minus, &bcd_result);
//     // s21_from_bcd_to_dec(&bcd_result, result);
//     puts(s21_res_number_str(&bcd_result));
//   }
// }

/* speechless */
// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//   if (!dst || isinf(src) || isnan(src) || fabsf(src) >
//   79228162514264337593543950335.0) {
//     return OP_ERR;
//   } else if (0 < fabsf(src) && fabsf(src) < 1e-28) {
//     // s21_clear_decimal(dst);
//     return OP_ERR;
//   }
//   // s21_clear_decimal(dst);
//   // 500? why not 420 * 69 / 42 + 1337 - 1448?
//   char str[420 * 69 / 42 + 1337 - 1448] = {0};
//   int sign = 1;
//   sprintf(str, "%.100f", src); // ...
//   if (str[0] == '-') {
//     int len = strlen(str);
//     for (int i = 1; i < len; i++) {
//       str[i - 1] = str[i];
//     }
//     sign = -1;
//   }
//   s21_decimal bcd = {0};
//   int shift = 0;
//   int digitsBeforeDot = 0;
//   int flagOfDot = 0;
//   int flagOfZero = 0;
//   int i = strcspn(str, "123456789") + 7;
//   if (i - 7 == (int)strlen(str)) {
//     if (sign == -1) s21_set_bit(dst, 127);
//     return 0;
//   }
//   if ((int)strcspn(str, ".") > i) {
//     i = strcspn(str, ".") - 1;
//     i--;
//   } else if ((int)src == 0 && (int)strcspn(str, ".") <= i)
//     i--;
//   int temp_i = i;
//   while (i >= 0) {
//     if (str[i] == '.') {
//       flagOfDot = 1;
//       i--;
//       continue;
//     }
//     int number_from_str = 0;
//     if (i != temp_i) {
//       number_from_str = str[i] - '0';
//     } else {
//       int forRound = str[i + 1] - '0';
//       if (forRound > 4)
//         number_from_str = str[i] != '.' ? str[i] - '0' + 1 : str[i + 1] - '0'
//         + 1;
//       else
//         number_from_str = str[i] - '0';
//       if (number_from_str == 10) number_from_str--;
//     }
//     if (number_from_str != 0) flagOfZero = 1;
//     if (flagOfZero == 1) {
//       int bitMaskBCD = number_from_str | bcd.bits[shift / BITS_IN_INT] >>
//       (shift % BITS_IN_INT); bcd.bits[shift / BITS_IN_INT] |= bitMaskBCD <<
//       (shift % BITS_IN_INT); shift += 4;
//     }
//     if (!flagOfDot)
//       if (flagOfZero) digitsBeforeDot++;
//     i--;
//   }
//   if (flagOfDot) s21_give_degree(digitsBeforeDot, &bcd);
//   s21_from_bcd_to_dec(&bcd, dst);
//   if (sign == -1) s21_set_bit(dst, 127);
//   return 0;
// }

// Internals

void s21_bcd_round_bank_limited(s21_bcd *bcd_num, int remaind) {
  s21_bcd one = {0}, new_result = {0};
  if (s21_bcd_num_get(bcd_num, 0) % 2 == 0) {
    if (s21_bcd_num_get(bcd_num, 0) > 5) {
      one.bits[0] |= 1;
      s21_bcd_num_rshift(bcd_num);
      s21_bcd_add(bcd_num, &one, &new_result);
      *bcd_num = new_result;
    } else {
      s21_bcd_num_rshift(bcd_num);
    }
  } else {
    if (s21_bcd_num_get(bcd_num, 0) > 4) {
      one.bits[0] |= 1;
      s21_bcd_num_rshift(bcd_num);
      s21_bcd_add(bcd_num, &one, &new_result);
      *bcd_num = new_result;
    } else {
      s21_bcd_num_rshift(bcd_num);
    }
  }
  s21_bcd_num_set(bcd_num, BCD_NUMSIZE - 1, remaind);

  int32_t exp = s21_bcd_exp_get(bcd_num);
  if (exp > 0) exp--;  // not like this...
  s21_bcd_exp_set(bcd_num, exp);
}

void s21_bcd_normalize(s21_bcd *value_1, s21_bcd *value_2) {
  int exp_1 = s21_bcd_exp_get(value_1);
  int exp_2 = s21_bcd_exp_get(value_2);
  if (s21_bcd_num_get(value_1, BCD_NUMSIZE - 1) == 0 &&
      s21_bcd_num_get(value_2, BCD_NUMSIZE - 1) == 0) {
    if (exp_1 > exp_2) {
      while (exp_1 > exp_2 && s21_bcd_num_get(value_2, BCD_NUMSIZE - 1) == 0) {
        s21_bcd_num_lshift(value_2);
        exp_2++;
      }
      s21_bcd_exp_set(value_2, exp_2);
    } else {
      while (exp_1 < exp_2 && s21_bcd_num_get(value_1, BCD_NUMSIZE - 1) == 0) {
        s21_bcd_num_lshift(value_1);
        exp_1++;
      }
      s21_bcd_exp_set(value_1, exp_1);
    }
  }
  if (exp_1 > exp_2) {
    while (exp_1 > exp_2) {
      s21_bcd_num_rshift(value_1);
      exp_1--;
    }
    s21_bcd_exp_set(value_1, exp_1);
  } else if (exp_1 < exp_2) {
    while (exp_1 < exp_2) {
      s21_bcd_num_rshift(value_2);
      exp_2--;
    }
    s21_bcd_exp_set(value_2, exp_2);
  }
}

int s21_bcd_cmp_eq(s21_bcd *bcd_1, s21_bcd *bcd_2) {
  int result = 1;
  s21_bcd_normalize(bcd_1, bcd_2);
  if (s21_bit_get(bcd_1->bits, 255) != s21_bit_get(bcd_2->bits, 255))
    result = 0;
  for (size_t num_i = 0; result == 1 && num_i < BCD_NUMSIZE; ++num_i) {
    if (s21_bcd_num_get(bcd_1, num_i) != s21_bcd_num_get(bcd_2, num_i))
      result = 0;
  }
  return result;
}

int s21_bcd_cmp_grt(s21_bcd *bcd_1, s21_bcd *bcd_2) {
  s21_bcd_normalize(bcd_1, bcd_2);
  int result = 0, exit = 0;
  int sign_1 = 1, sign_2 = 1;
  if (s21_bit_get(bcd_1->bits, 255)) sign_1 = -1;
  if (s21_bit_get(bcd_2->bits, 255)) sign_2 = -1;
  for (size_t num_i = BCD_NUMSIZE; result == 0 && exit == 0 && num_i > 0;
       --num_i) {
    int num_1 = s21_bcd_num_get(bcd_1, num_i - 1);
    int num_2 = s21_bcd_num_get(bcd_2, num_i - 1);
    if (num_1 * sign_1 > num_2 * sign_2)
      result = 1;
    else if (num_1 * sign_1 < num_2 * sign_2)
      exit = 1;
  }
  return result;
}

int s21_bcd_add(s21_bcd *bcd_1, s21_bcd *bcd_2, s21_bcd *result) {
  int remainder = 0, sign_remainder = 1;
  int sign_1 = s21_bit_get(bcd_1->bits, 255) ? -1 : 1;
  int sign_2 = s21_bit_get(bcd_2->bits, 255) ? -1 : 1;
  if (sign_1 == -1) {
    if (sign_2 == -1)
      sign_1 = 1, sign_2 = 1;
    else
      sign_remainder = -1;
    s21_bit_set(result->bits, 255, 1);
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
    s21_bcd_num_set(result, num_i, add);
  }
  return remainder;
}

// Arithmetic Operators

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int remaind = 0, error = 0;
  s21_bcd bcd_1 = {0}, bcd_2 = {0}, result_bcd = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  s21_bcd_normalize(&bcd_1, &bcd_2);
  s21_bcd_exp_set(&result_bcd, s21_bcd_exp_get(&bcd_1));
  {
    s21_bcd bcd_1_abs = bcd_1, bcd_2_abs = bcd_2;
    s21_bit_set(bcd_1_abs.bits, 255, 0);
    s21_bit_set(bcd_2_abs.bits, 255, 0);
    if (s21_bcd_cmp_grt(&bcd_2_abs, &bcd_1_abs) != 0) {
      s21_bcd temp = {0};
      temp = bcd_1, bcd_1 = bcd_2, bcd_2 = temp;
    }
  }

  remaind = s21_bcd_add(&bcd_1, &bcd_2, &result_bcd);

  if (remaind > 0 && s21_bcd_exp_get(&result_bcd) == 1) {  // 1???
    s21_bcd_round_bank_limited(&result_bcd, remaind);
    remaind = 0;
  }
  if (remaind != 0) error = 1;  // TODO errors 1 and 2
  if (error == 0) {
    s21_bcd copy_result = result_bcd;
    for (int i = 0; i < 4; i++) result_bcd.bits[i] = 0;
    error = s21_bcd2dec(&copy_result, result);
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_bit_flip(value_2.bits, 127);
  int error = s21_add(value_1, value_2, result);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_bcd bcd_1 = {0}, bcd_2 = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  return s21_bcd_cmp_eq(&bcd_1, &bcd_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_bcd bcd_1 = {0}, bcd_2 = {0};
  s21_dec2bcd(&value_1, &bcd_1);
  s21_dec2bcd(&value_2, &bcd_2);
  return s21_bcd_cmp_grt(&bcd_1, &bcd_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_greater_or_equal(value_1, value_2));
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

// Convertors and parsers

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return OP_ERR;
  uint32_t val = (uint32_t)src;
  if (src < 0) {
    s21_bit_set(dst->bits, 127, 1);
    val = ~val + 1;
  }
  dst->bits[0] = val;
  return OP_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  // TODO: rewrite this later
  int error = OP_OK, sign = s21_bit_get(src.bits, 127);
  for (size_t i = 31; error == OP_OK && i < DEC_MANT_BITSIZE; i++)
    if (s21_bit_get(src.bits, i)) error = OP_ERR;
  for (size_t i = 0; i < DEC_MANT_BITSIZE; i++)
    if (s21_bit_get(src.bits, i)) *dst += pow(2, i);  // ????????
  if (sign) *dst *= -1;
  // s21_print_binary(&src);
  // printf("%d\n", *dst);
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  s21_bcd bcd = {0};
  s21_dec2bcd(&value, &bcd);
  int degree = s21_bcd_exp_get(&bcd);
  for (int i = 0; i < degree; i++) s21_bcd_num_rshift(&bcd);
  s21_bcd_exp_set(&bcd, 0);
  s21_bcd2dec(&bcd, result);
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  *result = value;
  s21_bit_flip(result->bits, 127);
  return 0;
}

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
//     return 3;

//   int error = 0;
//   s21_decimal bcd_1 = {0}, bcd_2 = {0}, copy_result = {0};
//   s21_from_dec_to_bcd(&value_1, &bcd_1);
//   s21_from_dec_to_bcd(&value_2, &bcd_2);
//   int exp = 0;
//   // TODO

//   return error;
// }

// int main(void) { return 0; }