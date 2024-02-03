
#include "s21_sprintf_internal.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_charint.h"
#include "s21_string.h"

/******************************************************************************/
/*                              SPRINTF UTILS                                 */
/******************************************************************************/

unsigned long long s21_sprintf_get_number(const char **format_cur) {
  unsigned long long number = 0U;
  bool fin = false;
  while (**format_cur != 0 && !fin) {
    if (**format_cur >= '0' && **format_cur <= '9') {
      number *= 10;
      number += **format_cur - '0';
    } else
      fin = true;
    if (!fin) (*format_cur)++;
  }
  return number;
}

void s21_sprintf_write_byte(char **str_cur, int *result, int symbol) {
  **str_cur = symbol;
  (*str_cur)++;
  (*result)++;
}

void s21_sprintf_write_widechar(char **str_cur, int *result, wchar_t symbol) {
  mbstate_t state = {0};
  char out[MB_CUR_MAX];
  size_t count = wcrtomb(out, symbol, &state);
  if (count != (size_t)-1)
    for (size_t i = 0; i < count; ++i)
      s21_sprintf_write_byte(str_cur, result, out[i]);
  else
    *result = -1;
}

void s21_sprintf_write_string(char **str_cur, int *result, const char *str) {
  for (size_t i = 0; str[i] != '\0'; ++i)
    s21_sprintf_write_byte(str_cur, result, str[i]);
}

void s21_sprintf_write_widestring(char **str_cur, int *result, wchar_t *str) {
  for (size_t i = 0; str[i]; ++i)
    s21_sprintf_write_widechar(str_cur, result, str[i]);
}

void s21_sprintf_write_unumber(char **str_cur, int *result,
                               unsigned long long value, unsigned long base,
                               char a_char, int precision) {
  unsigned long long i_pow = 1;
  int i_prec = 1;
  while (value / i_pow > base - 1) {
    i_pow *= base;
    i_prec++;
  }
  if (value == 0) {
    i_pow = 0;
    i_prec = 0;
  }
  while (precision > i_prec) {
    s21_sprintf_write_byte(str_cur, result, '0');
    precision--;
  }
  while (i_pow != 0) {
    char num = (value / i_pow) % base;
    if (num >= 10)
      num = num - 10 + a_char;
    else
      num += '0';
    s21_sprintf_write_byte(str_cur, result, num);
    i_pow /= base;
  }
}

void s21_sprintf_write_number(char **str_cur, int *result, long long value,
                              unsigned long base, char a_char, int precision) {
  unsigned long long uvalue = value;
  if (value < 0) uvalue = (unsigned long long)(~value) + 1;
  s21_sprintf_write_unumber(str_cur, result, uvalue, base, a_char, precision);
}

void s21_sprintf_fill(char **str_cur, int *result, int symbol, int width) {
  for (int i = 0; i < width; ++i)
    s21_sprintf_write_byte(str_cur, result, symbol);
}

void s21_sprintf_fill_start(char **str_cur, int *result, const s21_token *token,
                            int count) {
  if (!token->left_justify && !token->zfill)
    s21_sprintf_fill(str_cur, result, ' ', token->width - count);
}

void s21_sprintf_fill_sign(char **str_cur, int *result,
                           const s21_token *token) {
  if (token->sign)
    s21_sprintf_write_byte(str_cur, result, '-');
  else if (token->sign_pos)
    s21_sprintf_write_byte(str_cur, result, '+');
  else if (token->sign_spc)
    s21_sprintf_write_byte(str_cur, result, ' ');
}

void s21_sprintf_fill_zero(char **str_cur, int *result, const s21_token *token,
                           int count) {
  if (token->zfill)
    s21_sprintf_fill(str_cur, result, '0', token->width - count);
}

void s21_sprintf_fill_end(char **str_cur, int *result, const s21_token *token,
                          int count) {
  if (token->left_justify)
    s21_sprintf_fill(str_cur, result, ' ', token->width - count);
}

/******************************************************************************/
/*                               TOKEN HANDLERS                               */
/******************************************************************************/

