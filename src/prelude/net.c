#include "index.h"

void
x_connect(worker_t *worker) {
    worker_connect_top_wire_pair(worker);
}

void
x_link(worker_t *worker) {
    wire_t *first_wire = wire_new();
    wire_t *second_wire = wire_new();

    wire_set_opposite(first_wire, second_wire);
    wire_set_opposite(second_wire, first_wire);

    stack_push(worker->value_stack, first_wire);
    stack_push(worker->value_stack, second_wire);
}

void
x_run(worker_t *worker) {
    run_task(worker);
}

void
x_inspect_run(worker_t *worker) {
    // TODO
    // x_wire_print_net(worker);
    run_task(worker);
    // x_wire_print_net(worker);
}

static void
define_node(mod_t *mod, const char *name, list_t *input_token_list, list_t *output_token_list) {
    size_t input_arity = list_length(input_token_list);
    size_t output_arity = list_length(output_token_list);
    node_ctor_t *node_ctor = node_ctor_new(name, input_arity, output_arity);
    def_t *def = def_node_ctor(node_ctor);

    size_t index = 0;

    token_t *input_token = list_first(input_token_list);
    while (input_token) {
        def->node_ctor->port_infos[index] =
            port_info_from_name(string_copy(input_token->string));
        input_token = list_next(input_token_list);
        index++;
    }

    token_t *output_token = list_first(output_token_list);
    while (output_token) {
        def->node_ctor->port_infos[index] =
            port_info_from_name(string_copy(output_token->string));
        output_token = list_next(output_token_list);
        index++;
    }

    mod_define(mod, def);
    return;
}

void
x_define_node(worker_t *worker) {
    token_t *head_token = list_shift(worker->token_list);
    char *name = head_token->string;

    check_name_not_defined(worker, name, head_token);

    list_t *input_token_list = list_new_with((destroy_fn_t *) token_destroy);
    list_t *output_token_list = list_new_with((destroy_fn_t *) token_destroy);

    bool output_flag = false;
    while (true) {
        assert(!list_is_empty(worker->token_list));

        token_t *token = list_shift(worker->token_list);
        if (string_equal(token->string, "end")) {
            token_destroy(&token);
            break;
        }

        if (string_equal(token->string, "--")) {
            output_flag = true;
            token_destroy(&token);
            continue;
        }

        if (output_flag) {
            list_push(output_token_list, token);
        } else {
            list_push(input_token_list, token);
        }
    }

    define_node(worker->mod, name, input_token_list, output_token_list);

    token_destroy(&head_token);
    list_destroy(&input_token_list);
    list_destroy(&output_token_list);
}

void
x_define_rule(worker_t *worker) {
    token_t *first_token = list_shift(worker->token_list);
    token_t *second_token = list_shift(worker->token_list);

    char *first_name = first_token->string;
    char *second_name = second_token->string;

    check_node_name_defined(worker, first_name, first_token);
    check_node_name_defined(worker, second_name, second_token);

    function_t *function = compile_function(worker);
    mod_define_rule(worker->mod, first_name, second_name, function);

    token_destroy(&first_token);
    token_destroy(&second_token);
}
