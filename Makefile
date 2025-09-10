# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 16:25:11 by mmisumi           #+#    #+#              #
#    Updated: 2025/09/10 15:57:34 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRCS := src/main.c \
	src/utils/exit_code_addr.c src/utils/exits_errors.c src/utils/lexer_utils.c src/utils/utils.c \
	src/tokens/tokens.c src/tokens/token_utils.c src/tokens/token_type.c src/tokens/quotes.c src/tokens/env_vars.c \
	src/signals/signals_child.c src/signals/signals_parent.c \
	src/lists/list.c src/lists/list_utils.c src/lists/get_command.c src/lists/free_lists.c src/lists/free_env.c \
	src/lists/files/heredoc.c src/lists/files/heredoc_utils.c src/lists/files/heredoc_delim.c src/lists/files/files.c src/lists/files/files_utils.c src/lists/files/create_files.c \
	src/history/history.c src/history/get_next_line.c src/history/get_next_line_utils.c \
	src/execution/waitpid.c src/execution/execute.c src/execution/execute_child.c src/execution/convert_env.c src/execution/access.c \
	src/execution/builtins/builtin_utils.c src/execution/builtins/unset_env.c src/execution/builtins/unset_env_utils.c src/execution/builtins/print_export.c src/execution/builtins/export.c src/execution/builtins/export_utils.c src/execution/builtins/exit.c src/execution/builtins/execute_builtin.c src/execution/builtins/builtin.c \
	src/environment/env.c src/environment/env_utils.c

OBJDIR := obj
OBJS := $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

LIBFT := libft/libft.a

CC := cc
CFLAGS := -Wall -Werror -Wextra -I. -Ilibft -g

RM := rm -f 

all: $(LIBFT) $(NAME) $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	make -C libft clean

fclean: clean 
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re