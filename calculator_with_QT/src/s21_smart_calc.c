#include "s21_smart_calc.h"

int s21_smart_calc(char* input, long double* answer) {
  int err = OK;
  stack* stack_num_arithm = NULL;
  stack* stack_rpn = NULL;
  err = s21_validator(input);
  if (err == OK) {
    s21_parser(&stack_num_arithm, input);
    s21_reverse_stack(&stack_num_arithm);
    s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
    s21_reverse_stack(&stack_rpn);
    err = s21_calculate(stack_rpn, answer);
  }
  stack_num_arithm = NULL;
  stack_rpn = NULL;
  return err;
}

#ifdef GCC
int main() {
  stack* stack_num_arithm = NULL;
  stack* stack_rpn = NULL;
  long double answer = 0;
  char answer_str[2 * MY_MAX_INPUT] = {'\0'};
  char input[MY_MAX_INPUT] = "1 / 0\n";
  s21_validator(input);
  s21_parser(&stack_num_arithm, input);
  s21_reverse_stack(&stack_num_arithm);
  s21_algorithm_dijkstra(stack_num_arithm, &stack_rpn);
  s21_reverse_stack(&stack_rpn);
  s21_str_rpn(stack_rpn, answer_str);
  s21_calculate(stack_rpn, &answer);
  printf("%LF\n", answer);
  return 0;
}
#endif
