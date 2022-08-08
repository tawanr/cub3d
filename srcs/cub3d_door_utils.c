/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_door_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 09:27:20 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 15:59:41 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	door_ray_open(t_gamevars *gv, t_ray *ray, int map_x, int map_y)
{
	double	offset_x;
	double	offset_y;
	t_door	*door;

	offset_y = gv->player->pos_y + (ray->side_dx - (ray->delta_x / 2)) * ray->ray_y;
	offset_x = gv->player->pos_x + (ray->side_dy - (ray->delta_y / 2)) * ray->ray_x;
	door = get_doorcall(gv, map_x, map_y);
	if (!door)
		return (1);
	if (ray->side == 1)
	{
		if (offset_x - (int)(offset_x) >= door->animate)
			return (1 - door->animate);
	}
	else
		if (offset_y - (int)(offset_y) >= door->animate)
			return (1 - door->animate);
	return (0);
}

t_door	*get_doorcall(t_gamevars *gv, int map_x, int map_y)
{
	t_door	*temp;

	temp = *gv->doorcalls;
	while (temp)
	{
		if (temp->pos.x == map_x && temp->pos.y == map_y)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	check_door_tile(t_gamevars *gv, t_ray *ray)
{
	double	off;

	if (ray->side == 1)
	{
		off = gv->player->pos_y + ray->side_dx * ray->ray_y;
		if (ray->side_dy < ray->side_dx)
			return (1);
		else if (ray->step_y >= 0 && off - (int)off >= 0.5)
			return (1);
		else if (ray->step_y < 0 && off - (int)off < 0.5)
			return (1);
	}
	else
	{
		off = gv->player->pos_x + ray->side_dy * ray->ray_x;
		if (ray->side_dx < ray->side_dy)
			return (1);
		else if (ray->step_x >= 0 && off - (int)off >= 0.5)
			return (1);
		else if (ray->step_x < 0 && off - (int)off < 0.5)
			return (1);
	}
	return (0);
}
