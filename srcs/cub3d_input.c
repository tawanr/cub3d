/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:46:20 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 22:10:44 by tratanat         ###   ########.fr       */
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

int	keymod(int keycode, t_gamevars *gamevars)
{
	if (keycode == KEY_D || keycode == KEY_RGHT)
		player_move_ad(gamevars, -1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		player_move_ad(gamevars, 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		player_move_ws(gamevars, -1);
	else if (keycode == KEY_W || keycode == KEY_UP)
		player_move_ws(gamevars, 1);
	else if (keycode == KEY_Q)
		player_rotate(gamevars, -1);
	else if (keycode == KEY_E)
		player_rotate(gamevars, 1);
	else if (keycode == KEY_ESC)
		end_win(gamevars);
	return (0);
}
