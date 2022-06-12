SRCS = main.c cub3d_init.c cub3d_input.c cub3d_player.c cub3d_camera.c cub3d_draw.c cub3d_clean.c cub3d_texture.c
#cub3d_map.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Ilibft -Imlx
CFLAGS = -Wextra -Wall -Werror -Ilibft -Iminilibx -I/usr/include

NAME = cub3d
INCLUDES = ./libft

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx
	$(CC) $(OBJS) -lm -Llibft -lft -Lminilibx -lmlx -L/usr/lib -Iminilibx -framework OpenGL -framework AppKit -o $(NAME) -Ilibft

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
