#include "../minishell.h"

static char ***g_environment_addr()
{
    static char **g_environment = NULL;

    return (&g_environment);
}

void set_g_environment(char **new_environment)
{
    char ***env_ptr;

    env_ptr = g_environment_addr();
    *env_ptr = new_environment;
}

char **get_g_environment()
{
    return (*(g_environment_addr()));
}

void free_g_environment()
{
    free_arr(get_g_environment());
    set_g_environment(NULL);
}