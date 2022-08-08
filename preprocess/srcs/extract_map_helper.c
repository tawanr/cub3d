/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:55:18 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/08 16:14:13 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

int	intarray_len(int *array[])
{
	int	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i])
	{
		i++;
	}
	return (i);
}

void	dup_map(int **new_map, int **old_map)
{
	int	i;
	int	size;

	i = 0;
	if (old_map == NULL)
	{
		new_map[i] = NULL;
		new_map[i + 1] = NULL;
		return ;
	}
	size = intarray_len(old_map);
	while (i < size)
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = NULL;
	new_map[i + 1] = NULL;
	free(old_map);
}

void	assign_player(t_cub *cub, int x, int y, char dir)
{
	t_preplayer	*player;

	player = (t_preplayer *)malloc(sizeof(t_preplayer) * 1);
	if (!player)
		return ;
	player->x = x;
	player->y = y;
	player->dir = dir;
	cub->player = player;
}
