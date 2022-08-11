/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:46:20 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/11 11:07:30 by spoolpra         ###   ########.fr       */
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
	double	rate;

	rate = ((double)gamevars->player->rot_speed / 1000) / gamevars->frametime;
	if (gamevars->input->rmouse_pressed == 0)
		return (0);
	if (gamevars->input->rmouse_pressed)
	{
		player_rotate(gamevars, rate * (x - gamevars->input->mouse_x));
		gamevars->input->mouse_x = x;
		gamevars->input->mouse_y = y;
	}
	return (0);
}
