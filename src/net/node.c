#include "index.h"

node_t *
node_new(const node_ctor_t *ctor, size_t id) {
    node_t *self = new(node_t);
    self->ctor = ctor;
    self->id = id;
    self->wires = allocate_pointers(ctor->arity);
    return self;
}

void
node_destroy(node_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_t *self = *self_pointer;
        free(self->wires);
        // Does NOT own wires in `wires`.
        free(self);
        *self_pointer = NULL;
    }
}

void
node_print(const node_t *self, file_t *file) {
    char *id_string = uint_to_subscript(self->id);
    fprintf(file, "(%s%s)", self->ctor->name, id_string);
    free(id_string);
}
