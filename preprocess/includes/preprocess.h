/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:33:29 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 21:34:42 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPROCESS_H
# define PREPROCESS_H

// Structure for Input Map

# define SEP_FLAG 2
# define P_FLAG 4

enum
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEIL
};

enum
{
	EMPTY,
	WALL,
	N,
	S,
	W,
	E,
	SPACE,
	CHECK,
	END = 9
};

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_map
{
	int	**map;
	int	height;
	int	width;
}	t_map;

typedef struct s_cub
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_rgb	*floor;
	t_rgb	*ceiling;
	t_map	*map;
}	t_cub;

// Preprocess
t_cub	*preprocess_cub(int argc, char *argv[]);

// Extract cub
t_cub	*extract_cub(int fd);

// Extract wall
void	add_cub_wall(t_cub *cub, char *array[]);

// Extract map
int		intarray_len(int *array[]);
void	dup_map(int **new_map, int **old_map);
void	add_map(char *line, t_cub *cub, int *i, int *flag);

// Refine map
void	refine_map(t_map *map);

// Helper
void	free_map(t_map *map);
void	free_cub(t_cub *cub);
int		strarray_len(char *array[]);
void	free_strarray(char *array[]);
void	map_error(t_cub *cub, char *msg);

// Split Space
char	**split_space(char *s);

// Validate cub
int		map_start(t_cub *cub);
int		validate_cub(t_cub *cub);
int		check_close_map(t_map *map, int i, int j);

#endif
