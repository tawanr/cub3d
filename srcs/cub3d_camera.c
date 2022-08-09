/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:03:41 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 13:35:12 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray(t_gamevars *gamevars)
{
	int			x;
	t_ray		ray;
	t_player	*p;

	p = gamevars->player;
	x = 0;
	while (x < WWIDTH)
	{
		ray.ray_x = p->dir_x + p->cam_x * (2 * x / (double)WWIDTH - 1);
		ray.ray_y = p->dir_y + p->cam_y * (2 * x / (double)WWIDTH - 1);
		ray.distance = wall_distance(gamevars, &ray);
		gamevars->zd[x] = ray.distance;
		if (ray.door == 1)
			ray.texture = &gamevars->textures[4];
		else if (ray.side == 0 && ray.step_x >= 0)
			ray.texture = &gamevars->textures[SOUTH];
		else if (ray.side == 0 && ray.step_x < 0)
			ray.texture = &gamevars->textures[NORTH];
		else if (ray.side == 1 && ray.step_y >= 0)
			ray.texture = &gamevars->textures[WEST];
		else
			ray.texture = &gamevars->textures[EAST];
		draw_wall_col(gamevars, x, &ray);
		x++;
	}
}

double	wall_distance(t_gamevars *gamevars, t_ray *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_dx = 0;
	ray->side_dy = 0;
	ray->side = 0;
	ray->door = 0;
	ray->count_x = 0;
	ray->count_y = 0;
	if (ray->ray_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->ray_x);
	if (ray->ray_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->ray_y);
	calc_sidedist(gamevars, ray);
	return (dda(gamevars, ray));
}

void	calc_sidedist(t_gamevars *gamevars, t_ray *ray)
{
	t_player	*p;

	p = gamevars->player;
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dx = (p->pos_x - (int)p->pos_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dx = ((int)p->pos_x + 1.0 - p->pos_x) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dy = (p->pos_y - (int)p->pos_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dy = ((int)p->pos_y + 1.0 - p->pos_y) * ray->delta_y;
	}
	ray->init_x = 1 - (gamevars->player->pos_x - (int)gamevars->player->pos_x);
	ray->init_y = 1 - (gamevars->player->pos_y - (int)gamevars->player->pos_y);
}

double	dda(t_gamevars *gamevars, t_ray *ray)
{
	int	map_x;
	int	map_y;

	map_x = (int)gamevars->player->pos_x;
	map_y = (int)gamevars->player->pos_y;
	while (gamevars->map.map[map_y][map_x] != 1)
	{
		if (ray_door(gamevars, ray, map_x, map_y))
			return (get_dis(gamevars, ray, map_x, map_y));
		if (gamevars->map.map[map_y][map_x] == 3)
			add_object(gamevars, map_x, map_y);
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_x;
			map_x += ray->step_x;
			ray->count_x++;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_y;
			map_y += ray->step_y;
			ray->count_y++;
			ray->side = 1;
		}
	}
	return (get_dis(gamevars, ray, map_x, map_y));
}

double	get_dis(t_gamevars *gamevars, t_ray *ray, int map_x, int map_y)
{
	double	distance;

	ray->tex_offset = 0;
	ray->map_x = map_x;
	ray->map_y = map_y;
	if (ray->side == 0)
	{
		distance = ray->side_dx - ray->delta_x;
		ray->tex_offset = gamevars->player->pos_y + distance * ray->ray_y;
	}
	else
	{
		distance = ray->side_dy - ray->delta_y;
		ray->tex_offset = gamevars->player->pos_x + distance * ray->ray_x;
	}
	if (ray->door == 1)
		ray->tex_offset += 1 - get_doorcall(gamevars, map_x, map_y)->animate;
	return (distance);
}
