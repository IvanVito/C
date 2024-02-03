#include "test_special.h"

#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

/******************************************************************************/
/*                                  to_upper                                  */
/******************************************************************************/

START_TEST(test_to_upper_1) {
  void *ptr = s21_to_upper("abc");
  ck_assert_str_eq((char *)ptr, "ABC");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_upper_2) {
  void *ptr = s21_to_upper("1abc4");
  ck_assert_str_eq((char *)ptr, "1ABC4");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_upper_3) {
  void *ptr = s21_to_upper("");
  ck_assert_str_eq((char *)ptr, "");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_upper_4) {
  void *ptr = s21_to_upper(NULL);
  ck_assert_ptr_null(ptr);
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_upper_5) {
  void *ptr = s21_to_upper("1ØØØ5");
  ck_assert_str_eq((char *)ptr, "1ØØØ5");
  if (ptr != NULL) free(ptr);
}
END_TEST

Suite *s21_suite_to_upper(void) {
  Suite *suite = suite_create("s21_to_uppper");
  TCase *tc = tcase_create("s21_to_uppper_tc");

  tcase_add_test(tc, test_to_upper_1);
  tcase_add_test(tc, test_to_upper_2);
  tcase_add_test(tc, test_to_upper_3);
  tcase_add_test(tc, test_to_upper_4);
  tcase_add_test(tc, test_to_upper_5);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  to_lower                                  */
/******************************************************************************/

START_TEST(test_to_lower_1) {
  void *ptr = s21_to_lower("ABC");
  ck_assert_str_eq((char *)ptr, "abc");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_lower_2) {
  void *ptr = s21_to_lower("1ABC4");
  ck_assert_str_eq((char *)ptr, "1abc4");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_lower_3) {
  void *ptr = s21_to_lower("");
  ck_assert_str_eq((char *)ptr, "");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_lower_4) {
  void *ptr = s21_to_lower(NULL);
  ck_assert_ptr_null(ptr);
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_to_lower_5) {
  void *ptr = s21_to_lower("1ØØØ5");
  ck_assert_str_eq((char *)ptr, "1ØØØ5");
  if (ptr != NULL) free(ptr);
}
END_TEST

Suite *s21_suite_to_lower(void) {
  Suite *suite = suite_create("s21_to_lower");
  TCase *tc = tcase_create("s21_to_lower_tc");

  tcase_add_test(tc, test_to_lower_1);
  tcase_add_test(tc, test_to_lower_2);
  tcase_add_test(tc, test_to_lower_3);
  tcase_add_test(tc, test_to_lower_4);
  tcase_add_test(tc, test_to_lower_5);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   insert                                   */
/******************************************************************************/

START_TEST(test_insert_1) {
  void *ptr = s21_insert("ABCDF", "123", 0);
  ck_assert_str_eq((char *)ptr, "123ABCDF");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_insert_2) {
  void *ptr = s21_insert("ABCDF", "123", 5);
  ck_assert_str_eq((char *)ptr, "ABCDF123");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_insert_3) {
  void *ptr = s21_insert("ABCDF", "123", 3);
  ck_assert_str_eq((char *)ptr, "ABC123DF");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_insert_4) {
  void *ptr = s21_insert("", "123", 0);
  ck_assert_str_eq((char *)ptr, "123");
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_insert_5) {
  void *ptr = s21_insert("ABCDF", "123", 7);
  ck_assert_ptr_null(ptr);
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_insert_6) {
  void *ptr = s21_insert("ABCDF", NULL, 7);
  ck_assert_ptr_null(ptr);
  if (ptr != NULL) free(ptr);
}
END_TEST

START_TEST(test_insert_7) {
  void *ptr = s21_insert(NULL, "123", 7);
  ck_assert_ptr_null(ptr);
  if (ptr != NULL) free(ptr);
}
END_TEST

Suite *s21_suite_insert(void) {
  Suite *suite = suite_create("s21_insert");
  TCase *tc = tcase_create("s21_insert_tc");

  tcase_add_test(tc, test_insert_1);
  tcase_add_test(tc, test_insert_2);
  tcase_add_test(tc, test_insert_3);
  tcase_add_test(tc, test_insert_4);
  tcase_add_test(tc, test_insert_5);
  tcase_add_test(tc, test_insert_6);
  tcase_add_test(tc, test_insert_7);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                    trim                                    */
/******************************************************************************/

START_TEST(test_trim_1) {
  void *ptr = s21_trim("AAA123BBB", "AB");
  ck_assert_str_eq((char *)ptr, "123");
  if (ptr) free(ptr);
}
END_TEST

START_TEST(test_trim_2) {
  void *ptr = s21_trim("        ", "");
  ck_assert_str_eq((char *)ptr, "");
  if (ptr) free(ptr);
}
END_TEST

START_TEST(test_trim_3) {
  void *ptr = s21_trim("**//**ABC0000/", "*/0");
  ck_assert_str_eq((char *)ptr, "ABC");
  if (ptr) free(ptr);
}
END_TEST

START_TEST(test_trim_4) {
  void *ptr = s21_trim("                ABC", "");
  ck_assert_str_eq((char *)ptr, "ABC");
  if (ptr) free(ptr);
}
END_TEST

START_TEST(test_trim_5) {
  void *ptr = s21_trim(NULL, "abc");
  ck_assert_ptr_null(ptr);
  if (ptr) free(ptr);
}
END_TEST

START_TEST(test_trim_6) {
  void *ptr = s21_trim("ABC", NULL);
  ck_assert_ptr_null(ptr);
  if (ptr) free(ptr);
}
END_TEST

Suite *s21_suite_trim(void) {
  Suite *suite = suite_create("s21_trim");
  TCase *tc = tcase_create("s21_trim_tc");

  tcase_add_test(tc, test_trim_1);
  tcase_add_test(tc, test_trim_2);
  tcase_add_test(tc, test_trim_3);
  tcase_add_test(tc, test_trim_4);
  tcase_add_test(tc, test_trim_5);
  tcase_add_test(tc, test_trim_6);

  suite_add_tcase(suite, tc);

  return suite;
}