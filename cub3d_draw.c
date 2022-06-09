/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:42:10 by tratanat          #+#    #+#             */
/*   Updated: 2022/06/10 02:09:03 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_col(t_gamevars *gamevars, int x, double distance)
{
	int	vert_line;
	int	y;

	vert_line = (int)(WHEIGHT / distance / 3);
	y = WHEIGHT / 2 - vert_line;
	while (y < WHEIGHT / 2 + vert_line)
	{
		if (x > 0 && x < WWIDTH && y > 0 && y < WHEIGHT)
			pixel_put(gamevars->img, x, y, 0x000000FF);
		y++;
	}
}

void	draw_ceiling(t_gamevars *gamevars)
{
	int	x;
	int	y;

	y = 0;
	while (y < WHEIGHT / 2)
	{
		x = 0;
		while (x < WWIDTH)
			pixel_put(gamevars->img, x++, y, 0x00999999);
		y++;
	}
}

void	draw_floor(t_gamevars *gamevars)
{
	int	x;
	int	y;

	y = WHEIGHT / 2;
	while (y < WHEIGHT)
	{
		x = 0;
		while (x < WWIDTH)
			pixel_put(gamevars->img, x++, y, 0x00333333);
		y++;
	}
}
