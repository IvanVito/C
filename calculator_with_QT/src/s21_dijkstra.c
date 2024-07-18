#include "s21_smart_calc.h"

void s21_algorithm_dijkstra(stack* stack_num_arithm, stack** stack_rpn) {
  stack* stack_support = NULL;
  while (stack_num_arithm != NULL) {
    if (stack_num_arithm->priority == 0)
      s21_add_stack_rpn(stack_rpn, &stack_num_arithm);
    if (stack_num_arithm != NULL && (stack_num_arithm->priority == 4 ||
                                     (stack_num_arithm->value)[0] == '(')) {
      s21_add_stack_support(&stack_support, &stack_num_arithm);
    }
    if (stack_num_arithm != NULL && (stack_num_arithm->value[0]) == ')') {
      while (stack_support != NULL && (stack_support->value[0]) != '(') {
        s21_add_stack_rpn(stack_rpn, &stack_support);
      }
      stack_support = s21_pop_stack(stack_support);
      if (stack_support != NULL && stack_support->priority == 4)
        s21_add_stack_rpn(stack_rpn, &stack_support);
      stack_num_arithm = s21_pop_stack(stack_num_arithm);
    }
    if ((stack_num_arithm != NULL) && (stack_num_arithm->priority >= 1) &&
        (stack_num_arithm->priority <= 4)) {
      while ((stack_support != NULL) &&
             (stack_num_arithm->priority <= stack_support->priority))
        s21_add_stack_rpn(stack_rpn, &stack_support);
      s21_add_stack_support(&stack_support, &stack_num_arithm);
    }
  }
  while (stack_support != NULL) {
    if (stack_support->priority != -1)
      s21_add_stack_rpn(stack_rpn, &stack_support);
  }
}

void s21_add_stack_support(stack** stack_support, stack** stack_num_arithm) {
  *stack_support = s21_push_stack(stack_support, (*stack_num_arithm)->value,
                                  (*stack_num_arithm)->priority);
  *stack_num_arithm = s21_pop_stack(*stack_num_arithm);
}

void s21_add_stack_rpn(stack** stack_rpn, stack** sign_or_num) {
  *stack_rpn = s21_push_stack(stack_rpn, (*sign_or_num)->value,
                              (*sign_or_num)->priority);
  *sign_or_num = s21_pop_stack(*sign_or_num);
}