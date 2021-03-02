## Minimal expression language

This C library provides a very minimal API for embedding a simple expression language into your application. The language syntax is fixed, but the API provides a mechianism for adding user-defined symbols and functions.

### Example
A basic example:
```C
#include <stdio.h>
#include <math.h>
#include <expr.h>

int main(int argc, char *argv[]) {
    expr_t expr = expr_create("x * sin(-pi) + pow(2, 3)");

    double x = 10;
    double pi = 3.14159;

    expr_insert_symbol(expr, "x", 0, &x);
    expr_insert_symbol(expr, "pi", 0, &pi);

    expr_insert_symbol(expr, "sin", 1, sin);
    expr_insert_symbol(expr, "pow", 2, pow);

    float result = expr_evaluate(expr);
    printf("%f\n", result);

    expr_destroy(expr);

    return 0;
}
```
Symbols are mapped to raw memory addresses where they can be resolved at evaluation time. For simple values (variables with no arguments), they are the memory address for the value. For more complex functions, they are the memory address of the function that performs the calculation. Arguments are evaluated and passed in as `double` values. Currently, this library only supports functions with up to 10 arguments.