#include "minishell.h"

#define GREEN   "\033[0;32m"
#define ORANGE  "\033[38;5;208m"  // or try 214 for a lighter orange
#define YELLOW  "\033[0;33m"
#define DEFAULT   "\033[0m"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

void print_line(t_list *list)
{
	while (list)
	{
		if (list->arg_type == COMMAND || list->arg_type == BUILTIN)
		{
			printf(GREEN "%s " DEFAULT, list->arg); fflush(NULL);
			list = list->next;
			while (list && list->arg_type != REDIRECTION && list->arg_type != PIPE)
			{
				printf(YELLOW "%s " DEFAULT, list->arg); fflush(NULL);
				list = list->next;
			}
		}
		else if (list->arg_type == PIPE)
		{
			printf("%s ", list->arg); fflush(NULL);
			list = list->next;
		}
		else if (list->arg_type == REDIRECTION)
		{
			printf(ORANGE "%s " DEFAULT, list->arg); fflush(NULL);
			list = list->next;
		}
		else
		{
			printf(ORANGE "%s " DEFAULT, list->arg); fflush(NULL);
			list = list->next;
		}
	}
	printf("\n"); fflush(NULL);
}

void print_type(int type)
{
	if (type == BUILTIN)
		printf("(builtin)");
	if (type == COMMAND)
		printf("(command)");
	if (type == REDIRECTION)
		printf("(redirection)");
	if (type == PIPE)
		printf("(pipe)");
	if (type == UNDEFINED)
		printf("(undefined)");
	if (type == SQUOTE)
		printf("(single quotes)");
	if (type == DQUOTE)
		printf("(double quotes)");
	printf("\n");
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("list->line: %s\n", list->arg);
		printf("list->arg_type: %d ", list->arg_type);
		print_type(list->arg_type);
		printf("-----------------------\n");
		list = list->next;
	}
}
