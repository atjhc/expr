#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "expr.h"

#ifdef YYDEBUG
extern int yydebug;
#endif // YYDEBUG

void test_expr() {
    expr_program_t expr = expr_program_create("x * sin(-pi) + pow(2, 3)");

    double x = 10;
    double pi = 3.14159;

    expr_program_insert_symbol(expr, "x", 0, &x);
    expr_program_insert_symbol(expr, "pi", 0, &pi);

    expr_program_insert_symbol(expr, "sin", 1, sin);
    expr_program_insert_symbol(expr, "pow", 2, pow);

    float result = expr_program_evaluate(expr);
    printf("%f\n", result);

    expr_program_destroy(expr);
}

int main(int argc, char *argv[]) {
#ifdef YYDEBUG
    yydebug = 1;
#endif // YYDEBUG

    test_expr();

    return 0;
}
