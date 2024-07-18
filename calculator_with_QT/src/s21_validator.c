#include "s21_smart_calc.h"

int s21_validator(char* input) {
  int err = OK, brackets = 0, carriage = 0, count = 0;
  char temp[MY_MAX_INPUT] = {'\0'};
  s21_delete_space(input);
  if (strchr(NOT_UNAR, input[0])) err = ERROR;
  while (strchr(OVER, input[count]) == NULL && err == OK) {
    if (isdigit(input[count]) || input[count] == '.')
      err = s21_digit(input, temp, &count, &carriage);
    if (isalpha(input[count]) && err == OK)
      err = s21_alpha(input, temp, &count, &carriage);
    if (strchr(BRACKETS, input[count]) && err == OK &&
        strchr(OVER, input[count]) == NULL)
      err = s21_bracket(input, &brackets, &count);
    if (strchr(NOT_DOUBLE_ARITHM, input[count]) &&
        strchr(OVER, input[count]) == NULL && err == OK)
      err = s21_sign(input, &count);
    s21_reset(temp, &carriage);
    if (strchr(OVER, input[count]) == NULL) count++;
  }
  if (brackets != 0 || strchr(OVER, input[0])) err = ERROR;
  return err;
}

int s21_digit(char* input, char* temp, int* count, int* carriage) {
  int not_double = 0, err = OK, count_num = 0;
  while (isdigit(input[*count]) || (input[*count] == '.')) {
    if (input[*count] == '.') not_double++;
    temp[(*carriage)++] = input[(*count)++];
    count_num++;
  }
  if (not_double >= 2) err = ERROR;
  s21_reset(temp, carriage);
  if (((strchr(NOT_DOUBLE_ARITHM, input[*count]) == NULL) &&
       input[*count] != ')' && (strchr(OVER, input[*count]) == NULL) &&
       input[*count] != 'm'))
    err = ERROR;
  int back_index = *count - count_num - 1;
  if ((back_index >= 0) &&
      (strchr(NOT_DOUBLE_ARITHM, input[back_index]) == NULL) &&
      input[back_index] != '(' && input[back_index] != 'd' &&
      isdigit(input[back_index]) == 0)
    err = ERROR;
  return err;
}

int s21_bracket(char* input, int* brackets, int* count) {
  int err = OK;
  if (input[*count] == '(') (*brackets)++;
  if (input[*count] == ')') (*brackets)--;
  if (input[0] == ')') err = ERROR;
  if ((*count) >= 1 && (input[*count] == ')') &&
      isdigit(input[*count - 1]) == 0 && input[*count - 1] != ')' &&
      input[*count - 1] != '.')
    err = ERROR;
  if ((input[*count] == ')') && input[*count + 1] != 'm' &&
      strchr(NOT_UNAR, input[*count + 1]) == NULL && input[*count + 1] != ')' &&
      strchr(NOT_DOUBLE_ARITHM, input[*count + 1]) == NULL)
    err = ERROR;
  if ((input[*count] == '(') && (strchr(NOT_UNAR, input[*count + 1]) != NULL) &&
      input[*count + 1] != '.')
    err = ERROR;
  return err;
}

int s21_alpha(char* input, char* temp, int* count, int* carriage) {
  int err = OK;
  while (isalpha(input[*count]) && strcmp(temp, "mod") != 0)
    temp[(*carriage)++] = input[(*count)++];
  if (strstr(FUNCTION, temp) == NULL ||
      (input[*count] != '(' && strcmp(temp, "mod") != 0))
    err = ERROR;
  if (strcmp(temp, "mod") == 0) {
    if ((isalpha(input[*count - 4]) || input[*count - 4] == '(') ||
        input[*count] == ')')
      err = ERROR;
    (*count)--;
  }
  s21_reset(temp, carriage);
  return err;
}

int s21_sign(char* input, int* count) {
  int err = OK;
  if ((*count >= 1) && (isdigit(input[*count - 1]) == 0) &&
      input[*count - 1] != ')' && input[*count - 1] != '(' && (*count != 0) &&
      isalpha(input[*count - 1]) == 0 && input[*count - 1] != '.')
    err = ERROR;
  if (((isdigit(input[*count + 1]) == 0) && input[*count + 1] != '(' &&
       isalpha(input[*count + 1]) == 0 && input[*count + 1] != '.'))
    err = ERROR;
  return err;
}
