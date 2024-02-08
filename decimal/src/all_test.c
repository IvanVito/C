#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_decimal_op.h"

// int s21_add(s21_decimal, s21_decimal, s21_decimal *);

START_TEST(test_s21_add0) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+15555553,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add1) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+1152921511049297920,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add2) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "-1152921498164396032,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add3) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+9903520314283042199192993792,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add4) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+10893872345711346419112293171,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add5) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 70, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 27, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+11805916207308330762,24";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add6) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 12, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 12, 1);
  s21_bit_set(num_2.bits, 115, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+,00008192";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add7) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 95, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_add8) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 95, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+46546545477130298336207070822,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add9) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 0, 1);
  s21_decimal_exp_set(&num_1, 28);
  s21_bit_set(num_2.bits, 0, 1);
  s21_decimal_exp_set(&num_2, 28);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+,0000000000000000000000000002";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add10) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 92, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 95, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+10398696329997194309152643482,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_add11) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 92, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 89, 1);
  s21_bit_set(num_2.bits, 95, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_add(num_1, num_2, &res), CALC_OK);
  char *answer = "+10460593331961463322897599693,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

Suite *s21_test_add() {
  Suite *result = suite_create("s21_add");
  TCase *tc = tcase_create("s21_add");

  tcase_add_test(tc, test_s21_add0);
  tcase_add_test(tc, test_s21_add1);
  tcase_add_test(tc, test_s21_add2);
  tcase_add_test(tc, test_s21_add3);
  tcase_add_test(tc, test_s21_add4);
  tcase_add_test(tc, test_s21_add5);
  tcase_add_test(tc, test_s21_add6);
  tcase_add_test(tc, test_s21_add7);
  tcase_add_test(tc, test_s21_add8);
  tcase_add_test(tc, test_s21_add9);
  tcase_add_test(tc, test_s21_add10);
  tcase_add_test(tc, test_s21_add11);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_sub(s21_decimal, s21_decimal, s21_decimal *);

START_TEST(test_s21_sub0) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  num_1.bits[0] = 7777777;
  num_2.bits[0] = 7777776;
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "+1,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub1) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "-1152921498164396032,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub2) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 31, 1);
  s21_bit_set(num_1.bits, 32, 1);
  s21_bit_set(num_2.bits, 60, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "+1152921511049297920,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub3) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 127, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "+29710560942849126597578981376,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub4) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 93, 1);
  s21_bit_set(num_2.bits, 112, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "+8913168282854737979273694413,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub5) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 70, 1);
  s21_bit_set(num_1.bits, 113, 1);
  s21_bit_set(num_2.bits, 27, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "+11805916207039895306,24";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub6) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 12, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_2.bits, 12, 1);
  s21_bit_set(num_2.bits, 115, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "+,";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

START_TEST(test_s21_sub7) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_2.bits, 95, 1);
  s21_bit_set(num_1.bits, 127, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_sub8) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 112, 1);
  s21_bit_set(num_2.bits, 95, 1);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
}
END_TEST

START_TEST(test_s21_sub9) {
  s21_decimal num_1 = {0}, num_2 = {0}, res = {0};
  s21_bit_set(num_1.bits, 0, 1);
  s21_decimal_exp_set(&num_1, 28);
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 0, 1);
  s21_decimal_exp_set(&num_2, 28);
  ck_assert_int_eq(s21_sub(num_1, num_2, &res), CALC_OK);
  char *answer = "-,0000000000000000000000000002";
  ck_assert_str_eq(s21_num2str(&res), answer);
}
END_TEST

