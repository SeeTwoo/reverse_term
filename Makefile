CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = $(CFLAGS) -g3
INCLUDES = -Iincludes

SRC_DIR = src
SRC_FILES =	destroy_term.c \
			init_event.c \
			init_window.c \
			main.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

NAME = reverse_term

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lX11

debug: fclean
	$(MAKE) CFLAGS="$(DFLAGS)" all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
