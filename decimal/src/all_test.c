#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_decimal_op.h"

START_TEST(test_s21_is_less) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_less(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_less1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  s21_bit_set(num_1.bits, 127, 1);
  num_2.bits[0] = 7777776;
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less2) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777777;
  ck_assert_int_eq(s21_is_less(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_less3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_1.bits[1] = 9;
  num_2.bits[0] = 7777778;
  ck_assert_int_eq(s21_is_less(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_less4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_1.bits[1] = 7777778;
  s21_bit_set(num_1.bits, 127, 1);
  num_2.bits[1] = 9;
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less5) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 8888888;
  num_2.bits[0] = 7777777;
  s21_bit_set(num_1.bits, 113, 1);
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less6) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 8888888;
  num_2.bits[0] = 7777;
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less7) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2;
  num_2.bits[1] = 1073741824;
  num_2.bits[2] = 3;
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less8) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 2147483647;
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2147483647;
  s21_bit_set(num_1.bits, 127, 1);
  num_2.bits[0] = 2147483647;
  num_2.bits[1] = 2147483647;
  num_2.bits[2] = 2147483647;
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less9) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_2.bits, 94, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_less(num_1, num_2), 1);
}
END_TEST

Suite *s21_decimal_is_less() {
  Suite *result;
  TCase *tc_s21_is_less;

  result = suite_create("s21_is_less");
  tc_s21_is_less = tcase_create("s21_is_less");

  tcase_add_test(tc_s21_is_less, test_s21_is_less);
  tcase_add_test(tc_s21_is_less, test_s21_is_less1);
  tcase_add_test(tc_s21_is_less, test_s21_is_less2);
  tcase_add_test(tc_s21_is_less, test_s21_is_less3);
  tcase_add_test(tc_s21_is_less, test_s21_is_less4);
  tcase_add_test(tc_s21_is_less, test_s21_is_less5);
  tcase_add_test(tc_s21_is_less, test_s21_is_less6);
  tcase_add_test(tc_s21_is_less, test_s21_is_less7);
  tcase_add_test(tc_s21_is_less, test_s21_is_less8);
  tcase_add_test(tc_s21_is_less, test_s21_is_less9);

  suite_add_tcase(result, tc_s21_is_less);

  return result;
}

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_less_or_equal(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  s21_bit_set(num_1.bits, 127, 1);
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal2) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777777;
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_1.bits[1] = 9;
  num_2.bits[0] = 7777778;
  ck_assert_int_eq(s21_is_less_or_equal(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_1.bits[1] = 7777778;
  num_2.bits[2] = 9;
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_less_or_equal(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal5) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 777777;
  num_2.bits[0] = 7777770;
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal6) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[2] = 8888888;
  num_2.bits[2] = 8888888;
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal7) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 1073741824;
  num_1.bits[2] = 2;
  num_2.bits[1] = 1073741824;
  num_2.bits[2] = 2;
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal8) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 2147483647;
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2147483647;
  num_2.bits[0] = 2147483647;
  num_2.bits[1] = 2147483647;
  num_2.bits[2] = 2147483647;
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal9) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_2.bits, 94, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_less_or_equal(num_1, num_2), 1);
}
END_TEST

Suite *s21_decimal_is_less_or_equal() {
  Suite *result;
  TCase *tc_s21_is_less_or_equal;

  result = suite_create("s21_is_less_or_equal");
  tc_s21_is_less_or_equal = tcase_create("s21_is_less_or_equal");

  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal1);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal2);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal3);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal4);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal5);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal6);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal7);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal8);
  tcase_add_test(tc_s21_is_less_or_equal, test_s21_is_less_or_equal9);

  suite_add_tcase(result, tc_s21_is_less_or_equal);

  return result;
}

