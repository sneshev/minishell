#include "../minishell.h"

static char **g_line_addr()
{
	static char *g_line = NULL;

	return (&g_line);
}

void set_g_line(char *new_line)
{
	char **line_ptr;

	line_ptr = g_line_addr();
	*line_ptr = new_line;
}

char *get_g_line()
{
	return (*(g_line_addr()));
}

void free_g_line()
{
	free(get_g_line());
	set_g_line(NULL);
}