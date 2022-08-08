/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:57:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 16:23:53 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_load(t_gamevars *gamevars)
{
	int			i;
	char		*path[5];
	t_texture	*tex;

	i = 0;
	printf("loading north: %s\n", gamevars->map_data->north);
	path[0] = gamevars->map_data->north;
	path[1] = gamevars->map_data->south;
	path[2] = gamevars->map_data->west;
	path[3] = gamevars->map_data->east;
	path[4] = "./textures/door.xpm";
	while (i < 5)
	{
		tex = &gamevars->textures[i];
		printf("cub3d: loading texture: %s\n", path[i]);
		tex->img = mlx_xpm_file_to_image(gamevars->mlx,
				path[i], &tex->width, &tex->height);
		if (!tex->img)
			return (1);
		tex->img->addr = mlx_get_data_addr(tex->img,
				&tex->img->bpp, &tex->img->linelen, &tex->img->endian);
		i++;
	}
	return (0);
}
