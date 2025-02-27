#pragma once

void call(vm_t *vm, const def_t *unknown_def);

void call_primitive(vm_t *vm, const primitive_def_t *def);
void call_function(vm_t *vm, const function_def_t *def);
void call_constant(vm_t *vm, const constant_def_t *def);
void call_node(vm_t *vm, const node_ctor_t *ctor);