START_TEST(test_s21_is_greater) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_greater(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_greater1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_greater(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater2) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777777;
  ck_assert_int_eq(s21_is_greater(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_1.bits[1] = 9;
  num_2.bits[0] = 7777778;
  ck_assert_int_eq(s21_is_greater(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[2] = 9;
  num_1.bits[1] = 7777778;
  ck_assert_int_eq(s21_is_greater(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater5) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 8888888;
  num_2.bits[0] = 7777777;
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_greater(num_2, num_1), 0);
}
END_TEST

START_TEST(test_s21_is_greater6) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 8888888;
  num_2.bits[0] = 7777;
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_greater(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater7) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2;
  num_2.bits[1] = 1073741824;
  num_2.bits[2] = 3;
  ck_assert_int_eq(s21_is_greater(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater8) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 2147483647;
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2147483646;
  num_2.bits[0] = 2147483647;
  num_2.bits[1] = 2147483647;
  num_2.bits[2] = 2147483647;
  ck_assert_int_eq(s21_is_greater(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_greater9) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_2.bits, 94, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_greater(num_2, num_1), 1);
}
END_TEST

Suite *s21_decimal_is_greater() {
  Suite *result;
  TCase *tc_s21_is_greater;

  result = suite_create("s21_is_greater");
  tc_s21_is_greater = tcase_create("s21_is_greater");

  tcase_add_test(tc_s21_is_greater, test_s21_is_greater);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater1);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater2);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater3);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater4);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater5);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater6);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater7);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater8);
  tcase_add_test(tc_s21_is_greater, test_s21_is_greater9);

  suite_add_tcase(result, tc_s21_is_greater);

  return result;
}

START_TEST(test_s21_is_greater_or_equal) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_greater_or_equal(num_2, num_1), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal2) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777777;
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_1.bits[1] = 9;
  num_2.bits[0] = 7777778;
  s21_bit_set(num_1.bits, 127, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[2] = 9;
  num_1.bits[1] = 7777778;
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal5) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 777777;
  num_2.bits[0] = 7777770;
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal6) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[2] = 8888888;
  num_2.bits[2] = 8888888;
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 113, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal7) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 1073741824;
  num_1.bits[2] = 2;
  num_2.bits[1] = 1073741824;
  num_2.bits[2] = 2;
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal8) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 2147483647;
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2147483647;
  num_2.bits[0] = 2147483647;
  num_2.bits[1] = 2147483647;
  num_2.bits[2] = 2147483647;
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal9) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_2.bits, 94, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(num_1, num_2), 0);
}
END_TEST

Suite *s21_decimal_is_greater_or_equal() {
  Suite *result;
  TCase *tc_s21_is_greater_or_equal;

  result = suite_create("s21_is_greater_or_equal");
  tc_s21_is_greater_or_equal = tcase_create("s21_is_greater_or_equal");

  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal1);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal2);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal3);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal4);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal5);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal6);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal7);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal8);
  tcase_add_test(tc_s21_is_greater_or_equal, test_s21_is_greater_or_equal9);

  suite_add_tcase(result, tc_s21_is_greater_or_equal);

  return result;
}

START_TEST(test_s21_is_equal) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_equal(num_2, num_1), 0);
}
END_TEST

START_TEST(test_s21_is_equal1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal2) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777777;
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 91234;
  num_2.bits[1] = 91234;
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_equal(num_2, num_1), 0);
}
END_TEST

START_TEST(test_s21_is_equal4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[3] = 7777777;
  num_2.bits[3] = 7777777;
  num_1.bits[1] = 7777778;
  num_2.bits[1] = 7777778;
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal5) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 77777;
  num_2.bits[0] = 77777000;
  s21_bit_set(num_2.bits, 113, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal6) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[2] = 8888887;
  num_2.bits[2] = 8888888;
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal7) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 1073741824;
  num_1.bits[2] = 2;
  num_2.bits[1] = 1073741824;
  num_2.bits[2] = 2;
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal8) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 2147483647;
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2147483647;
  num_2.bits[0] = 2147483647;
  num_2.bits[1] = 2147483647;
  num_2.bits[2] = 2147483647;
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal9) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 94, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_equal(num_1, num_2), 1);
}
END_TEST

Suite *s21_decimal_is_equal() {
  Suite *result;
  TCase *tc_s21_is_equal;

  result = suite_create("s21_is_equal");
  tc_s21_is_equal = tcase_create("s21_is_equal");

  tcase_add_test(tc_s21_is_equal, test_s21_is_equal);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal1);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal2);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal3);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal4);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal5);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal6);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal7);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal8);
  tcase_add_test(tc_s21_is_equal, test_s21_is_equal9);

  suite_add_tcase(result, tc_s21_is_equal);

  return result;
}

