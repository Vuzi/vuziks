#include "math.h"

// Modulo entre double
double modulo(double a, double b) {
    while(a > b)
        a -= b;
    return a;
}

// Division entière
double integer_division(double a, double b) {
    return (a - modulo(a, b)) / b;
}
