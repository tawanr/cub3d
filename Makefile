SRCS = main.c cub3d_init.c cub3d_input.c cub3d_player.c cub3d_camera.c cub3d_draw.c 
#cub3d_map.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Ilibft -Imlx
CFLAGS = -Wextra -Wall -Werror -Ilibft -Iminilibx-linux -I/usr/include -O3

NAME = cub3d
INCLUDES = ./libft

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx-linux
	$(CC) $(OBJS) -lm -Llibft -lft -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME) -Ilibft

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