START_TEST(test_s21_is_not_equal) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_not_equal(num_2, num_1), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal2) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777777;
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 91234;
  num_2.bits[1] = 91234;
  ck_assert_int_eq(s21_is_not_equal(num_2, num_1), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[3] = 7777777;
  num_2.bits[3] = 7777777;
  num_1.bits[1] = 7777779;
  num_2.bits[1] = 7777778;
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal5) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 77777;
  num_2.bits[0] = 77777000;
  s21_bit_set(num_2.bits, 113, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal6) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[2] = 8888887;
  num_2.bits[2] = 8888888;
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal7) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[1] = 1073741824;
  num_1.bits[2] = 2;
  num_2.bits[1] = 1073741824;
  num_2.bits[2] = 2;
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal8) {
  s21_decimal num_1 = {0}, num_2 = {0};
  num_1.bits[0] = 2147483647;
  num_1.bits[1] = 2147483647;
  num_1.bits[2] = 2147483647;
  num_2.bits[0] = 2147483647;
  num_2.bits[1] = 2147483647;
  num_2.bits[2] = 2147483647;
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal9) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 94, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 113, 1);
  ck_assert_int_eq(s21_is_not_equal(num_1, num_2), 1);
}
END_TEST

Suite *s21_decimal_is_not_equal() {
  Suite *result;
  TCase *tc_s21_is_not_equal;

  result = suite_create("s21_is_not_equal");
  tc_s21_is_not_equal = tcase_create("s21_is_not_equal");

  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal1);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal2);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal3);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal4);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal5);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal6);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal7);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal8);
  tcase_add_test(tc_s21_is_not_equal, test_s21_is_not_equal9);

  suite_add_tcase(result, tc_s21_is_not_equal);

  return result;
}

START_TEST(test_s21_add) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+15555553,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add1) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+1152921511049297920,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add2) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_bit_set(num_2.bits, 127, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "-1152921498164396032,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add3) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 127, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+9903520314283042199192993792,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add4) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 112, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+10893872345711346419112293171,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add5) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 70, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 27, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+11805916207308330762,24";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add6) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 12, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 12, 1);
  s21_bit_set(num_2.bits, 115, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+,00008192";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add7) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 95, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), 1);
}
END_TEST

START_TEST(test_s21_add8) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 95, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), 0);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+46546545477130298336207070822,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add9) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 0, 1);
  s21_bit_set(num_1.bits, 117, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 0, 1);
  s21_bit_set(num_2.bits, 117, 1);
  s21_bit_set(num_2.bits, 115, 1);
  s21_add(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+,0000000000000000000000000002";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add10) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 92, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 95, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), 0);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+10398696329997194309152643482,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_add11) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 92, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 89, 1);
  s21_bit_set(num_2.bits, 95, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), 0);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+10460593331961463322897599693,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

Suite *s21_decimal_s21_add() {
  Suite *result;
  TCase *tc_s21_add;

  result = suite_create("s21_add");
  tc_s21_add = tcase_create("s21_add");

  tcase_add_test(tc_s21_add, test_s21_add);
  tcase_add_test(tc_s21_add, test_s21_add1);
  tcase_add_test(tc_s21_add, test_s21_add2);
  tcase_add_test(tc_s21_add, test_s21_add3);
  tcase_add_test(tc_s21_add, test_s21_add4);
  tcase_add_test(tc_s21_add, test_s21_add5);
  tcase_add_test(tc_s21_add, test_s21_add6);
  tcase_add_test(tc_s21_add, test_s21_add7);
  tcase_add_test(tc_s21_add, test_s21_add8);
  tcase_add_test(tc_s21_add, test_s21_add9);
  tcase_add_test(tc_s21_add, test_s21_add10);
  tcase_add_test(tc_s21_add, test_s21_add11);

  suite_add_tcase(result, tc_s21_add);

  return result;
}

START_TEST(test_s21_sub) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+1,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub1) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "-1152921498164396032,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub2) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_bit_set(num_2.bits, 127, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+1152921511049297920,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub3) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 127, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+29710560942849126597578981376,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub4) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 112, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+8913168282854737979273694413,";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub5) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 70, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 27, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+11805916207039895306,24";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub6) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 12, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 12, 1);
  s21_bit_set(num_2.bits, 115, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "+,00000000";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

START_TEST(test_s21_sub7) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 95, 1);
  s21_bit_set(num_1.bits, 127, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), 1);
}
END_TEST

