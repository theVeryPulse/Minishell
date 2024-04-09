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
	-Ilib/libft/inc/ -Llib/libft/lib -lft -lreadline -o minishell -g -Wall -Wextra

developing:
	@echo "Compiling..."