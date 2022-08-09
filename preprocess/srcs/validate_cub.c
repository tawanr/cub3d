/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:26:16 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/09 08:49:46 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

int	map_start(t_cub *cub)
{
	if (!cub->north)
		return (0);
	if (!cub->south)
		return (0);
	if (!cub->west)
		return (0);
	if (!cub->east)
		return (0);
	if (!cub->floor)
		return (0);
	if (!cub->ceiling)
		return (0);
	if (!cub->door)
		return (0);
	if (!cub->sprite)
		return (0);
	return (1);
}

static int	complete_cub(t_cub *cub)
{
	if (!map_start(cub))
		return (0);
	if (!cub->map || !cub->map->map)
		return (0);
	return (1);
}

static t_map	*map_dup(t_map *map)
{
	int		i;
	int		j;
	t_map	*new_map;

	new_map = (t_map *)malloc(sizeof(t_map) * 1);
	new_map->height = map->height;
	new_map->width = map->width;
	new_map->map = (int **)malloc(sizeof(int *) * new_map->height);
	i = 0;
	while (i < new_map->height)
	{
		new_map->map[i] = (int *)malloc(sizeof(int) * new_map->width);
		j = 0;
		while (j < new_map->width)
		{
			new_map->map[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	return (new_map);
}

int	validate_close_map(t_map *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->map[i][j];
			if (c == EMPTY || c == DOOR || c == OBJ)
			{
				if (!check_close_map(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_cub(t_cub *cub)
{
	t_map	*check_map;

	if (!complete_cub(cub))
		return (0);
	check_map = map_dup(cub->map);
	if (!validate_close_map(check_map))
	{
		free_map(check_map);
		return (0);
	}
	free_map(check_map);
	if (!validate_door(cub))
		return (0);
	if (!validate_sprite(cub))
		return (0);
	return (1);
}
