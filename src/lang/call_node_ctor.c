#include "index.h"

static void
node_apply_input_ports(worker_t *worker, node_t *node) {
    for (size_t c = 0; c < node->ctor->input_arity; c++) {
        value_t value = stack_pop(worker->value_stack);
        if (is_wire(value)) {
            wire_t *wire = as_wire(value);
            size_t i = node->ctor->input_arity - 1 - c;
            node_set(node, i, wire);

            if (wire_is_principal(wire)) {
                maybe_return_task(worker, wire);
            }
        }
    }
}

static void
node_return_output_ports(worker_t *worker, node_t *node) {
    for (size_t c = 0; c < node->ctor->output_arity; c++) {
        wire_t *node_wire = wire_new();
        wire_t *free_wire = wire_new();

        wire_set_opposite(node_wire, free_wire);
        wire_set_opposite(free_wire, node_wire);

        size_t i = node->ctor->input_arity + c;
        node_set(node, i, node_wire);
        stack_push(worker->value_stack, free_wire);
    }
}

void
call_node_ctor(worker_t *worker, const node_ctor_t *ctor) {
    node_t *node = worker_add_node(worker, ctor);
    node_apply_input_ports(worker, node);
    node_return_output_ports(worker, node);
    return;
}
