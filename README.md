# Math 

![math png](./images/math_formuls.png)

This project presents the implementation of some functions of the standard library <math.h>. Most are implemented using Taylor series and the least squares method. A balance has been chosen regarding the accuracy of the obtained values ​​and the speed of the functions.

## Contents of the library

 1) `long double my_sin(double x)` - returns sin(x).
 2) `long double my_cos(double x)` - returns cos(x).
 3) `long double my_tan(double x)` - returns tan(x).
 4) `long int my_abs(int abs)` - returns |x| for long int.
 5) `long double my_fabs(double x)` - returns |x| for long doubles.
 6) `long double my_atan(double x)` - returns atan(x).
 7) `long double my_asin(double x)` - returns asin(x).
 8) `long double my_acos(double x)` - returns acos(x).
 9) `long double my_floor(double x)` - returns the nearest integer <= x.
 10) `long double my_sqrt(double x)` - returns the square root of x.
 11) `long double my_log(double x)` - returns ln(x).
 12) `long double my_pow(double x, double y)` - returns x^y.
 13) `long double my_ceil(double x)` - returns the nearest integer greater than x.
 14) `long double my_fmod(double x, double y)` - returns the remainder after dividing x by y.
 15) `long double my_exp(double x)` - returns e^x.

Additionally, common constants for calculations are set, such as ln2, pi/2, pi, etc.

All source files and makefile are in the src folder. Building is done with gcc version 9.4.0 using a makefile on Linux.