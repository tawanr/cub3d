/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:57:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 15:13:28 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_load(t_gamevars *gamevars)
{
	int				i;
	char			*path[5];
	t_texture		*tex;
	unsigned int	time;

	assign_textures(gamevars, path);
	i = 0;
	while (i < 5)
	{
		tex = &gamevars->textures[i];
		time = gettime();
		if (texture_file(gamevars, tex, path[i], i))
			return (-1);
		printf("cub3d: loaded texture: %s - %d ms\n", path[i++], difftime(time));
		tex->img->addr = mlx_get_data_addr(tex->img->img,
				&tex->img->bpp, &tex->img->linelen, &tex->img->endian);
	}
	if (sprite_load(gamevars))
		return (texture_err(gamevars, 5));
	gamevars->map.floor = rgb_to_int(gamevars->map_data->floor);
	gamevars->map.ceiling = rgb_to_int(gamevars->map_data->ceiling);
	return (0);
}

int	texture_file(t_gamevars *gv, t_texture *tex, char *path, int i)
{
	tex->img = (t_data *)malloc(sizeof(t_data));
	if (!tex->img)
		return (texture_err(gv, i));
	tex->img->img = mlx_xpm_file_to_image(gv->mlx,
			path, &tex->width, &tex->height);
	if (!tex->img->img)
	{
		free(tex->img);
		return (texture_err(gv, i));
	}
	return (0);
}

void	assign_textures(t_gamevars *gv, char **path)
{
	path[0] = gv->map_data->north;
	path[1] = gv->map_data->south;
	path[2] = gv->map_data->west;
	path[3] = gv->map_data->east;
	path[4] = gv->map_data->door;
}

int	sprite_load(t_gamevars *gv)
{
	size_t	len;
	char	*sprite;
	char	*newstr;
	int		i;
	int		frame;

	i = -1;
	frame = 0;
	if (!gv->map_data->sprite)
		return (-1);
	sprite = gv->map_data->sprite;
	len = ft_strlen(sprite);
	if (new_sprite(gv, sprite))
		return (-1);
	newstr = (char *)malloc((len - 1) * sizeof(char));
	ft_strlcpy(newstr, sprite, len - 1);
	while (sprite[len - 4 - ++i] != '.')
		newstr[len - 3 - i] = sprite[len - 4 - i];
	newstr[len - 3 - i] = sprite[len - 4 - i];
	while (frame < gv->sprite.count)
		if (sprite_texture(gv, frame++, newstr, len - 4 - i))
			return (sprite_err(gv, frame - 1, newstr));
	return (0);
}
