/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:18:16 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 20:59:09 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_col(t_gamevars *gamevars, int x, t_ray *ray)
{
	int		vert_line;
	double	y;
	double	x_off;
	int		color;
	double	tex_pos;

	vert_line = (int)(WHEIGHT / ray->distance / 3);
	y = WHEIGHT / 2 - vert_line;
	x_off = ray->tex_offset - (int)ray->tex_offset;
	while (y < WHEIGHT / 2 + vert_line)
	{
		tex_pos = (double)((y - (WHEIGHT / 2 - vert_line)) / (vert_line * 2));
		if (x_off < 0.005 || x_off > 0.995 || tex_pos < 0.01 || tex_pos > 0.99)
			color = 0;
		else
		{
			tex_pos = ray->texture->width * 4;
			tex_pos *= (int)(tex_pos * ray->texture->height);
			tex_pos += (int)((x_off * (ray->texture->width)) * 4);
			color = *(int *)(&ray->texture->img->addr[(int)tex_pos]);
		}
		if (x > 0 && x < WWIDTH && y > 0 && y < WHEIGHT)
			pixel_put(gamevars->img, x, y, color);
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
