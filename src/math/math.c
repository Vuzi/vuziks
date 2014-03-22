#include "math.h"

#define abs(a) \
           ( a > 0 ? a : -a )

// Modulo entre double
double modulo(double a, double b) {
    double sign = a / abs(a);
    a = abs(a); b = abs(b);

    while(a > b)
        a -= b;

    return a*sign;
}

// Division entière
double integer_division(double a, double b) {
    return (a - modulo(a, b)) / b;
}
