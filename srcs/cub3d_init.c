/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:42:30 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 14:58:13 by tratanat         ###   ########.fr       */
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
	player->movespeed = 6;
	player->rot_speed = 4;
}

void	init_minimap(t_minimap *minimap)
{
	minimap->pos_x = 10;
	minimap->pos_y = 10;
	minimap->scale = MAPSIZE / MWIDTH;
}

void	init_gamevars(t_gamevars *gamevars)
{
	gamevars->map.map = gamevars->map_data->map->map;
	gamevars->map.width = gamevars->map_data->map->width;
	gamevars->map.height = gamevars->map_data->map->height;
	gamevars->time = gettime();
	gamevars->input->rmouse_pressed = 0;
	gamevars->doorcalls = (t_door **)malloc(sizeof(t_door *));
	*gamevars->doorcalls = NULL;
	gamevars->map.map[7][14] = 2;
	gamevars->map.map[3][18] = 2;
}