// %[flags][width][.precision][length]specifier.
void s21_token_make(const char **format_cur, s21_token *token, va_list args) {
  (*format_cur)++;
  s21_token_flags(format_cur, token);
  s21_token_width(format_cur, token, args);
  s21_token_preci(format_cur, token, args);
  s21_token_length(format_cur, token);
  s21_token_specifier(format_cur, token);
}

void s21_token_flags(const char **format_cur, s21_token *token) {
  bool fin = false;
  while (!fin && **format_cur != '\0') {
    switch (**format_cur) {
      case '-':  // overrides '0'
        token->left_justify = true;
        token->zfill = !token->left_justify;
        break;
      case '0':
        token->zfill = !token->left_justify;
        break;
      case '+':  // overrides ' '
        token->sign_pos = true;
        token->sign_spc = !token->sign_pos;
        break;
      case ' ':
        token->sign_spc = !token->sign_pos;
        break;
      case '#':
        token->alt_form = true;
        break;
      default:
        fin = true;
        break;
    }
    if (!fin) (*format_cur)++;
  }
}

void s21_token_width(const char **format_cur, s21_token *token, va_list args) {
  if (**format_cur == '*') {
    token->width = va_arg(args, int);
    (*format_cur)++;
  } else
    token->width = s21_sprintf_get_number(format_cur);
}

void s21_token_preci(const char **format_cur, s21_token *token, va_list args) {
  if (**format_cur == '.') {
    (*format_cur)++;
    if (**format_cur == '*') {
      int new_prec = va_arg(args, int);
      if (new_prec < 0)
        token->prec_default = true;
      else
        token->precision = new_prec;
      (*format_cur)++;
    } else
      token->precision = s21_sprintf_get_number(format_cur);
  } else
    token->prec_default = true;
}

void s21_token_length(const char **format_cur, s21_token *token) {
  bool fin = false;
  while (!fin && **format_cur != '\0') {
    switch (**format_cur) {
      case 'h':
        token->len_short = true;
        break;
      case 'l':
        token->len_long = true;
        break;
      case 'L':
        token->len_long_double = true;
        break;
      default:
        fin = true;
        break;
    }
    if (!fin) (*format_cur)++;
  }
}

void s21_token_specifier(const char **format_cur, s21_token *token) {
  token->specifier = **format_cur;
  (*format_cur)++;
  if (token->prec_default) switch (token->specifier) {
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        token->precision = 6;
        break;
      default:
        token->precision = 1;
        break;
    }
}

void s21_token_write(char **str_cur, int *result, va_list args,
                     s21_token *token) {
  switch (token->specifier) {
    case 'n':
      s21_sprintf_save_count(*result, args);
      break;
    case 'c':
      s21_sprintf_char_write(str_cur, result, args, token);
      break;
    case 's':
      s21_sprintf_string_write(str_cur, result, args, token);
      break;
    case 'd':
    case 'i':
      s21_sprintf_int_write(str_cur, result, args, token);
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      s21_sprintf_uint_write(str_cur, result, args, token);
      break;
    case 'p':
      s21_sprintf_pointer_write(str_cur, result, args, token);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      s21_sprintf_float_write(str_cur, result, args, token);
      break;
    case '%':
      s21_sprintf_write_byte(str_cur, result, '%');
      break;
  }
}

/******************************************************************************/
/*                               VALUE HANDLERS                               */
/******************************************************************************/

// n - Number of characters printed until %n occurs
void s21_sprintf_save_count(const int result, va_list args) {
  int *value = va_arg(args, int *);
  *value = result;
}

// c - Character
void s21_sprintf_char_write(char **str_cur, int *result, va_list args,
                            const s21_token *token) {
  union {
    int c;
    wchar_t wc;
  } value;
  size_t chars_to_write = 1;
  if (token->len_long) {
    value.wc = (wchar_t)va_arg(args, wint_t);
    mbstate_t state = {0};
    char out[MB_CUR_MAX];
    chars_to_write = wcrtomb(out, value.wc, &state);
  } else
    value.c = va_arg(args, int);
  if (chars_to_write == (size_t)-1)
    *result = -1;
  else {
    s21_sprintf_fill_start(str_cur, result, token, (int)chars_to_write);
    if (token->len_long)
      s21_sprintf_write_widechar(str_cur, result, value.wc);
    else
      s21_sprintf_write_byte(str_cur, result, value.c);
    s21_sprintf_fill_end(str_cur, result, token, (int)chars_to_write);
  }
}

