NAME		= minishell
PATH_B		= builtins/builtins
PATH_C		= children/children
PATH_G		= get_args/get_args
PATH_H		= heredoc/heredoc
BUILTINS	= $(PATH_B)_cd_dot_utils.c \
			$(PATH_B)_cd_dot.c \
			$(PATH_B)_cd_remove_end.c \
			$(PATH_B)_cd_save_pwd.c \
			$(PATH_B)_cd_utils.c \
			$(PATH_B)_cd.c \
			$(PATH_B)_echo.c \
			$(PATH_B)_env_list_to_matrix.c \
			$(PATH_B)_export_sort.c \
			$(PATH_B)_export_utils.c \
			$(PATH_B)_export.c \
			$(PATH_B)_unset.c \
			$(PATH_B).c
CHILDREN	= $(PATH_C)_arrows_utils.c \
			$(PATH_C)_arrows.c \
			$(PATH_C)_process_utils.c \
			$(PATH_C)_process.c \
			$(PATH_C)_path_utils.c \
			$(PATH_C)_path.c \
			$(PATH_C)_utils.c \
			$(PATH_C).c
GET_ARGS	= $(PATH_G)_cut_arg.c \
			$(PATH_G)_path.c \
			$(PATH_G)_quotes.c \
			$(PATH_G)_syntax_errors.c \
			$(PATH_G)_utils.c \
			$(PATH_G)_variables.c \
			$(PATH_G).c
HEREDOC		= $(PATH_H)_free_kid_cmd.c \
			$(PATH_H)_is_valid.c \
			$(PATH_H)_utils.c \
			$(PATH_H).c
MY_SOURCES 	= $(BUILTINS) \
			$(CHILDREN) \
			$(GET_ARGS) \
			$(HEREDOC) \
			env_list_utils.c \
			env_list.c \
			envp_save.c \
			exit_status.c \
			exit.c \
			frees.c \
			main.c \
			shell_level.c \
			signals.c \
			terminal.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = @cc

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
	@cc $(CFLAGS) $(MY_OBJECTS) libft/libft.a -lreadline -lhistory -o $(NAME)
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
		--suppressions=readline_ignore.txt \
		./$(NAME)
	code valgrind-out.txt