/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error_macos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:11:35 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/11 11:21:46 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_err(t_gamevars *gv, int loaded)
{
	write(2, "cub3d: Cannot load texture\n", 27);
	clean_textures(gv, loaded);
	return (-1);
}

int	sprite_err(t_gamevars *gv, int frame, char *path)
{
	clean_sprite(gv, frame);
	free(path);
	return (-1);
}

int	cleanup_err(t_gamevars *gv)
{
	write(2, "cub3d: Error initializing\n", 26);
	free_cub(gv->map_data);
	mlx_clear_window(gv->mlx, gv->mlx_win);
	mlx_destroy_window(gv->mlx, gv->mlx_win);
	free(gv->mlx);
	return (-1);
}
