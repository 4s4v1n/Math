#include "my_math.h"

double LnSeries(double x) {
  long double sum = 0;
  long double stepen = x;
  long iterations = 100;
  if (x > -5 && x < 5) {
    iterations *= 70;
  }
  if (x > -1 && x < 1) {
    iterations *= 400;
  }
  for (int i = 1; i < iterations; i++) {
    sum += (((i % 2) ? 1 : -1) * stepen / i);
    stepen *= x;
  }
  return sum;
}

long double my_log(double x) {
  long double answer = MY_NAN;
  if (x > 0 && x != MY_INF) {
    int e = 0;
    while ((x > 2) ? x /= 2 : 0) e++;
    answer = (MY_LOG2 * e) + LnSeries(x - 1);
  }
  if (x == MY_INF) answer = MY_INF;
  if (x == 0) answer = MY_N_INF;
  return answer;
}

long double my_pow(double x, double y) {
  long double res = MY_NAN;
  if ((x < -1 || x > 1) && y == MY_INF) {
    res = MY_INF;
  } else if (x < 1 && x > -1 && y == MY_INF) {
    res = 0;
  } else if ((x > 1 || x < -1) && y == MY_N_INF) {
    res = 0;
  } else if (x > 1 && y == MY_INF) {
    res = MY_INF;
  } else if (x == MY_N_INF && y == -1) {
    res = -0;
  } else if ((int)y == y && x < 0) {
    res = x;
    if (y > 0) {
      for (int i = 1; i < y; i++) {
        res *= x;
      }
    } else if (y < 0) {
      for (int i = 1; i > y; i--) {
        res /= x;
      }
    } else {
      res = 1;
    }
  } else if (y == 0) {
    res = 1;
  } else if (y == 1) {
    res = x;
  } else {
    if (x != MY_INF && y != MY_INF && x != MY_N_INF && y != MY_N_INF)
      res = my_exp(y * my_log(x));
  }
  return res;
}

long double my_sqrt(double x) { return my_pow(x, 0.5); }

long double my_exp(double x) {
  long double res = x;
  if (x > 709.78271289) {
    res = 1 / 0.0L;
  } else if (x < -20.8) {
    res = 0;
  } else if (x != 1 / 0.0 && x != -1 / 0.0 && x == x) {
    int n = 20000;
    res = 1.0L;
    long double tmp = 1.0L;
    for (int i = 0; i < n; i++) {
      tmp = tmp / (i + 1) * x;
      res += tmp;
    }
  }
  return res;
}

long double my_sin(double x) {
  long double res;
  if (x == MY_INF || x == MY_N_INF || x == MY_NAN) {
    res = MY_NAN;
  } else {
    double x_f = my_fmod(x, (2 * MY_PI));
    long double shift = x_f;
    res = shift;
    for (int n = 1; n < 1000000; n++) {
      shift *= (-x_f * x_f) / (2 * (long double)n * (2 * (long double)n + 1));
      res += shift;
    }
  }
  return res;
}

long double my_cos(double x) {
  long double res;
  if (x == MY_INF || x == MY_N_INF || x == MY_NAN) {
    res = MY_NAN;
  } else {
    long double shift = 1.L;
    long double x_f = my_fmod(x, (2.L * MY_PI));
    res = shift;
    for (int n = 1; n < 10000; n++) {
      shift *= (-1.L) * (x_f * x_f) /
               (2.L * (long double)n * ((2.L * (long double)n) - 1.L));
      res += shift;
    }
  }
  return res;
}

long double my_tan(double x) {
  long double res = 0.L;
  if (x == MY_INF || x == MY_N_INF || x == MY_NAN) {
    res = MY_NAN;
  } else if (x == MY_PI_2) {
    res = MY_INF;
  } else if (x == -MY_PI_2) {
    res = MY_N_INF;
  } else {
    res = my_sin(x) / my_cos(x);
  }
  return res;
}

