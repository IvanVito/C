#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"
//Тесты
// 15 всего
// Сделанно 12 из 15
/*
Сделанно:
sin
cos
pow
exp
ceil
log
fabs
sqrt
num
atan
asin
acos
abs
fmod
floor
*/

//Синус

START_TEST(test_s21_sin) {
  ck_assert_ldouble_eq_tol(s21_sin(0.05), sinl(0.05), 1e-6);
}
END_TEST
START_TEST(test_s21_sin1) {
  ck_assert_ldouble_eq_tol(s21_sin(1 / 5), sinl(1 / 5), 1e-6);
}
END_TEST
START_TEST(test_s21_sin2) {
  ck_assert_ldouble_eq_tol(s21_sin(10), sinl(10), 1e-6);
}
END_TEST
START_TEST(test_s21_sin3) {
  ck_assert_ldouble_eq_tol(s21_sin(-10.005), sinl(-10.005), 1e-6);
}
END_TEST
START_TEST(test_s21_sin4) {
  ck_assert_ldouble_eq_tol(s21_sin(5.12356), sinl(5.12356), 1e-6);
}
END_TEST
START_TEST(test_s21_sin5) {
  ck_assert_ldouble_eq_tol(s21_sin(0.5), sinl(0.5), 1e-6);
}
END_TEST
START_TEST(test_s21_sin6) {
  ck_assert_ldouble_eq_tol(s21_sin(0.0), sinl(0.0), 1e-6);
}
END_TEST
START_TEST(test_s21_sin7) {
  ck_assert_ldouble_eq_tol(s21_sin(1), sinl(1), 1e-6);
}
END_TEST
START_TEST(test_s21_sin8) {
  ck_assert_ldouble_eq_tol(s21_sin(125), sinl(125), 1e-6);
}
END_TEST

Suite *s21_math_sin() {
  Suite *result;
  TCase *tc_sin;

  result = suite_create("s21_sin");
  tc_sin = tcase_create("s21_sin");

  tcase_add_test(tc_sin, test_s21_sin);
  tcase_add_test(tc_sin, test_s21_sin1);
  tcase_add_test(tc_sin, test_s21_sin2);
  tcase_add_test(tc_sin, test_s21_sin3);
  tcase_add_test(tc_sin, test_s21_sin4);
  tcase_add_test(tc_sin, test_s21_sin5);
  tcase_add_test(tc_sin, test_s21_sin6);
  tcase_add_test(tc_sin, test_s21_sin7);
  tcase_add_test(tc_sin, test_s21_sin8);
  suite_add_tcase(result, tc_sin);

  return result;
}

// Косинус

START_TEST(test_s21_cos) {
  ck_assert_ldouble_eq_tol(s21_cos(0.05), cosl(0.05), 1e-6);
}
END_TEST
START_TEST(test_s21_cos1) {
  ck_assert_ldouble_eq_tol(s21_cos(1 / 5), cosl(1 / 5), 1e-6);
}
END_TEST
START_TEST(test_s21_cos2) {
  ck_assert_ldouble_eq_tol(s21_cos(10), cosl(10), 1e-6);
}
END_TEST
START_TEST(test_s21_cos3) {
  ck_assert_ldouble_eq_tol(s21_cos(-10.005), cosl(-10.005), 1e-6);
}
END_TEST
START_TEST(test_s21_cos4) {
  ck_assert_ldouble_eq_tol(s21_cos(5.12356), cosl(5.12356), 1e-6);
}
END_TEST
START_TEST(test_s21_cos5) {
  ck_assert_ldouble_eq_tol(s21_cos(0.5), cosl(0.5), 1e-6);
}
END_TEST

Suite *s21_math_cos() {
  Suite *result;
  TCase *tc_cos;

  result = suite_create("s21_cos");
  tc_cos = tcase_create("s21_cos");

  tcase_add_test(tc_cos, test_s21_cos);
  tcase_add_test(tc_cos, test_s21_cos1);
  tcase_add_test(tc_cos, test_s21_cos2);
  tcase_add_test(tc_cos, test_s21_cos3);
  tcase_add_test(tc_cos, test_s21_cos4);
  tcase_add_test(tc_cos, test_s21_cos5);
  suite_add_tcase(result, tc_cos);

  return result;
}

