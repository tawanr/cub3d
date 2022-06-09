/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:46:20 by tratanat          #+#    #+#             */
/*   Updated: 2022/06/10 02:26:50 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mousectl(int button, int x, int y, t_gamevars *gamevars)
{
	gamevars->input->mouse_x = x;
	gamevars->input->mouse_y = y;
	if (button == 1)
		gamevars->input->mouse_pressed = 1;
	if (button == 3)
		gamevars->input->rmouse_pressed = 1;
	return (0);
}

int	mouserel(int button, int x, int y, t_gamevars *gamevars)
{
	gamevars->input->mouse_x = x;
	gamevars->input->mouse_y = y;
	if (button == 1)
		gamevars->input->mouse_pressed = 0;
	if (button == 3)
	{
		gamevars->input->rmouse_pressed = 0;
		mlx_mouse_show(gamevars->mlx, gamevars->mlx_win);
	}
	return (0);
}

int	mouserot(int x, int y, t_gamevars *gamevars)
{
	if (gamevars->input->rmouse_pressed == 0)
		return (0);
	if (gamevars->input->rmouse_pressed)
	{
		player_rotate(gamevars, 0.1 * (x - gamevars->input->mouse_x));
		mlx_mouse_hide(gamevars->mlx, gamevars->mlx_win);
		mlx_mouse_move(gamevars->mlx, gamevars->mlx_win, WWIDTH / 2, WHEIGHT / 2);
		gamevars->input->mouse_x = x;
		gamevars->input->mouse_y = y;
	}
	return (0);
}

int	keymod(int keycode, t_gamevars *gamevars)
{
	if (keycode == 100 || keycode == 65363)
		player_move_ad(gamevars, -1);
	else if (keycode == 97 || keycode == 65361)
		player_move_ad(gamevars, 1);
	else if (keycode == 115 || keycode == 65364)
		player_move_ws(gamevars, -1);
	else if (keycode == 119 || keycode == 65362)
		player_move_ws(gamevars, 1);
	else if (keycode == 113)
		player_rotate(gamevars, -1);
	else if (keycode == 101)
		player_rotate(gamevars, 1);
	return (0);
}
