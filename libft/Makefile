# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 13:28:01 by jjourdai          #+#    #+#              #
#    Updated: 2019/07/25 14:38:14 by jpriou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/

SRC_NAME = tab_is_sort.c \
		   shift_data.c \
		   endian.c \
		   print_bits.c get_next_line.c \
		   ft_memalloc.c ft_strcat.c ft_strncmp.c \
		   ft_memccpy.c ft_strchr.c ft_strncpy.c \
		   ft_atoi.c ft_memchr.c ft_strclr.c \
		   ft_bzero.c ft_memcmp.c ft_strcmp.c ft_strnew.c \
		   ft_memcpy.c ft_strcpy.c ft_strnstr.c \
		   ft_memdel.c ft_strdel.c ft_strrchr.c \
		   ft_memmove.c ft_strdup.c ft_strsplit.c \
		   ft_memset.c ft_strequ.c ft_strstr.c \
		   ft_striter.c ft_strsub.c \
		   ft_itoa.c ft_striteri.c ft_strtrim.c \
		   ft_strjoin.c ft_tolower.c \
		   ft_strlcat.c ft_toupper.c \
		   ft_putnbr.c ft_strlen.c \
		   ft_strmap.c ft_strncat.c \
		   ft_putstr.c ft_strmapi.c \
		   ft_itoa_base.c \
		   ft_strndup.c \
		   ft_strchr_base.c \
		   ft_insertion_sort.c \
		   ft_is.c ft_split.c ft_atoi_base.c \
		   ft_lststrsplit.c \
		   list_push.c \
		   list_merge.c \
		   list_atoi_split.c \
		   list_size.c list_pop.c \
		   btree_create_node.c btree_search_item.c checksum.c \
		   ft_str_is_only_digit.c

OBJ_PATH = .obj/

CPPFLAGS = -Iinclude

NAME = libft.a

CC = gcc

#CFLAGS = -Wall -Wextra -fsanitize=address -g -fno-omit-frame-pointer
CFLAGS = -MD -Wall -Wextra -Werror -g

OBJ_NAME = $(SRC_NAME:.c=.o)
DEP_NAME = $(SRC_NAME:.c=.d)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
DEP = $(addprefix $(OBJ_PATH), $(DEP_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

-include $(DEP)

.PHONY: clean
clean:
	rm -fv $(DEP)
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

.PHONY: fclean
fclean: clean
	rm -fv $(NAME)

.PHONY: re
re: fclean all
