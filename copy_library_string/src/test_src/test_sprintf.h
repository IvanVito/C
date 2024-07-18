#ifndef _TEST_SPRINTF_H
#define _TEST_SPRINTF_H

#include <check.h>

Suite *s21_suite_sprintf(void);

TCase *s21_sprintf_tcase_plain(void);
TCase *s21_sprintf_tcase_character(void);
TCase *s21_sprintf_tcase_string(void);
TCase *s21_sprintf_tcase_digit(void);
TCase *s21_sprintf_tcase_unsigned(void);
TCase *s21_sprintf_tcase_pointer(void);
TCase *s21_sprintf_tcase_ffloat(void);
TCase *s21_sprintf_tcase_efloat(void);
TCase *s21_sprintf_tcase_gfloat(void);

#endif