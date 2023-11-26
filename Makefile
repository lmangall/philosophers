SRCS = main.c utils.c init.c day_n_night.c
OBJS = $(SRCS:.c=.o)

CC = cc -g
NAME = philosophers

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	echo "Cleaned"

fclean:	clean
	rm -f $(NAME)
	echo "Fcleaned"

re:	fclean all

.PHONY: all clean fclean re





______________________________







# Directories
SRCDIR = src
OBJDIR = obj

# Source files
SRCS = main.c utils.c utils_time.c utils_condition.c init.c day_n_night.c
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

# Compiler and flags
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

# Target executable
NAME = philosophers

# Targets
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJDIR)
	@echo "Cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "Fcleaned"

re: fclean all

.PHONY: all clean fclean re