// s - String
void s21_sprintf_string_write(char **str_cur, int *result, va_list args,
                              const s21_token *token) {
  union {
    char *s;
    wchar_t *ws;
  } value;
  size_t chars_to_write;
  if (token->len_long) {
    value.ws = va_arg(args, wchar_t *);
    chars_to_write = s21_sprintf_string_count_long(value.ws);
  } else {
    value.s = va_arg(args, char *);
    chars_to_write = s21_strlen(value.s);
  }
  if (chars_to_write == (size_t)-1)
    *result = -1;
  else {
    s21_sprintf_fill_start(str_cur, result, token, (int)chars_to_write);
    if (token->len_long)
      s21_sprintf_write_widestring(str_cur, result, value.ws);
    else
      s21_sprintf_write_string(str_cur, result, value.s);
    s21_sprintf_fill_end(str_cur, result, token, (int)chars_to_write);
  }
}

size_t s21_sprintf_string_count_long(wchar_t *value) {
  size_t count = 0;
  while (*value && count != (size_t)-1) {
    mbstate_t state = {0};
    char out[MB_CUR_MAX];
    size_t res = wcrtomb(out, *value, &state);
    if (res == (size_t)-1)
      count = res;
    else
      count += res;
    value++;
  }
  return count;
}

// d, i - Signed decimal integer
void s21_sprintf_int_write(char **str_cur, int *result, va_list args,
                           s21_token *token) {
  long value;
  if (token->len_long)
    value = va_arg(args, long);
  else if (token->len_short)
    value = (long)((short)va_arg(args, int));
  else
    value = (long)va_arg(args, int);
  token->sign = value < 0;
  int chars_to_write = s21_sprintf_int_count(token, value);

  s21_sprintf_fill_start(str_cur, result, token, chars_to_write);
  s21_sprintf_fill_sign(str_cur, result, token);
  s21_sprintf_fill_zero(str_cur, result, token, chars_to_write);
  if (value < 0) value = -value;
  s21_sprintf_write_number(str_cur, result, value, 10, '\0', token->precision);
  s21_sprintf_fill_end(str_cur, result, token, chars_to_write);
}

int s21_sprintf_int_count(const s21_token *token, long value) {
  int count = 0;
  if (value < 0 || token->sign_pos || token->sign_spc) count++;

  for (unsigned long pow_i = 0; pow_i < token->precision || value != 0;
       ++pow_i) {
    value /= 10;
    count++;
  }
  return count;
}

void s21_sprintf_uint_write(char **str_cur, int *result, va_list args,
                            s21_token *token) {
  unsigned long value;
  if (token->len_long)
    value = va_arg(args, unsigned long);
  else if (token->len_short) {
    unsigned short s_value = (unsigned short)va_arg(args, unsigned int);
    value = (unsigned long)s_value;
  } else
    value = (unsigned long)va_arg(args, unsigned int);
  token->p_sym = token->specifier == 'X' ? 'A' : 'a';
  int base = 10;
  if (token->specifier == 'o') base = 8;
  if (token->specifier == 'x' || token->specifier == 'X') base = 16;
  int chars_to_write = s21_sprintf_uint_count(token, value, base);
  s21_sprintf_fill_start(str_cur, result, token, chars_to_write);
  if (value != 0 && token->alt_form) {
    if (base != 10) s21_sprintf_write_byte(str_cur, result, '0');
    if (base == 16) s21_sprintf_write_byte(str_cur, result, token->specifier);
  }
  s21_sprintf_fill_zero(str_cur, result, token, chars_to_write);
  s21_sprintf_write_unumber(str_cur, result, value, base, token->p_sym,
                            token->precision);
  s21_sprintf_fill_end(str_cur, result, token, chars_to_write);
}

int s21_sprintf_uint_count(const s21_token *token, unsigned long value,
                           int base) {
  int count = 0;
  if (value != 0 && token->alt_form) {
    if (base != 10) count++;
    if (base == 16) count++;
  }

  for (unsigned long pow_i = 0; pow_i < token->precision || value != 0;
       ++pow_i) {
    value /= base;
    count++;
  }
  return count;
}