// Тангес
START_TEST(test_s21_tan) { ck_assert_ldouble_nan(s21_tan(NAN)); }
END_TEST
START_TEST(test_s21_tan1) { ck_assert_ldouble_nan(s21_tan(+INFINITY)); }
END_TEST
START_TEST(test_s21_tan2) { ck_assert_ldouble_nan(s21_tan(-INFINITY)); }
END_TEST
START_TEST(test_s21_tan3) {
  ck_assert_ldouble_eq_tol(s21_tan(0.05), tanl(0.05), 1e-6);
}
END_TEST
START_TEST(test_s21_tan4) {
  ck_assert_ldouble_eq_tol(s21_tan(1 / 5), tanl(1 / 5), 1e-6);
}
END_TEST
START_TEST(test_s21_tan5) {
  ck_assert_ldouble_eq_tol(s21_tan(10), tanl(10), 1e-6);
}
END_TEST
START_TEST(test_s21_tan6) {
  ck_assert_ldouble_eq_tol(s21_tan(-10.005), tanl(-10.005), 1e-6);
}
END_TEST
START_TEST(test_s21_tan7) {
  ck_assert_ldouble_eq_tol(s21_tan(5.12356), tanl(5.12356), 1e-6);
}
END_TEST
START_TEST(test_s21_tan8) {
  ck_assert_ldouble_eq_tol(s21_tan(0.5), tanl(0.5), 1e-6);
}
END_TEST

Suite *s21_math_tan() {
  Suite *result;
  TCase *tc_tan;

  result = suite_create("s21_tan");
  tc_tan = tcase_create("s21_tan");

  tcase_add_test(tc_tan, test_s21_tan);
  tcase_add_test(tc_tan, test_s21_tan1);
  tcase_add_test(tc_tan, test_s21_tan2);
  tcase_add_test(tc_tan, test_s21_tan3);
  tcase_add_test(tc_tan, test_s21_tan4);
  tcase_add_test(tc_tan, test_s21_tan5);
  tcase_add_test(tc_tan, test_s21_tan6);
  tcase_add_test(tc_tan, test_s21_tan7);
  tcase_add_test(tc_tan, test_s21_tan8);
  suite_add_tcase(result, tc_tan);

  return result;
}

// Пов

START_TEST(test_s21_pow) {
  ck_assert_ldouble_eq_tol(s21_pow(1, 5), powl(1, 5), 1e-06);
}
END_TEST

START_TEST(test_s21_pow1) {
  ck_assert_ldouble_eq_tol(s21_pow(0, 5), powl(0, 5), 1e-06);
}
END_TEST

START_TEST(test_s21_pow2) {
  ck_assert_ldouble_eq_tol(s21_pow(-1, 5), powl(-1, 5), 1e-06);
}
END_TEST

START_TEST(test_s21_pow3) {
  ck_assert_ldouble_eq_tol(s21_pow(100.95, 5), powl(100.95, 5), 1e-05);
}
END_TEST

START_TEST(test_s21_pow4) {
  ck_assert_ldouble_eq_tol(s21_pow(-100, 5), powl(-100, 5), 1e-05);
}
END_TEST

Suite *s21_math_pow() {
  Suite *result;
  TCase *tc_pow;

  result = suite_create("s21_pow");
  tc_pow = tcase_create("s21_pow");

  tcase_add_test(tc_pow, test_s21_pow);
  tcase_add_test(tc_pow, test_s21_pow1);
  tcase_add_test(tc_pow, test_s21_pow2);
  tcase_add_test(tc_pow, test_s21_pow3);
  tcase_add_test(tc_pow, test_s21_pow4);
  suite_add_tcase(result, tc_pow);

  return result;
}

// Экспанента

START_TEST(exp_test_1) {
  double x = 1;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_2) {
  double x = -1;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_3) {
  double x = 0;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_4) {
  double x = -999999999999;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_5) {
  double x = -DBL_MAX;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_6) {
  double x = 1e-9;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_7) {
  double x = -1e-9;
  ck_assert_ldouble_eq_tol(s21_exp(x), expl(x), 1e-6);
}
END_TEST

