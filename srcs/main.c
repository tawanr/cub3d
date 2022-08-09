/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:22:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 17:13:43 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	drawframe(t_gamevars *gamevars)
{
	t_data	*img;

	gamevars->img = gamevars->buffer[gamevars->framecount];
	img = gamevars->img;
	run_door(gamevars);
	draw_ceiling(gamevars);
	draw_floor(gamevars);
	calc_ray(gamevars);
	run_objectque(gamevars);
	draw_map(gamevars);
	mlx_put_image_to_window(gamevars->mlx, gamevars->mlx_win, img->img, 0, 0);
	display_fps(gamevars);
	gamevars->framecount++;
	gamevars->framecount %= 2;
	return (0);
}

int	main(int argc, char **argv)
{
	t_gamevars	gamevars;
	t_player	player;
	t_minimap	minimap;
	t_input		input;

	gamevars.mlx = mlx_init();
	gamevars.mlx_win = mlx_new_window(gamevars.mlx, WWIDTH, WHEIGHT, "cub3d");
	init_minimap(&minimap);
	gamevars.map_data = preprocess_cub(argc, argv);
	init_player(&gamevars, &player);
	gamevars.player = &player;
	if (texture_load(&gamevars))
		texture_err();
	gamevars.minimap = &minimap;
	gamevars.input = &input;
	init_gamevars(&gamevars);
	printf("Initiliazing...\n");
	inithooks(gamevars.mlx_win, &gamevars);
	mlx_loop(gamevars.mlx);
}
