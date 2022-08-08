/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:53:00 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/07 20:53:13 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linelen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_map(t_gamevars *gamevars)
{
	t_minimap	*m;

	m = gamevars->minimap;
	draw_grid(gamevars, m->scale, m->pos_x, m->pos_y);
	draw_player(gamevars, m->scale, m->pos_x, m->pos_y);
}

void	draw_player(t_gamevars *gamevars, int scale, int off_h, int off_w)
{
	int			size;
	int			x;
	int			y;
	double		ray_x;
	double		ray_y;
	t_player	*player;

	size = 3;
	player = gamevars->player;
	x = (int)((MWIDTH / 2.0 * scale) + off_w - size);
	y = (int)((MHEIGHT / 2.0 * scale) + off_h - size);
	while (x <= (int)((MWIDTH / 2.0 * scale) + off_w + size))
	{
		while (y <= (int)((MHEIGHT / 2.0 * scale) + off_h + size))
			if (x < WWIDTH && y < WHEIGHT)
				pixel_put(gamevars->img, x, y++, 0x0000FF00);
		y = (int)((MHEIGHT / 2.0 * scale) + off_h - size);
		x++;
	}
	ray_x = (MWIDTH / 2.0f * scale) + off_w;
	ray_y = (MHEIGHT / 2.0f * scale) + off_h;
	while (ray_x > off_w && ray_x < off_w + (MWIDTH * scale) && ray_y > off_h && ray_y < off_h + (MHEIGHT * scale))
	{
		ray_x += player->dir_x;
		ray_y += player->dir_y;
		pixel_put(gamevars->img, (int)ray_x, (int)ray_y, 0x66AA0000);
	}
}

void	draw_grid(t_gamevars *gamevars, int scale, int off_h, int off_w)
{
	int	mx;
	int	my;
	int	dx;
	int	dy;
	int	**map;

	mx = 0;
	my = 0;
	map = gamevars->map.map;
	while (my <= MHEIGHT)
	{
		while (mx <= MWIDTH)
		{
			dx = off_w + (mx * scale);
			dy = off_h + (my * scale);
			if (mx < MWIDTH)
				while (dx < off_w + ((mx + 1) * scale) && dx < WWIDTH)
					pixel_put(gamevars->img, dx++, dy, 0x00FFFFFF);
			dx = off_w + (mx * scale);
			if (my < MHEIGHT)
			{
				while (dy < off_h + ((my + 1) * scale) && dy < WHEIGHT)
				{
					pixel_put(gamevars->img, dx, dy++, 0x00FFFFFF);
					if (mx < MWIDTH)
					{
						if ((int)(gamevars->player->pos_x - (int)(MWIDTH / 2) + mx) >= 0 && (int)(gamevars->player->pos_x - (int)(MWIDTH / 2) + mx) < gamevars->map.width &&\
							(int)(gamevars->player->pos_y - (int)(MHEIGHT / 2) + my) >= 0 && (int)(gamevars->player->pos_y - (int)(MHEIGHT / 2) + my) < gamevars->map.height &&\
							map[(int)(gamevars->player->pos_y - (int)(MHEIGHT / 2) + my)][(int)(gamevars->player->pos_x - (int)(MWIDTH / 2) + mx)] != 0)
						{
							while (dx < off_w + ((mx + 1) * scale) && dx < WWIDTH)
								pixel_put(gamevars->img, dx++, dy, 0x00444444);
						}
						else if (mx < MWIDTH && my < MHEIGHT)
							while (dx < off_w + ((mx + 1) * scale) && dx < WWIDTH)
								pixel_put(gamevars->img, dx++, dy, 0x00EEEEEE);
						dx = off_w + (mx * scale);
					}
				}
			}
			mx++;
		}
		mx = 0;
		my++;
	}
}