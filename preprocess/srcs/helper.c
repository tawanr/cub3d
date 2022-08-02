/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:26:45 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 21:45:08 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "preprocess.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (!map->map)
	{
		free(map);
		return ;
	}
	i = 0;
	while (i < map->height)
	{
		free(map->map[i++]);
	}
	free(map->map);
	free(map);
}

void	free_cub(t_cub *cub)
{
	if (cub->north)
		free(cub->north);
	if (cub->south)
		free(cub->south);
	if (cub->west)
		free(cub->west);
	if (cub->east)
		free(cub->east);
	if (cub->floor)
		free(cub->floor);
	if (cub->ceiling)
		free(cub->ceiling);
	free_map(cub->map);
	free(cub);
}

void	free_strarray(char *array[])
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i++]);
	}
	free(array);
}

int	strarray_len(char *array[])
{
	int	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	map_error(t_cub *cub, char *msg)
{
	if (cub)
		free_cub(cub);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
