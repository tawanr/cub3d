/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:53:00 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 09:10:59 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_gamevars *gamevars)
{
	t_minimap	*m;

	m = gamevars->minimap;
	draw_grid(gamevars, m);
	draw_player(gamevars, m->scale, m->pos_x, m->pos_y);
}

void	draw_player(t_gamevars *gamevars, int scale, int off_h, int off_w)
{
	t_pos		pos;
	double		ray_x;
	double		ray_y;
	t_player	*player;

	player = gamevars->player;
	pos.x = (int)((MWIDTH / 2.0 * scale) + off_w - MMPLSIZE);
	pos.y = (int)((MHEIGHT / 2.0 * scale) + off_h - MMPLSIZE);
	while (pos.x <= (int)((MWIDTH / 2.0 * scale) + off_w + MMPLSIZE))
	{
		while (pos.y <= (int)((MHEIGHT / 2.0 * scale) + off_h + MMPLSIZE))
			if (pos.x < WWIDTH && pos.y < WHEIGHT)
				pixel_put(gamevars->img, pos.x, pos.y++, 0x0000FF00);
		pos.y = (int)((MHEIGHT / 2.0 * scale) + off_h - MMPLSIZE);
		pos.x++;
	}
	ray_x = (MWIDTH / 2.0f * scale) + off_w;
	ray_y = (MHEIGHT / 2.0f * scale) + off_h;
	while (ray_x > off_w && ray_x < off_w + (MWIDTH * scale) && \
			ray_y > off_h && ray_y < off_h + (MHEIGHT * scale))
	{
		ray_x += player->dir_x;
		ray_y += player->dir_y;
		pixel_put(gamevars->img, (int)ray_x, (int)ray_y, 0x66AA0000);
	}
}

void	draw_grid(t_gamevars *gamevars, t_minimap *mini)
{
	t_pos	m;
	t_pos	d;

	m.x = 0;
	m.y = 0;
	while (m.y <= MHEIGHT)
	{
		while (m.x <= MWIDTH)
		{
			d.x = mini->pos_x + (m.x * mini->scale);
			d.y = mini->pos_y + (m.y * mini->scale);
			if (m.x < MWIDTH)
				while (d.x < mini->pos_x + ((m.x + 1) * mini->scale))
					pixel_put(gamevars->img, d.x++, d.y, 0x00FFFFFF);
			d.x = mini->pos_x + (m.x * mini->scale);
			if (m.y < MHEIGHT)
				mini_fill(gamevars, &m, &d, mini);
			m.x++;
		}
		m.x = 0;
		m.y++;
	}
}

void	mini_fill(t_gamevars *gv, t_pos *m, t_pos *d, t_minimap *mini)
{
	while (d->y < mini->pos_x + ((m->y + 1) * mini->scale))
	{
		pixel_put(gv->img, d->x, d->y++, 0x00FFFFFF);
		if (m->x < MWIDTH)
			mini_shift(gv, m, d, mini);
	}
}

void	mini_shift(t_gamevars *gv, t_pos *m, t_pos *d, t_minimap *mini)
{
	t_pos	p;
	t_pos	mm;
	int		color;

	p.x = gv->player->pos_x;
	p.y = gv->player->pos_y;
	mm.x = (int)(p.x - (int)(MWIDTH / 2) + m->x);
	mm.y = (int)(p.y - (int)(MHEIGHT / 2) + m->y);
	if ((int)(p.x - (int)(MWIDTH / 2) + m->x) >= 0 && \
		(int)(p.x - (int)(MWIDTH / 2) + m->x) < gv->map.width && \
		(int)(p.y - (int)(MHEIGHT / 2) + m->y) >= 0 && \
		(int)(p.y - (int)(MHEIGHT / 2) + m->y) < gv->map.height && \
		gv->map.map[mm.y][mm.x] != 0)
	{
		while (d->x < mini->pos_x + ((m->x + 1) * mini->scale) && d->x < WWIDTH)
		{
			color = tile_color(gv->map.map[mm.y][mm.x]);
			pixel_put(gv->img, d->x++, d->y, color);
		}
	}
	else if (m->x < MWIDTH && m->y < MHEIGHT)
		while (d->x < mini->pos_x + ((m->x + 1) * mini->scale) && d->x < WWIDTH)
			pixel_put(gv->img, d->x++, d->y, 0x00EEEEEE);
	d->x = mini->pos_x + (m->x * mini->scale);
}
