#include "index.h"

void
check_name_not_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token
) {
    mod_t *mod = worker->mod;
    const def_t *found = mod_find(mod, name);
    if (found) {
        fprintf(stderr, "[compiler-error] can not re-define name: %s\n", name);
        fprintf(stderr, "[compiler-error] already defined to: ");
        def_print(found, stderr);
        fprintf(stderr, "\n");
        fprintf(stderr, "[src] %s\n", mod->src);
        code_print_context(stderr, mod->code, token->start, token->end);
        exit(1);
    }
}

void
check_name_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token
) {
    mod_t *mod = worker->mod;
    const def_t *found = mod_find(mod, name);
    if (!found) {
        fprintf(stderr, "[compiler-error] undefined name: %s\n", name);
        fprintf(stderr, "[src] %s\n", mod->src);
        code_print_context(stderr, mod->code, token->start, token->end);
        exit(1);
    }
}

void
check_node_name_defined(
    const worker_t *worker,
    const char *name,
    const token_t *token
) {
    mod_t *mod = worker->mod;
    const def_t *found = mod_find(mod, name);
    if (!found) {
        fprintf(stderr, "[compiler-error] undefined node name: %s\n", name);
        fprintf(stderr, "[src] %s\n", mod->src);
        code_print_context(stderr, mod->code, token->start, token->end);
        exit(1);
    }

    if (found->kind != DEF_NODE_CTOR) {
        fprintf(stderr, "[compiler-error] expect name defined as node instead of: %s\n", def_kind_name(found->kind));
        fprintf(stderr, "[src] %s\n", mod->src);
        code_print_context(stderr, mod->code, token->start, token->end);
        exit(1);
    }
}

void
check_port_name_defined(
    const worker_t *worker,
    const char *node_name,
    const char *port_name,
    const token_t *token
) {
    check_node_name_defined(worker, node_name, token);
    mod_t *mod = worker->mod;
    const def_t *found = mod_find(mod, node_name);
    const node_ctor_t *ctor = found->node_ctor;
    for (size_t i = 0; i < ctor->arity; i++) {
        port_info_t *port_info = ctor->port_infos[i];
        if (string_equal(port_info->name, port_name)) return;
    }

    fprintf(stderr, "[compiler-error] undefined port name: %s\n", port_name);
    fprintf(stderr, "[compiler-error] for node name: %s\n", node_name);
    fprintf(stderr, "[src] %s\n", mod->src);
    code_print_context(stderr, mod->code, token->start, token->end);
    exit(1);
}
