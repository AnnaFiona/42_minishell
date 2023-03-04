NAME		= minishell
PATH_B		= builtins/builtins
PATH_C		= children/children
PATH_H		= heredoc/heredoc
BUILTINS	= $(PATH_B)_cd.c \
			$(PATH_B)_export_utils.c \
			$(PATH_B)_export_sort.c \
			$(PATH_B)_export.c \
			$(PATH_B).c
CHILDREN	= $(PATH_C)_arrows_utils.c \
			$(PATH_C)_arrows.c \
			$(PATH_C)_process.c \
			$(PATH_C)_path.c \
			$(PATH_C)_utils.c \
			$(PATH_C).c
HEREDOC		= $(PATH_H)_free_kid_cmd.c \
			$(PATH_H)_is_valid.c \
			$(PATH_H)_utils.c \
			$(PATH_H).c

MY_SOURCES 	= $(BUILTINS) \
			$(CHILDREN) \
			env_list_utils.c \
			env_list.c \
			envp_to_path.c \
			frees.c \
			get_args_path.c \
			get_args_quotes.c \
			get_args_utils.c \
			get_args.c \
			$(HEREDOC) \
			main.c \
			signals.c \
			terminal.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Werror -Wextra

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@$(MAKE) bonus -C libft
	@cc $(CFLAGS) $(MY_OBJECTS) libft/libft.a -lreadline -o $(NAME)
	@echo "$(GREEN)// Minishell created //$(DEF_COLOR)"

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