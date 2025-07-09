# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 16:25:11 by mmisumi           #+#    #+#              #
#    Updated: 2025/07/04 14:23:01 by sneshev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRCS := $(shell find src -name "*.c")

OBJDIR := obj
OBJS := $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

LIBFT := libft/libft.a
FT_PRINTF := ft_printf/libftprintf.a

CC := cc
CFLAGS := -Wall -Werror -Wextra -I. -Ilibft -g

RM := rm -f 

all: $(LIBFT) $(FT_PRINTF) $(NAME) $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C libft

$(FT_PRINTF):
	make -C ft_printf

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME) -lreadline

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	make -C libft clean
	make -C ft_printf clean

fclean: clean 
	$(RM) $(NAME)
	make -C libft fclean
	make -C ft_printf clean

re: fclean all

.PHONY: all clean fclean re