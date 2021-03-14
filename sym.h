#ifndef EXPR_SYM_H
#define EXPR_SYM_H

#define SYMHASH_SIZE 128
#define SYMHASH_MASK 127

typedef struct expr_sym_s {
    int hashv;

    char *name;
    int arity;

    void *value;

    struct expr_sym_s *next;
} * expr_sym_t;

typedef struct expr_sym_table_s {
    expr_sym_t table[SYMHASH_SIZE];
    int count;
} * expr_sym_table_t;

expr_sym_table_t expr_sym_table_create();
void expr_sym_table_destroy(expr_sym_table_t table);

void expr_sym_table_insert(expr_sym_table_t st, const char *name, int arity, void *value);
expr_sym_t expr_sym_table_lookup(expr_sym_table_t table, const char *name, int arity);

#endif // SYM_H