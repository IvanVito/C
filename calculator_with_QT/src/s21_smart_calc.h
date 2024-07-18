#ifndef CALC
#define CALC
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_MAX_INPUT 256
#define UNAR "+-"
#define NOT_UNAR "*/^"
#define BRACKETS "()"
#define FUNCTION "cos sin mod tan acos asin atan sqrt ln log"
#define NOT_DOUBLE_ARITHM "* / ^ + - \n"
#define KINDS_OF_NULL ".0 0 0. 0.0000000 "
#define OVER "\n \0"
#define MAX_VALUE 99999999999999L
#define MIN_VALUE 0.00000000000001L

enum err { OK, ERROR };

typedef struct stack_struct {
  char value[MY_MAX_INPUT];
  int priority;
  struct stack_struct* adress;
} stack;

int s21_smart_calc(char* input, long double* answer);
//////////////////PARSER/////////////////////
void s21_parser(stack** stack_num_arithm, char* input);
//////////////////STACK/////////////////////
stack* s21_init_stack(char* value, int priority);
stack* s21_push_stack(stack** stack_init, char* value, int priority);
stack* s21_pop_stack(stack* stack_delete);
void s21_see_all_stack(stack* stack_first);
void s21_destroy_all_stack(stack* stack_start);
void s21_reverse_stack(stack** stack_start);
///////////////////VALIDATOR//////////////////
int s21_validator(char* input);
int s21_digit(char* input, char* temp, int* count, int* carriage);
int s21_bracket(char* input, int* brackets, int* count);
int s21_alpha(char* input, char* temp, int* count, int* carriage);
void s21_delete_space(char* input);
int s21_sign(char* input, int* count);
void s21_reset(char* temp, int* carriage);
void s21_clear(char* temp);
/////////////////DIJKSTRA//////////////////////
void s21_algorithm_dijkstra(stack* stack_num_arithm, stack** stack_rpn);
void s21_str_rpn(stack* stack_rpn, char* answer);
void s21_add_stack_support(stack** stack_support, stack** stack_num_arithm);
void s21_add_stack_rpn(stack** stack_rpn, stack** sign_or_num);
/////////////////CALCULATE//////////////////////
int s21_calculate(stack* stack_rpn, long double* answer);
int s21_calc_function(char* function, char* number_1, char* number_2);
int s21_calc_operation(char* operation, char* number_1, char* number_2);
void s21_init_num(stack** stack_num, char* num);
void s21_push_num(stack** stack_num, stack** stack_rpn, char* num);
#endif
