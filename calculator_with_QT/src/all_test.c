#include <check.h>

#include "s21_smart_calc.h"

START_TEST(s21_validator_1) {
  char input[MY_MAX_INPUT] = "2+2-1\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_2) {
  char input[MY_MAX_INPUT] = "*\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_3) {
  char input[MY_MAX_INPUT] = {'\n'};
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_4) {
  char input[MY_MAX_INPUT] = "1()\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_5) {
  char input[MY_MAX_INPUT] = "(*5)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_6) {
  char input[MY_MAX_INPUT] = "5*-6\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_7) {
  char input[MY_MAX_INPUT] = "3+()\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_8) {
  char input[MY_MAX_INPUT] = "(-)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_9) {
  char input[MY_MAX_INPUT] = "(5+(3)-)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_10) {
  char input[MY_MAX_INPUT] = "(+8-(6)+)(\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_11) {
  char input[MY_MAX_INPUT] = ")+4-(3)+(\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_12) {
  char input[MY_MAX_INPUT] = "4..3\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_13) {
  char input[MY_MAX_INPUT] = "5.6.7.8\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_14) {
  char input[MY_MAX_INPUT] = "555.6+78.\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_15) {
  char input[MY_MAX_INPUT] = "-5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_16) {
  char input[MY_MAX_INPUT] = "7-(-5)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_17) {
  char input[MY_MAX_INPUT] = "sin(1)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_18) {
  char input[MY_MAX_INPUT] = "log\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_19) {
  char input[MY_MAX_INPUT] = "*5\n";

  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_20) {
  char input[MY_MAX_INPUT] = "+8\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_21) {
  char input[MY_MAX_INPUT] = "(-1-(-(1)))\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_22) {
  char input[MY_MAX_INPUT] = ")(\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_23) {
  char input[MY_MAX_INPUT] = "cos()\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_24) {
  char input[MY_MAX_INPUT] = "cos\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_25) {
  char input[MY_MAX_INPUT] = "cos(cos(1))\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_26) {
  char input[MY_MAX_INPUT] = "cos(cos(1*2/2.2))\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_27) {
  char input[MY_MAX_INPUT] = "cos(1-cos(1)-1)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_28) {
  char input[MY_MAX_INPUT] = "cos(1-cos(*)-1)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_29) {
  char input[MY_MAX_INPUT] = "cos*(1-cos(2)-1)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_30) {
  char input[MY_MAX_INPUT] = "cos(1)*cos((2)-1)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_31) {
  char input[MY_MAX_INPUT] = "(1/cos(1))*cos((2)-1)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_32) {
  char input[MY_MAX_INPUT] = " (   1/c   os(1 )) *cos (( 2) -1) \n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_33) {
  char input[MY_MAX_INPUT] = "\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_34) {
  char input[MY_MAX_INPUT] = "5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_35) {
  char input[MY_MAX_INPUT] = "5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_36) {
  char input[MY_MAX_INPUT] = "5mod2.2\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_37) {
  char input[MY_MAX_INPUT] = "5 mod 2\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_38) {
  char input[MY_MAX_INPUT] = "5 mod sin(2)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_39) {
  char input[MY_MAX_INPUT] = "sin(1) mod cos(1)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_40) {
  char input[MY_MAX_INPUT] = "sin(1) mod  5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_41) {
  char input[MY_MAX_INPUT] = "5.*sin(1)\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_42) {
  char input[MY_MAX_INPUT] = "sin(1)*.5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_43) {
  char input[MY_MAX_INPUT] = "5.*1.1\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_44) {
  char input[MY_MAX_INPUT] = "5.+1.1-.5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_45) {
  char input[MY_MAX_INPUT] = "5?\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_46) {
  char input[MY_MAX_INPUT] = "?5\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_47) {
  char input[MY_MAX_INPUT] = "5*?5\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_48) {
  char input[MY_MAX_INPUT] = "5*?\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_49) {
  char input[MY_MAX_INPUT] = "5*?cos(1)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_50) {
  char input[MY_MAX_INPUT] = "5*cos(?)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_51) {
  char input[MY_MAX_INPUT] = ".5 + 1\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_52) {
  char input[MY_MAX_INPUT] = "5. + 1\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_53) {
  char input[MY_MAX_INPUT] = "5 mod -1\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_54) {
  char input[MY_MAX_INPUT] = "-5 mod 5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_55) {
  char input[MY_MAX_INPUT] = "-5 mod s\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_56) {
  char input[MY_MAX_INPUT] = "-s mod 5\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_57) {
  char input[MY_MAX_INPUT] = "-5 + (s)\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_58) {
  char input[MY_MAX_INPUT] = "s mod 5\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_59) {
  char input[MY_MAX_INPUT] = "xx mod 8.88\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_60) {
  char input[MY_MAX_INPUT] = "(-sin(1 /2) +ln(10)) mod .7 *21 +5\n";
  ck_assert_int_eq(s21_validator(input), OK);
}
END_TEST

