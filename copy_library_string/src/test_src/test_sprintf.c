#include "test_sprintf.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

Suite *s21_suite_sprintf(void) {
  Suite *suite = suite_create("s21_sprintf");

  suite_add_tcase(suite, s21_sprintf_tcase_plain());
  suite_add_tcase(suite, s21_sprintf_tcase_character());
  suite_add_tcase(suite, s21_sprintf_tcase_string());
  suite_add_tcase(suite, s21_sprintf_tcase_digit());
  suite_add_tcase(suite, s21_sprintf_tcase_unsigned());
  suite_add_tcase(suite, s21_sprintf_tcase_pointer());
  suite_add_tcase(suite, s21_sprintf_tcase_ffloat());
  suite_add_tcase(suite, s21_sprintf_tcase_efloat());
  suite_add_tcase(suite, s21_sprintf_tcase_gfloat());

  return suite;
}

/******************************************************************************/
/*                                %%n common                                  */
/******************************************************************************/

START_TEST(test_sprintf_plain_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(s21_sprintf(res_2, ""), 0);
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_plain_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  int nres_1 = INT_MIN, nres_2 = INT_MIN;
  ck_assert_int_eq(sprintf(res_1, "%nSample text", &nres_1),
                   s21_sprintf(res_2, "%nSample text", &nres_2));
  ck_assert_int_eq(nres_1, nres_2);
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_plain_3) {
  char res_1[64] = {0}, res_2[64] = {0};
  int nres_1 = INT_MIN, nres_2 = INT_MIN;
  ck_assert_int_eq(sprintf(res_1, "%% %% %% %% %n", &nres_1),
                   s21_sprintf(res_2, "%% %% %% %% %n", &nres_2));
  ck_assert_int_eq(nres_1, nres_2);
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_plain_4) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%*.*d", 20, 5, 0),
                   s21_sprintf(res_2, "%*.*d", 20, 5, 0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_plain_5) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%*.*d", 20, -1, 0),
                   s21_sprintf(res_2, "%*.*d", 20, -1, 0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_plain(void) {
  TCase *tc = tcase_create("s21_sprintf_plain");

  tcase_add_test(tc, test_sprintf_plain_1);
  tcase_add_test(tc, test_sprintf_plain_2);
  tcase_add_test(tc, test_sprintf_plain_3);
  tcase_add_test(tc, test_sprintf_plain_4);
  tcase_add_test(tc, test_sprintf_plain_5);

  return tc;
}

/******************************************************************************/
/*                                %c character                                */
/******************************************************************************/

START_TEST(test_sprintf_character_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-30c", 'a'),
                   s21_sprintf(res_2, "%-30c", 'a'));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_character_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  wchar_t symb = L'🗿';
  ck_assert_int_eq(sprintf(res_1, "%30lc", symb),
                   s21_sprintf(res_2, "%30lc", symb));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_character(void) {
  TCase *tc = tcase_create("s21_sprintf_character");

  tcase_add_test(tc, test_sprintf_character_1);
  tcase_add_test(tc, test_sprintf_character_2);

  return tc;
}

/******************************************************************************/
/*                                 %s string                                  */
/******************************************************************************/

START_TEST(test_sprintf_string_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-30s", "abc"),
                   s21_sprintf(res_2, "%-30s", "abc"));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_string_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  wchar_t *line = L"🗿🗿🗿";
  ck_assert_int_eq(sprintf(res_1, "%30ls", line),
                   s21_sprintf(res_2, "%30ls", line));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_string(void) {
  TCase *tc = tcase_create("s21_sprintf_string");

  tcase_add_test(tc, test_sprintf_string_1);
  tcase_add_test(tc, test_sprintf_string_2);

  return tc;
}

/******************************************************************************/
/*                                 %di digit                                  */
/******************************************************************************/

START_TEST(test_sprintf_digit_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%i", INT_MIN),
                   s21_sprintf(res_2, "%i", INT_MIN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%d", 0), s21_sprintf(res_2, "%d", 0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_3) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+d", INT_MAX),
                   s21_sprintf(res_2, "%+d", INT_MAX));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_4) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30.25hd", SHRT_MIN),
                   s21_sprintf(res_2, "%30.25hd", SHRT_MIN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_5) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-30hd", (short)0),
                   s21_sprintf(res_2, "%-30hd", (short)0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_6) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% hd", SHRT_MAX),
                   s21_sprintf(res_2, "% hd", SHRT_MAX));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_7) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%030ld", LONG_MIN),
                   s21_sprintf(res_2, "%030ld", LONG_MIN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_8) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30ld", 0L),
                   s21_sprintf(res_2, "%30ld", 0L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_digit_9) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%ld", LONG_MAX),
                   s21_sprintf(res_2, "%ld", LONG_MAX));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_digit(void) {
  TCase *tc = tcase_create("s21_sprintf_digit");

  tcase_add_test(tc, test_sprintf_digit_1);
  tcase_add_test(tc, test_sprintf_digit_2);
  tcase_add_test(tc, test_sprintf_digit_3);
  tcase_add_test(tc, test_sprintf_digit_4);
  tcase_add_test(tc, test_sprintf_digit_5);
  tcase_add_test(tc, test_sprintf_digit_6);
  tcase_add_test(tc, test_sprintf_digit_7);
  tcase_add_test(tc, test_sprintf_digit_8);
  tcase_add_test(tc, test_sprintf_digit_9);

  return tc;
}

