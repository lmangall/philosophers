# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 13:14:20 by lmangall          #+#    #+#              #
#    Updated: 2023/12/07 13:31:04 by lmangall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRCDIR = src
OBJDIR = obj

# Source files
SRCS = main.c utils_check.c utils_time.c utils_condition.c init.c day_n_night.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

# Target executable
NAME = philo

# Targets
all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# Create the object directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)

.PHONY: all clean fclean re