START_TEST(test_s21_sub8) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 95, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), 0);
}
END_TEST

START_TEST(test_s21_sub9) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 0, 1);
  s21_bit_set(num_1.bits, 117, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 0, 1);
  s21_bit_set(num_2.bits, 117, 1);
  s21_bit_set(num_2.bits, 115, 1);
  s21_sub(num_1, num_2, &res);
  s21_dec2bcd(&res, &bcd);
  char *answer = "-,0000000000000000000000000002";
  ck_assert_str_eq(s21_num2str(&bcd), answer);
}
END_TEST

Suite *s21_decimal_s21_sub() {
  Suite *result;
  TCase *tc_s21_sub;

  result = suite_create("s21_sub");
  tc_s21_sub = tcase_create("s21_sub");

  tcase_add_test(tc_s21_sub, test_s21_sub);
  tcase_add_test(tc_s21_sub, test_s21_sub1);
  tcase_add_test(tc_s21_sub, test_s21_sub2);
  tcase_add_test(tc_s21_sub, test_s21_sub3);
  tcase_add_test(tc_s21_sub, test_s21_sub4);
  tcase_add_test(tc_s21_sub, test_s21_sub5);
  tcase_add_test(tc_s21_sub, test_s21_sub6);
  tcase_add_test(tc_s21_sub, test_s21_sub7);
  tcase_add_test(tc_s21_sub, test_s21_sub8);
  tcase_add_test(tc_s21_sub, test_s21_sub9);

  suite_add_tcase(result, tc_s21_sub);

  return result;
}

START_TEST(test_negate) {
  s21_decimal num_1 = {0}, num_2 = {0};
  ck_assert_int_eq(s21_negate(num_1, &num_2), 0);
}
END_TEST

START_TEST(test_negate1) {
  s21_decimal num_1 = {0};
  ck_assert_int_eq(s21_negate(num_1, NULL), 1);
}
END_TEST

START_TEST(test_negate2) {
  s21_decimal num_1 = {0};
  s21_negate(num_1, &num_1);
  ck_assert_int_eq(s21_bit_get(num_1.bits, 127), 1);
}
END_TEST

START_TEST(test_negate3) {
  s21_decimal num_1 = {0};
  s21_bcd bcd = {0};
  s21_negate(num_1, &num_1);
  char *actualResult = "-,";
  s21_dec2bcd(&num_1, &bcd);
  ck_assert_str_eq(s21_num2str(&bcd), actualResult);
}
END_TEST

START_TEST(test_negate4) {
  s21_decimal num_1 = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 127, 1);
  s21_negate(num_1, &num_1);
  char *actualResult = "+,";
  s21_dec2bcd(&num_1, &bcd);
  ck_assert_str_eq(s21_num2str(&bcd), actualResult);
}
END_TEST

Suite *s21_decimal_negate() {
  Suite *result = suite_create("s21_negate");
  TCase *tc_negate = tcase_create("s21_negate");

  tcase_add_test(tc_negate, test_negate);
  tcase_add_test(tc_negate, test_negate1);
  tcase_add_test(tc_negate, test_negate2);
  tcase_add_test(tc_negate, test_negate3);
  tcase_add_test(tc_negate, test_negate4);

  suite_add_tcase(result, tc_negate);

  return result;
}

START_TEST(test_truncate) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 80, 1);
  s21_bit_set(num_1.bits, 116, 1);
  s21_truncate(num_1, &num_2);
  s21_dec2bcd(&num_2, &bcd);
  char *actualResult = "+120892581,";  // changed from "+120892581961462,"
  ck_assert_str_eq(s21_num2str(&bcd), actualResult);
}
END_TEST

START_TEST(test_truncate1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  ck_assert_int_eq(s21_truncate(num_1, &num_2), 0);
}
END_TEST

START_TEST(test_truncate2) {
  s21_decimal num_1 = {0};
  ck_assert_int_eq(s21_truncate(num_1, NULL), 1);
}
END_TEST

START_TEST(test_truncate3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 114, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_1.bits, 116, 1);  // changed here too, looks good
  s21_truncate(num_1, &num_2);
  s21_dec2bcd(&num_2, &bcd);
  char *actualResult = "+6,";
  ck_assert_str_eq(s21_num2str(&bcd), actualResult);
}
END_TEST

