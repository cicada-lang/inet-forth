#pragma once

typedef void (primitive_fn_t)(worker_t *worker);
typedef value_t (primitive_fn_0_t)(void);
typedef value_t (primitive_fn_1_t)(value_t x);
typedef value_t (primitive_fn_2_t)(value_t x, value_t y);
typedef value_t (primitive_fn_3_t)(value_t x, value_t y, value_t z);
typedef value_t (primitive_fn_4_t)(value_t x, value_t y, value_t z, value_t w);

typedef enum {
    PRIMITIVE_FN,
    PRIMITIVE_FN_0,
    PRIMITIVE_FN_1,
    PRIMITIVE_FN_2,
    PRIMITIVE_FN_3,
    PRIMITIVE_FN_4,
} primitive_fn_kind_t;

struct primitive_t {
    char *name;
    primitive_fn_kind_t fn_kind;
    union {
        primitive_fn_t *primitive_fn;
        primitive_fn_0_t *primitive_fn_0;
        primitive_fn_1_t *primitive_fn_1;
        primitive_fn_2_t *primitive_fn_2;
        primitive_fn_3_t *primitive_fn_3;
        primitive_fn_4_t *primitive_fn_4;
    };
};

primitive_t *primitive_from_fn(const char *name, primitive_fn_t *primitive_fn);
primitive_t *primitive_from_fn_0(const char *name, primitive_fn_0_t *primitive_fn_0);
primitive_t *primitive_from_fn_1(const char *name, primitive_fn_1_t *primitive_fn_1);
primitive_t *primitive_from_fn_2(const char *name, primitive_fn_2_t *primitive_fn_2);
primitive_t *primitive_from_fn_3(const char *name, primitive_fn_3_t *primitive_fn_3);
primitive_t *primitive_from_fn_4(const char *name, primitive_fn_4_t *primitive_fn_4);

void primitive_destroy(primitive_t **self_pointer);
