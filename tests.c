#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "expr.h"

#ifdef YYDEBUG
extern int yydebug;
#endif // YYDEBUG

void test_basic_program() {
    expr_program_t program = expr_program_create("x + pow(2, 3)");

    double x = 10;

    expr_program_insert_symbol(program, "x", 0, &x);
    expr_program_insert_symbol(program, "pow", 2, pow);

    assert(expr_program_evaluate(program) == 19);

    expr_program_destroy(program);
}

int main(int argc, char *argv[]) {
#ifdef YYDEBUG
    yydebug = 1;
#endif // YYDEBUG

    test_basic_program();

    return 0;
}
