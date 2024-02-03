#ifndef _S21_DECIMAL_H
#define _S21_DECIMAL_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

// #define BITS_IN_INT (32)
// #define BYTES_IN_DECIMAL (4)
// #define DECIMAL_BITSIZE (BYTES_IN_DECIMAL * BITS_IN_INT)
// #define DECIMAL_MANT_BCD (DECIMAL_BITSIZE - 12)
// #define DECIMAL_MANT (DECIMAL_BITSIZE - BITS_IN_INT)

// Arithmetic Operators
#define CALC_OK ((int)0)
#define CALC_ELARGE ((int)1)
#define CALC_ESMALL ((int)2)
#define CALC_EDIVZ ((int)3)

// Comparison Operators
#define COMP_FALSE ((int)0)
#define COMP_TRUE ((int)1)

// Convertors, parsers and functions
#define OP_OK ((int)0)
#define OP_ERR ((int)1)

#define INT_BITSIZE (CHAR_BIT * sizeof(uint32_t))

#define DEC_INTSIZE ((size_t)4U)
#define DEC_BITSIZE (INT_BITSIZE * DEC_INTSIZE)
#define DEC_MANT_BITSIZE (DEC_BITSIZE - INT_BITSIZE)

typedef struct {
  uint32_t bits[DEC_INTSIZE];
} s21_decimal;

#define BCD_INTSIZE ((size_t)8U)
#define BCD_BITSIZE (INT_BITSIZE * BCD_INTSIZE)
#define BCD_MANT_BITSIZE ((size_t)236U)
#define BCD_NUMSIZE ((size_t)59U)

typedef struct {
  uint32_t bits[BCD_INTSIZE];
} s21_bcd;

int check_sign(s21_decimal bcd_1, s21_decimal bcd_2);
int mask_full(s21_decimal copy_res);
size_t s21_bcd_rank_get(s21_bcd *bcd);
void examination(s21_bcd *bcd_1, s21_bcd *bcd_2, int *reduction, int *degree_1,
                 int *degree_2);
void s21_clear_decimal(s21_decimal *result);

void s21_bcd_round_bank_limited(s21_bcd *bcd_num, int remaind);
void s21_bcd_normalize(s21_bcd *value_1, s21_bcd *value_2);
int s21_bcd_cmp_eq(s21_bcd *bcd_1, s21_bcd *bcd_2);
int s21_bcd_cmp_grt(s21_bcd *bcd_1, s21_bcd *bcd_2);
int s21_bcd_add(s21_bcd *bcd_1, s21_bcd *bcd_2, s21_bcd *result);

int s21_add(s21_decimal, s21_decimal, s21_decimal *);
int s21_sub(s21_decimal, s21_decimal, s21_decimal *);
int s21_mul(s21_decimal, s21_decimal, s21_decimal *);
int s21_div(s21_decimal, s21_decimal, s21_decimal *);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int, s21_decimal *);
int s21_from_float_to_decimal(float, s21_decimal *);
int s21_from_decimal_to_int(s21_decimal, int *);
int s21_from_decimal_to_float(s21_decimal, float *);

int s21_floor(s21_decimal, s21_decimal *);
int s21_round(s21_decimal, s21_decimal *);
int s21_truncate(s21_decimal, s21_decimal *);
int s21_negate(s21_decimal, s21_decimal *);

#endif
