#include "../minishell.h"

static int *exit_code_addr()
{
    static int exit_code = 0;

    return (&exit_code);
}

void set_exit_code(int new_code)
{
    int *exit_code_ptr;

    exit_code_ptr = exit_code_addr();
    *exit_code_ptr = new_code;
}

int get_exit_code()
{
    return (*(exit_code_addr()));
}   