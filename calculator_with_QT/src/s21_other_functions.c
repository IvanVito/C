#include "s21_smart_calc.h"

void s21_clear(char* temp) {
  int i = 0;
  while (temp[i] != '\0' && temp[i] != '\n') temp[i++] = '\0';
}

void s21_reset(char* temp, int* carriage) {
  *carriage = 0;
  s21_clear(temp);
}

void s21_delete_space(char* input) {
  int count = 0, count_copy = 0;
  char copy_input[MY_MAX_INPUT] = {'\0'};
  while (input[count] != '\n' && input[count] != '\0') {
    if (input[count] != ' ') copy_input[count_copy++] = input[count];
    count++;
  }
  s21_clear(input);
  strcpy(input, copy_input);
  input[strlen(copy_input)] = '\n';
}

void s21_str_rpn(stack* stack_rpn, char* answer) {
  while (stack_rpn != NULL) {
    strncpy(answer, stack_rpn->value, MY_MAX_INPUT - 1);
    answer += strlen(stack_rpn->value);
    stack_rpn = stack_rpn->adress;
    if (stack_rpn != NULL) {
      strncpy(answer, ", ", 2);
      answer += 2;
    }
  }
}
