#include "../minishell.h"

static t_env **g_env_addr()
{
    static t_env *g_env = NULL;

    return (&g_env);
}

void set_g_env(t_env *new_g_env)
{
    t_env **env_ptr;

    env_ptr = g_env_addr();
    *env_ptr = new_g_env;
}

t_env *get_g_env()
{
    return (*(g_env_addr()));
}

t_env **get_g_env_addr()
{
    return (g_env_addr());
}

void free_g_env()
{
    free_env(get_g_env_addr());
    set_g_env(NULL);
}