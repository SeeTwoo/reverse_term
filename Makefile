CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = $(CFLAGS) -g3
INCLUDES = -Iincludes

SRC_DIR = src
SRC_FILES =	cursor_handling.c \
			destroy_term.c \
			escape_code_parser_skippers.c \
			exit_term.c \
			fill_grid.c \
			get_output.c \
			handle_keypress.c \
			init_grid.c \
			init_pty.c \
			init_window.c \
			main.c \
			new_render_op.c \
			parse_escape_code.c \
			render.c \
			term_runtime.c \
			VT100_commands.c

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
