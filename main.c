/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/06/10 02:13:44 by tratanat         ###   ########.fr       */
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
	x = (player->pos_x * scale) + off_w - size;
	y = (player->pos_y * scale) + off_h - size;
	while (x <= (player->pos_x * scale) + off_w + size)
	{
		while (y <= (player->pos_y * scale) + off_h + size)
			if (x < WWIDTH && y < WHEIGHT)
				pixel_put(gamevars->img, x, y++, 0x0000FF00);
		y = (player->pos_y * scale) + off_h - size;
		x++;
	}
	ray_x = (player->pos_x * scale) + off_w;
	ray_y = (player->pos_y * scale) + off_h;
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
	while (my <= 5)
	{
		while (mx <= 6)
		{
			dx = off_w + (mx * scale);
			dy = off_h + (my * scale);
			if (mx < 6)
				while (dx < off_w + ((mx + 1) * scale) && dx < WWIDTH)
					pixel_put(gamevars->img, dx++, dy, 0x00FFFFFF);
			dx = off_w + (mx * scale);
			if (my < 5)
			{
				while (dy < off_h + ((my + 1) * scale) && dy < WHEIGHT)
				{
					pixel_put(gamevars->img, dx, dy++, 0x00FFFFFF);
					if (mx < MWIDTH && my < MHEIGHT && map[my][mx] == 1)
						while (dx < off_w + ((mx + 1) * scale) && dx < WWIDTH)
							pixel_put(gamevars->img, dx++, dy, 0x00444444);
					else if (mx < MWIDTH && my < MHEIGHT)
						while (dx < off_w + ((mx + 1) * scale) && dx < WWIDTH)
							pixel_put(gamevars->img, dx++, dy, 0x00EEEEEE);
					dx = off_w + (mx * scale);
				}
			}
			mx++;
		}
		mx = 0;
		my++;
	}
}

int	drawframe(t_gamevars *gamevars)
{
	t_data	*img;
	void	*o_img;
	char	*addr;

	o_img = gamevars->img->img;
	img = gamevars->img;
	img->img = mlx_new_image(gamevars->mlx, WWIDTH, WHEIGHT);
	addr = mlx_get_data_addr(img->img, &img->bpp, &img->linelen, &img->endian);
	img->addr = addr;
	draw_ceiling(gamevars);
	draw_floor(gamevars);
	calc_ray(gamevars);
	draw_map(gamevars);
	mlx_put_image_to_window(gamevars->mlx, gamevars->mlx_win, img->img, 0, 0);
	mlx_destroy_image(gamevars->mlx, o_img);
	return (0);
}

int	main(void)
{
	t_gamevars	gamevars;
	t_data		img;
	t_player	player;
	t_minimap	minimap;
	t_input		input;

	gamevars.mlx = mlx_init();
	gamevars.mlx_win = mlx_new_window(gamevars.mlx, 800, 600, "cub3d");
	img.img = mlx_new_image(gamevars.mlx, WWIDTH, WHEIGHT);
	gamevars.img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);
	init_player(&player);
	init_minimap(&minimap);
	gamevars.player = &player;
	gamevars.map.map = init_map();
	gamevars.minimap = &minimap;
	input.rmouse_pressed = 0;
	gamevars.input = &input;
	inithooks(gamevars.mlx_win, &gamevars);
	// draw_map(&gamevars);
	// mlx_put_image_to_window(gamevars.mlx, gamevars.mlx_win, img.img, 0, 0);
	mlx_loop(gamevars.mlx);
}
