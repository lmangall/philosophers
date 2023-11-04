SRCS = main.c utils.c init.c days_nights.c
OBJS = $(SRCS:.c=.o)

CC = cc
NAME = philosophers

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	echo "Done"

clean:
	rm -f $(OBJS)
	echo "Cleaned"

fclean:	clean
	rm -f $(NAME)
	echo "Fcleaned"

re:	fclean all

.PHONY: all clean fclean re