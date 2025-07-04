# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 16:25:11 by mmisumi           #+#    #+#              #
#    Updated: 2025/07/04 14:20:56 by sneshev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

# Recursively get all .c files in src/
SRCS := $(shell find src -name "*.c")

# Mirror object file paths under obj/
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