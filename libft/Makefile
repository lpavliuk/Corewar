# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 16:04:15 by opavliuk          #+#    #+#              #
#    Updated: 2018/05/14 13:31:16 by opavliuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc 
CFLAGS=-Wall -Werror -Wextra
SRC=./ft_memset.c \
	./ft_atoi.c \
	./ft_bzero.c \
	./ft_count_words.c \
	./ft_isalnum.c \
	./ft_isalpha.c \
	./ft_isascii.c \
	./ft_isdigit.c \
	./ft_isprint.c \
	./ft_itoa.c \
	./ft_lstadd.c \
	./ft_lstdel.c \
	./ft_lstdelone.c \
	./ft_lstiter.c \
	./ft_lstlen.c \
	./ft_lstmap.c \
	./ft_lstnew.c \
	./ft_lstprint.c \
	./ft_memalloc.c \
	./ft_memccpy.c \
	./ft_memchr.c \
	./ft_memcmp.c \
	./ft_memcpy.c \
	./ft_memdel.c \
	./ft_memmove.c \
	./ft_memset.c \
	./ft_putchar.c \
	./ft_putchar_fd.c \
	./ft_putendl.c \
	./ft_putendl_fd.c \
	./ft_putnbr.c \
	./ft_putnbr_fd.c \
	./ft_putstr.c \
	./ft_putstr_fd.c \
	./ft_sqrt.c \
	./ft_stralldel.c \
	./ft_strcat.c \
	./ft_strchr.c \
	./ft_strclr.c \
	./ft_strcmp.c \
	./ft_strcpy.c \
	./ft_strdel.c \
	./ft_strdup.c \
	./ft_strequ.c \
	./ft_striter.c \
	./ft_striteri.c \
	./ft_strjoin.c \
	./ft_strlcat.c \
	./ft_strlen.c \
	./ft_strmap.c \
	./ft_strmapi.c \
	./ft_strncat.c \
	./ft_strncmp.c \
	./ft_strncpy.c \
	./ft_strnequ.c \
	./ft_strnew.c \
	./ft_strnstr.c \
	./ft_strrchr.c \
	./ft_strsplit.c \
	./ft_strstr.c \
	./ft_strsub.c \
	./ft_strtrim.c \
	./ft_tolower.c \
	./ft_toupper.c \
	./get_next_line.c \
	./check_percent.c \
	./ft_printf.c \
	./ft_putnbr_base.c \
	./write_symbol_s_uni.c \
	./write_to_buffer.c \
	./write_type_c.c \
	./write_type_s.c \
	./write_type_d_i.c \
	./write_type_x_p.c \
	./write_type_o.c \
	./write_type_u.c \
	./write_colors.c
OBJ=$(SRC:.c=.o)
NAME=libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ printf "\e[37;1m[\e[33;1mlibft.a \e[37;1mis \e[32;1mREADY!\e[37;1m]\e[0m📚\n"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I ./

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