START_TEST(s21_validator_61) {
  char input[MY_MAX_INPUT] = "5(1) mod 8.88\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_62) {
  char input[MY_MAX_INPUT] = "( mod 8.88\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_63) {
  char input[MY_MAX_INPUT] = "0.1 +..1\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_64) {
  char input[MY_MAX_INPUT] = "0.1 ++ 1\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

START_TEST(s21_validator_65) {
  char input[MY_MAX_INPUT] = "0.1 + v\n";
  ck_assert_int_eq(s21_validator(input), ERROR);
}
END_TEST

Suite *test_s21_validator() {
  Suite *result;
  TCase *tc_s21_validator;

  result = suite_create("s21_validator");
  tc_s21_validator = tcase_create("s21_validator");

  tcase_add_test(tc_s21_validator, s21_validator_1);
  tcase_add_test(tc_s21_validator, s21_validator_2);
  tcase_add_test(tc_s21_validator, s21_validator_3);
  tcase_add_test(tc_s21_validator, s21_validator_4);
  tcase_add_test(tc_s21_validator, s21_validator_5);
  tcase_add_test(tc_s21_validator, s21_validator_6);
  tcase_add_test(tc_s21_validator, s21_validator_7);
  tcase_add_test(tc_s21_validator, s21_validator_8);
  tcase_add_test(tc_s21_validator, s21_validator_9);
  tcase_add_test(tc_s21_validator, s21_validator_10);
  tcase_add_test(tc_s21_validator, s21_validator_11);
  tcase_add_test(tc_s21_validator, s21_validator_12);
  tcase_add_test(tc_s21_validator, s21_validator_13);
  tcase_add_test(tc_s21_validator, s21_validator_14);
  tcase_add_test(tc_s21_validator, s21_validator_15);
  tcase_add_test(tc_s21_validator, s21_validator_16);
  tcase_add_test(tc_s21_validator, s21_validator_17);
  tcase_add_test(tc_s21_validator, s21_validator_18);
  tcase_add_test(tc_s21_validator, s21_validator_19);
  tcase_add_test(tc_s21_validator, s21_validator_20);
  tcase_add_test(tc_s21_validator, s21_validator_21);
  tcase_add_test(tc_s21_validator, s21_validator_22);
  tcase_add_test(tc_s21_validator, s21_validator_23);
  tcase_add_test(tc_s21_validator, s21_validator_24);
  tcase_add_test(tc_s21_validator, s21_validator_25);
  tcase_add_test(tc_s21_validator, s21_validator_26);
  tcase_add_test(tc_s21_validator, s21_validator_27);
  tcase_add_test(tc_s21_validator, s21_validator_28);
  tcase_add_test(tc_s21_validator, s21_validator_29);
  tcase_add_test(tc_s21_validator, s21_validator_30);
  tcase_add_test(tc_s21_validator, s21_validator_31);
  tcase_add_test(tc_s21_validator, s21_validator_32);
  tcase_add_test(tc_s21_validator, s21_validator_33);
  tcase_add_test(tc_s21_validator, s21_validator_34);
  tcase_add_test(tc_s21_validator, s21_validator_35);
  tcase_add_test(tc_s21_validator, s21_validator_36);
  tcase_add_test(tc_s21_validator, s21_validator_37);
  tcase_add_test(tc_s21_validator, s21_validator_38);
  tcase_add_test(tc_s21_validator, s21_validator_39);
  tcase_add_test(tc_s21_validator, s21_validator_40);
  tcase_add_test(tc_s21_validator, s21_validator_41);
  tcase_add_test(tc_s21_validator, s21_validator_42);
  tcase_add_test(tc_s21_validator, s21_validator_43);
  tcase_add_test(tc_s21_validator, s21_validator_44);
  tcase_add_test(tc_s21_validator, s21_validator_45);
  tcase_add_test(tc_s21_validator, s21_validator_46);
  tcase_add_test(tc_s21_validator, s21_validator_47);
  tcase_add_test(tc_s21_validator, s21_validator_48);
  tcase_add_test(tc_s21_validator, s21_validator_49);
  tcase_add_test(tc_s21_validator, s21_validator_50);
  tcase_add_test(tc_s21_validator, s21_validator_51);
  tcase_add_test(tc_s21_validator, s21_validator_52);
  tcase_add_test(tc_s21_validator, s21_validator_53);
  tcase_add_test(tc_s21_validator, s21_validator_54);
  tcase_add_test(tc_s21_validator, s21_validator_55);
  tcase_add_test(tc_s21_validator, s21_validator_56);
  tcase_add_test(tc_s21_validator, s21_validator_57);
  tcase_add_test(tc_s21_validator, s21_validator_58);
  tcase_add_test(tc_s21_validator, s21_validator_59);
  tcase_add_test(tc_s21_validator, s21_validator_60);
  tcase_add_test(tc_s21_validator, s21_validator_61);
  tcase_add_test(tc_s21_validator, s21_validator_62);
  tcase_add_test(tc_s21_validator, s21_validator_63);
  tcase_add_test(tc_s21_validator, s21_validator_64);
  tcase_add_test(tc_s21_validator, s21_validator_65);

  suite_add_tcase(result, tc_s21_validator);

  return result;
}

START_TEST(s21_algorithm_dijkstra_1) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "cos(1*2)-1\n";
  char true_answer[] = "1, 2, *, cos, 1, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_2) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "1+1-2.2\n";
  char true_answer[] = "1, 1, +, 2.2, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_3) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = ".1 -2.2  +1.\n";
  char true_answer[] = ".1, 2.2, -, 1., +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_4) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "-1-(-1-1)+5\n";
  char true_answer[] = "0, 1, -, 0, 1, -, 1, -, -, 5, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_5) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "-(-1-2)-(-2+5)\n";
  char true_answer[] = "0, 0, 1, -, 2, -, -, 0, 2, -, 5, +, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_6) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "1*2-1+1*(-1/2)-1*7\n";
  char true_answer[] = "1, 2, *, 1, -, 1, 0, 1, 2, /, -, *, +, 1, 7, *, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_7) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "1/2-2*2+((-1+2)/2)\n";
  char true_answer[] = "1, 2, /, 2, 2, *, -, 0, 1, -, 2, +, 2, /, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_8) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "((-1-2)/2+(-1-(-1)))\n";
  char true_answer[] = "0, 1, -, 2, -, 2, /, 0, 1, -, 0, 1, -, -, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_9) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[3 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "-1*(-1+2)/2*(-1)\n";
  char true_answer[] = "0, 1, 0, 1, -, 2, +, *, 2, /, 0, 1, -, *, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_10) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "-2.2*(((2.2-1.1)-3)+3)-1\n";
  char true_answer[] = "0, 2.2, 2.2, 1.1, -, 3, -, 3, +, *, -, 1, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_11) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "cos(cos(1+2)-1)+sin(2*1)\n";
  char true_answer[] = "1, 2, +, cos, 1, -, cos, 2, 1, *, sin, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_12) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "atan(1-2/1-log((2-1)/1)*5)\n";
  char true_answer[] = "1, 2, 1, /, -, 2, 1, -, 1, /, log, 5, *, -, atan";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_13) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] =
      "log(2/2/2/2-sqrt(9*9*9.9/2)*tan(1+1-1/2)/sin((sin(1)-1)))\n";
  char true_answer[] =
      "2, 2, /, 2, /, 2, /, 9, 9, *, 9.9, *, 2, /, sqrt, 1, 1, +, 1, 2, /, -, "
      "tan, *, 1, sin, 1, -, sin, /, -, log";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_14) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "cos(2.) mod ((8*2) mod sin(1))\n";
  char true_answer[] = "2., cos, 8, 2, *, 1, sin, mod, mod";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_15) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "(-1 mod 1) + 2*((sin(-1)-2) mod (-1-2))\n";
  char true_answer[] =
      "0, 1, 1, mod, -, 2, 0, 1, -, sin, 2, -, 0, 1, -, 2, -, mod, *, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_16) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "5 mod sin(5) * (5 * 5 mod (5 * 5))\n";
  char true_answer[] = "5, 5, sin, mod, 5, 5, *, 5, 5, *, mod, *";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_17) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "(5 mod 5 + (5)mod((5*1)-1) *cos(5-(-1)))\n";
  char true_answer[] =
      "5, 5, mod, 5, 5, 1, *, 1, -, mod, 5, 0, 1, -, -, cos, *, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_18) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "1. + .2 * 5 mod.5 ^ (sin(2-(-1.)))\n";
  char true_answer[] = "1., .2, 5, *, .5, 2, 0, 1., -, -, sin, ^, mod, +";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_19) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "5.mod 5 -((-5-.5*5)^5)\n";
  char true_answer[] = "5., 5, mod, 0, 5, -, .5, 5, *, -, 5, ^, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

