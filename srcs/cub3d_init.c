/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:42:30 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 09:51:30 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inithooks(void *mlx_win, t_gamevars *gamevars)
{
	mlx_hook(mlx_win, 2, 1L << 0, keypress, gamevars);
	mlx_hook(mlx_win, 3, 1L << 1, keyrelease, gamevars);
	mlx_hook(mlx_win, 6, 1L << 6, mouserot, gamevars);
	mlx_hook(mlx_win, 4, 1L << 2, mousectl, gamevars);
	mlx_hook(mlx_win, 5, 1L << 3, mouserel, gamevars);
	mlx_hook(mlx_win, 17, 1L << 17, end_win, gamevars);
	mlx_loop_hook(gamevars->mlx, drawframe, gamevars);
}

void	init_player(t_gamevars *gv, t_player *player)
{
	player->pos_x = gv->map_data->player->x + 0.5;
	player->pos_y = gv->map_data->player->y + 0.5;
	player->dir_x = 0;
	player->dir_y = 0;
	player->cam_x = 0;
	player->cam_y = 0;
	if (gv->map_data->player->dir == 'N')
		player->dir_y = -1;
	else if (gv->map_data->player->dir == 'S')
		player->dir_y = 1;
	else if (gv->map_data->player->dir == 'W')
		player->dir_x = -1;
	else if (gv->map_data->player->dir == 'E')
		player->dir_x = 1;
	if (gv->map_data->player->dir == 'N' || gv->map_data->player->dir == 'S')
		player->cam_x = 1;
	else
		player->cam_y = 1;
	player->movespeed = 5;
	player->rot_speed = 5;
}

void	init_minimap(t_minimap *minimap)
{
	minimap->pos_x = 10;
	minimap->pos_y = 10;
	minimap->scale = MAPSIZE / MWIDTH;
}

void	init_keys(t_gamevars *gv)
{
	gv->input->w_down = 0;
	gv->input->a_down = 0;
	gv->input->s_down = 0;
	gv->input->d_down = 0;
	gv->input->left_down = 0;
	gv->input->right_down = 0;
	gv->input->up_down = 0;
	gv->input->down_down = 0;
	gv->input->q_down = 0;
	gv->input->e_down = 0;
	gv->input->mouse_pressed = 0;
	gv->input->rmouse_pressed = 0;
}

void	init_gamevars(t_gamevars *gamevars)
{
	int		i;
	char	*a;
	t_data	*img;

	gamevars->map.map = gamevars->map_data->map->map;
	gamevars->map.width = gamevars->map_data->map->width;
	gamevars->map.height = gamevars->map_data->map->height;
	gamevars->time = gettime();
	gamevars->input->rmouse_pressed = 0;
	gamevars->doorcalls = (t_door **)malloc(sizeof(t_door *));
	*gamevars->doorcalls = NULL;
	gamevars->objectque = (t_object **)malloc(sizeof(t_object *));
	*gamevars->objectque = NULL;
	gamevars->framecount = 0;
	i = 0;
	while (i < 2)
	{
		img = (t_data *)malloc(sizeof(t_data));
		img->img = mlx_new_image(gamevars->mlx, WWIDTH, WHEIGHT);
		a = mlx_get_data_addr(img->img, &img->bpp, &img->linelen, &img->endian);
		img->addr = a;
		gamevars->buffer[i++] = img;
	}
	gamevars->img = gamevars->buffer[0];
	init_keys(gamevars);
}