Suite *s21_test_sub() {
  Suite *result = suite_create("s21_sub");
  TCase *tc = tcase_create("s21_sub");

  tcase_add_test(tc, test_s21_sub0);
  tcase_add_test(tc, test_s21_sub1);
  tcase_add_test(tc, test_s21_sub2);
  tcase_add_test(tc, test_s21_sub3);
  tcase_add_test(tc, test_s21_sub4);
  tcase_add_test(tc, test_s21_sub5);
  tcase_add_test(tc, test_s21_sub6);
  tcase_add_test(tc, test_s21_sub7);
  tcase_add_test(tc, test_s21_sub8);
  tcase_add_test(tc, test_s21_sub9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_mul(s21_decimal, s21_decimal, s21_decimal *);

START_TEST(test_s21_mul1) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  int error;
  s21_decimal_exp_set(&num_1, 28);
  error = s21_mul(num_1, num_2, &result);
  char *answer = "+,0000000000000000000000000001";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul2) {
  s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
  int error = 0;
  s21_decimal_exp_set(&num_1, 14);
  s21_decimal_exp_set(&num_2, 14);
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_2.bits, 95, 1);
  error = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(error, CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_mul3) {
  s21_decimal num_1 = {{12, 0, 0, 0}}, num_2 = {{12, 0, 0, 0}}, result = {0};
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+144,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul4) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{15, 0, 0, 0}}, result = {0};
  s21_decimal_exp_set(&num_1, 2);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+,15";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul5) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{0, 0, 0, 0}}, result = {0};
  s21_bit_set(num_2.bits, 95, 1);
  s21_decimal_exp_set(&num_1, 14);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+396140812571321,68796771975168";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul6) {
  s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
  s21_bit_set(num_1.bits, 49, 1);
  s21_bit_set(num_2.bits, 46, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+39614081257132168796771975168,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul7) {
  s21_decimal num_1 = {0}, num_2 = {{1, 0, 0, 0}}, result = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_decimal_exp_set(&num_1, 28);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+3,9614081257132168796771975168";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul8) {
  s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
  s21_bit_set(num_1.bits, 127, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "-,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul9) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  s21_decimal_exp_set(&num_1, 14);
  s21_decimal_exp_set(&num_2, 14);
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+,0000000000000000000000000001";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul10) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  s21_bit_set(num_2.bits, 127, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "-1,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul11) {
  s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
  s21_decimal_exp_set(&num_1, 15);
  s21_decimal_exp_set(&num_2, 15);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_2.bits, 94, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+392318858461667547739736838,95";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul12) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  s21_bit_set(num_2.bits, 127, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "-1,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul13) {
  s21_decimal num_1 = {{792281625, 0, 0, 0}}, num_2 = {{782281625, 0, 0, 0}},
              result = {0};
  s21_decimal_exp_set(&num_1, 1);
  s21_decimal_exp_set(&num_2, 10);
  s21_bit_set(num_1.bits, 127, 1);
  s21_bit_set(num_2.bits, 127, 1);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+6197873,57062640625";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul14) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  s21_decimal_exp_set(&num_1, 14);
  s21_bit_set(num_1.bits, 127, 1);
  s21_decimal_exp_set(&num_2, 14);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "-,0000000000000000000000000001";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul15) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+1,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul16) {
  s21_decimal num_1 = {{0, 0, 0, 0}}, num_2 = {{0, 0, 0, 0}}, result = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_2.bits, 95, 1);
  int error = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(error, CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_mul17) {
  s21_decimal num_1 = {{1, 0, 0, 0}}, num_2 = {{1, 0, 0, 0}}, result = {0};
  s21_decimal_exp_set(&num_1, 28);
  s21_decimal_exp_set(&num_2, 28);
  int error = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(error, CALC_ESMALL);
}
END_TEST

// TODO:
// the value should be 0.00001237940039285380274899124224
// which actually can be rounded to 0.0000123794003928538027489912

START_TEST(test_s21_mul18) {
  s21_decimal num_1 = {{0, 0, 0, 0}}, num_2 = {{0, 0, 0, 0}}, result = {0};
  s21_bit_set(num_1.bits, 45, 1);
  s21_bit_set(num_2.bits, 45, 1);
  s21_decimal_exp_set(&num_1, 14);
  s21_decimal_exp_set(&num_2, 18);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+,0000123794003928538027489912";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul19) {
  s21_decimal num_1 = {{0, 0, 0, 0}}, num_2 = {{0, 0, 0, 0}}, result = {0};
  s21_bit_set(num_1.bits, 45, 1);
  s21_bit_set(num_2.bits, 45, 1);
  s21_decimal_exp_set(&num_1, 14);
  s21_decimal_exp_set(&num_2, 14);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+,1237940039285380274899124224";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul20) {
  s21_decimal num_1 = {{0, 0, 0, 0}}, num_2 = {{0, 0, 0, 0}}, result = {0};
  s21_bit_set(num_1.bits, 30, 1);
  s21_decimal_exp_set(&num_1, 3);
  s21_bit_set(num_2.bits, 57, 1);
  s21_decimal_exp_set(&num_2, 8);
  s21_mul(num_1, num_2, &result);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+1547425049106725,34362390528";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul21) {
  s21_decimal num_1 = {{0, 0, 0, 0}}, num_2 = {{0, 0, 0, 0}}, result = {0};
  s21_bit_set(num_1.bits, 32, 1);
  s21_decimal_exp_set(&num_1, 3);
  s21_bit_set(num_2.bits, 82, 1);
  s21_decimal_exp_set(&num_2, 8);
  s21_mul(num_1, num_2, &result);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+207691874341393105141219,85317";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul22) {
  s21_decimal num_1 = {0}, num_2 = {0}, result = {0};
  s21_decimal_exp_set(&num_1, 28);
  s21_decimal_exp_set(&num_2, 28);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul23) {
  s21_decimal num_1 = {{100}}, num_2 = {{1}}, result = {0};
  s21_decimal_exp_set(&num_2, 2);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+1,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

START_TEST(test_s21_mul24) {
  s21_decimal num_1 = {{123456}}, num_2 = {{0}}, result = {0};
  s21_decimal_exp_set(&num_2, 28);
  int error = s21_mul(num_1, num_2, &result);
  char *answer = "+,";
  ck_assert_str_eq(s21_num2str(&result), answer);
  ck_assert_int_eq(error, CALC_OK);
}
END_TEST

Suite *s21_test_mul() {
  Suite *result = suite_create("s21_mul");
  TCase *tc = tcase_create("s21_mul");

  tcase_add_test(tc, test_s21_mul1);
  tcase_add_test(tc, test_s21_mul2);
  tcase_add_test(tc, test_s21_mul3);
  tcase_add_test(tc, test_s21_mul4);
  tcase_add_test(tc, test_s21_mul5);
  tcase_add_test(tc, test_s21_mul6);
  tcase_add_test(tc, test_s21_mul7);
  tcase_add_test(tc, test_s21_mul8);
  tcase_add_test(tc, test_s21_mul9);
  tcase_add_test(tc, test_s21_mul10);
  tcase_add_test(tc, test_s21_mul11);
  tcase_add_test(tc, test_s21_mul12);
  tcase_add_test(tc, test_s21_mul13);
  tcase_add_test(tc, test_s21_mul14);
  tcase_add_test(tc, test_s21_mul15);
  tcase_add_test(tc, test_s21_mul16);
  tcase_add_test(tc, test_s21_mul17);
  tcase_add_test(tc, test_s21_mul18);
  tcase_add_test(tc, test_s21_mul19);
  tcase_add_test(tc, test_s21_mul20);
  tcase_add_test(tc, test_s21_mul21);
  tcase_add_test(tc, test_s21_mul22);
  tcase_add_test(tc, test_s21_mul23);
  tcase_add_test(tc, test_s21_mul24);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_div(s21_decimal, s21_decimal, s21_decimal *);

START_TEST(test_s21_div1) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  v1.bits[0] = 1;
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_EDIVZ);
}
END_TEST