START_TEST(s21_algorithm_dijkstra_20) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  char answer[2 * MY_MAX_INPUT];
  char input[MY_MAX_INPUT] = "-1-.2+2.*1.-cos(-1.^2)*5^(2.mod.0)\n";
  char true_answer[] =
      "0, 1, -, .2, -, 2., 1., *, +, 0, 1., 2, ^, -, cos, 5, 2., .0, mod, ^, "
      "*, -";
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer);
  ck_assert_str_eq(answer, true_answer);
  s21_destroy_all_stack(stack_rpn);
}
END_TEST

Suite *test_s21_algorithm_dijkstra() {
  Suite *result;
  TCase *tc_s21_algorithm_dijkstra;
  result = suite_create("s21_algorithm_dijkstra");
  tc_s21_algorithm_dijkstra = tcase_create("s21_algorithm_dijkstra");
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_1);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_2);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_3);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_4);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_5);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_6);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_7);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_8);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_9);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_10);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_11);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_12);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_13);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_14);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_15);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_16);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_17);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_18);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_19);
  tcase_add_test(tc_s21_algorithm_dijkstra, s21_algorithm_dijkstra_20);

  suite_add_tcase(result, tc_s21_algorithm_dijkstra);

  return result;
}

START_TEST(s21_calculate_1) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "cos(0)\n";
  char true_answer_rpn[] = "0, cos";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 1, 1e-7);
}
END_TEST

