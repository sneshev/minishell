/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:38:46 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 13:39:21 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// #define GREEN   "\033[0;32m"
// #define ORANGE  "\033[38;5;208m"  // or try 214 for a lighter orange
// #define YELLOW  "\033[0;33m"
// #define DEFAULT   "\033[0m"

// void print_line(t_list *list)
// {
// 	(void)list;
// 	// while (list)
// 	// {
// 	// 	int i = 0;
// 	// 	while (list->files)
// 	// 	{
// 	// 		if (list->files->type == REDIR_IN)
// 	// 			write(1, "< ", 2);
// 	// 		else if (list->infiles->type == REDIR_HEREDOC)
// 	// 			write(1, "<< ", 3);
// 	// 		printf(ORANGE "%s " DEFAULT, list->infiles->filename);
// 	// 		list->infiles = list->infiles->next;
// 	// 	}
// 	// 	printf(GREEN "%s " YELLOW, list->cmd.cmd); fflush(NULL);
// 	// 	while (list->cmd.args[i])
// 	// 	{
// 	// 		printf(YELLOW "%s " DEFAULT, list->cmd.args[i]); fflush(NULL);
// 	// 		i++;
// 	// 	}
// 	// 	while (list->outfiles)
// 	// 	{
// 	// 		if (list->outfiles->type == REDIR_OUT)
// 	// 			write(1, "> ", 2);
// 	// 		else if (list->outfiles->type == REDIR_APPEND)
// 	// 			write(1, ">> ", 3);
// 	// 		printf(ORANGE "%s " DEFAULT, list->outfiles->filename);
// 	// 		list->outfiles = list->outfiles->next;
// 	// 	}
// 	// 	list = list->next;

// 		// if (list->arg_type == COMMAND 
// || list->arg_type == BUILTIN)
// 		// {
// 		// 	printf(GREEN "%s " DEFAULT, list->arg); fflush(NULL);
// 		// 	list = list->next;
// 		// 	while (list && list->arg_type != REDIRECTION 
// && list->arg_type != PIPE)
// 		// 	{
// 		// 		printf(YELLOW "%s " DEFAULT, list->arg); fflush(NULL);
// 		// 		list = list->next;
// 		// 	}
// 		// }
// 		// else if (list->arg_type == PIPE)
// 		// {
// 		// 	printf("%s ", list->arg); fflush(NULL);
// 		// 	list = list->next;
// 		// }
// 		// else if (list->arg_type == REDIRECTION)
// 		// {
// 		// 	printf(ORANGE "%s " DEFAULT, list->arg); fflush(NULL);
// 		// 	list = list->next;
// 		// }
// 		// else
// 		// {
// 		// 	printf(ORANGE "%s " DEFAULT, list->arg); fflush(NULL);
// 		// 	list = list->next;
// 		// }
// 	// }
// 	printf("\n"); fflush(NULL);
// }

// void print_type(int type)
// {
// 	(void)type;
// 	// 	if (type == BUILTIN)
// // 		printf("(builtin)");
// // 	if (type == COMMAND)
// // 		printf("(command)");
// // 	if (type == REDIRECTION)
// // 		printf("(redirection)");
// // 	if (type == PIPE)
// // 		printf("(pipe)");
// // 	if (type == UNDEFINED)
// // 		printf("(undefined)");
// // 	if (type == SQUOTE)
// // 		printf("(single quotes)");
// // 	if (type == DQUOTE)
// // 		printf("(double quotes)");
// // 	printf("\n");
// }

// void	print_files(t_file *file)
// {
// 	while (file)
// 	{
// 		printf("filetype: %d\n", file->type);
// 		printf("filename: %s\n", file->filename);
// 		file = file->next;
// 	}
// }

// void	print_list(t_list *list)
// {
// 	while (list)
// 	{
// 		printf("cmd: %s\n", list->cmd);
// 		print_arr(list->args);
// 		printf("input: %d\n", list->input);
// 		printf("output: %d\n", list->output);
// 		printf("--------------------------\n");
// 		list = list->next;
// 	}
// }