START_TEST(test_s21_div2) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  s21_bit_range_set(v1.bits, 0, DEC_MANT_BITSIZE, 1);
  v2.bits[0] = 1;
  s21_decimal_exp_set(&v2, 28);
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_div3) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  s21_bit_range_set(v1.bits, 0, DEC_MANT_BITSIZE, 1);
  v2.bits[0] = 1;
  s21_decimal_exp_set(&v2, 28);
  s21_bit_flip(v2.bits, DEC_BITSIZE - 1);
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_ELARGE);
}
END_TEST

START_TEST(test_s21_div4) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  v1.bits[0] = 1;
  s21_decimal_exp_set(&v1, 28);
  s21_bit_range_set(v2.bits, 0, DEC_MANT_BITSIZE, 1);
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_ESMALL);
}
END_TEST

START_TEST(test_s21_div5) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  v1.bits[0] = 1;
  v2.bits[0] = 1;
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_OK);
  ck_assert_str_eq(s21_num2str(&res), "+1,");
}
END_TEST

START_TEST(test_s21_div6) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  v2.bits[0] = 1;
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_OK);
  ck_assert_str_eq(s21_num2str(&res), "+,");
}
END_TEST

START_TEST(test_s21_div7) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  v1.bits[0] = 1;
  v2.bits[0] = 3;
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_OK);
  ck_assert_str_eq(s21_num2str(&res), "+,3333333333333333333333333333");
}
END_TEST

START_TEST(test_s21_div8) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  s21_bit_range_set(v1.bits, 0, DEC_MANT_BITSIZE, 1);
  v2.bits[0] = 1000000000;
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_OK);
  ck_assert_str_eq(s21_num2str(&res), "+79228162514264337593,543950335");
}
END_TEST

START_TEST(test_s21_div9) {
  s21_decimal v1 = {0}, v2 = {0}, res = {0};
  s21_bit_range_set(v1.bits, 0, DEC_MANT_BITSIZE, 1);
  v2.bits[0] = 999999999;
  ck_assert_int_eq(s21_div(v1, v2, &res), CALC_OK);
  ck_assert_str_eq(s21_num2str(&res), "+79228162593492500187,03645052");
}
END_TEST

