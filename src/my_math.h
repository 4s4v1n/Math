#ifndef MATH_H
#define MATH_H
#include <limits.h>  // LLONG_MAX LLONG_MIN
#define MY_LOG2 0.69314718055994530942
#define MY_PI 3.1415926535897932384626433832795L
#define MY_PI_2 (MY_PI / 2.L)
#define MY_INF 1 / 0.L
#define MY_N_INF -1 / 0.L
#define MY_NAN 0 / 0.L
#define MY_ATAN_1 0.785398163  // константы результата atan от 1
#define MY_ATAN_1_DIV_2 0.46364760900080609352  // -||- от 1/2
#define MY_ATAN_3_DIV_2 0.982793723             // -||- от 3/2
#define MY_ATAN_INF MY_PI_2                    // -||- от inf


// деление нацело
void my_div(unsigned long long x, unsigned long long y,
             unsigned long long* res, long long exp_x, long long* exp_y);
// x >= y
void my_mul(unsigned long long x, unsigned long long y,
             unsigned long long* mul);
void my_add(const unsigned long long* x, const unsigned long long* y,
             unsigned long long* sum);
// x >= y
void my_sub(unsigned long long* x, unsigned long long* y,
             unsigned long long* sub);
void my_shift_right(unsigned long long* number);
void my_shift_left(unsigned long long* number);


// Main fuctions
//--------------------------------------------------------------------
long double my_sin(double x);
long double my_cos(double x);
long double my_tan(double x);
long int my_abs(int abs);
long double my_fabs(double x);
long double my_atan(double x);
long double my_asin(double x);
long double my_acos(double x);
long double my_floor(double x);
long double my_sqrt(double x);
long double my_log(double x);
long double my_pow(double x, double y);
long double my_ceil(double x);
long double my_fmod(double x, double y);
long double my_exp(double x);
long double my_fabs(double x);
//--------------------------------------------------------------------


#endif  // MATH_H