/******************************************************************************/
/*                               %uoxX unsigned                               */
/******************************************************************************/

START_TEST(test_sprintf_unsigned_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%u", 0U), s21_sprintf(res_2, "%u", 0U));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_unsigned_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%u", UINT_MAX),
                   s21_sprintf(res_2, "%u", UINT_MAX));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_unsigned_3) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#030hx", (unsigned short)0),
                   s21_sprintf(res_2, "%#030hx", (unsigned short)0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_unsigned_4) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-#30ho", USHRT_MAX),
                   s21_sprintf(res_2, "%-#30ho", USHRT_MAX));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_unsigned_5) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#lX", 0UL),
                   s21_sprintf(res_2, "%#lX", 0UL));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_unsigned_6) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#30.25lx", ULONG_MAX),
                   s21_sprintf(res_2, "%#30.25lx", ULONG_MAX));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_unsigned(void) {
  TCase *tc = tcase_create("s21_sprintf_unsigned");

  tcase_add_test(tc, test_sprintf_unsigned_1);
  tcase_add_test(tc, test_sprintf_unsigned_2);
  tcase_add_test(tc, test_sprintf_unsigned_3);
  tcase_add_test(tc, test_sprintf_unsigned_4);
  tcase_add_test(tc, test_sprintf_unsigned_5);
  tcase_add_test(tc, test_sprintf_unsigned_6);

  return tc;
}

/******************************************************************************/
/*                                 %p pointer                                 */
/******************************************************************************/

START_TEST(test_sprintf_pointer_1) {
  void *ptr = (void *)INTPTR_MIN;
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30p", ptr),
                   s21_sprintf(res_2, "%30p", ptr));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_pointer_2) {
  void *ptr = (void *)INTPTR_MAX;
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30p", ptr),
                   s21_sprintf(res_2, "%30p", ptr));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_pointer_3) {
  void *ptr = NULL;
  char res_1[64] = {0};
#if defined(__APPLE__)
  ck_assert_int_eq(s21_sprintf(res_1, "%p", ptr), 3);
  ck_assert_str_eq(res_1, "0x0");
#else
  ck_assert_int_eq(s21_sprintf(res_1, "%p", ptr), 5);
  ck_assert_str_eq(res_1, "(nil)");
#endif
}
END_TEST

