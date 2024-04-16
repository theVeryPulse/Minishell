NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror

INC_DIR := inc
SRC_DIR := src


all: $(NAME)

$(NAME): developing lib/libft/lib/libft.a
	cc src/*.c \
	src/lexical_analyzer/*.c \
	src/syntax_analyzer/*.c \
	src/environment_variables/*.c \
	src/character_list/*.c \
	src/command_list/*.c \
	src/arguments_expansion/*.c \
	src/built_in/*.c \
	src/pipes/*.c \
	src/character_checks/*.c \
	src/search_executable/*.c \
	-Ilib/libft/inc/ -Llib/libft/lib -lft -lreadline -o minishell -g -Wall -Wextra

developing:
	@echo "Compiling..."

lib/libft/lib/libft.a:
	$(MAKE) -C lib/libft