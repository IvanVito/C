#ifndef _S21_SPRINTF_INTERNAL_H
#define _S21_SPRINTF_INTERNAL_H

#include <stdarg.h>
#include <stdbool.h>

#include "s21_charint.h"
#include "s21_string.h"

typedef struct s21_token {
  int width;
  unsigned int precision;
  char specifier;
  char p_sym;               // e or E for float/a or A for hex
  bool left_justify : 1,    // flag -
      sign_pos : 1,         // flag +
      sign_spc : 1,         // flag (space)
      alt_form : 1,         // flag #
      zfill : 1,            // flag 0
      len_long : 1,         // length l
      len_short : 1,        // length h
      len_long_double : 1,  // length L
      prec_default : 1,     // is precision not specified?
      exp_null : 1,         // is exponent of double equals zero?
      exp_max : 1,          // is exponent of double equals max?
      frac_not_null : 1,    // is any bit of fraction equals 1?
      f_short : 1,          // is g specifier?
      f_scient : 1,         // is scientific form for float?
      sign : 1;             // true for negative
} s21_token;

#define FRACTION_SIZE ((size_t)128)

#define FRACTION_RANGE(i) ((i) >= 0 && (i) < (long long)FRACTION_SIZE)
#define FRACTION_NUM(i) (FRACTION_RANGE(i) ? fraction[i] : 0)
#define FRACTION_CHAR(i) ('0' + FRACTION_NUM(i))

/******************************************************************************/
/*                              SPRINTF UTIL                                  */
/******************************************************************************/

unsigned long long s21_sprintf_get_number(const char **format_cur);

void s21_sprintf_write_byte(char **str_cur, int *result, int symbol);
void s21_sprintf_write_widechar(char **str_cur, int *result, wchar_t symbol);
void s21_sprintf_write_string(char **str_cur, int *result, const char *str);
void s21_sprintf_write_widestring(char **str_cur, int *result, wchar_t *str);
void s21_sprintf_write_unumber(char **str_cur, int *result,
                               unsigned long long value, unsigned long base,
                               char a_char, int precision);
void s21_sprintf_write_number(char **str_cur, int *result, long long value,
                              unsigned long base, char a_char, int precision);

void s21_sprintf_fill(char **str_cur, int *result, int symbol, int width);
void s21_sprintf_fill_start(char **str_cur, int *result, const s21_token *token,
                            int count);
void s21_sprintf_fill_sign(char **str_cur, int *result, const s21_token *token);
void s21_sprintf_fill_zero(char **str_cur, int *result, const s21_token *token,
                           int count);
void s21_sprintf_fill_end(char **str_cur, int *result, const s21_token *token,
                          int count);

/******************************************************************************/
/*                               TOKEN HANDLERS                               */
/******************************************************************************/

void s21_token_make(const char **format_cur, s21_token *token, va_list args);
void s21_token_flags(const char **format_cur, s21_token *token);
void s21_token_width(const char **format_cur, s21_token *token, va_list args);
void s21_token_preci(const char **format_cur, s21_token *token, va_list args);
void s21_token_length(const char **format_cur, s21_token *token);
void s21_token_specifier(const char **format_cur, s21_token *token);

void s21_token_write(char **str_cur, int *result, va_list args,
                     s21_token *token);

/******************************************************************************/
/*                               VALUE HANDLERS                               */
/******************************************************************************/

void s21_sprintf_save_count(const int result, va_list args);

void s21_sprintf_char_write(char **str_cur, int *result, va_list args,
                            const s21_token *token);

void s21_sprintf_string_write(char **str_cur, int *result, va_list args,
                              const s21_token *token);
size_t s21_sprintf_string_count_long(wchar_t *value);

void s21_sprintf_int_write(char **str_cur, int *result, va_list args,
                           s21_token *token);
int s21_sprintf_int_count(const s21_token *token, long value);

void s21_sprintf_uint_write(char **str_cur, int *result, va_list args,
                            s21_token *token);
int s21_sprintf_uint_count(const s21_token *token, unsigned long value,
                           int base);

void s21_sprintf_pointer_write(char **str_cur, int *result, va_list args,
                               const s21_token *token);
int s21_sprintf_pointer_count(const s21_token *token, unsigned long value);

/******************************************************************************/
/*                                   FLOATS                                   */
/******************************************************************************/

void s21_sprintf_float_write(char **str_cur, int *result, va_list args,
                             s21_token *token);
int s21_sprintf_float_count(const s21_token *token, int e_decimal);

void s21_sprintf_float_extract(va_list args, s21_token *token, char *fraction,
                               int *e_decimal);
void s21_sprintf_float_prepare(s21_token *token, char *fraction,
                               int *e_decimal);

void s21_write_float_basic(char **str_cur, int *result, const s21_token *token,
                           char *fraction, int e_decimal);

#endif