START_TEST(test_sprintf_pointer_4) {
  char res_1[64] = {0}, res_2[64] = {0}, *val = "";
  ck_assert_int_eq(sprintf(res_1, "%-30p", val),
                   s21_sprintf(res_2, "%-30p", val));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_pointer(void) {
  TCase *tc = tcase_create("s21_sprintf_pointer");

  tcase_add_test(tc, test_sprintf_pointer_1);
  tcase_add_test(tc, test_sprintf_pointer_2);
  tcase_add_test(tc, test_sprintf_pointer_3);
  tcase_add_test(tc, test_sprintf_pointer_4);

  return tc;
}

/******************************************************************************/
/*                                  %f float                                  */
/******************************************************************************/

START_TEST(test_sprintf_ffloat_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+Lf", .0L),
                   s21_sprintf(res_2, "%+Lf", .0L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%f", -.0), s21_sprintf(res_2, "%f", -.0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_3) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% f", INFINITY),
                   s21_sprintf(res_2, "% f", INFINITY));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_4) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%f", -INFINITY),
                   s21_sprintf(res_2, "%f", -INFINITY));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_5) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% f", NAN), s21_sprintf(res_2, "% f", NAN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_6) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+f", NAN), s21_sprintf(res_2, "%+f", NAN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_7) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30.6f", 0.99999),
                   s21_sprintf(res_2, "%30.6f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_8) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-30.5f", 0.99999),
                   s21_sprintf(res_2, "%-30.5f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_9) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.4f", 0.99999),
                   s21_sprintf(res_2, "%.4f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_10) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.3f", 0.99999),
                   s21_sprintf(res_2, "%.3f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_11) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.2f", 0.99999),
                   s21_sprintf(res_2, "%.2f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_12) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.1f", 0.99999),
                   s21_sprintf(res_2, "%.1f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_13) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#.0f", 0.99999),
                   s21_sprintf(res_2, "%#.0f", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_14) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30f", 1e20),
                   s21_sprintf(res_2, "%30f", 1e20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_15) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%f", 1e-20),
                   s21_sprintf(res_2, "%f", 1e-20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_16) {
  char res_1[512] = {0}, res_2[512] = {0};
  ck_assert_int_eq(sprintf(res_1, "%f", 1e300),
                   s21_sprintf(res_2, "%f", 1e300));
  res_1[10] = '\0';
  res_2[10] = '\0';
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_17) {
  char res_1[512] = {0}, res_2[512] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.300f", 1e-300),
                   s21_sprintf(res_2, "%.300f", 1e-300));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_18) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30f", 123.456789),
                   s21_sprintf(res_2, "%30f", 123.456789));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_19) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%030Lf", 1.L / 3.L),
                   s21_sprintf(res_2, "%030Lf", 1.L / 3.L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_ffloat_20) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30f", 123.456789e20),
                   s21_sprintf(res_2, "%30f", 123.456789e20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_ffloat(void) {
  TCase *tc = tcase_create("s21_sprintf_ffloat");

  tcase_add_test(tc, test_sprintf_ffloat_1);
  tcase_add_test(tc, test_sprintf_ffloat_2);
  tcase_add_test(tc, test_sprintf_ffloat_3);
  tcase_add_test(tc, test_sprintf_ffloat_4);
  tcase_add_test(tc, test_sprintf_ffloat_5);
  tcase_add_test(tc, test_sprintf_ffloat_6);
  tcase_add_test(tc, test_sprintf_ffloat_7);
  tcase_add_test(tc, test_sprintf_ffloat_8);
  tcase_add_test(tc, test_sprintf_ffloat_9);
  tcase_add_test(tc, test_sprintf_ffloat_10);
  tcase_add_test(tc, test_sprintf_ffloat_11);
  tcase_add_test(tc, test_sprintf_ffloat_12);
  tcase_add_test(tc, test_sprintf_ffloat_13);
  tcase_add_test(tc, test_sprintf_ffloat_14);
  tcase_add_test(tc, test_sprintf_ffloat_15);
  tcase_add_test(tc, test_sprintf_ffloat_16);
  tcase_add_test(tc, test_sprintf_ffloat_17);
  tcase_add_test(tc, test_sprintf_ffloat_18);
  tcase_add_test(tc, test_sprintf_ffloat_19);
  tcase_add_test(tc, test_sprintf_ffloat_20);

  return tc;
}

/******************************************************************************/
/*                                 %eE float                                  */
/******************************************************************************/

START_TEST(test_sprintf_efloat_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+Le", .0L),
                   s21_sprintf(res_2, "%+Le", .0L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%e", -.0), s21_sprintf(res_2, "%e", -.0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_3) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% e", INFINITY),
                   s21_sprintf(res_2, "% e", INFINITY));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_4) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%0e", -INFINITY),
                   s21_sprintf(res_2, "%0e", -INFINITY));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_5) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% e", NAN), s21_sprintf(res_2, "% e", NAN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_6) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+e", NAN), s21_sprintf(res_2, "%+e", NAN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_7) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30.6e", 0.99999),
                   s21_sprintf(res_2, "%30.6e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_8) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-30.5e", 0.99999),
                   s21_sprintf(res_2, "%-30.5e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_9) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.4e", 0.99999),
                   s21_sprintf(res_2, "%.4e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_10) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.3e", 0.99999),
                   s21_sprintf(res_2, "%.3e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_11) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.2e", 0.99999),
                   s21_sprintf(res_2, "%.2e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_12) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.1e", 0.99999),
                   s21_sprintf(res_2, "%.1e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_13) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#.0e", 0.99999),
                   s21_sprintf(res_2, "%#.0e", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_14) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30E", 1e20),
                   s21_sprintf(res_2, "%30E", 1e20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_15) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%e", 1e-20),
                   s21_sprintf(res_2, "%e", 1e-20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_16) {
  char res_1[512] = {0}, res_2[512] = {0};
  ck_assert_int_eq(sprintf(res_1, "%e", 1e300),
                   s21_sprintf(res_2, "%e", 1e300));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_17) {
  char res_1[512] = {0}, res_2[512] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.300e", 1e-300),
                   s21_sprintf(res_2, "%.300e", 1e-300));
  res_1[10] = '\0';
  res_2[10] = '\0';
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_18) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30e", 123.456789),
                   s21_sprintf(res_2, "%30e", 123.456789));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_19) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%030Le", 1.L / 3.L),
                   s21_sprintf(res_2, "%030Le", 1.L / 3.L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_efloat_20) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30e", 123.456789e20),
                   s21_sprintf(res_2, "%30e", 123.456789e20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_efloat(void) {
  TCase *tc = tcase_create("s21_sprintf_efloat");

  tcase_add_test(tc, test_sprintf_efloat_1);
  tcase_add_test(tc, test_sprintf_efloat_2);
  tcase_add_test(tc, test_sprintf_efloat_3);
  tcase_add_test(tc, test_sprintf_efloat_4);
  tcase_add_test(tc, test_sprintf_efloat_5);
  tcase_add_test(tc, test_sprintf_efloat_6);
  tcase_add_test(tc, test_sprintf_efloat_7);
  tcase_add_test(tc, test_sprintf_efloat_8);
  tcase_add_test(tc, test_sprintf_efloat_9);
  tcase_add_test(tc, test_sprintf_efloat_10);
  tcase_add_test(tc, test_sprintf_efloat_11);
  tcase_add_test(tc, test_sprintf_efloat_12);
  tcase_add_test(tc, test_sprintf_efloat_13);
  tcase_add_test(tc, test_sprintf_efloat_14);
  tcase_add_test(tc, test_sprintf_efloat_15);
  tcase_add_test(tc, test_sprintf_efloat_16);
  tcase_add_test(tc, test_sprintf_efloat_17);
  tcase_add_test(tc, test_sprintf_efloat_18);
  tcase_add_test(tc, test_sprintf_efloat_19);
  tcase_add_test(tc, test_sprintf_efloat_20);

  return tc;
}

/******************************************************************************/
/*                                 %gG float                                  */
/******************************************************************************/

START_TEST(test_sprintf_gfloat_1) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+Lg", .0L),
                   s21_sprintf(res_2, "%+Lg", .0L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_2) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%g", -.0), s21_sprintf(res_2, "%g", -.0));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_3) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% g", INFINITY),
                   s21_sprintf(res_2, "% g", INFINITY));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_4) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%g", -INFINITY),
                   s21_sprintf(res_2, "%g", -INFINITY));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_5) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "% g", NAN), s21_sprintf(res_2, "% g", NAN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_6) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%+g", NAN), s21_sprintf(res_2, "%+g", NAN));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_7) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30.6g", 0.99999),
                   s21_sprintf(res_2, "%30.6g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_8) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%-30.5g", 0.99999),
                   s21_sprintf(res_2, "%-30.5g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_9) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.4g", 0.99999),
                   s21_sprintf(res_2, "%.4g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_10) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.3g", 0.99999),
                   s21_sprintf(res_2, "%.3g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_11) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.2g", 0.99999),
                   s21_sprintf(res_2, "%.2g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_12) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.1g", 0.99999),
                   s21_sprintf(res_2, "%.1g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_13) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#.0g", 0.99999),
                   s21_sprintf(res_2, "%#.0g", 0.99999));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_14) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30g", 1e20),
                   s21_sprintf(res_2, "%30g", 1e20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_15) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%g", 1e-20),
                   s21_sprintf(res_2, "%g", 1e-20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_16) {
  char res_1[512] = {0}, res_2[512] = {0};
  ck_assert_int_eq(sprintf(res_1, "%.0G", 1.5e300),
                   s21_sprintf(res_2, "%.0G", 1.5e300));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_17) {
  char res_1[512] = {0}, res_2[512] = {0};
  ck_assert_int_eq(sprintf(res_1, "%#.300g", 1e-300),
                   s21_sprintf(res_2, "%#.300g", 1e-300));
  res_1[10] = '\0';
  res_2[10] = '\0';
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_18) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30g", 123.456789),
                   s21_sprintf(res_2, "%30g", 123.456789));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_19) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%030Lg", 1.L / 3.L),
                   s21_sprintf(res_2, "%030Lg", 1.L / 3.L));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

