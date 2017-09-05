# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afillion <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 15:37:28 by afillion          #+#    #+#              #
#    Updated: 2017/06/02 11:16:23 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

VPATH = srcs:srcs/libft:srcs/ft_printf

INCLUDES = include/

CC = clang

CFLAGS = -g -Wall -Wextra -Werror

SRC =  ft_strlcat.c \
	ft_lstiter.c \
	ft_memalloc.c \
	ft_lstmap.c \
	ft_lstadd_back.c \
	ft_putendl_fd.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_putnbr_fd.c \
	ft_strjoin.c \
	ft_memdel.c \
	ft_putstr_fd.c \
	ft_strclr.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strncpy.c \
	ft_strsplit.c \
	ft_putnbr.c \
	ft_toupper.c \
	ft_memchr.c \
	ft_strtrim.c \
	ft_isalnum.c \
	ft_putstr.c \
	ft_isascii.c \
	ft_lstdelone.c \
	ft_strdel.c \
	ft_isalpha.c \
	ft_isprint.c \
	ft_strsub.c \
	ft_striteri.c \
	ft_striter.c \
	ft_lstadd.c \
	ft_memcpy.c \
	ft_strchr.c \
	ft_putbase.c \
	ft_bzero.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_strmap.c \
	ft_strnequ.c \
	ft_putchar.c \
	ft_memccpy.c \
	ft_iswhitespace.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strequ.c \
	ft_putchar_fd.c \
	ft_isdigit.c \
	ft_memcmp.c \
	ft_strmapi.c \
	ft_strncat.c \
	ft_tolower.c \
	ft_lstdel.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strnstr.c \
	ft_putendl.c \
	ft_lstnew.c \
	ft_strcat.c \
	ft_strnew.c \
	ft_strcpy.c \
	get_next_line.c \
	ft_getnbr.c \
	ft_abs.c \
	ft_itoa_base.c \
	ft_cleanjoin.c \
	ft_printf.c \
	types.c \
	arg_length.c \
	flags.c \
	ft_putnbru.c \
	ft_utoa_base.c \
	type_d_i.c \
	type_s.c \
	type_x.c \
	type_percent.c \
	type_f.c \
	type_c.c \
	type_u.c \
	type_o.c \
	type_p.c \
	ft_wchar.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@echo " # sh : Job done $(shell pwd)/$(NAME)"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo " + sh : Creating Library $(shell pwd)/$(NAME)"

%.o: %.c
	@echo " + sh : Compiling OBJ_FILES < $^"
	@$(CC) $(CFLAGS) -o $@ -c $(SOURCES)$< -I $(INCLUDES)

clean:
	@rm -f $(OBJ)
	@echo " $(shell\
		if [ -d $(OBJ_DIR) ]; then\
			echo "- sh : Removing $(OBJ_DIR) with";\
			ls $(OBJ_DIR) | wc -w; echo "*.o";\
			rm -Rf $(OBJ_DIR);\
		else\
			echo "# sh : Nothing to clean";\
		fi)"

fclean: clean
	@rm -f $(NAME)
	@echo " $(shell\
		if [ -f $(NAME) ]; then\
			echo "- sh : Removing $ $(NAME) ";\
			rm -f $(NAME);\
		else\
			echo "# sh : Nothing to fclean";\
		fi)"

re: fclean all
