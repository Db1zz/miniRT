# Project settings
NAME = miniRT
CC = cc
UNAME_S := $(shell uname -s)
FLAGS = -Wall -Wextra -Werror
MINILIBX_TGZ_NAME = MiniLibX.tgz
MINILIBX = minilibx_opengl_20191021/libmlx.a
LIBFT = libft/libft.a
LIBFT_DIR = libft
SRCS = src/minirt.c
SRCS_DIR = src
OBJS = $(SRCS:src/%.c=objs/%.o)
OBJS_DIR = objs
INCLUDE = -I include -I libft/ft_printf/include
ifeq ($(UNAME_S), Linux)
	LIB_URL = https://cdn.intra.42.fr/document/document/26192/minilibx-linux.tgz
	FLAGS_MINILIBX = -I/usr/include -Imlx_linux -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MINILIBX_DIR = ./minilibx-linux
else ifeq ($(UNAME_S), Darwin)
	LIB_URL = https://cdn.intra.42.fr/document/document/26193/minilibx_opengl.tgz
	FLAGS_MINILIBX = -Lmlx -framework OpenGL -framework AppKit
	MINILIBX_DIR = ./minilibx_opengl_20191021
endif

all: $(MINILIBX_DIR) $(MINILIBX) $(LIBFT) $(OBJS) $(NAME)

$(MINILIBX_DIR):
	@echo "Downloading MiniLibX for $(UNAME_S) from $(LIB_URL)"
	curl -L -o $(MINILIBX_TGZ_NAME) $(LIB_URL)
	@echo "Download completed."
	tar -xzf $(MINILIBX_TGZ_NAME)
	rm -f $(MINILIBX_TGZ_NAME)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(FLAGS_MINILIBX) $(MINILIBX) $(LIBFT) $(INCLUDE) -o $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re