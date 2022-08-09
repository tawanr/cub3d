/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_camera_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:18:36 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 16:40:02 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_stepy(t_ray *ray, int *map_y)
{
	ray->side_dy += ray->delta_y;
	*map_y += ray->step_y;
	ray->count_y++;
	ray->side = 1;
}
