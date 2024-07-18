#ifndef S21_MATH_H
#define S21_MATH_H
#include <float.h>
#include <math.h>
#include <stdio.h>

#define S21_PI 3.141592653589793238462643383L
#define S21_EXP 2.7182818284590452353602874713527L
#define S21_EPS 0.00000000000001L
#define MAX 999999999999999999999999999999999.9L
#define INF_P (1.0) / (+0.0)
#define INF_N (1.0) / (-0.0)
#define NaN (0.0) / (0.0)

//Ссылки
long double s21_ceil(double x);
long double s21_log(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_num(double x);
long double s21_sqrt(double x);
long double s21_fmod(double x, double y);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
int s21_abs(int n);
long double s21_Factorial(int n);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_floor(double x);
long double s21_pow(double x, double degree);
#endif