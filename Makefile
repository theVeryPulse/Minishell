NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror

INC_DIR := inc
SRC_DIR := src


all: $(NAME)

$(NAME): developing
	cc src/*.c -I lib/libft/inc/ -I inc -L lib/libft/lib -lft -lreadline -o minishell -g -Wall -Wextra

developing:
	@echo "Compiling..."