long double my_fmod(double x, double y) {
  unsigned long long xx = *(unsigned long long*)&x;
  unsigned long long yy = *(unsigned long long*)&y;
  unsigned long long sign = (xx >> 63) << 63;
  long long exp_x = ((xx << 1) >> 53) - 1023;
  long long exp_y = ((yy << 1) >> 53) - 1023;
  unsigned long long mantiss_x[2] = {0};
  mantiss_x[0] = (xx << 12) >> 12;
  unsigned long long mantiss_y = (yy << 12) >> 12;
  double tmp;
  long double res;
  // 0 (в y) или NAN (в x или y) или +-INF (в x)
  if (y == 0 || (exp_x == 1024) || (exp_y == 1024 && mantiss_y != 0)) {
    mantiss_x[0] = 1ULL;
    mantiss_x[0] |= 2047ULL << 52;  // поставить экспоненту
    tmp = *((double*)(&(mantiss_x[0])));
  } else {
    mantiss_x[0] |= 1ULL << 52;  // добавить 1 перед мантиссой
    mantiss_y |= 1ULL << 52;
    if ((exp_x < exp_y) || (exp_x == exp_y && mantiss_x[0] < mantiss_y) ||
        (exp_y == 1024 && mantiss_y == 0)) {
      tmp = *((double*)&x);  // в том числе +-INF (в y)
    } else {
      unsigned long long buffer[2];
      my_div(mantiss_x[0], mantiss_y, buffer, exp_x, &exp_y);
      my_mul(mantiss_y, buffer[0], buffer);
      for (; exp_x > exp_y && (mantiss_x[1] >> 63) == 0; exp_x--) {
        my_shift_left(mantiss_x);
      }
      for (; exp_x > exp_y; exp_y++) {
        my_shift_right(buffer);
      }
      my_sub(mantiss_x, buffer, buffer);
      if (buffer[1] == 0 && buffer[0] == 0) {
        exp_x = -1023;
      } else {
        for (; buffer[1] != 0; exp_x++) {
          my_shift_right(buffer);
        }
        for (; buffer[0] > 0x1FFFFFFFFFFFFF; exp_x++) {
          buffer[0] >>= 1;  // делить на 2 и увеличивать exp
        }
        for (; buffer[0] < 0x10000000000000; exp_x--) {
          buffer[0] <<= 1;  // умножать на 2 и уменьшать exp
        }
        buffer[0] &= (1ULL << 52) - 1;  // убрать 52ой бит
      }
      mantiss_x[0] = buffer[0];
      mantiss_x[0] |= sign;                     // поставить знак
      mantiss_x[0] |= (1023ULL + exp_x) << 52;  // поставить экспоненту
      tmp = *((double*)(&(mantiss_x[0])));
    }
  }
  res = (long double)tmp;
  if (my_fabs(res) > my_fabs(y)) {
    res = my_fabs(y) * (long double)(-2 * (long long)sign + 1);
  }
  return res;
}

void my_shift_right(unsigned long long* number) {
  number[0] >>= 1;
  number[0] |= (number[1] << 63) >> 63;
  number[1] >>= 1;
}

void my_shift_left(unsigned long long* number) {
  number[1] <<= 1;
  number[1] |= number[0] >> 63;
  number[0] <<= 1;
}

void my_div(unsigned long long x, unsigned long long y,
             unsigned long long* res, long long exp_x, long long* exp_y) {
  unsigned long long dividend = 0;
  res[1] = 0, res[0] = 0;
  int j = 63, flag_begin = 0;
  long long exp_res = exp_x - *exp_y;

  for (int i = 63; (i >= 0 || exp_res > 0) && j >= 0; i--) {
    dividend <<= 1;
    dividend += x >> 63;
    if (dividend >= y) {
      res[0] |= 1ULL << j;
      dividend -= y;
      if (flag_begin == 0) flag_begin = 1;
    }
    if (flag_begin == 1) j--;
    x <<= 1;
    if (i < 0) {
      exp_res--;
    }
  }
  j++;
  if (j <= 63) {
    res[0] >>= j;
  }
  *exp_y += exp_res;
}

void my_mul(unsigned long long x, unsigned long long y,
             unsigned long long* mul) {
  mul[1] = 0, mul[0] = 0;
  unsigned long long buf[2];
  buf[1] = 0, buf[0] = x;
  unsigned long long tmp[2] = {0};
  for (int i = 0; i < 64; i++) {
    if (i > 0) {
      my_shift_left(buf);
    }
    if (((y << (63 - i)) >> 63) == 1) {
      my_add(tmp, buf, tmp);
    }
  }
  mul[1] = tmp[1], mul[0] = tmp[0];
}

void my_add(const unsigned long long* x, const unsigned long long* y,
             unsigned long long* sum) {
  unsigned carry = 0;  // разряд переноса
  unsigned long long res[2] = {0};
  for (int i = 0; i < 128; i++) {
    unsigned tmp = ((x[i / 64] << (63 - (i % 64))) >> 63) +
                   ((y[i / 64] << (63 - (i % 64))) >> 63) + carry;
    res[i / 64] |= (tmp & 1ULL) << i % 64;
    carry = tmp >> 1;
  }
  sum[1] = res[1], sum[0] = res[0];
}

void my_sub(unsigned long long* x, unsigned long long* y,
             unsigned long long* sub) {
  //  перевод в допкод
  unsigned bit = y[0] >> 63;
  y[0] = ~y[0];
  y[1] = ~y[1];
  y[0]++;
  if (y[0] == bit && bit == 0) {
    y[1]++;
  }
  my_add(x, y, sub);
}

