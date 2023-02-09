# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aplank <aplank@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 12:24:01 by aplank            #+#    #+#              #
#    Updated: 2023/02/09 18:09:57 by aplank           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MY_SOURCES = frees.c \
			main.c \
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