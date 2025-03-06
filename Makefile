NAME = philosophers
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRCS =	main.c \
		dinner.c \
		getters_setters.c \
		init.c \
		parsing.c \
		safe.c \
		synchro_utils.c \
		utils1.c \
		write.c \
		monitoring.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re