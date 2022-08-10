/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:46:20 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 13:29:14 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mousectl(int button, int x, int y, t_gamevars *gamevars)
{
	gamevars->input->mouse_x = x;
	gamevars->input->mouse_y = y;
	if (button == MSE_LEFT)
		gamevars->input->mouse_pressed = 1;
	if (button == MSE_RIGHT)
		gamevars->input->rmouse_pressed = 1;
	return (0);
}

int	mouserel(int button, int x, int y, t_gamevars *gamevars)
{
	gamevars->input->mouse_x = x;
	gamevars->input->mouse_y = y;
	if (button == MSE_LEFT)
		gamevars->input->mouse_pressed = 0;
	if (button == MSE_RIGHT)
		gamevars->input->rmouse_pressed = 0;
	return (0);
}

int	mouserot(int x, int y, t_gamevars *gamevars)
{
	if (gamevars->input->rmouse_pressed == 0)
		return (0);
	if (gamevars->input->rmouse_pressed)
	{
		player_rotate(gamevars, 0.1 * (x - gamevars->input->mouse_x));
		gamevars->input->mouse_x = x;
		gamevars->input->mouse_y = y;
	}
	return (0);
}

int	mousetrack(t_gamevars *gv)
{
	int	x;
	int	y;
	int	x_diff;

	if (!gv->input->mouse_cam)
		return (0);
	mlx_mouse_get_pos(gv->mlx, gv->mlx_win, &x, &y);
	x_diff = x - gv->input->mouse_x;
	player_rotate(gv, gv->frametime * x_diff * .2);
	gv->input->mouse_x = x;
	gv->input->mouse_y = y;
	mlx_mouse_move(gv->mlx, gv->mlx_win, WWIDTH / 2, WHEIGHT / 2);
	return (0);
}
