#include "sym.h"

#include <stdlib.h>
#include <string.h>

// From Donald Knuth's The Art Of Computer Programming Volume 3
static unsigned int hash(const char *str, unsigned int len) {
    unsigned int hash = len;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }
    return (hash & 0x7FFFFFFF);
}

sym_table_t sym_table_create() {
    sym_table_t st = malloc(sizeof(struct sym_table_s));

    for (int i = 0; i < SYMHASH_SIZE; i++) {
        st->table[i] = NULL;
    }

    return st;
}

void sym_table_destroy(sym_table_t st) {
    sym_t p, pn;

    for (int i = 0; i < SYMHASH_SIZE; i++) {
        for (p = st->table[i]; p != NULL; p = pn) {
            pn = p->next;

            free(p->name);
            free(p);
        }
    }

    free(st);
}

void sym_table_insert(sym_table_t st, const char *name, int arity, void *value) {
    sym_t symbol = NULL, temp = NULL;
    unsigned int bucket = 0;

    if ((symbol = sym_table_lookup(st, name, arity)) != NULL) {
        symbol->value = value;
    }

    symbol = malloc(sizeof(struct sym_s));
    symbol->name = strdup(name);
    symbol->arity = arity;
    symbol->value = value;
    symbol->hashv = hash(name, strlen(name));

    bucket = symbol->hashv & SYMHASH_MASK;
    temp = st->table[bucket];
    st->table[bucket] = symbol;
    symbol->next = temp;

    st->count++;
}

sym_t sym_table_lookup(sym_table_t st, const char *name, int arity) {
    unsigned int hashv = hash(name, strlen(name));
    unsigned int bucket = hashv & SYMHASH_MASK;

    sym_t p = NULL;
    for (p = st->table[bucket]; p != NULL; p = p->next) {
        if (hashv == p->hashv && strcmp(p->name, name) == 0 && p->arity == arity) {
            return p;
        }
    }

    return p;
}
