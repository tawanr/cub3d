/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:03:41 by tratanat          #+#    #+#             */
/*   Updated: 2022/06/10 02:39:02 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray(t_gamevars *gamevars)
{
	int			x;
	double		cam;
	double		ray_x;
	double		ray_y;
	t_player	*p;

	p = gamevars->player;
	x = 0;
	while (x < WWIDTH)
	{
		cam = 2 * x / (double)WWIDTH - 1;
		ray_x = p->dir_x + p->cam_x * cam;
		ray_y = p->dir_y + p->cam_y * cam;
		draw_wall_col(gamevars, x, wall_distance(gamevars, ray_x, ray_y));
		x++;
	}
}

double	wall_distance(t_gamevars *gamevars, double ray_x, double ray_y)
{
	t_ray	ray;

	ray.stepX = 0;
	ray.stepY = 0;
	ray.sideDistX = 0;
	ray.sideDistY = 0;
	if (ray_x == 0)
		ray.deltaDistX = 1e30;
	else
		ray.deltaDistX = fabs(1.0 / ray_x);
	if (ray_y == 0)
		ray.deltaDistY = 1e30;
	else
		ray.deltaDistY = fabs(1.0 / ray_y);
	calc_sidedist(gamevars, &ray, ray_x, ray_y);
	return (dda(gamevars, &ray));
}

void	calc_sidedist(t_gamevars *gamevars, t_ray *ray, double ray_x, double ray_y)
{
	t_player	*p;

	p = gamevars->player;
	if (ray_x < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (p->pos_x - (int)p->pos_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = ((int)p->pos_x + 1.0 - p->pos_x) * ray->deltaDistX;
	}
	if (ray_y < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (p->pos_y - (int)p->pos_y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = ((int)p->pos_y + 1.0 - p->pos_y) * ray->deltaDistY;
	}
}

double	dda(t_gamevars *gamevars, t_ray *ray)
{
	int	side;
	int	map_x;
	int	map_y;

	side = 0;
	map_x = (int)gamevars->player->pos_x;
	map_y = (int)gamevars->player->pos_y;
	while (gamevars->map.map[map_y][map_x] == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			map_x += ray->stepX;
			side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			map_y += ray->stepY;
			side = 1;
		}
	}
	return (get_distance(ray, side));
}

double	get_distance(t_ray *ray, int side)
{
	if (side == 0)
		return (ray->sideDistX - ray->deltaDistX);
	else
		return (ray->sideDistY - ray->deltaDistY);
}
