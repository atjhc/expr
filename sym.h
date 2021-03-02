#ifndef SYM_H
#define SYM_H

#define SYMHASH_SIZE 128
#define SYMHASH_MASK 127

typedef struct sym_s {
    int hashv;

    char *name;
    int arity;

    void *value;

    struct sym_s *next;
} * sym_t;

typedef struct sym_table_s {
    sym_t table[SYMHASH_SIZE];
    int count;
} * sym_table_t;

sym_table_t sym_table_create();
void sym_table_destroy(sym_table_t table);

void sym_table_insert(sym_table_t st, const char *name, int arity, void *value);
sym_t sym_table_lookup(sym_table_t table, const char *name, int arity);

#endif // SYM_H