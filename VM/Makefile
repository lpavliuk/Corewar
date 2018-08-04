COLOR_OFF=\033[0m#			# Text Reset
BLACK	=\033[0;30m#		# Black
RED		=\033[0;31m#		# Red
GREEN	=\033[0;32m#		# Green
YELLOW	=\033[0;33m#		# Yellow
BLUE	=\033[0;34m#		# Blue
PURPLE	=\033[0;35m#		# Purple
CYAN	=\033[0;36m#		# Cyan
WHITE	=\033[0;37m#		# White

CC=		gcc

# FLAGS=	-Wall -Wextra -Werror

NAME=	core

SRCNAME=	bot_parsing.c\
			check_exec.c\
			get_server_info.c\
			main.c\
			parse_argument.c\
			process_function_ft_aff_zjmp.c\
			ft_add_sub.c\
			ft_and_or_xor.c\
			ft_fork_lfork.c\
			ft_ld_ldi_lld_lldi.c\
			ft_live_st_sti.c\
			sort_bot_list.c\
			staff.c\
			staff2.c\
			step.c\
			text_output.c\
			visualize.c
			# test_socket.c\

			# bot_parsing.c\
			# check_exec.c\
			# get_args.c\
			# main.c\
			# process_functions.c\
			# staff.c\
			# staff2.c\
			# step.c\
			# text_output.c\
			# get_server_info.c\
			# visualize.c
			# # test_socket.c
			# visualize.c
#main.c

INCLD=	./include

SRC=$(addprefix ./src/, $(SRCNAME))
# SRC= ./src/*.c

OBJ= $(SRC:%.c=%.o)

LIBFT= ../libft/libft.a
# LIBFTPRINTF= ./src/libft/libftprintf.a

OK_STRING    =***	$(NAME) created		***

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJ) -I $(INCLD) -o $(NAME) -lncurses
	@printf "\n$(GREEN)$(OK_STRING)\n\n"

%.o:%.c $(LIBFT) ./include/corewar.h
	@$(CC) $(FLAGS) -c $< -I $(INCLD) -o $@ 
	@printf "$(CYAN)*$(COLOR_OFF)"

$(LIBFT):
	$(MAKE) -C ../libft
	@printf "\n$(GREEN)libft created $(COLOR_OFF)\n\n"

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C ../libft
	@printf  "$(YELLOW)remove OBJ\n"

fclean:
	@printf "$(YELLOW)remove OBJ$(COLOR_OFF)\n"
	@$(MAKE) fclean -C ../libft
	@rm -f $(OBJ)
	@printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"
	@rm -f $(NAME)
	@printf "$(RED)remove $(NAME2)$(COLOR_OFF)\n"
	@rm -f $(NAME2)

re: fclean all