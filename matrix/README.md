# Разработка библиотеки s21_matrix

## Общая информация

Программа `s21_matrix` реализует основные операции над матрицами на языке программирования C стандарта C11 с использованием компилятора gcc. Все операции над матрицами выполнены в соответствии с принципами структурного программирования и оформлены в виде статической библиотеки.

## Структура проекта

- **Структура матрицы**:
  ```c
  typedef struct matrix_struct {
      double** matrix;
      int rows;
      int columns;
  } matrix_t;
  ```

- **Функции библиотеки**:
  - Создание матриц (create_matrix):
    ```c
    int s21_create_matrix(int rows, int columns, matrix_t *result);
    ```
  - Очистка матриц (remove_matrix):
    ```c
    void s21_remove_matrix(matrix_t *A);
    ```
  - Сравнение матриц (eq_matrix):
    ```c
    int s21_eq_matrix(matrix_t *A, matrix_t *B);
    ```
  - Сложение (sum_matrix) и вычитание матриц (sub_matrix):
    ```c
    int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
    int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
    ```
  - Умножение матрицы на число (mult_number) и умножение двух матриц (mult_matrix):
    ```c
    int s21_mult_number(matrix_t *A, double number, matrix_t *result);
    int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
    ```
  - Транспонирование матрицы (transpose):
    ```c
    int s21_transpose(matrix_t *A, matrix_t *result);
    ```
  - Минор матрицы и матрица алгебраических дополнений (calc_complements):
    ```c
    int s21_calc_complements(matrix_t *A, matrix_t *result);
    ```
  - Определитель матрицы (determinant):
    ```c
    int s21_determinant(matrix_t *A, double *result);
    ```
  - Обратная матрица (inverse_matrix):
    ```c
    int s21_inverse_matrix(matrix_t *A, matrix_t *result);
    ```

- **Расположение кода**:
  - Код библиотеки находится в папке `src` в ветке `develop`.

- **Сборка библиотеки**:
  - Makefile включает следующие цели: `all`, `clean`, `test`, `s21_matrix.a`, `gcov_report`.
  - В целях `gcov_report` формируется отчет gcov в виде HTML страницы. Для этого unit-тесты запускаются с флагами gcov.

## Принципы разработки

- **Структурное программирование**:
  - Программа разработана в соответствии с принципами структурного программирования, что способствует ясности, простоте и поддерживаемости кода.
- **Стиль кодирования**:
  - При написании кода использовался стиль кодирования Google Style, обеспечивающий единообразие и читабельность кода.

## Тестирование

- **Unit-тесты**:
  - Все функции библиотеки покрыты unit-тестами с использованием библиотеки `Check`.
  - Покрытие тестами составляет не менее 80 процентов для каждой функции, что гарантирует стабильность и корректность работы библиотеки.

#### Описание операций над матрицами

- **Создание матриц (create_matrix)**:
  - Функция создает матрицу с указанным числом строк и столбцов и возвращает результирующий код: 0 - OK, 1 - ошибка, некорректная матрица.
  
- **Очистка матриц (remove_matrix)**:
  - Функция освобождает память, выделенную под матрицу.
  
- **Сравнение матриц (eq_matrix)**:
  - Функция сравнивает две матрицы на равенство. Возвращает `SUCCESS` (1), если матрицы равны, и `FAILURE` (0), если не равны. Сравнение производится вплоть до седьмого знака после запятой.
  
- **Сложение (sum_matrix) и вычитание матриц (sub_matrix)**:
  - Функции выполняют сложение и вычитание двух матриц одинаковых размеров. Возвращают результирующий код: 0 - OK, 2 - ошибка вычисления (несовпадающие размеры матриц).

- **Умножение матрицы на число (mult_number) и умножение двух матриц (mult_matrix)**:
  - Функции выполняют умножение матрицы на число и умножение двух матриц. Возвращают результирующий код: 0 - OK, 2 - ошибка вычисления (несовпадающие размеры матриц).
  
- **Транспонирование матрицы (transpose)**:
  - Функция выполняет транспонирование матрицы. Возвращает результирующий код: 0 - OK.
  
- **Минор матрицы и матрица алгебраических дополнений (calc_complements)**:
  - Функция вычисляет минор матрицы и матрицу алгебраических дополнений. Возвращает результирующий код: 0 - OK, 2 - ошибка вычисления.
  
- **Определитель матрицы (determinant)**:
  - Функция вычисляет определитель матрицы. Возвращает результирующий код: 0 - OK, 2 - ошибка вычисления. Определитель может быть вычислен только для квадратной матрицы.
  
- **Обратная матрица (inverse_matrix)**:
  - Функция вычисляет обратную матрицу. Возвращает результирующий код: 0 - OK, 2 - ошибка вычисления. Обратная матрица существует только для квадратных матриц с ненулевым определителем.

## Заключение

Программа `s21_matrix` соответствует стандартам и обладает всеми необходимыми функциональными возможностями, включая создание, очистку, сравнение, сложение, вычитание, умножение матриц и чисел, транспонирование, вычисление определителя, минора и обратной матрицы. Код библиотеки оформлен в соответствии с Google Style и покрыт unit-тестами, обеспечивающими надежность и стабильность работы.