// p - Pointer address
void s21_sprintf_pointer_write(char **str_cur, int *result, va_list args,
                               const s21_token *token) {
  void *value = va_arg(args, void *);
  int chars_to_write = s21_sprintf_pointer_count(token, (unsigned long)value);
  s21_sprintf_fill_start(str_cur, result, token, chars_to_write);

#if defined(__linux__)
  if (value != NULL) {
#endif
    s21_sprintf_write_string(str_cur, result, "0x");
    s21_sprintf_fill_zero(str_cur, result, token, chars_to_write);
    s21_sprintf_write_unumber(str_cur, result, (unsigned long long)value, 16,
                              'a', token->precision);
#if defined(__linux__)
  } else
    s21_sprintf_write_string(str_cur, result, "(nil)");
#endif
  s21_sprintf_fill_end(str_cur, result, token, chars_to_write);
}

int s21_sprintf_pointer_count(const s21_token *token, unsigned long value) {
  int count = 2;
#if defined(__linux__)
  if (value != 0) {
#endif
    for (unsigned long pow_i = 0; pow_i < token->precision || value != 0;
         ++pow_i) {
      value /= 16;
      count++;
    }
#if defined(__linux__)
  } else
    count += 3;
#endif
  return count;
}

/******************************************************************************/
/*                                   FLOATS                                   */
/******************************************************************************/

void s21_sprintf_float_write(char **str_cur, int *result, va_list args,
                             s21_token *token) {
  char fraction[FRACTION_SIZE] = {1};
  int e_decimal = 0;
  s21_sprintf_float_extract(args, token, fraction, &e_decimal);
  s21_sprintf_float_prepare(token, fraction, &e_decimal);
  int chars_to_write = s21_sprintf_float_count(token, e_decimal);

  s21_sprintf_fill_start(str_cur, result, token, chars_to_write);
  if (token->exp_max) {
#if defined(__APPLE__)
    if (!token->frac_not_null)
#endif
    {
      if (token->zfill)
        s21_sprintf_fill(str_cur, result, ' ', token->width - chars_to_write);
      s21_sprintf_fill_sign(str_cur, result, token);
    }
    if (token->frac_not_null)
      s21_sprintf_write_string(str_cur, result, "nan");
    else
      s21_sprintf_write_string(str_cur, result, "inf");
  } else {
    s21_sprintf_fill_sign(str_cur, result, token);
    s21_sprintf_fill_zero(str_cur, result, token, chars_to_write);
    s21_write_float_basic(str_cur, result, token, fraction, e_decimal);
  }

  s21_sprintf_fill_end(str_cur, result, token, chars_to_write);
}

int s21_sprintf_float_count(const s21_token *token, int e_decimal) {
  int count = 0;
  if (token->sign || token->sign_pos || token->sign_spc)
#if defined(__APPLE__)
    if (!(token->exp_max && token->frac_not_null))  // not nan
#endif
      count++;  // sign
  if (token->exp_max)
    count += 3;  // nan, inf
  else {
    count++;                                                // base
    if (token->precision != 0 || token->alt_form) count++;  // pt
    count += token->precision;                              // afterpoint
    if (token->f_scient) {
      count += 1 + 1 + 2;  // e + exponenta sign and 2 numbers
      e_decimal /= 100;
      while (e_decimal != 0) {
        count++;
        e_decimal /= 10;
      }
    } else if (e_decimal >= 0)
      count += e_decimal;  // before point
  }
  return count;
}