START_TEST(exp_test_8) {
  ck_assert_ldouble_nan(s21_exp(NAN));
  ck_assert_ldouble_nan(expl(NAN));
}
END_TEST

START_TEST(exp_test_9) {
  ck_assert_ldouble_infinite(s21_exp(INFINITY));
  ck_assert_ldouble_infinite(expl(INFINITY));
}
END_TEST

START_TEST(exp_test_10) {
  ck_assert_ldouble_eq_tol(s21_exp(-INFINITY), expl(-INFINITY), 1e-6);
}
END_TEST

Suite *s21_exp_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_exp");

  tc = tcase_create("s21_exp_case");
  tcase_add_test(tc, exp_test_1);
  tcase_add_test(tc, exp_test_2);
  tcase_add_test(tc, exp_test_3);
  tcase_add_test(tc, exp_test_4);
  tcase_add_test(tc, exp_test_5);
  tcase_add_test(tc, exp_test_6);
  tcase_add_test(tc, exp_test_7);
  tcase_add_test(tc, exp_test_8);
  tcase_add_test(tc, exp_test_9);
  tcase_add_test(tc, exp_test_10);
  suite_add_tcase(s, tc);

  return s;
}

// Ceil

START_TEST(ceil_test_1) {
  ck_assert_ldouble_eq_tol(s21_ceil(-5.5), ceill(-5.5), 1e-6);
}
END_TEST
START_TEST(ceil_test_2) {
  ck_assert_ldouble_eq_tol(s21_ceil(5.5), ceill(5.5), 1e-6);
}
END_TEST
START_TEST(ceil_test_3) {
  ck_assert_ldouble_eq_tol(s21_ceil(555555.5), ceill(555555.5), 1e-6);
}
END_TEST
START_TEST(ceil_test_4) {
  ck_assert_ldouble_eq_tol(s21_ceil(0.1), ceill(0.1), 1e-6);
}
END_TEST
START_TEST(ceil_test_5) {
  ck_assert_ldouble_eq_tol(s21_ceil(-1.1), ceill(-1.1), 1e-6);
}
END_TEST

Suite *s21_ceil_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_ceil");

  tc = tcase_create("s21_ceil_case");
  tcase_add_test(tc, ceil_test_1);
  tcase_add_test(tc, ceil_test_2);
  tcase_add_test(tc, ceil_test_3);
  tcase_add_test(tc, ceil_test_4);
  tcase_add_test(tc, ceil_test_5);
  suite_add_tcase(s, tc);

  return s;
}

// Log

START_TEST(log_test_1) {
  ck_assert_ldouble_eq_tol(s21_log(10), logl(10), 1e-6);
}
END_TEST
START_TEST(log_test_2) { ck_assert_ldouble_infinite(s21_log(0)); }
END_TEST
START_TEST(log_test_3) { ck_assert_ldouble_nan(s21_log(-10)); }
END_TEST

Suite *s21_log_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_log");

  tc = tcase_create("s21_log_case");
  tcase_add_test(tc, log_test_1);
  tcase_add_test(tc, log_test_2);
  tcase_add_test(tc, log_test_3);
  suite_add_tcase(s, tc);

  return s;
}

// fabs

START_TEST(fabs_test_1) {
  ck_assert_ldouble_eq_tol(s21_fabs(-5.5), fabsl(-5.5), 1e-6);
}
END_TEST
START_TEST(fabs_test_2) {
  ck_assert_ldouble_eq_tol(s21_fabs(5.5), fabsl(5.5), 1e-6);
}
END_TEST
START_TEST(fabs_test_3) {
  ck_assert_ldouble_eq_tol(s21_fabs(-111111115.00005), fabsl(-111111115.00005),
                           1e-6);
}
END_TEST

Suite *s21_fabs_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_fabs");

  tc = tcase_create("s21_fabs_case");
  tcase_add_test(tc, fabs_test_1);
  tcase_add_test(tc, fabs_test_2);
  tcase_add_test(tc, fabs_test_3);
  suite_add_tcase(s, tc);

  return s;
}

