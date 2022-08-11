# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 10:41:23 by spoolpra          #+#    #+#              #
#    Updated: 2022/08/11 10:45:54 by spoolpra         ###   ########.fr        #
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
		validate_cub.c validate_map.c validate_map_helper.c validate_bonus.c\
		split_space.c split_space_helper.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	$(MAKE) -C $(LIB_DIR)
	ar -rcs $(NAME) $^

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
