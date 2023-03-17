# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aplank <aplank@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 12:24:01 by aplank            #+#    #+#              #
#    Updated: 2023/03/17 18:36:09 by aplank           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MY_SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpa.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c\
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_char.c ft_decimal_integer.c ft_hexa_itoa.c ft_lower_hexa.c ft_pointer.c \
	ft_printf.c ft_redirecting.c ft_string.c ft_unsigned_decimal.c ft_upper_hexa.c \
	get_next_line_bonus.c get_next_line_utils_bonus.c

MY_BONUS_SOURCES = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

MY_BONUS_OBJECTS = $(MY_BONUS_SOURCES:.c=.o)

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS += -Wall -Werror -Wextra

CC = @cc

.PHONY: clean fclean all bonus

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@ar rcs $(MY_OBJECTS) -o $(NAME)
	@echo making mandatory .o files

bonus: $(MY_OBJECTS) $(MY_BONUS_OBJECTS)
	@ar rcs $(NAME) $(MY_OBJECTS) $(MY_BONUS_OBJECTS)
	@echo making mandatory and bonus .o files

clean:
	@rm -f $(MY_OBJECTS) $(MY_BONUS_OBJECTS)
	@echo all .o-files deleted

fclean: clean
	@rm -f libft.a
	@echo
	@echo ...and the libft.a too

re: fclean all

so:
	cc -nostartfiles -fPIC $(CFLAGS) $(MY_SOURCES) $(MY_BONUS_SOURCES)
	gcc -nostartfiles -shared -o libft.so $(MY_OBJECTS) $(MY_BONUS_OBJECTS)