HEADER := ft_printf.h

NAME = libftprintf.a

SRCS := det_type.c \
		ft_printf.c \
		low_hexa.c \
		print_adres.c \
		print_char.c \
		print_nbr.c \
		print_str.c \
		put_u.c \
		upp_hexa.c

OBJS := $(SRCS:.c=.o);

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all 