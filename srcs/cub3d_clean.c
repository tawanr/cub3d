/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:34:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 09:10:13 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_win(t_gamevars *gamevars)
{
	cleanup(gamevars);
	mlx_destroy_image(gamevars->mlx, gamevars->buffer[0]->img);
	mlx_destroy_image(gamevars->mlx, gamevars->buffer[1]->img);
	free(gamevars->buffer[0]);
	free(gamevars->buffer[1]);
	mlx_clear_window(gamevars->mlx, gamevars->mlx_win);
	mlx_destroy_window(gamevars->mlx, gamevars->mlx_win);
	mlx_destroy_display(gamevars->mlx);
	free(gamevars->mlx);
	exit(0);
}

void	clean_textures(t_gamevars *gv)
{
	int	count;
	int	i;

	count = 5;
	i = 0;
	while (i < count)
	{
		mlx_destroy_image(gv->mlx, gv->textures[i].img->img);
		free(gv->textures[i++].img);
	}
}

void	clean_sprite(t_gamevars *gv)
{
	int	count;
	int	i;

	i = 0;
	count = gv->sprite.count;
	while (i < count)
	{
		mlx_destroy_image(gv->mlx, gv->sprite.frames[i]->img->img);
		free(gv->sprite.frames[i]->img);
		free(gv->sprite.frames[i++]);
	}
	free(gv->sprite.frames);
}

void	cleanup(t_gamevars *gamevars)
{
	clean_textures(gamevars);
	clean_sprite(gamevars);
	free_cub(gamevars->map_data);
	clean_doorcalls(gamevars);
	clean_objque(gamevars);
}
