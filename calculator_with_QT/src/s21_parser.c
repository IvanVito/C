#include "s21_smart_calc.h"

void s21_parser(stack** stack_num_arithm, char* input) {
  char temp[MY_MAX_INPUT] = {'\0'};
  int carriage_temp = 0, carriage_input = 0, exit = 0;
  if (strchr(UNAR, input[0]))
    *stack_num_arithm = s21_push_stack(stack_num_arithm, "0", 0);
  while (strchr(OVER, input[carriage_input]) == NULL) {
    while (((input[carriage_input] >= '0' && input[carriage_input] <= '9') ||
            (input[carriage_input] == '.') ||
            (input[carriage_input] >= 'a' && input[carriage_input] <= 'z')) &&
           (exit == 0)) {
      temp[carriage_temp] = input[carriage_input];
      carriage_temp++;
      carriage_input++;
      if (strcmp(temp, "mod") == 0) exit = 1;
      if (carriage_temp >= 1 && carriage_temp < MY_MAX_INPUT &&
          ((isdigit(temp[carriage_temp - 1]) ||
            temp[carriage_temp - 1] == '.') &&
           isalpha(input[carriage_input])))
        exit = 1;
    }
    exit = 0;
    if ((atof(temp) != 0.0) || (strcmp(".0", temp) == 0) ||
        (strcmp("0", temp) == 0) || (strcmp("0.", temp) == 0) ||
        (strcmp("0.0000000", temp) == 0))
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 0);
    else if (strcmp(temp, "mod") == 0)
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 2);
    else if (strstr(FUNCTION, temp) && strchr(OVER, temp[0]) == NULL)
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 4);
    s21_reset(temp, &carriage_temp);
    temp[carriage_temp] = input[carriage_input];
    if (carriage_input >= 1 && strchr(UNAR, temp[0]) &&
        input[carriage_input - 1] == '(' && carriage_input != 0) {
      *stack_num_arithm = s21_push_stack(stack_num_arithm, "0", 0);
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 1);
    } else if (strchr(UNAR, temp[0]))
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 1);
    else if (temp[0] == '*' || temp[0] == '/')
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 2);
    else if (temp[0] == '^')
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, 3);
    else if (strchr(BRACKETS, temp[0]))
      *stack_num_arithm = s21_push_stack(stack_num_arithm, temp, -1);
    if (strchr(OVER, input[carriage_input]) == NULL &&
        isalpha(input[carriage_input]) == 0 &&
        isdigit(input[carriage_input]) == 0 && input[carriage_input] != '.')
      carriage_input++;
    s21_reset(temp, &carriage_temp);
  }
}