START_TEST(test_truncate4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bcd bcd = {0};
  s21_bit_set(num_1.bits, 117, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_truncate(num_1, &num_2);
  s21_dec2bcd(&num_2, &bcd);
  char *actualResult = "-,";
  ck_assert_str_eq(s21_num2str(&bcd), actualResult);
}
END_TEST

Suite *s21_decimal_truncate() {
  Suite *result = suite_create("s21_truncate");
  TCase *tc_truncate = tcase_create("s21_truncate");

  tcase_add_test(tc_truncate, test_truncate);
  tcase_add_test(tc_truncate, test_truncate1);
  tcase_add_test(tc_truncate, test_truncate2);
  tcase_add_test(tc_truncate, test_truncate3);
  tcase_add_test(tc_truncate, test_truncate4);

  suite_add_tcase(result, tc_truncate);

  return result;
}

// START_TEST(test_floor) {
//   s21_decimal num_1 = {0}, res = {0};
//   s21_bit_set(num_1.bits, 117, 1);
//   s21_bit_set(num_1.bits, 127, 1);
//   s21_floor(num_1, &res);
//   char *actual_result = "-,";
//   ck_assert_str_eq(s21_num2str(&res), actual_result);
// }
// END_TEST

// START_TEST(test_floor1) {
//   s21_decimal num_1 = {0}, res = {0};
//   s21_bit_set(num_1.bits, 95, 1);
//   s21_bit_set(num_1.bits, 112, 1);
//   s21_bit_set(num_1.bits, 127, 1);
//   s21_floor(num_1, &res);
//   char *actual_result = "-3961408125713216879677197517,";
//   ck_assert_str_eq(s21_num2str(&res), actual_result);
// }
// END_TEST

// Suite *s21_decimal_floor() {
//   Suite *result = suite_create("s21_floor");
//   TCase *tc_floor = tcase_create("s21_floor");

//   tcase_add_test(tc_floor, test_floor);
//   tcase_add_test(tc_floor, test_floor1);

//   suite_add_tcase(result, tc_floor);
//   return result;
// }

// START_TEST(test_from_float_to_decimal) {
//   float num_1 = 10.01023F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+10,01023");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal1) {
//   float num_1 = 123456.789F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+123456,8");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal2) {
//   float num_1 = INFINITY;
//   s21_decimal num_2 = {0};
//   ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
// }
// END_TEST

// START_TEST(test_from_float_to_decimal3) {
//   float num_1 = -INFINITY;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   actual_result.bits[0] = 123;
//   actual_result.bits[1] = 456;
//   actual_result.bits[2] = 789;
//   s21_bit_set(actual_result.bits, 127, 1);
//   ck_assert_int_eq(s21_from_float_to_decimal(num_1, &actual_result), 1);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "-14554481076115341312123,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal4) {
//   float num_1 = -INFINITY;
//   s21_decimal num_2 = {0};
//   ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
// }
// END_TEST

// START_TEST(test_from_float_to_decimal5) {
//   float num_1 = -NAN;
//   s21_decimal num_2 = {0};
//   ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
// }
// END_TEST

// START_TEST(test_from_float_to_decimal6) {
//   float num_1 = NAN;
//   s21_decimal num_2 = {0};
//   ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
// }
// END_TEST

// START_TEST(test_from_float_to_decimal7) {
//   float num_1 = 0.0F;
//   ck_assert_int_eq(s21_from_float_to_decimal(num_1, NULL), 1);
// }
// END_TEST

// START_TEST(test_from_float_to_decimal8) {
//   float num_1 = -09135.09135F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "-9135,092");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal9) {
//   float num_1 = 5.0F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   actual_result.bits[0] = 123;
//   actual_result.bits[1] = 456;
//   actual_result.bits[2] = 789;
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+5,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal10) {
//   float num_1 = FLT_MAX;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   actual_result.bits[0] = 123;
//   s21_bit_set(actual_result.bits, 127, 1);
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "-123,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal11) {
//   float num_1 = 79228162514264337593543950335.0F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   actual_result.bits[0] = 123;
//   actual_result.bits[1] = 456;
//   actual_result.bits[2] = 789;
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal12) {
//   float num_1 = 7922816251426433759354395033.0F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+7922816000000000000000000000,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal13) {
//   float num_1 = 0.00054321054321F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+,0005432105");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal14) {
//   float num_1 = 54321758321.00054321054321F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+54321760000,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal15) {
//   float num_1 = 5432105.321054321F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+5432105,");
// }
// END_TEST

// START_TEST(test_from_float_to_decimal16) {
//   float num_1 = -0.0F;
//   s21_decimal actual_result = {0}, expected_result = {0};
//   s21_bit_set(expected_result.bits, 127, 1);
//   s21_from_float_to_decimal(num_1, &actual_result);
//   ck_assert_int_eq(s21_is_equal(actual_result, expected_result), 1);
// }
// END_TEST

// START_TEST(test_from_float_to_decimal17) {
//   float num_1 = 0.0F;
//   s21_decimal actual_result = {0}, expected_result = {0};
//   s21_bit_set(expected_result.bits, 127, 1);
//   s21_from_float_to_decimal(num_1, &actual_result);
//   ck_assert_int_eq(s21_is_equal(actual_result, expected_result), 1);
// }

// START_TEST(test_from_float_to_decimal18) {
//   float num_1 = -0.000000000000000000000000000121054832F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "-");
// }

// START_TEST(test_from_float_to_decimal19) {
//   float num_1 = -10.980355F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "-9480192000000000000000,");
// }

// START_TEST(test_from_float_to_decimal20) {
//   float num_1 = 10.980365F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+10,98036");
// }

// START_TEST(test_from_float_to_decimal21) {
//   float num_1 = 10.980355F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+10,98036");
// }

// START_TEST(test_from_float_to_decimal22) {
//   float num_1 = 1234567500.12F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+1234568000,");
// }

// START_TEST(test_from_float_to_decimal23) {
//   float num_1 = 1234568500.12F;
//   s21_decimal actual_result = {0};
//   s21_bcd bcd = {0};
//   s21_from_float_to_decimal(num_1, &actual_result);
//   s21_dec2bcd(&actual_result, &bcd);
//   ck_assert_str_eq(s21_num2str(&bcd), "+1234568000,");
// }

// Suite *s21_decimal_from_float_to_decimal() {
//   Suite *result = suite_create("s21_from_float_to_decimal");
//   TCase *tc_from_float_to_decimal = tcase_create("s21_from_float_to_decimal");

//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal1);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal2);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal3);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal4);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal5);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal6);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal7);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal8);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal9);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal10);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal11);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal12);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal13);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal14);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal15);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal16);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal17);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal18);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal19);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal20);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal21);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal22);
//   tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal23);

//   suite_add_tcase(result, tc_from_float_to_decimal);

//   return result;
// }

// START_TEST(test_s21_mul) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 0, 1);
//   s21_bit_set(num_2.bits, 0, 1);
//   s21_bit_set(num_1.bits, 117, 1);
//   s21_bit_set(num_1.bits, 115, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+,0000000000000000000000000001";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul2) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 115, 1);
//   s21_bit_set(num_1.bits, 116, 1);
//   s21_bit_set(num_2.bits, 115, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_1.bits, 95, 1);
//   s21_bit_set(num_2.bits, 95, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+1569275433846664740317,1168504";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul3) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = num_2.bits[0] = 12;
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+144,";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul4) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 15;
//   s21_bit_set(num_1.bits, 113, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+,15";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul5) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 1;
//   s21_bit_set(num_2.bits, 95, 1);
//   s21_bit_set(num_2.bits, 114, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+396140812571321,68796771975168";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul6) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 49, 1);
//   s21_bit_set(num_2.bits, 46, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+39614081257132168796771975168,";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul7) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_2.bits[0] = 1;
//   s21_bit_set(num_1.bits, 95, 1);
//   s21_bit_set(num_2.bits, 117, 1);
//   s21_bit_set(num_2.bits, 115, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+3,9614081257132168796771975168";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul8) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 127, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "-,";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul9) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 1;
//   s21_bit_set(num_1.bits, 114, 1);
//   s21_bit_set(num_1.bits, 116, 1);
//   s21_bit_set(num_2.bits, 114, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_1.bits, 127, 1);
//   s21_bit_set(num_2.bits, 127, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+,0000000000000000000000000001";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul10) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 1;
//   s21_bit_set(num_2.bits, 127, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "-1,";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul11) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 112, 1);
//   s21_bit_set(num_1.bits, 114, 1);
//   s21_bit_set(num_1.bits, 116, 1);
//   s21_bit_set(num_2.bits, 112, 1);
//   s21_bit_set(num_2.bits, 114, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_1.bits, 94, 1);
//   s21_bit_set(num_2.bits, 94, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+392318858461666185079279212,6";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul12) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 1;
//   s21_bit_set(num_2.bits, 127, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "-1,";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul13) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 792281625;
//   num_2.bits[0] = 782281625;
//   s21_bit_set(num_1.bits, 112, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_1.bits, 127, 1);
//   s21_bit_set(num_2.bits, 127, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+6197873,57062640625";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul14) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 1;
//   s21_bit_set(num_1.bits, 114, 1);
//   s21_bit_set(num_1.bits, 116, 1);
//   s21_bit_set(num_2.bits, 114, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_1.bits, 127, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "-,0000000000000000000000000001";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul15) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 1;
//   int res = s21_mul(num_1, num_2, &result);

//   ck_assert_int_eq(res, CALC_OK);
// }
// END_TEST

// START_TEST(test_s21_mul16) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bit_set(num_1.bits, 95, 1);
//   s21_bit_set(num_2.bits, 95, 1);
//   int res = s21_mul(num_1, num_2, &result);
//   ck_assert_int_eq(res, CALC_ESMALL);
// }
// END_TEST

// START_TEST(test_s21_mul17) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   num_1.bits[0] = 1;
//   num_2.bits[0] = 1;
//   s21_bit_set(num_1.bits, 117, 1);
//   s21_bit_set(num_1.bits, 115, 1);
//   s21_bit_set(num_2.bits, 117, 1);
//   s21_bit_set(num_2.bits, 115, 1);
//   int res = s21_mul(num_1, num_2, &result);
//   ck_assert_int_eq(res, CALC_ESMALL);
// }
// END_TEST

// START_TEST(test_s21_mul18) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bit_set(num_1.bits, 45, 1);
//   s21_bit_set(num_2.bits, 45, 1);
//   s21_bit_set(num_1.bits, 116, 1);
//   s21_bit_set(num_1.bits, 114, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_2.bits, 115, 1);
//   int res = s21_mul(num_1, num_2, &result);
//   ck_assert_int_eq(res, CALC_ESMALL);
// }
// END_TEST

// START_TEST(test_s21_mul19) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bit_set(num_1.bits, 45, 1);
//   s21_bit_set(num_2.bits, 45, 1);
//   s21_bit_set(num_1.bits, 116, 1);
//   s21_bit_set(num_1.bits, 114, 1);
//   s21_bit_set(num_2.bits, 116, 1);
//   s21_bit_set(num_2.bits, 114, 1);
//   int res = s21_mul(num_1, num_2, &result);

//   ck_assert_int_eq(res, CALC_OK);
// }
// END_TEST

// START_TEST(test_s21_mul20) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 30, 1);
//   s21_bit_set(num_1.bits, 112, 1);
//   s21_bit_set(num_1.bits, 113, 1);
//   s21_bit_set(num_2.bits, 57, 1);
//   s21_bit_set(num_2.bits, 115, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+1547425049106725,34362390528";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// START_TEST(test_s21_mul21) {
//   s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
//   s21_bcd bcd = {0};
//   s21_bit_set(num_1.bits, 30, 1);
//   s21_bit_set(num_1.bits, 112, 1);
//   s21_bit_set(num_1.bits, 113, 1);
//   s21_bit_set(num_2.bits, 80, 1);
//   s21_bit_set(num_2.bits, 115, 1);
//   s21_mul(num_1, num_2, &result);
//   s21_dec2bcd(&result, &bcd);
//   char *answer = "+12980742097980036286674,75954";
//   ck_assert_str_eq(s21_num2str(&bcd), answer);
// }
// END_TEST

// Suite *s21_decimal_is_mul() {
//   Suite *result;
//   TCase *tc_s21_mul;
//   result = suite_create("s21_mul");
//   tc_s21_mul = tcase_create("s21_mul");
//   tcase_add_test(tc_s21_mul, test_s21_mul);
//   tcase_add_test(tc_s21_mul, test_s21_mul2);
//   tcase_add_test(tc_s21_mul, test_s21_mul3);
//   tcase_add_test(tc_s21_mul, test_s21_mul4);
//   tcase_add_test(tc_s21_mul, test_s21_mul5);
//   tcase_add_test(tc_s21_mul, test_s21_mul6);
//   tcase_add_test(tc_s21_mul, test_s21_mul7);
//   tcase_add_test(tc_s21_mul, test_s21_mul8);
//   tcase_add_test(tc_s21_mul, test_s21_mul9);
//   tcase_add_test(tc_s21_mul, test_s21_mul10);
//   tcase_add_test(tc_s21_mul, test_s21_mul11);
//   tcase_add_test(tc_s21_mul, test_s21_mul12);
//   tcase_add_test(tc_s21_mul, test_s21_mul13);
//   tcase_add_test(tc_s21_mul, test_s21_mul14);
//   tcase_add_test(tc_s21_mul, test_s21_mul15);
//   tcase_add_test(tc_s21_mul, test_s21_mul16);
//   tcase_add_test(tc_s21_mul, test_s21_mul17);
//   tcase_add_test(tc_s21_mul, test_s21_mul18);
//   tcase_add_test(tc_s21_mul, test_s21_mul19);
//   tcase_add_test(tc_s21_mul, test_s21_mul20);
//   tcase_add_test(tc_s21_mul, test_s21_mul21);

//   suite_add_tcase(result, tc_s21_mul);

//   return result;
// }

START_TEST(test_s21_dec2int) {
  s21_decimal src = {0};
  s21_bit_set(src.bits, 30, 1);
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CALC_OK);
}
END_TEST

