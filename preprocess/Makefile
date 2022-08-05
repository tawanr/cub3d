# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 10:41:23 by spoolpra          #+#    #+#              #
#    Updated: 2022/08/04 08:25:50 by tratanat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/
LIB_DIR = ../libft

INCS = -Iincludes/ -I$(LIB_DIR) -I../includes
NAME = libprecub3d.a
SRCS =	preprocess.c helper.c \
		extract_cub.c extract_wall.c extract_map.c extract_map_helper.c \
		refine_map.c \
		validate_cub.c validate_map.c validate_map_helper.c\
		split_space.c split_space_helper.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	$(MAKE) -C $(LIB_DIR)
	ar -rcs $(NAME) $^

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCS) -lft -o $@ -L$(LIB_DIR) -lft

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
