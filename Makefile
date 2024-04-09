NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror

INC_DIR := inc
SRC_DIR := src


all: $(NAME)

$(NAME): developing
	cc src/*.c \
	src/lexical_analyzer/*.c \
	src/syntax_analyzer/*.c \
	src/environment_variables/*.c \
	src/character_list/*.c \
	src/command_list/*.c \
	src/arguments_expansion/*.c \
	-Ilib/libft/inc/ -Llib/libft/lib -lft -lreadline -o minishell -g -Wall -Wextra

developing:
	@echo "Compiling..."