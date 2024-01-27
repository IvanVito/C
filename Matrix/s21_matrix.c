#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows < 1 || columns < 1) return INCORRECT_MATRIX;
  int res = OK;
  result->matrix = calloc(rows, sizeof(double *));
  if (result->matrix != NULL) {
    for (int count = 0; (count < rows) && res != INCORRECT_MATRIX; count++) {
      result->matrix[count] = calloc(columns, sizeof(double));
      if (result->matrix[count] == NULL) res = INCORRECT_MATRIX;
    }
    result->rows = rows;
    result->columns = columns;
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if ((A != NULL) && (A->matrix != NULL) &&
      (s21_row_or_col_err(A) != INCORRECT_MATRIX)) {
    for (int count = 0; count < A->rows; count++)
      if (A->matrix[count] != NULL) free(A->matrix[count]);
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || s21_not_same_size(A, B) ||
      s21_is_inf_or_nan(A) || s21_is_inf_or_nan(B))
    return FAILURE;
  int res = SUCCESS;
  for (int row = 0; (row < A->rows) && (res != FAILURE); row++) {
    for (int column = 0; (column < A->columns) && (res != FAILURE); column++) {
      if (fabsl(A->matrix[row][column] - B->matrix[row][column]) >= ACCURACY)
        res = FAILURE;
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || s21_create_matrix(A->rows, A->columns, result))
    return INCORRECT_MATRIX;
  if (s21_not_same_size(A, B) || s21_is_inf_or_nan(A) || s21_is_inf_or_nan(B))
    return CALCULATION_ERROR;
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[row][column] =
          A->matrix[row][column] + B->matrix[row][column];
    }
  }
  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || s21_create_matrix(A->rows, A->columns, result))
    return INCORRECT_MATRIX;
  if (s21_not_same_size(A, B) || s21_is_inf_or_nan(A) || s21_is_inf_or_nan(B))
    return CALCULATION_ERROR;
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[row][column] =
          A->matrix[row][column] - B->matrix[row][column];
    }
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || s21_create_matrix(A->rows, A->columns, result))
    return INCORRECT_MATRIX;
  if (s21_is_inf_or_nan(A) || number != number || number == INFINITY ||
      number == -INFINITY)
    return CALCULATION_ERROR;
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[row][column] = A->matrix[row][column] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || s21_create_matrix(A->rows, B->columns, result))
    return INCORRECT_MATRIX;
  if (s21_is_inf_or_nan(A) || s21_is_inf_or_nan(B) || A->columns != B->rows)
    return CALCULATION_ERROR;
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < B->columns; column++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[row][column] += A->matrix[row][k] * B->matrix[k][column];
      }
    }
  }
  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || s21_create_matrix(A->columns, A->rows, result))
    return INCORRECT_MATRIX;
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      result->matrix[column][row] = A->matrix[row][column];
    }
  }
  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  matrix_t copy_matrix;
  s21_create_matrix(A->rows, A->columns, &copy_matrix);
  s21_copy_matrix(A, &copy_matrix);
  int ind_not_null = 0;
  *result = 1;
  if (A->rows != 2) {
    for (int count = 0; (count < (copy_matrix.rows - 1)) && (*result != 0);
         count++) {
      ind_not_null = s21_search_not_null(&copy_matrix, count);
      if (ind_not_null >= 0)
        s21_gaus_str(&copy_matrix, ind_not_null, count);
      else
        *result = 0;
    }
    for (int column = 0; column < copy_matrix.columns; column++)
      *result *= copy_matrix.matrix[column][column];
  } else {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  }
  s21_remove_matrix(&copy_matrix);
  return OK;
}

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

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || s21_create_matrix(A->columns, A->rows, result))
    return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  double res = 0;
  matrix_t B;
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      s21_create_matrix(A->columns - 1, A->rows - 1, &B);
      s21_cross_off(row, column, A, &B);
      s21_determinant(&B, &res);
      result->matrix[row][column] = pow(-1, row + column) * res;
      s21_remove_matrix(&B);
    }
  }
  return OK;
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

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  matrix_t ally, transp;
  int res = OK;
  double deter = 0, deter_re = 0;
  s21_determinant(A, &deter);
  if (deter != 0) {
    deter_re = 1 / deter;
    s21_create_matrix(A->columns, A->rows, result);
    s21_create_matrix(A->columns, A->rows, &ally);
    s21_calc_complements(A, &ally);
    s21_create_matrix(A->columns, A->rows, &transp);
    s21_transpose(&ally, &transp);
    s21_mult_number(&transp, deter_re, result);
    s21_remove_matrix(&ally);
    s21_remove_matrix(&transp);
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}

void s21_copy_matrix(matrix_t *A, matrix_t *B) {
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      B->matrix[row][column] = A->matrix[row][column];
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

void s21_print_matrix(matrix_t *A) {
  for (int row = 0; row < A->rows; row++) {
    for (int column = 0; column < A->columns; column++) {
      printf("%0.7lf ", A->matrix[row][column]);
    }
    printf("\n");
  }
}

int s21_row_or_col_err(matrix_t *A) {
  if (A->rows < 1 || A->columns < 1) return INCORRECT_MATRIX;
  return OK;
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

// int main() {
//   matrix_t *matrix_test_1 = NULL;
//   matrix_t result;
//   s21_transpose(matrix_test_1, &result);
//   s21_remove_matrix(matrix_test_1);
//   s21_remove_matrix(&result);
//   return 0;
// }