# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/11 13:37:44 by qdegraev          #+#    #+#              #
#    Updated: 2017/08/11 13:50:39 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

CC = clang
CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes/

VPATH = srcs/
SRCS = ft_nm.c

OBJDIR = objs/
OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

default: all

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(OBJDIR)%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

$(OBJDIR):
	mkdir $(OBJDIR)
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re clean fclean all
