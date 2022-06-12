/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:34:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/06/11 14:37:35 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_win(t_gamevars *gamevars)
{
	int	y;

	y = 0;
	while (y < MHEIGHT)
		free(gamevars->map.map[y++]);
	free(gamevars->map.map);
	mlx_destroy_image(gamevars->mlx, gamevars->img->img);
	mlx_clear_window(gamevars->mlx, gamevars->mlx_win);
	mlx_destroy_window(gamevars->mlx, gamevars->mlx_win);
	// mlx_destroy_display(gamevars->mlx);
	free(gamevars->mlx);
	exit(0);
}
