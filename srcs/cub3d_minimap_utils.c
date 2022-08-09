/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 09:08:17 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 09:10:25 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tile_color(int type)
{
	if (type == 1)
		return (0x00444444);
	else if (type == 2)
		return (0x000000DD);
	else if (type == 3)
		return (0x00DD0000);
	return (0x00EEEEEE);
}
