#ifndef EXPR_H
#define EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef double scalar_t;
typedef struct expr_program_s *expr_program_t;

expr_program_t expr_program_create(const char *code);
void expr_program_destroy(expr_program_t program);

void expr_program_insert_symbol(expr_program_t program, const char *name, int arity,
                                void *location);

scalar_t expr_program_evaluate(expr_program_t program);

#ifdef __cplusplus
}
#endif

#endif // EXPR_H