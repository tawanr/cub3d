/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:55:23 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/04 15:38:47 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_ws(t_gamevars *gamevars, int fwd)
{
	double		*pos_x;
	double		*pos_y;
	double		movespeed;
	int			**map;
	t_player	*p;

	pos_x = &gamevars->player->pos_x;
	pos_y = &gamevars->player->pos_y;
	p = gamevars->player;
	movespeed = gamevars->player->movespeed;
	map = gamevars->map.map;
	if (map[(int)*pos_y][(int)(*pos_x + (p->dir_x * fwd * movespeed))] == 0)
		*pos_x += p->dir_x * fwd * movespeed;
	if (map[(int)(*pos_y + (p->dir_y * fwd * movespeed))][(int)*pos_x] == 0)
		*pos_y += p->dir_y * fwd * movespeed;
}

void	player_move_ad(t_gamevars *gamevars, int fwd)
{
	double		*pos_x;
	double		*pos_y;
	double		movespeed;
	int			**map;
	t_player	*p;

	pos_x = &gamevars->player->pos_x;
	pos_y = &gamevars->player->pos_y;
	p = gamevars->player;
	movespeed = gamevars->player->movespeed;
	map = gamevars->map.map;
	if (map[(int)*pos_y][(int)(*pos_x + (p->dir_y * movespeed))] == 0)
		*pos_x += p->dir_y * fwd * movespeed;
	if (map[(int)(*pos_y + (p->dir_x * movespeed))][(int)*pos_x] == 0)
		*pos_y += p->dir_x * -fwd * movespeed;
}

void	player_rotate(t_gamevars *gamevars, int dir)
{
	double		dir_x;
	double		dir_y;
	double		speed;
	t_player	*p;

	p = gamevars->player;
	speed = dir * p->rot_speed;
	dir_x = p->dir_x;
	dir_y = p->dir_y;
	p->dir_x = dir_x * cos(speed) - dir_y * sin(speed);
	p->dir_y = dir_x * sin(speed) + dir_y * cos(speed);
	dir_x = p->cam_x;
	dir_y = p->cam_y;
	p->cam_x = dir_x * cos(speed) - dir_y * sin(speed);
	p->cam_y = dir_x * sin(speed) + dir_y * cos(speed);
}
