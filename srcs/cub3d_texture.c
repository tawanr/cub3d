/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:57:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/04 08:35:55 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_load(t_gamevars *gamevars)
{
	int			count;
	int			i;
	char	*path = "textures/wall_1.xpm";
	t_texture	*tex;

	count = 1;
	i = 0;
	// tex = (t_texture *)malloc(sizeof(t_texture));
	tex = &gamevars->textures[0];
	while (i < count)
	{
		tex->img = mlx_xpm_file_to_image(gamevars->mlx,
				path, &tex->width, &tex->height);
		// printf("loading texture width: %d height: %d\n", tex->width, tex->height);
		if (!tex->img)
			return (1);
		tex->img->addr = mlx_get_data_addr(tex->img,
				&tex->img->bpp, &tex->img->linelen, &tex->img->endian);
		printf("done loading texture\n");
		i++;
	}
	// for (int i = 0; i < tex->width * tex->height; i++)
	// 	printf("[%0#10x]", *(int *)(tex->img->addr + (i * 4)));
	// gamevars->textures[0] = tex;
	return (0);
}
