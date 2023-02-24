NAME = minishell

MY_SOURCES = builtins_export_utils.c \
			builtins_export_sort.c \
			builtins_export.c \
			builtins.c \
			children_outfile.c \
			children_utils.c \
			children.c \
			env_list_utils.c \
			env_list.c \
			envp_to_path.c \
			frees.c \
			get_args_quotes.c \
			get_args_utils.c \
			get_args.c \
			heredoc_is_valid.c \
			heredoc_utils.c \
			heredoc.c \
			main.c \
			signals.c \
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

val: all
	make -C ./ clean
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind-out.txt \
		./$(NAME)
	code valgrind-out.txt