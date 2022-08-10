/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:40:13 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 12:36:13 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dbl_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linelen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(t_rgb *rgb)
{
	int	color;

	color = 0;
	color |= rgb->r << 16;
	color |= rgb->g << 8;
	color |= rgb->b;
	return (color);
}