START_TEST(test_sprintf_gfloat_20) {
  char res_1[64] = {0}, res_2[64] = {0};
  ck_assert_int_eq(sprintf(res_1, "%30g", 123.456789e20),
                   s21_sprintf(res_2, "%30g", 123.456789e20));
  ck_assert_str_eq(res_1, res_2);
}
END_TEST

TCase *s21_sprintf_tcase_gfloat(void) {
  TCase *tc = tcase_create("s21_sprintf_gfloat");

  tcase_add_test(tc, test_sprintf_gfloat_1);
  tcase_add_test(tc, test_sprintf_gfloat_2);
  tcase_add_test(tc, test_sprintf_gfloat_3);
  tcase_add_test(tc, test_sprintf_gfloat_4);
  tcase_add_test(tc, test_sprintf_gfloat_5);
  tcase_add_test(tc, test_sprintf_gfloat_6);
  tcase_add_test(tc, test_sprintf_gfloat_7);
  tcase_add_test(tc, test_sprintf_gfloat_8);
  tcase_add_test(tc, test_sprintf_gfloat_9);
  tcase_add_test(tc, test_sprintf_gfloat_10);
  tcase_add_test(tc, test_sprintf_gfloat_11);
  tcase_add_test(tc, test_sprintf_gfloat_12);
  tcase_add_test(tc, test_sprintf_gfloat_13);
  tcase_add_test(tc, test_sprintf_gfloat_14);
  tcase_add_test(tc, test_sprintf_gfloat_15);
  tcase_add_test(tc, test_sprintf_gfloat_16);
  tcase_add_test(tc, test_sprintf_gfloat_17);
  tcase_add_test(tc, test_sprintf_gfloat_18);
  tcase_add_test(tc, test_sprintf_gfloat_19);
  tcase_add_test(tc, test_sprintf_gfloat_20);

  return tc;
}