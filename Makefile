# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 16:25:11 by mmisumi           #+#    #+#              #
#    Updated: 2025/06/04 15:36:13 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRCS := $(wildcard src/*.c)

OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

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

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
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