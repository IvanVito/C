#include "test_memfunc.h"

#include <check.h>
#include <string.h>

#include "../s21_string.h"

/******************************************************************************/
/*                                   memchr                                   */
/******************************************************************************/

START_TEST(test_memchr_1) {
  const char src[] = "012345678911";
  ck_assert_ptr_eq(memchr(src, '5', 10), s21_memchr(src, '5', 10));
}
END_TEST

START_TEST(test_memchr_2) {
  const char src[] = "012345678911";
  ck_assert_ptr_eq(memchr(src, 'a', 10), s21_memchr(src, 'a', 10));
}
END_TEST

START_TEST(test_memchr_3) {
  const char src[] = "012345678911";
  ck_assert_ptr_eq(memchr(src, 0, 10), s21_memchr(src, 0, 10));
}
END_TEST

START_TEST(test_memchr_4) {
  const char src[] = "012345678911";
  ck_assert_ptr_eq(memchr(src, '5', 3), s21_memchr(src, '5', 3));
}
END_TEST

START_TEST(test_memchr_5) {
  const char src[] = "012345678911";
  ck_assert_ptr_eq(memchr(src, '5', 0), s21_memchr(src, '5', 0));
}
END_TEST

Suite *s21_suite_memchr(void) {
  Suite *suite = suite_create("s21_memchr");
  TCase *tc = tcase_create("s21_memchr_tc");

  tcase_add_test(tc, test_memchr_1);
  tcase_add_test(tc, test_memchr_2);
  tcase_add_test(tc, test_memchr_3);
  tcase_add_test(tc, test_memchr_4);
  tcase_add_test(tc, test_memchr_5);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   memcmp                                   */
/******************************************************************************/

START_TEST(test_memcmp_1) {
  ck_assert_int_eq(memcmp("1234567890", "1234567890", 11),
                   s21_memcmp("1234567890", "1234567890", 11));
}
END_TEST

START_TEST(test_memcmp_2) {
  ck_assert_int_eq(memcmp("1234567890", "1234567890", 0),
                   s21_memcmp("1234567890", "1234567890", 0));
}
END_TEST

START_TEST(test_memcmp_3) {
  ck_assert_int_eq(memcmp("abcdefgh", "abcDefgh", 3),
                   s21_memcmp("abcdefgh", "abcDefgh", 3));
}
END_TEST

START_TEST(test_memcmp_4) {
  ck_assert_int_eq(memcmp("abcdefgh", "abcDefgh", 4),
                   s21_memcmp("abcdefgh", "abcDefgh", 4));
}
END_TEST

START_TEST(test_memcmp_5) {
  ck_assert_int_eq(memcmp("abcdefgh", "abcDefgh", 5),
                   s21_memcmp("abcdefgh", "abcDefgh", 5));
}
END_TEST

START_TEST(test_memcmp_6) {
  ck_assert_int_eq(memcmp("abc", "cba", 0), s21_memcmp("abc", "cba", 0));
}
END_TEST

START_TEST(test_memcmp_7) {
  ck_assert_int_eq(memcmp("abc", "cba", 4), s21_memcmp("abc", "cba", 4));
}
END_TEST

Suite *s21_suite_memcmp(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tc = tcase_create("s21_memcmp_tc");

  tcase_add_test(tc, test_memcmp_1);
  tcase_add_test(tc, test_memcmp_2);
  tcase_add_test(tc, test_memcmp_3);
  tcase_add_test(tc, test_memcmp_4);
  tcase_add_test(tc, test_memcmp_5);
  tcase_add_test(tc, test_memcmp_6);
  tcase_add_test(tc, test_memcmp_7);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   memcpy                                   */
/******************************************************************************/

START_TEST(test_memcpy_1) {
  char dest_1[] = "                              ";
  char dest_2[] = "                              ";
  ck_assert_str_eq(s21_memcpy(dest_1, "abcdefg", 4),
                   memcpy(dest_2, "abcdefg", 4));
}
END_TEST

START_TEST(test_memcpy_2) {
  char dest_1[] = "                              ";
  char dest_2[] = "                              ";
  ck_assert_str_eq(s21_memcpy(dest_1, "abcdefg", 0),
                   memcpy(dest_2, "abcdefg", 0));
}
END_TEST

START_TEST(test_memcpy_3) {
  char dest_1[] = "                              ";
  char dest_2[] = "                              ";
  ck_assert_str_eq(s21_memcpy(dest_1, "abcdefg", 8),
                   memcpy(dest_2, "abcdefg", 8));
}
END_TEST

Suite *s21_suite_memcpy(void) {
  Suite *suite = suite_create("s21_memcpy");
  TCase *tc = tcase_create("s21_memcpy_tc");

  tcase_add_test(tc, test_memcpy_1);
  tcase_add_test(tc, test_memcpy_2);
  tcase_add_test(tc, test_memcpy_3);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   memset                                   */
/******************************************************************************/

START_TEST(test_memset_1) {
  char dest_1[] = "                              ";
  char dest_2[] = "                              ";
  ck_assert_str_eq(s21_memset(dest_1, '0', 1), memset(dest_2, '0', 1));
}
END_TEST

START_TEST(test_memset_2) {
  char dest_1[] = "                              ";
  char dest_2[] = "                              ";
  ck_assert_str_eq(s21_memset(dest_1, '0', 0), dest_2);
}
END_TEST

START_TEST(test_memset_3) {
  char dest_1[] = "                              ";
  char dest_2[] = "                              ";
  ck_assert_str_eq(s21_memset(dest_1, 200, 4), memset(dest_2, 200, 4));
}
END_TEST

Suite *s21_suite_memset(void) {
  Suite *suite = suite_create("s21_memset");
  TCase *tc = tcase_create("s21_memset_tc");

  tcase_add_test(tc, test_memset_1);
  tcase_add_test(tc, test_memset_2);
  tcase_add_test(tc, test_memset_3);

  suite_add_tcase(suite, tc);

  return suite;
}
