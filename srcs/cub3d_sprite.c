/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:14:55 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 16:20:48 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	new_sprite(t_gamevars *gv, char *path)
{
	size_t	len;
	int		count;

	len = ft_strlen(path);
	if (path[len - 3] == '[' && path[len - 1] == ']')
		gv->sprite.count = path[len - 2] - '0';
	count = gv->sprite.count;
	gv->sprite.frames = (t_texture **)malloc(count * sizeof(t_texture *));
	if (!gv->sprite.frames)
		return (-1);
	else
		return (0);
}

int	sprite_texture(t_gamevars *gv, int frame, char *path, int pos)
{
	unsigned int	time;
	t_texture		*tex;

	tex = (t_texture *)malloc(sizeof(t_texture));
	path[pos] = frame + '0';
	time = gettime();
	tex->img = mlx_xpm_file_to_image(gv->mlx, path, &tex->width, &tex->height);
	printf("cub3d: loaded sprite: %s - %d ms\n", path, difftime(time));
	if (!tex->img)
		return (-1);
	tex->img->addr = mlx_get_data_addr(tex->img, \
			&tex->img->bpp, &tex->img->linelen, &tex->img->endian);
	if (frame == gv->sprite.count - 1)
		free(path);
	gv->sprite.frames[frame] = tex;
	return (0);
}
