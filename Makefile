NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra # -Werror
DEBUG := -g

RED := \033[0;31m
GREEN := \033[0;32m
NC := \033[0m
SRC_DIR := src

# $ ls src/*.c | grep '\.c' >> Makefile
# $ ls src/*/*.c | grep '\.c' >> Makefile
# Temporary
FILES := \
	$(wildcard src/*.c) \
	$(wildcard src/*/*.c)

OFILES := $(patsubst src/%.c, build/%.o, $(FILES))
LIBFT := lib/libft/lib/libft.a

all: $(NAME)

$(NAME): $(OFILES) $(LIBFT)
	@$(CC) $(OFILES) \
	-Ilib/libft/inc/ -Llib/libft/lib -lft -lreadline -o $(NAME) -g -Wall -Wextra
	@echo "$(GREEN)Done$(NC)"

$(LIBFT):
	$(MAKE) -C lib/libft

build/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "$(GREEN) $^ $(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -Ilib/libft/inc $(DEBUG)

clean:
	rm -rf build

fclean: clean
	rm -f ./minishell

re: fclean all

.PHONY: all, clean, fclean, re