Suite *s21_test_div() {
  Suite *result = suite_create("s21_div");
  TCase *tc = tcase_create("s21_div");

  tcase_add_test(tc, test_s21_div1);
  tcase_add_test(tc, test_s21_div2);
  tcase_add_test(tc, test_s21_div3);
  tcase_add_test(tc, test_s21_div4);
  tcase_add_test(tc, test_s21_div5);
  tcase_add_test(tc, test_s21_div6);
  tcase_add_test(tc, test_s21_div7);
  tcase_add_test(tc, test_s21_div8);
  tcase_add_test(tc, test_s21_div9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_is_less(s21_decimal, s21_decimal);

START_TEST(test_s21_is_less0) {
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

Suite *s21_test_is_less() {
  Suite *result = suite_create("s21_is_less");
  TCase *tc = tcase_create("s21_is_less");

  tcase_add_test(tc, test_s21_is_less0);
  tcase_add_test(tc, test_s21_is_less1);
  tcase_add_test(tc, test_s21_is_less2);
  tcase_add_test(tc, test_s21_is_less3);
  tcase_add_test(tc, test_s21_is_less4);
  tcase_add_test(tc, test_s21_is_less5);
  tcase_add_test(tc, test_s21_is_less6);
  tcase_add_test(tc, test_s21_is_less7);
  tcase_add_test(tc, test_s21_is_less8);
  tcase_add_test(tc, test_s21_is_less9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_is_less_or_equal(s21_decimal, s21_decimal);

START_TEST(test_s21_is_less_or_equal0) {
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

Suite *s21_test_is_less_or_equal() {
  Suite *result = suite_create("s21_is_less_or_equal");
  TCase *tc = tcase_create("s21_is_less_or_equal");

  tcase_add_test(tc, test_s21_is_less_or_equal0);
  tcase_add_test(tc, test_s21_is_less_or_equal1);
  tcase_add_test(tc, test_s21_is_less_or_equal2);
  tcase_add_test(tc, test_s21_is_less_or_equal3);
  tcase_add_test(tc, test_s21_is_less_or_equal4);
  tcase_add_test(tc, test_s21_is_less_or_equal5);
  tcase_add_test(tc, test_s21_is_less_or_equal6);
  tcase_add_test(tc, test_s21_is_less_or_equal7);
  tcase_add_test(tc, test_s21_is_less_or_equal8);
  tcase_add_test(tc, test_s21_is_less_or_equal9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_is_greater(s21_decimal, s21_decimal);

START_TEST(test_s21_is_greater0) {
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

Suite *s21_test_is_greater() {
  Suite *result;
  TCase *tc;

  result = suite_create("s21_is_greater");
  tc = tcase_create("s21_is_greater");

  tcase_add_test(tc, test_s21_is_greater0);
  tcase_add_test(tc, test_s21_is_greater1);
  tcase_add_test(tc, test_s21_is_greater2);
  tcase_add_test(tc, test_s21_is_greater3);
  tcase_add_test(tc, test_s21_is_greater4);
  tcase_add_test(tc, test_s21_is_greater5);
  tcase_add_test(tc, test_s21_is_greater6);
  tcase_add_test(tc, test_s21_is_greater7);
  tcase_add_test(tc, test_s21_is_greater8);
  tcase_add_test(tc, test_s21_is_greater9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_is_greater_or_equal(s21_decimal, s21_decimal);

START_TEST(test_s21_is_greater_or_equal0) {
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

Suite *s21_test_is_greater_or_equal() {
  Suite *result = suite_create("s21_is_greater_or_equal");
  TCase *tc = tcase_create("s21_is_greater_or_equal");

  tcase_add_test(tc, test_s21_is_greater_or_equal0);
  tcase_add_test(tc, test_s21_is_greater_or_equal1);
  tcase_add_test(tc, test_s21_is_greater_or_equal2);
  tcase_add_test(tc, test_s21_is_greater_or_equal3);
  tcase_add_test(tc, test_s21_is_greater_or_equal4);
  tcase_add_test(tc, test_s21_is_greater_or_equal5);
  tcase_add_test(tc, test_s21_is_greater_or_equal6);
  tcase_add_test(tc, test_s21_is_greater_or_equal7);
  tcase_add_test(tc, test_s21_is_greater_or_equal8);
  tcase_add_test(tc, test_s21_is_greater_or_equal9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_is_equal(s21_decimal, s21_decimal);

START_TEST(test_s21_is_equal0) {
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

Suite *s21_test_is_equal() {
  Suite *result = suite_create("s21_is_equal");
  TCase *tc = tcase_create("s21_is_equal");

  tcase_add_test(tc, test_s21_is_equal0);
  tcase_add_test(tc, test_s21_is_equal1);
  tcase_add_test(tc, test_s21_is_equal2);
  tcase_add_test(tc, test_s21_is_equal3);
  tcase_add_test(tc, test_s21_is_equal4);
  tcase_add_test(tc, test_s21_is_equal5);
  tcase_add_test(tc, test_s21_is_equal6);
  tcase_add_test(tc, test_s21_is_equal7);
  tcase_add_test(tc, test_s21_is_equal8);
  tcase_add_test(tc, test_s21_is_equal9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_is_not_equal(s21_decimal, s21_decimal);

START_TEST(test_s21_is_not_equal0) {
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

Suite *s21_test_is_not_equal() {
  Suite *result = suite_create("s21_is_not_equal");
  TCase *tc = tcase_create("s21_is_not_equal");

  tcase_add_test(tc, test_s21_is_not_equal0);
  tcase_add_test(tc, test_s21_is_not_equal1);
  tcase_add_test(tc, test_s21_is_not_equal2);
  tcase_add_test(tc, test_s21_is_not_equal3);
  tcase_add_test(tc, test_s21_is_not_equal4);
  tcase_add_test(tc, test_s21_is_not_equal5);
  tcase_add_test(tc, test_s21_is_not_equal6);
  tcase_add_test(tc, test_s21_is_not_equal7);
  tcase_add_test(tc, test_s21_is_not_equal8);
  tcase_add_test(tc, test_s21_is_not_equal9);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_from_int_to_decimal(int, s21_decimal *);

START_TEST(test_s21_int2dec1) {
  s21_decimal dst = {0};
  int src = -2147483648, res = 0;
  res = s21_from_int_to_decimal(src, &dst);
  char *answer = "-2147483648,";
  ck_assert_str_eq(s21_num2str(&dst), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_int2dec2) {
  s21_decimal dst = {0};
  int src = 2147483647, res = 0;
  res = s21_from_int_to_decimal(src, &dst);
  char *answer = "+2147483647,";
  ck_assert_str_eq(s21_num2str(&dst), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_int2dec3) {
  s21_decimal dst = {0};
  int src = 0, res = 0;
  res = s21_from_int_to_decimal(src, &dst);
  char *answer = "+,";
  ck_assert_str_eq(s21_num2str(&dst), answer);
  ck_assert_int_eq(res, CALC_OK);
}

Suite *s21_test_from_int_to_decimal() {
  Suite *result = suite_create("s21_from_int_to_decimal");
  TCase *tc = tcase_create("s21_from_int_to_decimal");

  tcase_add_test(tc, test_s21_int2dec1);
  tcase_add_test(tc, test_s21_int2dec2);
  tcase_add_test(tc, test_s21_int2dec3);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_from_float_to_decimal(float, s21_decimal *);

START_TEST(test_from_float_to_decimal) {
  float num_1 = 10.01023F;
  s21_decimal result = {0}, decimal_check = {{0xF463F, 0, 0, 0x5 << 16}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal1) {
  float num_1 = 123456.789F;
  s21_decimal result = {0}, decimal_check = {{0x12D688, 0, 0, 0x1 << 16}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal2) {
  float num_1 = INFINITY;
  s21_decimal num_2 = {0};
  ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal3) {
  float num_1 = -INFINITY;
  s21_decimal actual_result = {0};
  actual_result.bits[0] = 123;
  actual_result.bits[1] = 456;
  actual_result.bits[2] = 789;
  s21_bit_set(actual_result.bits, 127, 1);
  ck_assert_int_eq(s21_from_float_to_decimal(num_1, &actual_result), 1);
  ck_assert_str_eq(s21_num2str(&actual_result), "-14554481076115341312123,");
}

START_TEST(test_from_float_to_decimal4) {
  float num_1 = -INFINITY;
  s21_decimal num_2 = {0};
  ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal5) {
  float num_1 = -NAN;
  s21_decimal num_2 = {0};
  ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal6) {
  float num_1 = NAN;
  s21_decimal num_2 = {0};
  ck_assert_int_eq(s21_from_float_to_decimal(num_1, &num_2), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal7) {
  float num_1 = 0.0F;
  ck_assert_int_eq(s21_from_float_to_decimal(num_1, NULL), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal8) {
  float num_1 = -09135.09135F;
  s21_decimal result = {0}, decimal_check = {{0x8B63F4, 0, 0, 0x80030000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal9) {
  float num_1 = 5.0F;
  s21_decimal actual_result = {0};
  actual_result.bits[0] = 123;
  actual_result.bits[1] = 456;
  actual_result.bits[2] = 789;
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+5,");
}
END_TEST

START_TEST(test_from_float_to_decimal10) {
  float num_1 = FLT_MAX;
  s21_decimal actual_result = {0};
  actual_result.bits[0] = 123;
  s21_bit_set(actual_result.bits, 127, 1);
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "-123,");
}
END_TEST

START_TEST(test_from_float_to_decimal11) {
  float num_1 = 79228162514264337593543950335.0F;
  s21_decimal actual_result = {0};
  actual_result.bits[0] = 123;
  actual_result.bits[1] = 456;
  actual_result.bits[2] = 789;
  s21_from_float_to_decimal(num_1, &actual_result);
  char answer[] = "+79228160000000000000000000000,";
  ck_assert_str_eq(s21_num2str(&actual_result), answer);
}
END_TEST

START_TEST(test_from_float_to_decimal12) {
  float num_1 = 7922816251426433759354395033.0F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  char answer[] = "+7922816000000000000000000000,";
  ck_assert_str_eq(s21_num2str(&actual_result), answer);
}
END_TEST

START_TEST(test_from_float_to_decimal13) {
  float num_1 = 0.00054321054321F;
  s21_decimal result = {0}, decimal_check = {{0x52E329, 0, 0, 0xA0000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal14) {
  float num_1 = 54321758321.00054321054321F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+54321760000,");
}
END_TEST

START_TEST(test_from_float_to_decimal15) {
  float num_1 = 5432105.321054321F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+5432106,");
}
END_TEST

START_TEST(test_from_float_to_decimal16) {
  float num_1 = -0.0F;
  s21_decimal actual_result = {0}, expected_result = {0};
  s21_bit_set(expected_result.bits, 127, 1);
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_int_eq(s21_is_equal(actual_result, expected_result), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal17) {
  float num_1 = 0.0F;
  s21_decimal actual_result = {0}, expected_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_int_eq(s21_is_equal(actual_result, expected_result), 1);
}

START_TEST(test_from_float_to_decimal18) {
  float num_1 = -0.000000000000000000000000000121054832F;
  s21_decimal result = {0}, decimal_check = {{0x1, 0, 0, 0x801C0000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal19) {
  float num_1 = -10.980355F;
  s21_decimal result = {0}, decimal_check = {{0x10C134, 0, 0, 0x80050000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal20) {
  float num_1 = 10.980365F;
  s21_decimal result = {0}, decimal_check = {{0x10C134, 0, 0, 0x5 << 16}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal21) {
  float num_1 = 10.980355F;
  s21_decimal result = {0}, decimal_check = {{0x10C134, 0, 0, 0x5 << 16}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal22) {
  float num_1 = 1234567500.12F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+1234568000,");
}

START_TEST(test_from_float_to_decimal23) {
  float num_1 = 1234568500.12F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+1234568000,");
}

START_TEST(test_from_float_to_decimal24) {
  float num_1 = 123459999.3003F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+123460000,");
}

START_TEST(test_from_float_to_decimal25) {
  float num_1 = 34567995.0F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+34568000,");
}

START_TEST(test_from_float_to_decimal26) {
  float num_1 = 9999999999.000000999F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "+10000000000,");
}

START_TEST(test_from_float_to_decimal27) {
  float num_1 = 123456.78F;
  s21_decimal result = {0}, decimal_check = {{0x12D688, 0, 0, 0x1 << 16}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal28) {
  float num_1 = -0.000000000000000000000000469790976F;
  s21_decimal result = {0}, decimal_check = {{0x125A, 0, 0, 0x801C0000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal29) {
  float num_1 = -0.00000000123F;
  s21_decimal result = {0}, decimal_check = {{0x7B, 0, 0, 0x800B0000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal30) {
  float num_1 = 0.000000000000000000228401628F;
  s21_decimal result = {0}, decimal_check = {{0x22D9F0, 0, 0, 0x190000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal31) {
  float num_1 = 0.0123F;
  s21_decimal result = {0}, decimal_check = {{0x7B, 0, 0, 0x40000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal32) {
  float num_1 = 4882.71582F;
  s21_decimal result = {0}, decimal_check = {{0x4A811C, 0, 0, 0x30000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_from_float_to_decimal33) {
  float num_1 = -54321758321.00054321054321F;
  s21_decimal actual_result = {0};
  s21_from_float_to_decimal(num_1, &actual_result);
  ck_assert_str_eq(s21_num2str(&actual_result), "-54321760000,");
}
END_TEST

START_TEST(test_from_float_to_decimal34) {
  float num_1 = -0.0000000000000000000000311720F;
  s21_decimal result = {0}, decimal_check = {{0x79C4, 0, 0, 0x801C0000}};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal35) {
  float num_1 = 1e-29F;
  s21_decimal result = {{1, 2, 3, 0x80000000}}, decimal_check = {0};
  int code = s21_from_float_to_decimal(num_1, &result);
  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST

Suite *s21_test_from_float_to_decimal() {
  Suite *result = suite_create("s21_from_float_to_decimal");
  TCase *tc = tcase_create("s21_from_float_to_decimal");

  tcase_add_test(tc, test_from_float_to_decimal);
  tcase_add_test(tc, test_from_float_to_decimal1);
  tcase_add_test(tc, test_from_float_to_decimal2);
  tcase_add_test(tc, test_from_float_to_decimal3);
  tcase_add_test(tc, test_from_float_to_decimal4);
  tcase_add_test(tc, test_from_float_to_decimal5);
  tcase_add_test(tc, test_from_float_to_decimal6);
  tcase_add_test(tc, test_from_float_to_decimal7);
  tcase_add_test(tc, test_from_float_to_decimal8);
  tcase_add_test(tc, test_from_float_to_decimal9);
  tcase_add_test(tc, test_from_float_to_decimal10);
  tcase_add_test(tc, test_from_float_to_decimal11);
  tcase_add_test(tc, test_from_float_to_decimal12);
  tcase_add_test(tc, test_from_float_to_decimal13);
  tcase_add_test(tc, test_from_float_to_decimal14);
  tcase_add_test(tc, test_from_float_to_decimal15);
  tcase_add_test(tc, test_from_float_to_decimal16);
  tcase_add_test(tc, test_from_float_to_decimal17);
  tcase_add_test(tc, test_from_float_to_decimal18);
  tcase_add_test(tc, test_from_float_to_decimal19);
  tcase_add_test(tc, test_from_float_to_decimal20);
  tcase_add_test(tc, test_from_float_to_decimal21);
  tcase_add_test(tc, test_from_float_to_decimal22);
  tcase_add_test(tc, test_from_float_to_decimal23);
  tcase_add_test(tc, test_from_float_to_decimal24);
  tcase_add_test(tc, test_from_float_to_decimal25);
  tcase_add_test(tc, test_from_float_to_decimal26);
  tcase_add_test(tc, test_from_float_to_decimal27);
  tcase_add_test(tc, test_from_float_to_decimal28);
  tcase_add_test(tc, test_from_float_to_decimal29);
  tcase_add_test(tc, test_from_float_to_decimal30);
  tcase_add_test(tc, test_from_float_to_decimal31);
  tcase_add_test(tc, test_from_float_to_decimal32);
  tcase_add_test(tc, test_from_float_to_decimal33);
  tcase_add_test(tc, test_from_float_to_decimal34);
  tcase_add_test(tc, test_from_float_to_decimal35);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_from_decimal_to_int(s21_decimal, int *);

START_TEST(test_s21_dec2int1) {
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

Suite *s21_test_from_decimal_to_int() {
  Suite *result = suite_create("s21_from_decimal_to_int");
  TCase *tc = tcase_create("s21_from_decimal_to_int");

  tcase_add_test(tc, test_s21_dec2int1);
  tcase_add_test(tc, test_s21_dec2int2);
  tcase_add_test(tc, test_s21_dec2int3);
  tcase_add_test(tc, test_s21_dec2int4);
  tcase_add_test(tc, test_s21_dec2int5);
  tcase_add_test(tc, test_s21_dec2int6);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_from_decimal_to_float(s21_decimal, float *);

START_TEST(test_from_decimal_to_float0) {
  s21_decimal num_1 = {{0x7B, 0, 0, 0x40000}};
  float actual_result = 0.0F, expected_result = 0.0123F;
  s21_from_decimal_to_float(num_1, &actual_result);
  ck_assert_float_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_from_decimal_to_float1) {
  s21_decimal num_1 = {{0, 0, 0, 0x80000000}};
  float actual_result = 0.0F, expected_result = -0.0F;
  s21_from_decimal_to_float(num_1, &actual_result);
  ck_assert_float_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_from_decimal_to_float2) {
  s21_decimal num_1 = {{123456, 0, 0, 0x80000000}};
  float actual_result = 0.0F, expected_result = -123456.0F;
  s21_from_decimal_to_float(num_1, &actual_result);
  ck_assert_float_eq(actual_result, expected_result);
}
END_TEST

START_TEST(test_from_decimal_to_float3) {
  s21_decimal num_1 = {{12345678, 0, 0, 0}};
  float actual_result = 0.0F, expected_result = 12345678.0F;
  s21_from_decimal_to_float(num_1, &actual_result);
  ck_assert_float_eq(actual_result, expected_result);
}
END_TEST

// TODO: DISGUSTING WORST CASING HANDLING
Suite *s21_test_from_decimal_to_float() {
  Suite *result = suite_create("s21_from_decimal_to_float");
  TCase *tc = tcase_create("s21_from_decimal_to_float");

  tcase_add_test(tc, test_from_decimal_to_float0);
  tcase_add_test(tc, test_from_decimal_to_float1);
  tcase_add_test(tc, test_from_decimal_to_float2);
  tcase_add_test(tc, test_from_decimal_to_float3);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_floor(s21_decimal, s21_decimal *);

START_TEST(test_floor0) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_decimal_exp_set(&num_1, 1);
  s21_floor(num_1, &res);
  char *actual_result = "+3961408125713216879677197516,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor1) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_decimal_exp_set(&num_1, 1);
  s21_floor(num_1, &res);
  char *actual_result = "-3961408125713216879677197517,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor2) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_decimal_exp_set(&num_1, 27);
  s21_floor(num_1, &res);
  char *actual_result = "-40,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor3) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_decimal_exp_set(&num_1, 28);
  s21_floor(num_1, &res);
  char *actual_result = "-4,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor4) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 90, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_decimal_exp_set(&num_1, 28);
  s21_floor(num_1, &res);
  char *actual_result = "-1,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor5) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_decimal_exp_set(&num_1, 27);
  s21_floor(num_1, &res);
  char *actual_result = "+39,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor6) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 95, 1);
  s21_decimal_exp_set(&num_1, 28);
  s21_floor(num_1, &res);
  char *actual_result = "+3,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor7) {
  s21_decimal num_1 = {0}, res = {0};
  s21_bit_set(num_1.bits, 90, 1);
  s21_decimal_exp_set(&num_1, 28);
  s21_floor(num_1, &res);
  char *actual_result = "+,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

START_TEST(test_floor8) {
  s21_decimal num_1 = {0}, res = {0};
  s21_decimal_exp_set(&num_1, 28);
  s21_floor(num_1, &res);
  char *actual_result = "+,";
  ck_assert_str_eq(s21_num2str(&res), actual_result);
}
END_TEST

Suite *s21_test_floor() {
  Suite *result = suite_create("s21_floor");
  TCase *tc = tcase_create("s21_floor");

  tcase_add_test(tc, test_floor0);
  tcase_add_test(tc, test_floor1);
  tcase_add_test(tc, test_floor2);
  tcase_add_test(tc, test_floor3);
  tcase_add_test(tc, test_floor4);
  tcase_add_test(tc, test_floor5);
  tcase_add_test(tc, test_floor6);
  tcase_add_test(tc, test_floor7);
  tcase_add_test(tc, test_floor8);

  suite_add_tcase(result, tc);
  return result;
}

// int s21_round(s21_decimal, s21_decimal *);

START_TEST(test_s21_round1) {
  s21_decimal dst = {0}, src = {0};
  int res = 0;
  s21_bit_set(dst.bits, 95, 1);
  s21_decimal_exp_set(&dst, 28);
  res = s21_round(dst, &src);
  char *answer = "+4,";
  ck_assert_str_eq(s21_num2str(&src), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_round2) {
  s21_decimal dst = {0}, src = {0};
  int res = 0;
  s21_bit_set(dst.bits, 95, 1);
  s21_bit_set(dst.bits, 127, 1);
  s21_decimal_exp_set(&dst, 28);
  res = s21_round(dst, &src);
  char *answer = "-4,";
  ck_assert_str_eq(s21_num2str(&src), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_round3) {
  s21_decimal dst = {0}, src = {0};
  int res = 0;
  s21_bit_set(dst.bits, 95, 1);
  res = s21_round(dst, &src);
  char *answer = "+39614081257132168796771975168,";
  ck_assert_str_eq(s21_num2str(&src), answer);
  ck_assert_int_eq(res, CALC_ELARGE);
}

START_TEST(test_s21_round4) {
  s21_decimal dst = {0}, src = {0};
  int res = 0;
  s21_bit_set(dst.bits, 1, 1);
  s21_decimal_exp_set(&dst, 1);
  res = s21_round(dst, &src);
  char *answer = "+,";
  ck_assert_str_eq(s21_num2str(&src), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_round5) {
  s21_decimal dst = {0}, src = {0};
  int res = 0;
  s21_bit_set(dst.bits, 1, 1);
  s21_bit_set(dst.bits, 127, 1);
  s21_decimal_exp_set(&dst, 1);
  res = s21_round(dst, &src);
  char *answer = "-,";
  ck_assert_str_eq(s21_num2str(&src), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_round6) {
  s21_decimal dst = {{149999}}, src = {0};
  int res = 0;
  s21_bit_set(dst.bits, 127, 1);
  s21_decimal_exp_set(&dst, 5);
  res = s21_round(dst, &src);
  char *answer = "-2,";
  ck_assert_str_eq(s21_num2str(&src), answer);
  ck_assert_int_eq(res, CALC_OK);
}

START_TEST(test_s21_round7) {
  s21_decimal dst = {{2147483647}}, src = {0};
  int res = 0;
  s21_decimal_exp_set(&dst, 5);
  s21_bit_set(dst.bits, 127, 1);
  res = s21_round(dst, &src);
  char *answer = "-21475,";
  ck_assert_int_eq(res, CALC_OK);
  ck_assert_str_eq(s21_num2str(&src), answer);
}

Suite *s21_test_round() {
  Suite *result = suite_create("s21_round");
  TCase *tc = tcase_create("s21_round");

  tcase_add_test(tc, test_s21_round1);
  tcase_add_test(tc, test_s21_round2);
  tcase_add_test(tc, test_s21_round3);
  tcase_add_test(tc, test_s21_round4);
  tcase_add_test(tc, test_s21_round5);
  tcase_add_test(tc, test_s21_round6);
  tcase_add_test(tc, test_s21_round7);

  suite_add_tcase(result, tc);

  return result;
}

// int s21_truncate(s21_decimal, s21_decimal *);
START_TEST(test_truncate0) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 80, 1);
  s21_bit_set(num_1.bits, 116, 1);
  s21_truncate(num_1, &num_2);
  ck_assert_str_eq(s21_num2str(&num_2), "+120892581,");
}
END_TEST

START_TEST(test_truncate1) {
  s21_decimal num_1 = {0}, num_2 = {0};
  ck_assert_int_eq(s21_truncate(num_1, &num_2), OP_OK);
}
END_TEST

START_TEST(test_truncate2) {
  s21_decimal num_1 = {0};
  ck_assert_int_eq(s21_truncate(num_1, NULL), OP_ERR);
}
END_TEST

START_TEST(test_truncate3) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 93, 1);
  s21_bit_set(num_1.bits, 94, 1);
  s21_bit_set(num_1.bits, 95, 1);
  s21_bit_set(num_1.bits, 114, 1);
  s21_bit_set(num_1.bits, 115, 1);
  s21_bit_set(num_1.bits, 116, 1);  // changed here too, looks good
  s21_truncate(num_1, &num_2);
  ck_assert_str_eq(s21_num2str(&num_2), "+6,");
}
END_TEST

START_TEST(test_truncate4) {
  s21_decimal num_1 = {0}, num_2 = {0};
  s21_bit_set(num_1.bits, 117, 1);
  s21_bit_set(num_1.bits, 127, 1);
  s21_truncate(num_1, &num_2);
  ck_assert_str_eq(s21_num2str(&num_2), "-,");
}
END_TEST

Suite *s21_test_truncate() {
  Suite *result = suite_create("s21_truncate");
  TCase *tc = tcase_create("s21_truncate");

  tcase_add_test(tc, test_truncate0);
  tcase_add_test(tc, test_truncate1);
  tcase_add_test(tc, test_truncate2);
  tcase_add_test(tc, test_truncate3);
  tcase_add_test(tc, test_truncate4);

  suite_add_tcase(result, tc);

  return result;
}
// int s21_negate(s21_decimal, s21_decimal *);

START_TEST(test_negate0) {
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
  s21_negate(num_1, &num_1);
  ck_assert_str_eq(s21_num2str(&num_1), "-,");
}
END_TEST

START_TEST(test_negate4) {
  s21_decimal num_1 = {0};
  s21_bit_set(num_1.bits, 127, 1);
  s21_negate(num_1, &num_1);
  ck_assert_str_eq(s21_num2str(&num_1), "+,");
}
END_TEST

Suite *s21_test_negate() {
  Suite *result = suite_create("s21_negate");
  TCase *tc = tcase_create("s21_negate");

  tcase_add_test(tc, test_negate0);
  tcase_add_test(tc, test_negate1);
  tcase_add_test(tc, test_negate2);
  tcase_add_test(tc, test_negate3);
  tcase_add_test(tc, test_negate4);

  suite_add_tcase(result, tc);

  return result;
}

int main(void) {
  int failed = 0;
  Suite *result[] = {s21_test_add(),
                     s21_test_sub(),
                     s21_test_mul(),
                     s21_test_div(),
                     s21_test_is_less(),
                     s21_test_is_less_or_equal(),
                     s21_test_is_greater(),
                     s21_test_is_greater_or_equal(),
                     s21_test_is_equal(),
                     s21_test_is_not_equal(),
                     s21_test_from_int_to_decimal(),
                     s21_test_from_float_to_decimal(),
                     s21_test_from_decimal_to_int(),
                     s21_test_from_decimal_to_float(),
                     s21_test_floor(),
                     s21_test_round(),
                     s21_test_truncate(),
                     s21_test_negate(),
                     NULL};

  for (int i = 0; result[i] != NULL; i++) {
    SRunner *runner = srunner_create(result[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}