START_TEST(s21_calculate_2) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "cos(0)-1+2\n";
  char true_answer_rpn[] = "0, cos, 1, -, 2, +";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 2, 1e-7);
}
END_TEST

START_TEST(s21_calculate_3) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "((cos(0) +1 -3 )/2)^0.5\n";
  char true_answer_rpn[] = "0, cos, 1, +, 3, -, 2, /, 0.5, ^";
  int err = ERROR;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
}
END_TEST

START_TEST(s21_calculate_4) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "(((cos(0) +1 -3 )/2)*(-1))^0.5\n";
  char true_answer_rpn[] = "0, cos, 1, +, 3, -, 2, /, 0, 1, -, *, 0.5, ^";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 0.707106781, 1e-7);
}
END_TEST

START_TEST(s21_calculate_5) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "(-1*(-1)+2)/2+1*log(6)\n";
  char true_answer_rpn[] = "0, 1, 0, 1, -, *, -, 2, +, 2, /, 1, 6, log, *, +";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 2.27815125038, 1e-7);
}
END_TEST

START_TEST(s21_calculate_6) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "((-1*(-1)+2)/2)^2+1*ln(6*2-1/1)\n";
  char true_answer_rpn[] =
      "0, 1, 0, 1, -, *, -, 2, +, 2, /, 2, ^, 1, 6, 2, *, 1, 1, /, -, ln, *, +";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 4.6478952, 1e-7);
}
END_TEST

START_TEST(s21_calculate_7) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "cos(1.1)-sin(0.2) +tan(10)\n";
  char true_answer_rpn[] = "1.1, cos, 0.2, sin, -, 10, tan, +";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 0.90328761809, 1e-7);
}
END_TEST

