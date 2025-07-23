#include "../minishell.h"

static t_list **g_list_addr()
{
    static t_list *g_list = NULL;

    return (&g_list);
}

void set_g_list(t_list *new_g_list)
{
	t_list **list_ptr;

	list_ptr = g_list_addr();
	*list_ptr = new_g_list;
}

t_list *get_g_list()
{
	return (*(g_list_addr()));
}

t_list **get_g_list_addr()
{
	return (g_list_addr());
}

void free_g_list()
{
	free_list(get_g_list_addr());
	set_g_list(NULL);
}