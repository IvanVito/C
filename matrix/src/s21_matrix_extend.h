#include "s21_matrix.h"

void s21_fill_matrix(matrix_t *A, char *src);
void s21_print_matrix(matrix_t *A);
int s21_this_is_null(matrix_t *A);
int s21_not_same_size(matrix_t *A, matrix_t *B);
int s21_is_inf_or_nan(matrix_t *A);
int s21_search_not_null(matrix_t *A, int count);
void s21_gaus_str(matrix_t *A, int not_null, int count);
void s21_cross_off(int index_row, int index_column, matrix_t *A, matrix_t *B);
void s21_copy_matrix(matrix_t A, matrix_t *B);