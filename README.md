## What?

This C library provides a very minimal API for embedding a simple expression language into your application. The language syntax is fixed, but the API provides a mechianism for adding builtin symbols and functions.

## Why?

Why not? I built this a long time ago while I was working on a larger project to help me understand and visualize noise functions (for [procedural content generation](https://en.wikipedia.org/wiki/Procedural_generation)). I figured it could be useful for others, and decided to refactor it into a self contained library. I've also kept it relatively simple, so it can be used as a reference for how you might implement a lexer/parser in your own application.

### How?
A basic example:
```C
#include <stdio.h>
#include <math.h>
#include <expr.h>

int main(int argc, char *argv[]) {
    expr_program_t program = expr_program_create("x * sin(-pi) + pow(2, 3)");

    double x = 10;
    double pi = 3.14159;

    expr_program_insert_symbol(program, "x", 0, &x);
    expr_program_insert_symbol(program, "pi", 0, &pi);

    expr_program_insert_symbol(program, "sin", 1, sin);
    expr_program_insert_symbol(program, "pow", 2, pow);

    expr_scalar_t result = expr_program_evaluate(program);
    printf("%f\n", result);

    expr_program_destroy(program);

    return 0;
}
```
Symbols are mapped to raw memory addresses where they can be resolved at evaluation time. For simple values (variables with no arguments), they are the memory address for the value. For more complex functions, they are the memory address of the function that performs the calculation. Arguments are evaluated and passed in as `double` values. Currently, this library only supports functions with up to 10 arguments.