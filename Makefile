UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MLX_DIR = minilibx-macos
else
	MLX_DIR = minilibx-linux
endif

LIBFT_DIR = libft

SRCS = main.c cub3d_init.c cub3d_input.c cub3d_player.c cub3d_camera.c cub3d_draw.c cub3d_clean.c cub3d_texture.c
#cub3d_map.c

SRC_DIR = srcs/
OBJS = $(SRCS:.c=.o)
OBJ_DIR = objs/

CC = gcc -Ilibft -Imlx
CFLAGS = -Wextra -Wall -Werror -Ilibft -I$(MLX_DIR) -I/usr/include

NAME = cub3d
INCLUDES = -I$(MLX_DIR) -Ilibft -Iincludes -Ipreprocess/includes

ifeq ($(UNAME_S), Darwin)
	LIBS = -L$(MLX_DIR) -lmlx -L/usr/lib -L$(LIBFT_DIR) -lft -lm -framework OpenGL -framework AppKit -Lpreprocess -lprecub3d
else
	LIBS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -Lpreprocess -lprecub3d -L$(LIBFT_DIR) -lft
endif

$(OBJ_DIR)%o: $(SRC_DIR)%c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	$(MAKE) -C ./libft
	$(MAKE) -C ./$(MLX_DIR)
	$(MAKE) -C ./preprocess
	$(CC) $(addprefix $(OBJ_DIR), $(OBJS)) $(INCLUDES) $(LIBS) -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./$(MLX_DIR)
	$(MAKE) clean -C ./preprocess
	rm -rf $(addprefix $(OBJ_DIR), $(OBJS))

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) clean -C ./$(MLX_DIR)
	$(MAKE) fclean -C ./preprocess
	rm -rf $(NAME)

re: fclean all
