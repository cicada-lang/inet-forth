#include "index.h"

tag_t
value_tag(value_t value) {
    return (size_t) value & TAG_MASK;
}

void
value_print(value_t value, file_t *file) {
    if (value == xtrue) {
        fprintf(file, "true");
        return;
    }

    if (value == xfalse) {
        fprintf(file, "false");
        return;
    }

    if (is_xint(value)) {
        fprintf(file, "%ld", to_int64(value));
        return;
    }

    if (is_xfloat(value)) {
        char buffer[64];
        sprintf(buffer, "%.17g", to_double(value));
        if (!string_has_char(buffer, '.')) {
            size_t end = string_length(buffer);
            buffer[end] = '.';
            buffer[end + 1] = '0';
            buffer[end + 2] = '\0';
        }

        fprintf(stdout, "%s", buffer);
        return;
    }

    if (is_xobject(value)) {
        object_t *object = as_object(value);
        if (object->spec->print_fn) {
            object->spec->print_fn(object, file);
            return;
        }

        // fprintf(file, "#<unknown-object 0x%p>", value);
        fprintf(file, "#<%s 0x%p>", object->spec->name, value);
        return;
    }

    fprintf(file, "#<unknown-value 0x%p>", value);
    return;
}
