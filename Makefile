# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nprljic <nprljic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 12:24:01 by aplank            #+#    #+#              #
#    Updated: 2023/02/14 14:52:18 by nprljic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MY_SOURCES = builtins.c \
			children_utils.c \
			children.c \
			envp_to_path.c \
			frees.c \
			main.c \
			signals.c \
			split_line.c \
			terminal.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Werror -Wextra

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@$(MAKE) bonus -C libft
	@cc $(CFLAGS) $(MY_OBJECTS) libft/libft.a -lreadline -o $(NAME)
	@echo making mandatory .o files

clean:
	@$(MAKE) -C libft fclean
	@rm -f $(MY_OBJECTS)
	@echo all .o-files deleted

fclean: clean
	@rm -f minishell
	@echo
	@echo ...and the minishell too

re: fclean all

debug: CFLAGS += -g
debug: re