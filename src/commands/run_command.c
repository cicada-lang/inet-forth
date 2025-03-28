#include "index.h"

static int run(commander_t *commander);

void
run_command(commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files";
    command->run = run;
    commander_add(runner, command);
}

int
run(commander_t *commander) {
    char **paths = commander_rest_argv(commander);
    while (*paths) {
        char *src = *paths++;
        if (string_ends_with(src, ".fth")) {
            file_t *file = file_open_or_fail(src, "r");
            const char *code = file_read_string(file);
            fclose(file);
            mod_t *mod = mod_new(src, code);
            import_prelude(mod);
            worker_t *worker = worker_new(mod);
            execute_all(worker);
            mod_destroy(&mod);
            worker_destroy(&worker);
        } else  {
            fprintf(stderr, "[run] file name must ends with .fth, given file name: %s\n", src);
            exit(1);
        }
    }

    return 0;
}
