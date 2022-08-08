/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 16:22:24 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	display_fps(gamevars);
	run_door(gamevars);
	draw_ceiling(gamevars);
	draw_floor(gamevars);
	calc_ray(gamevars);
	draw_map(gamevars);
	mlx_put_image_to_window(gamevars->mlx, gamevars->mlx_win, img->img, 0, 0);
	mlx_destroy_image(gamevars->mlx, o_img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_gamevars	gamevars;
	t_data		img;
	t_player	player;
	t_minimap	minimap;
	t_input		input;

	gamevars.mlx = mlx_init();
	gamevars.mlx_win = mlx_new_window(gamevars.mlx, WWIDTH, WHEIGHT, "cub3d");
	img.img = mlx_new_image(gamevars.mlx, WWIDTH, WHEIGHT);
	gamevars.img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);
	init_player(&player);
	init_minimap(&minimap);
	gamevars.player = &player;
	gamevars.map_data = preprocess_cub(argc, argv);
	printf("north: %s\n", gamevars.map_data->north);
	texture_load(&gamevars);
	gamevars.minimap = &minimap;
	gamevars.input = &input;
	init_gamevars(&gamevars);
	inithooks(gamevars.mlx_win, &gamevars);
	mlx_loop(gamevars.mlx);
}
