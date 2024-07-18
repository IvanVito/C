#include "s21_math.h"

//
long double s21_ceil(double x) {
  long double ceil_x = (long long int)x;
  if (s21_fabs(x) > 0. && x != ceil_x) {
    if (x > 0.) {
      ceil_x++;
    }
  }
  return ceil_x;
}

long double s21_log(double x) {
  long double p = x;
  int count_pow = 0;
  long double res = 0;
  long double last_res = 0;
  if (p == p && p != INF_P && (p > 0)) {
    while (p >= S21_EXP) {
      p /= S21_EXP;
      count_pow++;
    }
    for (int i = 0; i < 1000; i++) {
      last_res = res;
      res = last_res + 2 * (p - s21_exp(last_res)) / (p + s21_exp(last_res));
    }
  } else {
    if (p != p) {
      res = NaN;
    } else if (p == INF_P) {
      res = INF_P;
    } else if (p < 0) {
      res = NaN;
    } else if (p == 0) {
      res = INF_N;
    }
  }

  return res + count_pow;
}

long double s21_exp(double x) {
  long double p = x;
  long double add = 1;
  long double value = 1;
  long double i = 1;
  int out = 0;

  if (p != INF_N && p != NaN) {
    while (s21_fabs(add) > S21_EPS && !out) {
      add *= p / i;
      i++;
      value += add;
      if (value > MAX && p > 0) {
        out = 1;
      } else if (value > MAX && p < 0) {
        value = 0.0;
        out = 1;
      }
    }
  } else {
    if (p == INF_P) value = INF_P;
    if (p == INF_N) value = 0;
  }
  if (value < 0) value = 0.0;

  return value;
}

long double s21_fabs(double x) {
  long double p = x;
  return p < 0 ? -p : p;
}

long double s21_sqrt(double x) {
  long double p = x;
  long double left = 0;
  long double right = s21_num(x);
  long double mid = 0;
  if (p > 0) {
    mid = (left + right) / 2;

    while ((mid - left) > S21_EPS) {
      if (mid * mid > p)
        right = mid;
      else
        left = mid;
      mid = (left + right) / 2;
    }
  } else if (p == 0) {
    mid = 0;
  } else {
    mid = NaN;
  }

  return mid;
}

long double s21_num(double x) {
  long double p = x;
  long double num = 0;
  if (p >= 1.0)
    num = p;
  else
    num = 1;
  return num;
}

long double s21_pow(double x, double degree) {
  long double p = x;
  long double res = 0;
  long double x_2 = x;

  if (((degree > MAX) && (p >= 1)) || (((p == 0) && (degree < 0)))) {
    res = INF_P;
  } else if (degree == 0) {
    res = 1;
  } else if (((degree != degree) || (p != p)) ||
             ((degree < MAX) && (degree > 0) && (p > -1) && (p < 0) &&
              p != INF_N)) {
    res = NaN;
  } else if (((p < -1) && (degree < -1)) ||
             ((p == INF_N) && (degree < 0) && (degree > -1))) {
    res = 0.0;
  } else if ((((p < 0) && (degree > -1) && (degree < 1)) && (p != INF_N)) ||
             (p != p)) {
    res = NaN;
  } else if (degree > MAX &&
             (((p < 1) && (p >= 0)) || ((p > -1) && (p <= 0)))) {
    res = 0.0;
  } else if (((p == INF_N) && (degree < 1) && (degree > 0)) ||
             ((degree == INF_N) && (p < 1) && (p >= 0))) {
    res = INF_P;
  } else if (((p == INF_N) && (degree == INF_P)) ||
             ((p == INF_N) && (degree != 0))) {
    res = INF_P;
  } else if (((degree == INF_N) && (p < 0) && (p >= -1)) ||
             ((degree > MAX) && (p < 0))) {
    res = INF_P;
  } else if (((degree == INF_N) && (p > 1)) ||
             ((degree == INF_N) && (p < -1))) {
    res = 0.0;
  } else if (p < 0) {
    x_2 = -p;
    res = s21_exp(degree * s21_log(x_2));
    if (s21_fmod(degree, 2) != 0) {
      res = -res;
    }
  } else {
    res = s21_exp(degree * s21_log(p));
  }

  if (res != res && ((p < -1) && (degree > 1))) res = INF_P;
  return res;
}

