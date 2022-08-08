/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:34:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/07 21:01:00 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_win(t_gamevars *gamevars)
{
	cleanup(gamevars);
	mlx_destroy_image(gamevars->mlx, gamevars->img->img);
	mlx_clear_window(gamevars->mlx, gamevars->mlx_win);
	mlx_destroy_window(gamevars->mlx, gamevars->mlx_win);
	mlx_destroy_display(gamevars->mlx);
	free(gamevars->mlx);
	exit(0);
}

void	cleanup(t_gamevars *gamevars)
{
	int	row;

	row = 0;
	while (row < gamevars->map.height)
		free(gamevars->map.map[row++]);
	free(gamevars->map.map);
	free(gamevars->doorcalls);
}
