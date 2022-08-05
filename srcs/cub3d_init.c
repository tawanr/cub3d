/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:42:30 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/04 11:02:45 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inithooks(void *mlx_win, t_gamevars *gamevars)
{
	mlx_hook(mlx_win, 2, 1L << 0, keymod, gamevars);
	mlx_hook(mlx_win, 6, 1L << 6, mouserot, gamevars);
	mlx_hook(mlx_win, 4, 1L << 2, mousectl, gamevars);
	mlx_hook(mlx_win, 5, 1L << 3, mouserel, gamevars);
	mlx_hook(mlx_win, 17, 1L << 17, end_win, gamevars);
	mlx_loop_hook(gamevars->mlx, drawframe, gamevars);
}

void	init_player(t_player *player)
{
	player->pos_x = 15 - 0.5;
	player->pos_y = 5 - 0.5;
	player->dir_x = 0;
	player->dir_y = -1;
	player->cam_x = 1;
	player->cam_y = 0;
	player->movespeed = 0.05;
	player->rot_speed = 0.05;
}

int	**init_map(void)
{
	int	map[MHEIGHT][MWIDTH] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1}
	};
	int	**newMap;

	newMap = (int **)malloc(MHEIGHT * sizeof(int *));
	for (int y = 0; y < MHEIGHT; y++)
	{
		newMap[y] = (int *)malloc(MWIDTH * sizeof(int));
		for (int x = 0; x < MWIDTH; x++)
			newMap[y][x] = map[y][x];
	}
	return (newMap);
}

void	init_minimap(t_minimap *minimap)
{
	minimap->pos_x = 10;
	minimap->pos_y = 10;
	minimap->scale = MAPSIZE / MWIDTH;
}