long double s21_fmod(double x, double y) {
  long double p = x;
  long double py = y;
  long long int mod = 0;
  long double res = 0;
  if (p != INF_N && p != INF_P && p == p && y == y && y != 0.0) {
    mod = p / y;
    if (s21_fabs(mod) < S21_EPS) {
      res = p;
    } else {
      res = p - mod * py;
    }
  } else {
    res = NaN;
  }

  return res;
}

long double s21_atan(double x) {
  long double res = 0.0;
  if (x == 1) {
    res = S21_PI / 4;
  } else if (x == -1) {
    res = -(S21_PI / 4);
  } else if (x == NaN) {
    res = NaN;
  } else if (x == INF_P) {
    res = S21_PI / 2;
  } else if (x == INF_N) {
    res = -S21_PI / 2;
  } else if (-1 <= x && x <= 1) {
    for (int i = 0; i < 1000; i++) {
      res = res + s21_pow(-1, i) * (s21_pow(x, (2 * i) + 1)) / ((2 * i) + 1);
    }
  } else {
    for (int i = 0; i < 1000; i++) {
      res += s21_pow(-1, i) * s21_pow(x, -1 - 2 * i) / (1 + 2 * i);
    }
    res = (S21_PI * sqrt(x * x) / (2 * x)) - res;
  }

  return res;
}

// sqrt и pow из math.h
long double s21_asin(double x) {
  long double res = 0;
  if (x == 1.0) {
    res = S21_PI / 2;
  } else if (x == -1.0) {
    res = -(S21_PI / 2);
  } else if (-1 <= x && x <= 1) {
    res = s21_atan(x / (s21_sqrt(1 - s21_pow(x, 2))));
  } else
    res = NaN;
  return res;
}

// sqrt, S21_PI и pow из math.h
long double s21_acos(double x) {
  long double res = 0;
  if (x == 0)
    res = S21_PI / 2;
  else if (x < -1 && x > 1)
    res = NaN;
  else {
    res = s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
    if (-1 <= x && x < 0) res = S21_PI + res;
  }
  return res;
}

int s21_abs(int n) {
  if (n <= 0) {
    return -n;
  } else
    return n;
}

long double s21_Factorial(int n) {
  return (n < 2) ? 1 : n * s21_Factorial(n - 1);
}

long double s21_cos(double x) {
  long double sum_cos = 0;

  if (x != NaN && x != INF_P && x != INF_N) {
    for (; x < -2 * S21_PI || 2 * S21_PI < x;) {
      if (x > 2 * S21_PI) {
        x -= 2 * S21_PI;
      } else {
        x += 2 * S21_PI;
      }
    }

    for (int i = 0; i < 100; i++) {
      sum_cos += s21_pow(-1, i) * s21_pow(x, 2 * i) / s21_Factorial(2 * i);
    }
  } else {
    if (x == INF_P) sum_cos = NaN;
    if (x == INF_N) sum_cos = NaN;
    if (x == NaN) sum_cos = NaN;
  }
  return sum_cos;
}

long double s21_sin(double x) {
  long double sum_sin = 0;
  if (x != NaN && x != INF_P && x != INF_N) {
    for (; x < -2 * S21_PI || 2 * S21_PI < x;) {
      if (x > 2 * S21_PI) {
        x -= 2 * S21_PI;
      } else {
        x += 2 * S21_PI;
      }
    }

    for (register int i = 0; i < 100; i++) {
      sum_sin +=
          (s21_pow((-1), i) * s21_pow(x, 1 + 2 * i)) / s21_Factorial(2 * i + 1);
    }
    //
  }
  // else {
  //   if (x == INF_P) sum_sin = NaN;
  //   if (x == INF_N) sum_sin = NaN;
  //   if (x == NaN) sum_sin = NaN;
  // }
  return sum_sin;
}

long double s21_tan(double x) {
  long double res = 0;
  if (x != NaN && x != INF_P && x != INF_N) {
    for (; x < -2 * S21_PI || 2 * S21_PI < x;) {
      if (x > 2 * S21_PI) {
        x -= 2 * S21_PI;
      } else {
        x += 2 * S21_PI;
      }
    }

    res = s21_sin(x) / s21_cos(x);

  } else {
    if (x == INF_P) res = NaN;
    if (x == INF_N) res = NaN;
    if (x == NaN) res = NaN;
  }
  return res;
}

long double s21_floor(double x) {
  long double floor_x = (long long int)x;
  if (s21_fabs(x - floor_x) > 0 && s21_fabs(x) > 0.) {
    if (x < 0) {
      floor_x -= 1;
    }
  }
  return floor_x;
}