// sqrt

START_TEST(sqrt_test_1) {
  ck_assert_ldouble_eq_tol(s21_sqrt(4), sqrtl(4), 1e-6);
}
END_TEST
START_TEST(sqrt_test_2) { ck_assert_ldouble_nan(s21_sqrt(-4)); }
END_TEST
START_TEST(sqrt_test_3) {
  ck_assert_ldouble_eq_tol(s21_sqrt(4.555), sqrtl(4.555), 1e-6);
}
END_TEST
START_TEST(sqrt_test_4) {
  ck_assert_ldouble_eq_tol(s21_sqrt(10004.55), sqrtl(10004.55), 1e-6);
}
END_TEST

Suite *s21_sqrt_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sqrt");

  tc = tcase_create("s21_sqrt_case");
  tcase_add_test(tc, sqrt_test_1);
  tcase_add_test(tc, sqrt_test_2);
  tcase_add_test(tc, sqrt_test_3);
  tcase_add_test(tc, sqrt_test_4);
  suite_add_tcase(s, tc);

  return s;
}

// atan
START_TEST(atan_test_1) {
  ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), 1e-6);
}
END_TEST
START_TEST(atan_test_2) {
  ck_assert_ldouble_eq_tol(s21_atan(-1), atan(-1), 1e-6);
}
END_TEST
START_TEST(atan_test_3) {
  ck_assert_ldouble_eq_tol(s21_atan(1), atan(1), 1e-6);
}
END_TEST
START_TEST(atan_test_4) {
  ck_assert_ldouble_eq_tol(s21_atan(9.999), atan(9.999), 1e-6);
}
END_TEST
START_TEST(atan_test_5) {
  ck_assert_ldouble_eq_tol(s21_atan(-1.01), atan(-1.01), 1e-6);
}
END_TEST

Suite *s21_atan_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_atan");

  tc = tcase_create("s21_atan_case");
  tcase_add_test(tc, atan_test_1);
  tcase_add_test(tc, atan_test_2);
  tcase_add_test(tc, atan_test_3);
  tcase_add_test(tc, atan_test_4);
  tcase_add_test(tc, atan_test_5);
  suite_add_tcase(s, tc);

  return s;
}

// asin
START_TEST(asin_test_1) {
  ck_assert_ldouble_eq_tol(s21_asin(0), asin(0), 1e-6);
}
END_TEST
START_TEST(asin_test_2) {
  ck_assert_ldouble_eq_tol(s21_asin(-1), asin(-1), 1e-6);
}
END_TEST
START_TEST(asin_test_3) {
  ck_assert_ldouble_eq_tol(s21_asin(1), asin(1), 1e-6);
}
END_TEST
START_TEST(asin_test_4) { ck_assert_ldouble_nan(s21_asin(9.999)); }
END_TEST
START_TEST(asin_test_5) { ck_assert_ldouble_nan(s21_asin(-1.0001)); }
END_TEST

Suite *s21_asin_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_asin");

  tc = tcase_create("s21_asin_case");
  tcase_add_test(tc, asin_test_1);
  tcase_add_test(tc, asin_test_2);
  tcase_add_test(tc, asin_test_3);
  tcase_add_test(tc, asin_test_4);
  tcase_add_test(tc, asin_test_5);
  suite_add_tcase(s, tc);

  return s;
}

// acos

START_TEST(acos_test_1) {
  ck_assert_ldouble_eq_tol(s21_acos(0), acos(0), 1e-6);
}
END_TEST
START_TEST(acos_test_2) {
  ck_assert_ldouble_eq_tol(s21_acos(-1), acos(-1), 1e-6);
}
END_TEST
START_TEST(acos_test_3) {
  ck_assert_ldouble_eq_tol(s21_acos(1), acos(1), 1e-6);
}
END_TEST
START_TEST(acos_test_4) { ck_assert_ldouble_nan(s21_acos(9.999)); }
END_TEST
START_TEST(acos_test_5) { ck_assert_ldouble_nan(s21_acos(-1.0001)); }
END_TEST

