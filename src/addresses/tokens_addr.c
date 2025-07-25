#include "../minishell.h"

static char ***g_tokens_addr()
{
    static char **g_tokens = NULL;

    return (&g_tokens);
}

void set_g_tokens(char **new_tokens)
{
    char ***tokens_ptr;

    tokens_ptr = g_tokens_addr();
    *tokens_ptr = new_tokens;
}

char **get_g_tokens()
{
    return (*(g_tokens_addr()));
}

void free_g_tokens()
{
    free_arr(get_g_tokens());
    set_g_tokens(NULL);
}