void s21_sprintf_float_extract(va_list args, s21_token *token, char *fraction,
                               int *e_decimal) {
  union {
    double d;
    unsigned char b[sizeof(double)];
  } value;
  char b_pow_r[FRACTION_SIZE] = {1};
  if (token->len_long_double)
    value.d = (double)va_arg(args, long double);
  else
    value.d = va_arg(args, double);
  token->sign = value.b[7] >> 7;
  for (int fraction_i = 51; fraction_i >= 0; --fraction_i) {
    s21_charint_div2(b_pow_r, FRACTION_SIZE);
    if (value.b[fraction_i >> 3] >> (fraction_i & 7) & 1) {
      s21_charint_add(fraction, b_pow_r, FRACTION_SIZE);
      token->frac_not_null = true;
    }
  }
  long e_binary = value.b[6] >> 4 | (value.b[7] & 0x7f) << 4;
  token->exp_max = e_binary == 0x7ff;
  token->exp_null = e_binary == 0;
  e_binary -= 0x3ff;
  if (token->exp_null) {
    e_binary = 0;
    s21_charint_clear(fraction, FRACTION_SIZE);
  }
  while (e_binary != 0) {
    if (e_binary > 0) {
      if (s21_charint_mul2(fraction, FRACTION_SIZE) != 0) {
        s21_charint_rshift(fraction, FRACTION_SIZE, 1);
        (*e_decimal)++;
      }
    } else {
      s21_charint_div2(fraction, FRACTION_SIZE);
      if (fraction[0] == 0) {
        s21_charint_lshift(fraction, FRACTION_SIZE, 0);
        (*e_decimal)--;
      }
    }
    e_binary += e_binary < 0 ? 1 : -1;
  }
}

void s21_sprintf_float_prepare(s21_token *token, char *fraction,
                               int *e_decimal) {
  int do_short = 0;
  token->p_sym = token->specifier == 'E' || token->specifier == 'G' ? 'E' : 'e';
  switch (token->specifier) {
    case 'E':
    case 'e':
      token->f_scient = true;
      break;
    case 'G':
    case 'g':
      do_short = 1;
      if (token->precision == 0) token->precision = 1;
      if (*e_decimal < -4 || *e_decimal >= (int)token->precision)
        token->f_scient = true;
      if (!token->f_scient) token->precision -= *e_decimal;
      token->precision--;
      break;
  }
  int round_precision = token->precision;
  if (!token->f_scient) round_precision += *e_decimal;
  if (FRACTION_RANGE(round_precision + 1)) {  // rounding
    if (FRACTION_NUM(round_precision + 1) >= 5)
      fraction[round_precision + 1] += 10;
    for (int prec_i = round_precision + 1; prec_i > 0; --prec_i) {
      fraction[prec_i - 1] += fraction[prec_i] / 10;
      fraction[prec_i] %= 10;
    }
    char overflow = fraction[0] / 10;
    fraction[0] %= 10;
    if (overflow != 0) {
      s21_charint_rshift(fraction, FRACTION_SIZE, overflow);
      (*e_decimal)++;
      if (do_short != 0 && token->alt_form) token->precision--;
      round_precision++;
    }
  }
  if (do_short != 0 && !(token->alt_form)) {
    while (token->precision > 0 && FRACTION_NUM(round_precision) == 0) {
      token->precision--;
      round_precision--;
    }
  }
}

void s21_write_float_basic(char **str_cur, int *result, const s21_token *token,
                           char *fraction, int e_decimal) {
  if (token->f_scient != 0)
    s21_sprintf_write_byte(str_cur, result, FRACTION_CHAR(0));
  else {
    if (e_decimal >= 0)
      for (int i = 0; i <= e_decimal; ++i)
        s21_sprintf_write_byte(str_cur, result, FRACTION_CHAR(i));
    else
      s21_sprintf_write_byte(str_cur, result, '0');
  }
  if (token->precision != 0 || token->alt_form)
    s21_sprintf_write_byte(str_cur, result, '.');
  if (token->f_scient != 0) {
    for (int i = 1; i <= (int)token->precision; ++i)
      s21_sprintf_write_byte(str_cur, result, FRACTION_CHAR(i));
    s21_sprintf_write_byte(str_cur, result, token->p_sym);
    if (e_decimal < 0) {
      e_decimal = -e_decimal;
      s21_sprintf_write_byte(str_cur, result, '-');
    } else
      s21_sprintf_write_byte(str_cur, result, '+');
    s21_sprintf_write_number(str_cur, result, e_decimal, 10, '\0', 2);
  } else if (token->precision != 0)
    for (int i = e_decimal + 1; i < (int)token->precision + e_decimal + 1; ++i)
      s21_sprintf_write_byte(str_cur, result, FRACTION_CHAR(i));
}