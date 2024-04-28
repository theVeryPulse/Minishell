NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror
DEBUG := -g

RED := \033[0;31m
GREEN := \033[0;32m
NC := \033[0m
SRC_DIR := src

# ls src/**/*.c >> Makefile
FILES := \
	src/arguments_expansion/expand_arguments.c \
	src/arguments_expansion/_expand_string.c \
	src/arguments_expansion/_is_variable_name.c \
	src/arguments_expansion/_replace_arg.c \
	src/character_checks/is_metacharacter.c \
	src/character_checks/is_quotation_mark.c \
	src/character_checks/is_redirect.c \
	src/character_checks/is_variable_name_middle.c \
	src/character_checks/is_variable_name_start.c \
	src/character_list/char_list_add_char.c \
	src/character_list/char_list_add_str.c \
	src/character_list/char_list_free_and_null.c \
	src/character_list/char_list_to_str.c \
	src/check_redirect_files.c \
	src/command_list/cmd_list_append.c \
	src/command_list/cmd_list_free.c \
	src/command_list/cmd_list_last.c \
	src/command_list/cmd_list_len.c \
	src/command_list/cmd_list_new.c \
	src/environment_variables/_env_append.c \
	src/environment_variables/env_build_envp.c \
	src/environment_variables/env_copy.c \
	src/environment_variables/env_free.c \
	src/environment_variables/env_get_value_by_name.c \
	src/environment_variables/env_init.c \
	src/environment_variables/env_remove_by_name.c \
	src/environment_variables/env_update_exit_status.c \
	src/environment_variables/env_update_name_value.c \
	src/environment_variables/is_valid_identifier.c \
	src/execution/_apply_redirects.c \
	src/execution/built_in/builtin_cd.c \
	src/execution/built_in/builtin_echo.c \
	src/execution/built_in/builtin_env.c \
	src/execution/built_in/builtin_exit.c \
	src/execution/built_in/builtin_export.c \
	src/execution/built_in/builtin_pwd.c \
	src/execution/built_in/builtin_unset.c \
	src/execution/built_in/is_builtin_function.c \
	src/execution/_child_execute_target_command.c \
	src/execution/_execute_builtin_function.c \
	src/execution/execute_commands.c \
	src/execution/execute_line.c \
	src/execution/_execute_one_command.c \
	src/execution/_execute_piped_commands.c \
	src/execution/_execute_shell_script.c \
	src/execution/_exit_status.c \
	src/execution/file_check.c \
	src/execution/_heredoc.c \
	src/execution/_stdin_stdout.c \
	src/free/free_and_null.c \
	src/free/free_cmds_env_pipes_rl_history.c \
	src/free/free_string_array_and_null.c \
	src/history.c \
	src/lexical_analyzer/_add_this_cmd_to_list.c \
	src/lexical_analyzer/analyze_lexemes.c \
	src/lexical_analyzer/_get_next_word_and_update_i.c \
	src/list_to_string_array.c \
	src/main.c \
	src/minishell/minishell.c \
	src/minishell/minishell_free.c \
	src/minishell/minishell_init.c \
	src/pipes/pipes_close_all.c \
	src/pipes/pipes_init.c \
	src/search_executable/paths_free.c \
	src/search_executable/paths_init.c \
	src/search_executable/search_executable.c \
	src/search_executable/search_executable_in_commands.c \
	src/signal_handler/sigint_sigquit_handler.c \
	src/syntax_analyzer/syntax_analyzer.c \
	src/test_func.c

OFILES := $(patsubst src/%.c, build/%.o, $(FILES))
LIBFT := lib/libft/lib/libft.a

all: $(NAME)

$(NAME): $(OFILES) $(LIBFT)
	@$(CC) $(OFILES) \
	-Ilib/libft/inc/ -Llib/libft/lib -lft -lreadline -o $(NAME) -g $(CFLAGS)
	@echo "$(GREEN)> $@$(NC)"

$(LIBFT):
	$(MAKE) -C lib/libft

build/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "$(GREEN)* $^$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -Ilib/libft/inc $(DEBUG)

clean:
	rm -rf build

fclean: clean
	rm -f ./minishell

re: fclean all

.PHONY: all, clean, fclean, re