Suite *s21_acos_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_acos");

  tc = tcase_create("s21_acos_case");
  tcase_add_test(tc, acos_test_1);
  tcase_add_test(tc, acos_test_2);
  tcase_add_test(tc, acos_test_3);
  tcase_add_test(tc, acos_test_4);
  tcase_add_test(tc, acos_test_5);
  suite_add_tcase(s, tc);

  return s;
}

// abs

START_TEST(abs_test_1) { ck_assert_ldouble_eq_tol(s21_abs(-5), abs(-5), 1e-6); }
END_TEST
START_TEST(abs_test_2) { ck_assert_ldouble_eq_tol(s21_abs(5), abs(5), 1e-6); }
END_TEST
START_TEST(abs_test_3) {
  ck_assert_ldouble_eq_tol(s21_abs(-111111115), abs(-111111115), 1e-6);
}
END_TEST

Suite *s21_abs_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_abs");

  tc = tcase_create("s21_abs_case");
  tcase_add_test(tc, abs_test_1);
  tcase_add_test(tc, abs_test_2);
  tcase_add_test(tc, abs_test_3);
  suite_add_tcase(s, tc);

  return s;
}

// fmod
START_TEST(fmod_test_1) {
  ck_assert_ldouble_eq_tol(s21_fmod(3.5, 3), fmodl(3.5, 3), 1e-6);
}
END_TEST
START_TEST(fmod_test_2) {
  ck_assert_ldouble_eq_tol(s21_fmod(3.5, 7), fmodl(3.5, 7), 1e-6);
}
END_TEST
START_TEST(fmod_test_3) {
  ck_assert_ldouble_eq_tol(s21_fmod(-3.5, 3), fmodl(-3.5, 3), 1e-6);
}
END_TEST
START_TEST(fmod_test_4) {
  ck_assert_ldouble_eq_tol(s21_fmod(3.5, -4), fmodl(3.5, -4), 1e-6);
}
END_TEST
START_TEST(fmod_test_5) {
  ck_assert_ldouble_eq_tol(s21_fmod(13.5, 4.5), fmodl(13.5, 4.5), 1e-6);
}
END_TEST

Suite *s21_fmod_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_fmod");
  tc = tcase_create("s21_fmod_case");
  tcase_add_test(tc, fmod_test_1);
  tcase_add_test(tc, fmod_test_2);
  tcase_add_test(tc, fmod_test_3);
  tcase_add_test(tc, fmod_test_4);
  tcase_add_test(tc, fmod_test_5);
  suite_add_tcase(s, tc);

  return s;
}

// floor
START_TEST(floor_test_1) {
  ck_assert_ldouble_eq_tol(s21_floor(5.555), floorl(5.555), 1e-6);
}
END_TEST
START_TEST(floor_test_2) {
  ck_assert_ldouble_eq_tol(s21_floor(-5.555), floorl(-5.555), 1e-6);
}
END_TEST
START_TEST(floor_test_3) {
  ck_assert_ldouble_eq_tol(s21_floor(0.555), floorl(0.555), 1e-6);
}
END_TEST
START_TEST(floor_test_4) {
  ck_assert_ldouble_eq_tol(s21_floor(55555.555), floorl(55555.555), 1e-6);
}
END_TEST
START_TEST(floor_test_5) {
  ck_assert_ldouble_eq_tol(s21_floor(-0), floorl(-0), 1e-6);
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_floor");

  tc = tcase_create("s21_floor_case");
  tcase_add_test(tc, floor_test_1);
  tcase_add_test(tc, floor_test_2);
  tcase_add_test(tc, floor_test_3);
  tcase_add_test(tc, floor_test_4);
  tcase_add_test(tc, floor_test_5);
  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *result;
  int failed = 0;
  SRunner *runner;
  result = s21_math_sin();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_math_cos();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_math_pow();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_exp_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_ceil_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_log_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_fabs_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_sqrt_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_math_tan();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_atan_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_asin_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_acos_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_abs_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_fmod_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  result = s21_floor_suite();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
