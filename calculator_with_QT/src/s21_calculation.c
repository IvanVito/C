#include "s21_smart_calc.h"

int s21_calculate(stack* stack_rpn, long double* answer) {
  stack* stack_num = NULL;
  int err = OK;
  char operation;
  char function[10] = {'\0'}, num_1[MY_MAX_INPUT] = {'\0'},
       num_2[MY_MAX_INPUT] = {'\0'};
  while (stack_rpn != NULL) {
    if ((atof(stack_rpn->value) != 0.0 ||
         strstr(KINDS_OF_NULL, (stack_rpn)->value) != NULL)) {
      s21_push_num(&stack_num, &stack_rpn, stack_rpn->value);
    } else if (isalpha((stack_rpn->value)[0])) {
      strncpy(function, stack_rpn->value, 9);
      if (strcmp(function, "mod") == 0) {
        s21_init_num(&stack_num, num_2);
        s21_init_num(&stack_num, num_1);
      } else {
        s21_init_num(&stack_num, num_2);
      }
      err = s21_calc_function(function, num_1, num_2);
      s21_push_num(&stack_num, &stack_rpn, num_2);
    } else if (strstr(NOT_DOUBLE_ARITHM, stack_rpn->value)) {
      operation = (stack_rpn->value)[0];
      s21_init_num(&stack_num, num_1);
      s21_init_num(&stack_num, num_2);
      err = s21_calc_operation(&operation, num_1, num_2);
      s21_push_num(&stack_num, &stack_rpn, num_2);
    }
  }
  if (stack_num != NULL) s21_init_num(&stack_num, num_2);
  if (err == OK) sscanf(num_2, "%15LF", answer);
  return err;
}

void s21_init_num(stack** stack_num, char* num) {
  if (stack_num != NULL && *stack_num != NULL && num != NULL) {
    strncpy(num, (*stack_num)->value, MY_MAX_INPUT - 1);
    *stack_num = s21_pop_stack(*stack_num);
  }
}

void s21_push_num(stack** stack_num, stack** stack_rpn, char* num) {
  if (stack_num != NULL && stack_rpn != NULL) {
    *stack_num = s21_push_stack(stack_num, num, 1);
    *stack_rpn = s21_pop_stack(*stack_rpn);
  }
}

int s21_calc_function(char* function, char* number_1, char* number_2) {
  int err = 0;
  long double num_1 = 0, num_2 = 0;
  sscanf(number_1, "%15LF", &num_1);
  sscanf(number_2, "%15LF", &num_2);
  if (strcmp(function, "cos") == 0)
    num_2 = cosl(num_2);
  else if (strcmp(function, "sin") == 0)
    num_2 = sinl(num_2);
  else if (strcmp(function, "mod") == 0) {
    if (num_2 != 0)
      num_2 = num_1 - (int)((num_1) / (num_2)) * (num_2);
    else
      err = ERROR;
  } else if (strcmp(function, "tan") == 0)
    num_2 = tanl(num_2);
  else if (strcmp(function, "acos") == 0)
    num_2 = acosl(num_2);
  else if (strcmp(function, "asin") == 0)
    num_2 = asinl(num_2);
  else if (strcmp(function, "atan") == 0)
    num_2 = atanl(num_2);
  else if (strcmp(function, "sqrt") == 0)
    num_2 = sqrtl(num_2);
  else if (strcmp(function, "ln") == 0)
    num_2 = logl(num_2);
  else if (strcmp(function, "log") == 0)
    num_2 = logl(num_2) / logl(10);
  s21_clear(function);
  if (isfinite(num_2) == 0) err = ERROR;
  if (err == OK) snprintf(number_2, MY_MAX_INPUT, "%.15Lf", num_2);
  return err;
}

int s21_calc_operation(char* operation, char* number_1, char* number_2) {
  int err = 0;
  long double num_1 = 0, num_2 = 0;
  sscanf(number_1, "%15LF", &num_1);
  sscanf(number_2, "%15LF", &num_2);
  if (*operation == '+')
    num_2 += (num_1);
  else if (*operation == '-')
    num_2 -= (num_1);
  else if (*operation == '*')
    num_2 *= (num_1);
  else if (*operation == '/')
    num_2 /= (num_1);
  else if (*operation == '^')
    num_2 = powl(num_2, num_1);
  *operation = '\0';
  if (isfinite(num_2) == 0) err = ERROR;
  if (err == OK) snprintf(number_2, MY_MAX_INPUT, "%.15Lf", num_2);
  return err;
}
