[thread] wrap `pthread_cond_t` -- maybe `condvar_t`

# memory

[memory] fix the naming of `new_shared` and `allocate_shared`

- because the aim is to avoid false sharing, not to sharing.

# allocator

[allocator] `allocator_new` -- has `thread_stack_array`
[allocator] `allocator_new` -- take `thread_count`

# net

[net] `node_allocator_t`
[net] `principal_port_t`
[net] single list `wire_t`
[net] fix `x_inspect_run` -- fix snapshot tests

# core

[core] `worker_t` -- safe use of `task_queue` -- which might be full

# module system

```
import zero add1 add "nat.fth"
```

# primitive value

[design] write `list-map` as example -- use explicit `dup` -- keep linear variable simple

- use `{ ... }` for un-named program -- just program, no closure over linear variables
- another solution is to use quoted symbol to reference defined program

# debug

[debug] 尝试使用真实的物理学来实现 force
[debug] `node_physics_simulate` -- move by `velocity` and clear `force` for every `node_model`
[debug] remove `node_physics_fake_simulate`
