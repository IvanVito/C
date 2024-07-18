#include "s21_matrix_extend.h"

int s21_search_not_null(matrix_t *copy_matrix, int count) {
  int not_null = -1;
  for (int row = count; (row < copy_matrix->rows) && (not_null == -1); row++)
    if (copy_matrix->matrix[row][count]) not_null = row;
  if ((not_null != count) && (not_null != -1)) {
    for (int column = count; column < copy_matrix->columns; column++) {
      int temp = 0;
      temp = copy_matrix->matrix[count][column];
      copy_matrix->matrix[count][column] =
          -copy_matrix->matrix[not_null][column];
      copy_matrix->matrix[not_null][column] = temp;
    }
    not_null = count;
  }
  return not_null;
}

void s21_gaus_str(matrix_t *copy_matrix, int not_null, int count) {
  for (int row = count + 1; row < copy_matrix->rows; row++) {
    double divider =
        copy_matrix->matrix[row][count] / copy_matrix->matrix[not_null][count];
    for (int column = count + 1; column < copy_matrix->columns; column++) {
      copy_matrix->matrix[row][column] -=
          copy_matrix->matrix[not_null][column] * divider;
    }
  }
}

void s21_cross_off(int index_row, int index_column, matrix_t *A, matrix_t *B) {
  int count_row = -1;
  for (int row = 0; row < A->rows; row++) {
    if (row != index_row) {
      count_row++;
      int count_column = -1;
      for (int column = 0; column < A->columns; column++) {
        if (column != index_column) {
          count_column++;
          B->matrix[count_row][count_column] = A->matrix[row][column];
        }
      }
    }
  }
}

void s21_copy_matrix(matrix_t A, matrix_t *B) {
  for (int row = 0; row < A.rows; row++) {
    for (int column = 0; column < A.columns; column++) {
      B->matrix[row][column] = A.matrix[row][column];
    }
  }
}

void s21_fill_matrix(matrix_t *A, char *src) {
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      sscanf(src, "%lf ", &(A->matrix[row][column]));
      src += strcspn(src, " ") + 1;
    }
  }
}

int s21_not_same_size(matrix_t *A, matrix_t *B) {
  if ((A->rows != B->rows) || (A->columns != B->columns))
    return INCORRECT_MATRIX;
  return OK;
}

int s21_is_inf_or_nan(matrix_t *A) {
  int res = OK;
  for (int row = 0; row < A->rows && res != CALCULATION_ERROR; row++) {
    for (int column = 0; column < A->columns && res != CALCULATION_ERROR;
         column++) {
      if (A->matrix[row][column] != A->matrix[row][column] ||
          A->matrix[row][column] == INFINITY ||
          A->matrix[row][column] == -INFINITY)
        res = CALCULATION_ERROR;
    }
  }
  return res;
}