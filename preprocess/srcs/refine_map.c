/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:00:12 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 20:18:16 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

static void	resize_map_line(int **map_line, int width)
{
	int	i;
	int	*new_map_line;

	i = 0;
	new_map_line = (int *)malloc(sizeof(int) * width);
	while ((*map_line)[i] != END)
	{
		new_map_line[i] = (*map_line)[i];
		i++;
	}
	while (i < width)
	{
		new_map_line[i] = SPACE;
		i++;
	}
	free(*map_line);
	*map_line = new_map_line;
}

void	refine_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		resize_map_line(&map->map[i++], map->width);
	}
}
