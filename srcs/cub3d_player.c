/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:55:23 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 12:45:24 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_play(t_gamevars *gv)
{
	if (gv->input->w_down || gv->input->up_down)
		player_move_ws(gv, 1);
	if (gv->input->s_down || gv->input->down_down)
		player_move_ws(gv, -1);
	if (gv->input->a_down || gv->input->left_down)
		player_move_ad(gv, 1);
	if (gv->input->d_down || gv->input->right_down)
		player_move_ad(gv, -1);
	if (gv->input->e_down)
		player_rotate(gv, 1);
	if (gv->input->q_down)
		player_rotate(gv, -1);
}

void	player_move_ws(t_gamevars *gamevars, int fwd)
{
	double		*pos_x;
	double		*pos_y;
	double		ms;
	int			**map;
	t_player	*p;

	pos_x = &gamevars->player->pos_x;
	pos_y = &gamevars->player->pos_y;
	p = gamevars->player;
	ms = gamevars->player->movespeed * gamevars->frametime;
	map = gamevars->map.map;
	if (map[(int)((*pos_y - .2 * fwd) + p->dir_y * fwd * ms)]
		[(int)((*pos_x - .2 * fwd) + p->dir_x * fwd * ms)] == 0)
	{
		*pos_x += p->dir_x * fwd * ms;
		*pos_y += p->dir_y * fwd * ms;
	}
	else if (map[(int)*pos_y][(int)((*pos_x - .2 * fwd) + \
		p->dir_x * fwd * ms)] == 0)
		*pos_x += p->dir_x * fwd * ms;
	else if (map[(int)((*pos_y - .2 * fwd) + p->dir_y * fwd * ms)]
		[(int)*pos_x] == 0)
		*pos_y += p->dir_y * fwd * ms;
}

void	player_move_ad(t_gamevars *gamevars, int fwd)
{
	double		*pos_x;
	double		*pos_y;
	double		ms;
	int			**map;
	t_player	*p;

	pos_x = &gamevars->player->pos_x;
	pos_y = &gamevars->player->pos_y;
	p = gamevars->player;
	ms = gamevars->player->movespeed * gamevars->frametime;
	map = gamevars->map.map;
	if (map[(int)((*pos_y - .2 * fwd) + p->dir_x * fwd * ms)]
		[(int)((*pos_x - .2 * fwd) + p->dir_y * fwd * ms)] == 0)
	{
		*pos_x += p->dir_y * fwd * ms;
		*pos_y += p->dir_x * -fwd * ms;
	}
	else if (map[(int)*pos_y][(int)((*pos_x - .2 * fwd) + \
		p->dir_y * fwd * ms)] == 0)
		*pos_x += p->dir_y * fwd * ms;
	else if (map[(int)((*pos_y - .2 * fwd) + p->dir_x * fwd * ms)]
		[(int)*pos_x] == 0)
		*pos_y += p->dir_x * -fwd * ms;
}

void	player_rotate(t_gamevars *gamevars, int dir)
{
	double		dir_x;
	double		dir_y;
	double		speed;
	t_player	*p;

	p = gamevars->player;
	speed = dir * p->rot_speed * gamevars->frametime;
	dir_x = p->dir_x;
	dir_y = p->dir_y;
	p->dir_x = dir_x * cos(speed) - dir_y * sin(speed);
	p->dir_y = dir_x * sin(speed) + dir_y * cos(speed);
	dir_x = p->cam_x;
	dir_y = p->cam_y;
	p->cam_x = dir_x * cos(speed) - dir_y * sin(speed);
	p->cam_y = dir_x * sin(speed) + dir_y * cos(speed);
	p->moved = 1;
}

void	check_pos(t_gamevars *gv)
{
	double	pos_x;
	double	pos_y;

	pos_x = gv->player->pos_x;
	pos_y = gv->player->pos_y;
	if (gv->player->last_pos.x == pos_x && gv->player->last_pos.y == pos_y)
		return ;
	if ((int)pos_x < gv->map.width && \
		(int)pos_y < gv->map.height && \
		gv->map.map[(int)(pos_y)][(int)(pos_x)] == 0 && \
		gv->map.map[(int)(pos_y + .1)][(int)(pos_x)] != 1 && \
		gv->map.map[(int)(pos_y - .1)][(int)(pos_x)] != 1 && \
		gv->map.map[(int)(pos_y)][(int)(pos_x + .1)] != 1 && \
		gv->map.map[(int)(pos_y)][(int)(pos_x - .1)] != 1)
	{
		gv->player->last_pos.x = pos_x;
		gv->player->last_pos.y = pos_y;
		gv->player->moved = 1;
	}
	else
	{
		gv->player->pos_x = gv->player->last_pos.x;
		gv->player->pos_y = gv->player->last_pos.y;
		gv->player->moved = 0;
	}
}