// возвращает ближайшее целое число, не меньше заданного значения
long double my_ceil(double x) {
  unsigned long long data = *(unsigned long long*)&x;
  int exp = ((data << 1) >> 53) - 1023;
  if (exp < 1024) {
    unsigned long long sign = data >> 63;
    unsigned long long mantiss = (data << 12) >> 12;
    // получить маску со всеми единицами после всех значащих цифр
    int diff_exp;
    if (exp >= 0 && exp <= 52) {
      diff_exp = exp;
    } else if (exp > 52) {
      diff_exp = 52;
    } else {
      diff_exp = 0;
    }
    unsigned long long mask = (1ULL << (52 - diff_exp)) - 1;
    mask &= mantiss;  // маска всех битов после значащих цифр
    if ((exp == -1023 && mantiss == 0)) {  // == +-0
      sign = 0;                            // оставляем только +0
    } else if (sign == 1 && exp < 0) {     // (-1; -0]
      exp = -1023;
      mantiss = 0;  // записываем -0
    } else if (exp >= 0 && exp < 52 && (mask != 0)) {
      // округлять если остаток ненулевой и 0 <= exp < 52
      mantiss |= 1ULL << 52;  // добавить 1 перед мантиссой
      mask = ~mask;
      mantiss &= mask;  // оставляем только значащие цифры
      if (sign == 0) {
        mantiss += 1ULL << (52 - diff_exp);  // добавляем единицу
      }
      if ((mantiss >> 53) > 0) {
        exp++;  // при переполнении мантиссы
      }
      mask = (1ULL << 52) - 1;
      mantiss &= mask;  // убрать 52ой бит

    } else if (sign == 0 && exp < 0) {  // (0; 1)
      exp = 0;
      mantiss = 0;  // установить единицу
    }
    data = sign << 63;  // обнулить всё кроме знака
    data |= mantiss;    // добавить мантиссу
    data |= (unsigned long long)(exp + 1023) << 52;  // добавить экспоненту
  }
  double tmp = *((double*)&data);
  long double res = (long double)tmp;
  return res;
}

long double my_fabs(double x) {
  return (x < 0.L) ? (long double)(x * -1.L) : (long double)x;
}
long int my_abs(int x) { return (x < 0L) ? (long)(x * -1) : (long)x; }

// Функция использует преобразования в зависимости от того, в каком
// промежутке аргумент. Использую рекурентный вызов с костантными
// значениями функции (заменить ф-цию)
long double my_atan(double x) {
  long double res = 0.;
  if (x != x) {
    res = -MY_NAN;
  } else if (x == MY_INF) {
    res = MY_PI_2;
  } else if (x == -MY_INF) {
    res = -MY_PI_2;
  } else {
    int sign = 0;  // ф-ция нечет, рассматриваем только +полуось
    if (x < 0.L) {
      sign = 1;
      x *= -1;
    }
    if (x >= 0 && x < 0.6875) {  // [0;11/16)
      int sign_x = -1;
      double shift = x;

      for (int n = 0; n < 100; n++) {
        sign_x *= -1;
        res += sign_x * shift / (2 * n + 1);
        shift *= x * x;
      }
    }
    if (x >= 0.6875 && x < 1.1875) {  // [11/16;19/16)
      res = MY_ATAN_1 + my_atan((x - 1) / (1 + x));
    }
    if (x >= 1.1875 && x < 2.4375) {  // [19/16;39/16)
      res = MY_ATAN_3_DIV_2 + my_atan((x - 1.5) / (1. + 1.5 * x));
    }
    if (x >= 2.4375) {  // [39/16;+inf)
      res = MY_ATAN_INF + my_atan(-1 / x);
    }
    if (sign) {
      res *= -1;
    }
  }
  return res;
}

// Вычисляем арксинус через арктангенс и тригонометрическое преобразование
// (заменить ф-цию)
long double my_asin(double x) {
  long double res = 0.;
  if (x != x || x > 1. || x < -1.) {
    res = MY_NAN;
  } else if (x == 1) {
    res = MY_PI_2;
  } else if (x == -1) {
    res = -MY_PI_2;
  } else {
    res = my_atan(x / my_sqrt(1 - x * x));
  }
  return res;
}

// Вычисляет арккосинус через арксинус, все просто
long double my_acos(double x) {
  long double res = 0.;
  if (x != x || x > 1. || x < -1.) {
    res = MY_NAN;
  } else if (x == 1) {
    res = 0.;
  } else if (x == -1) {
    res = MY_PI;
  } else {
    res = MY_PI_2 - my_asin(x);
  }
  return res;
}

// Возвращает ближайшее целое число (в виде дабла) не превышающее данное
long double my_floor(double x) {
  long double res = 0.;
  if (x >= LLONG_MAX || x <= LLONG_MIN || x == 0.) {
    res = x;  // c inf некорректно работает
  } else {
    long long number = (long long)x;
    res = (double)number;
    if (res != x && x < 0) {  // если < 0 и x - (int)x != 0
      res -= 1;
    }
  }
  return (x != x) ? MY_NAN : res;
}
