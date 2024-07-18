#include "s21_smart_calc.h"

stack* s21_init_stack(char* value, int priority) {
  stack* stack_init = malloc(sizeof(stack));
  if (stack_init != NULL) {
    strncpy(stack_init->value, value, MY_MAX_INPUT - 1);
    stack_init->priority = priority;
    stack_init->adress = NULL;
  }
  return stack_init;
}

stack* s21_push_stack(stack** stack_init, char* value, int priority) {
  if (*stack_init != NULL) {
    stack* new_stack = s21_init_stack(value, priority);
    new_stack->adress = *stack_init;
    *stack_init = new_stack;
  } else {
    *stack_init = s21_init_stack(value, priority);
  }
  return *stack_init;
}

stack* s21_pop_stack(stack* stack_delete) {
  stack* next_stack = NULL;
  if (stack_delete != NULL) {
    next_stack = stack_delete->adress;
    free(stack_delete);
  }
  return next_stack;
}

// void s21_see_all_stack(stack* stack_first) {
//   while (stack_first != NULL) {
//     printf("value: %s, priority: %d, adress: %p\n", stack_first->value,
//            stack_first->priority, stack_first->adress);
//     stack_first = stack_first->adress;
//   }
//   printf("\n");
// }

void s21_destroy_all_stack(stack* stack_start) {
  stack* temp = NULL;
  while (stack_start != NULL) {
    temp = stack_start->adress;
    free(stack_start);
    stack_start = temp;
  }
}

void s21_reverse_stack(stack** stack_start) {
  stack* reverse_stack = NULL;
  while (*stack_start != NULL) {
    reverse_stack = s21_push_stack(&reverse_stack, (*stack_start)->value,
                                   (*stack_start)->priority);
    *stack_start = s21_pop_stack(*stack_start);
  }
  *stack_start = reverse_stack;
}
