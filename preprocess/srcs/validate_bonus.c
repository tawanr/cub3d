/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:57:39 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/08 21:50:18 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

static int	check_door(t_map *map, int i, int j)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (i + 1 >= map->height)
		return (0);
	else if (i <= 0)
		return (0);
	if (j + 1 >= map->width)
		return (0);
	else if (j <= 0)
		return (0);
	up = map->map[i - 1][j];
	down = map->map[i + 1][j];
	left = map->map[i][j - 1];
	right = map->map[i][j + 1];
	if (!(left == WALL && right == WALL) && !(up == WALL && down == WALL))
		return (0);
	return (1);
}

int	validate_door(t_cub *cub)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	map = cub->map;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == DOOR)
			{
				if (!cub->door)
					return (0);
				if (!check_door(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_sprite(t_cub *cub)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	map = cub->map;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == OBJ)
			{
				if (!cub->sprite)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
