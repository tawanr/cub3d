/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:57:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 14:04:10 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_load(t_gamevars *gamevars)
{
	int				i;
	char			*path[5];
	t_texture		*tex;
	unsigned int	time;

	i = 0;
	path[0] = gamevars->map_data->north;
	path[1] = gamevars->map_data->south;
	path[2] = gamevars->map_data->west;
	path[3] = gamevars->map_data->east;
	path[4] = gamevars->map_data->door;
	while (i < 5)
	{
		tex = &gamevars->textures[i];
		time = gettime();
		tex->img = mlx_xpm_file_to_image(gamevars->mlx,
				path[i], &tex->width, &tex->height);
		printf("cub3d: loaded texture: %s - %d ms\n", path[i], difftime(time));
		if (!tex->img)
			return (1);
		tex->img->addr = mlx_get_data_addr(tex->img,
				&tex->img->bpp, &tex->img->linelen, &tex->img->endian);
		i++;
	}
	sprite_load(gamevars);
	return (0);
}

int	sprite_load(t_gamevars *gv)
{
	size_t	len;
	char	*sprite;
	char	*newstr;
	int		i;
	int		frame;

	i = 0;
	frame = 0;
	if (!gv->map_data->sprite)
		return (-1);
	sprite = gv->map_data->sprite;
	len = ft_strlen(sprite);
	if (new_sprite(gv, sprite))
		return (-1);
	newstr = (char *)malloc((len - 1) * sizeof(char));
	ft_strlcpy(newstr, sprite, len - 1);
	while (sprite[len - 4 - i] != '.')
	{
		newstr[len - 3 - i] = sprite[len - 4 - i];
		i++;
	}
	newstr[len - 3 - i] = sprite[len - 4 - i];
	while (frame < gv->sprite.count)
		sprite_texture(gv, frame++, newstr, len - 4 - i);
	return (0);
}