START_TEST(test_s21_dec2int2) {
  s21_decimal src = {0};
  s21_bit_set(src.bits, 31, 1);
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_dec2int3) {
  s21_decimal src = {0};
  s21_bit_set(src.bits, 30, 1);
  s21_bit_set(src.bits, 127, 1);
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CALC_OK);
}
END_TEST

START_TEST(test_s21_dec2int4) {
  s21_decimal src = {0};
  s21_bit_set(src.bits, 31, 1);
  s21_bit_set(src.bits, 127, 1);
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_dec2int5) {
  s21_decimal src = {0};
  s21_bit_set(src.bits, 30, 1);
  s21_bit_set(src.bits, 127, 1);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, -1073741824);
}
END_TEST

START_TEST(test_s21_dec2int6) {
  s21_decimal src = {0};
  s21_bit_set(src.bits, 30, 1);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 1073741824);
}
END_TEST

Suite *s21_dec_from_decimal_to_int() {
  Suite *result;
  TCase *tc_s21_dec2int;
  result = suite_create("dec2int");
  tc_s21_dec2int = tcase_create("dec2int");
  tcase_add_test(tc_s21_dec2int, test_s21_dec2int);
  tcase_add_test(tc_s21_dec2int, test_s21_dec2int2);
  tcase_add_test(tc_s21_dec2int, test_s21_dec2int3);
  tcase_add_test(tc_s21_dec2int, test_s21_dec2int4);
  tcase_add_test(tc_s21_dec2int, test_s21_dec2int5);
  tcase_add_test(tc_s21_dec2int, test_s21_dec2int6);

  suite_add_tcase(result, tc_s21_dec2int);

  return result;
}

int main(void) {
  int failed = 0;
  Suite *result[] = {s21_decimal_is_less(),
                     s21_decimal_is_less_or_equal(),
                     s21_decimal_is_greater(),
                     s21_decimal_is_greater_or_equal(),
                     s21_decimal_is_equal(),
                     s21_decimal_is_not_equal(),
                     s21_decimal_s21_add(),
                     s21_decimal_s21_sub(),
                     s21_decimal_negate(),
                     s21_decimal_truncate(),
                    //  s21_decimal_floor(),
                    //  s21_decimal_from_float_to_decimal(),
                    //  s21_decimal_is_mul(),
                     s21_dec_from_decimal_to_int(),
                     NULL};

  for (int i = 0; result[i] != NULL; i++) {
    SRunner *runner = srunner_create(result[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
