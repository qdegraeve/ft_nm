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
LDFLAGS = -L ../libft -lft

LIBPATH = ../libft/
LIB = $(LIBPATH)/libft.a

INCLUDES = includes/

VPATH = srcs/
SRCS = ft_nm.c \
	   handler_64.c \
	   handler_32.c \
	   fat_handler.c \
	   lib_handler.c \
	   shared.c \
	   comp_tools.c \
	   swap.c \
	   errors.c

OBJDIR = objs/
OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

default: all

all: $(LIB) $(NAME)
	@echo " # sh : Job done $(shell pwd)/$(NAME)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

$(LIB):
	@make -C $(LIBPATH)

$(OBJDIR)%.o: %.c $(OBJDIR)
	@echo " + sh : Compiling $(OBJ_DIR) < $^"
	@$(CC) $(CFLAGS) -o $@ -c $< -I libft/include -I $(INCLUDES)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	make -C $(LIBPATH) clean
	@echo " $(shell\
		if [ -d $(OBJ_DIR) ]; then\
			echo "- sh : Removing $(OBJ_DIR) with";\
			ls $(OBJ_DIR) | wc -w; echo "*.o";\
			rm -Rf $(OBJ_DIR);\
		else\
			echo "# sh : Nothing to clean";\
		fi)"

fclean: clean
	make -C $(LIBPATH) fclean
	@echo " $(shell\
		if [ -f $(NAME) ]; then\
			echo "- sh : Removing $ $(NAME) ";\
			rm -f $(NAME);\
		else\
			echo "# sh : Nothing to fclean";\
		fi)"

re: fclean all

.PHONY: re clean fclean all
