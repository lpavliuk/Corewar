# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 16:04:15 by opavliuk          #+#    #+#              #
#    Updated: 2018/06/08 13:37:57 by opavliuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc 
CFLAGS=-Wall -Werror -Wextra
SRC=./srcs/add_argument.c \
	./srcs/compute_variables.c \
	./srcs/create_binary.c \
	./srcs/disassembly_output.c \
	./srcs/get_arguments.c \
	./srcs/get_commands.c \
	./srcs/get_header.c \
	./srcs/get_labels.c \
	./srcs/get_type.c \
	./srcs/read_binary.c \
	./srcs/show_bot.c \
	./srcs/staff.c \
	./srcs/staff2.c \
	./srcs/write_types.c \
	./srcs/main.c
	
INCLUDES=includes/
OBJ=$(SRC:.c=.o)
LIB = ../libft/libft.a
NAME=asm

all: $(NAME)

%.o: %.c
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

$(NAME): $(LIB) $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@ printf "\e[37;1m[Program \e[34;1masm \e[37;1mis \e[32;1mREADY!\e[37;1m]\e[0m🎅🏾🤙🏾🥃\n\n"
	@ ./asm

$(LIB):
	@ printf "\e[32;1mCompiling libft.a ...\n"
	@ make -C ../libft/
	@ printf "\n\e[32;1mCompiling asm ...\n"

clean:
	@ rm -f $(OBJ)
	@ make clean -C ../libft/
	@ printf "\e[37;1m[Directories \e[33;1msrcs/ \e[37;1m&& \e[33;1mlibft/ \e[37;1mis \e[32;1mCLEAN!\e[37;1m]\e[0m🗑\n"

fclean: clean
	@ rm -f $(NAME)
	@ make fclean -C ../libft/
	@ printf "\e[37;1m[Directories \e[33;1masm/ \e[37;1m&& \e[33;1mlibft/ \e[37;1mis \e[32;1mFCLEAN!\e[37;1m]\e[0m🗑\n"

re: fclean all

.PHONY: all, clean, fclean, re