START_TEST(s21_calculate_8) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "acos(1)-asin(0.2) + atan(10)\n";
  char true_answer_rpn[] = "1, acos, 0.2, asin, -, 10, atan, +";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 1.2697697, 1e-7);
}
END_TEST

START_TEST(s21_calculate_9) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "2^3^4";
  char true_answer_rpn[] = "2, 3, ^, 4, ^";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 4096, 1e-7);
}
END_TEST

START_TEST(s21_calculate_10) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "9.2mod2.0";
  char true_answer_rpn[] = "9.2, 2.0, mod";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 1.2, 1e-7);
}
END_TEST

START_TEST(s21_calculate_11) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "9.2mod0";
  char true_answer_rpn[] = "9.2, 0, mod";
  int err = ERROR;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
}
END_TEST

START_TEST(s21_calculate_12) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "sqrt(-1)";
  char true_answer_rpn[] = "0, 1, -, sqrt";
  int err = ERROR;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
}
END_TEST

START_TEST(s21_calculate_13) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "- 1 - 0.2 + 2. * 1. - cos(-1.0 ^ 2) * 3 ^1";
  char true_answer_rpn[] =
      "0, 1, -, 0.2, -, 2., 1., *, +, 0, 1.0, 2, ^, -, cos, 3, 1, ^, *, -";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
}
END_TEST

START_TEST(s21_calculate_14) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "3 mod (-9)\n";
  char true_answer_rpn[] = "3, 0, 9, -, mod";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 3, 1e-7);
}
END_TEST

START_TEST(s21_calculate_15) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "3 mod cos(0)\n";
  char true_answer_rpn[] = "3, 0, cos, mod";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 0, 1e-7);
}
END_TEST

START_TEST(s21_calculate_16) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "5\n";
  char true_answer_rpn[] = "5";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 5, 1e-7);
}
END_TEST

START_TEST(s21_calculate_17) {
  stack *stack_num_arithm = NULL;
  stack *stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "(16.7/1200)^12\n";
  char true_answer_rpn[] = "16.7, 1200, /, 12, ^";
  int err = OK;
  ck_assert_int_eq(s21_validator(input), OK);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  ck_assert_str_eq(answer_str, true_answer_rpn);
  ck_assert_int_eq(err, s21_calculate(stack_rpn, &answer));
  ck_assert_double_eq_tol(answer, 0, 1e-7);
}
END_TEST

Suite *test_s21_calculate() {
  Suite *result;
  TCase *tc_s21_calculate;
  result = suite_create("s21_calculate");
  tc_s21_calculate = tcase_create("s21_calculate");

  tcase_add_test(tc_s21_calculate, s21_calculate_1);
  tcase_add_test(tc_s21_calculate, s21_calculate_2);
  tcase_add_test(tc_s21_calculate, s21_calculate_3);
  tcase_add_test(tc_s21_calculate, s21_calculate_4);
  tcase_add_test(tc_s21_calculate, s21_calculate_5);
  tcase_add_test(tc_s21_calculate, s21_calculate_6);
  tcase_add_test(tc_s21_calculate, s21_calculate_7);
  tcase_add_test(tc_s21_calculate, s21_calculate_8);
  tcase_add_test(tc_s21_calculate, s21_calculate_9);
  tcase_add_test(tc_s21_calculate, s21_calculate_10);
  tcase_add_test(tc_s21_calculate, s21_calculate_11);
  tcase_add_test(tc_s21_calculate, s21_calculate_12);
  tcase_add_test(tc_s21_calculate, s21_calculate_13);
  tcase_add_test(tc_s21_calculate, s21_calculate_14);
  tcase_add_test(tc_s21_calculate, s21_calculate_15);
  tcase_add_test(tc_s21_calculate, s21_calculate_16);
  tcase_add_test(tc_s21_calculate, s21_calculate_17);

  suite_add_tcase(result, tc_s21_calculate);

  return result;
}

int main() {
  int failed = 0;
  Suite *result[] = {test_s21_validator(), test_s21_algorithm_dijkstra(),
                     test_s21_calculate(), NULL};

  for (int i = 0; result[i] != NULL; i++) {
    SRunner *runner = srunner_create(result[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
