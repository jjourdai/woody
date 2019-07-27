# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 13:28:01 by jjourdai          #+#    #+#              #
#    Updated: 2019/07/25 15:14:28 by jpriou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/

SRC_NAME = \
		main.c \
		param.c \
		err.c \
		consts.c \
		elf64_loader.c \
		elf64_dissect.c \
		useless.c \
		check_or_generate_key.c \
		encrypt/rc5_encrypt.c \
		encrypt/xor.c \
		shellcode/sh_alloc.c \
		shellcode/sh_free.c \
		shellcode/sh_finish.c \
		shellcode/sh_print.c \
		shellcode/sh_jump.c \
		shellcode/sh_mprotect.c \
		shellcode/sh_regs_recover.c \
		shellcode/sh_regs_save.c \
		shellcode/sh_initframe.c \
		shellcode/sh_endframe.c \
		shellcode/sh_xor.c \
		shellcode/sh_file.c \
		

OBJ_PATH = ./.obj/

CPPFLAGS = -Iinclude -I ./libft/include

LDFLAGS = -Llibft

LDLIBS = -lft

NAME = woody_woodpacker

CC = gcc

#CFLAGS = -Wall -Wextra -fsanitize=address -g -fno-omit-frame-pointer
#CFLAGS = -Wall -Wextra -Werror
# Weverything
CFLAGS = -MD -std=gnu11 -Wall -Wextra -g

OBJ_NAME = $(SRC_NAME:.c=.o)
DEP_NAME = $(SRC_NAME:.c=.d)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
DEP = $(addprefix $(OBJ_PATH), $(DEP_NAME))

.PHONY: all
all:
	make $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	$(CC) $^ -o $(NAME) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ mkdir -p $(shell dirname $@)
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -c $<

-include $(DEP)

.PHONY: clean
clean:
	rm -fv $(OBJ)
	rm -rf $(DEP)
	make clean -C ./libft/
	@rmdir $(OBJ_PATH) 2> /dev/null || true

.PHONY: fclean
fclean: clean
	make fclean -C ./libft/
	rm -fv $(NAME)
	rm -fv woody

.PHONY: re
re:
	make fclean
	make all

.PHONY: test
test:
	make -f test.mk all
