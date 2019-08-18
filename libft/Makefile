# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 13:28:01 by jjourdai          #+#    #+#              #
#    Updated: 2019/08/18 11:21:06 by jpriou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/

SRC_NAME =	\
			btree_create_node.c \
			btree_search_item.c \
			checksum.c \
			endian.c \
			ft_atoi.c \
			ft_atoi_base.c \
			ft_bzero.c \
			ft_insertion_sort.c \
			ft_is.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_lststrsplit.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putnbr.c \
			ft_putstr.c \
			ft_split.c \
			ft_str_is_only_digit.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strchr_base.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strndup.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c \
			list_atoi_split.c \
			list_merge.c \
			list_pop.c \
			list_push.c \
			list_size.c \
			print_bits.c \
			shift_data.c \
			tab_is_sort.c

OBJ_PATH = .obj/

NAME = libft.a

CC = gcc

#CFLAGS = -Wall -Wextra -fsanitize=address -g -fno-omit-frame-pointer
CFLAGS = -g -Wall -Wextra -Werror
CFLAGS_STD = -std=gnu11
CFLAGS_DEP = -MT $@ -MD -MP -MF $(@:.o=.d)
IFLAGS = -Iinclude

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
	@ mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) -c $(CFLAGS) $(CFLAGS_STD) $(CFLAGS_DEP) $(IFLAGS) -o $@ $<

-include $(DEP)

.PHONY: clean
clean:
	rm -rf $(DEP)
	rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
