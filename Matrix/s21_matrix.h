#ifndef _S21_MATRIX
#define _S21_MATRIX
#define SUCCESS 1
#define FAILURE 0
#define ACCURACY 0.0000001L
#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum res_code { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_fill_matrix(matrix_t *A, char *src);
void s21_print_matrix(matrix_t *A);
int s21_this_is_null(matrix_t *A);
int s21_row_or_col_err(matrix_t *A);
int s21_not_same_size(matrix_t *A, matrix_t *B);
int s21_is_inf_or_nan(matrix_t *A);
int s21_search_not_null(matrix_t *A, int count);
void s21_gaus_str(matrix_t *A, int not_null, int count);
void s21_cross_off(int index_row, int index_column, matrix_t *A, matrix_t *B);
void s21_copy_matrix(matrix_t *A, matrix_t *B);

#endif