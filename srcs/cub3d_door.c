/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:52:35 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 16:05:50 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_door(t_gamevars *gv, t_ray *ray, int map_x, int map_y)
{
	double	door_open;

	if (gv->map.map[map_y][map_x] != 2)
		return (0);
	door_open = door_ray_open(gv, ray, map_x, map_y);
	if (ray->side == 1 && door_open)
	{
		if (check_door_tile(gv, ray))
		{
			ray->side_dy += ray->delta_y / 2;
			ray->door = 1;
			return (draw_door(gv, map_x, map_y));
		}
	}
	else if (door_open)
	{
		if (check_door_tile(gv, ray))
		{
			ray->side_dx += ray->delta_x / 2;
			ray->door = 1;
			return (draw_door(gv, map_x, map_y));
		}
	}
	return (0);
}

int	draw_door(t_gamevars *gv, int map_x, int map_y)
{
	t_door	*door;

	door = *gv->doorcalls;
	if (*gv->doorcalls != NULL)
	{
		while (door)
		{
			if (door->pos.x == map_x && door->pos.y == map_y)
				door->visible = 1;
			if (door->pos.x == map_x && door->pos.y == map_y)
				return (1);
			door = door->next;
		}
	}
	door = (t_door *)malloc(sizeof(t_door));
	door->animate = 0;
	door->opening = 0;
	door->pos.x = map_x;
	door->pos.y = map_y;
	door->visible = 1;
	door->next = *gv->doorcalls;
	if (door->next)
		door->next->prev = door;
	door->prev = NULL;
	*gv->doorcalls = door;
	return (1);
}

void	run_door(t_gamevars *gv)
{
	t_door	*temp;
	t_door	*clean;
	int		count;

	count = 0;
	temp = *gv->doorcalls;
	while (temp)
	{
		if (!temp->animate && !temp->opening && !temp->visible)
		{
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				*gv->doorcalls = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			gv->map.map[temp->pos.y][temp->pos.x] = 2;
			clean = temp;
			temp = temp->next;
			free(clean);
			continue ;
		}
		temp->visible = 0;
		check_door_open(gv, temp, gv->player->pos_x, gv->player->pos_y);
		count++;
		temp = temp->next;
	}
}

void	check_door_open(t_gamevars *gv, t_door *door, double x, double y)
{
	int	playerhold;

	if (door->opening == 0)
	{
		printf("fabs_y: %f\n", fabs(door->pos.y - y));
		if (door->pos.x == (int)x && fabs(door->pos.y - y) - 0.5 <= 1)
			door->opening = 1;
		else if (door->pos.y == (int)y && fabs(door->pos.x - x) - 0.5 <= 1)
			door->opening = 1;
	}
	playerhold = (door->pos.x == (int)gv->player->pos_x && fabs(gv->player->pos_y - door->pos.y) - 0.5 < 1);
	playerhold = (playerhold || ((door->pos.y == (int)gv->player->pos_y) && fabs(gv->player->pos_x - door->pos.x) - 0.5 < 1));
	if (door->opening)
	{
		if (animate_door(door, playerhold))
			gv->map.map[door->pos.y][door->pos.x] = 0;
		else
			gv->map.map[door->pos.y][door->pos.x] = 2;
	}
}

// Animate door through frames; animate = 1 -> opening; animate = 2 -> closing
int	animate_door(t_door *door, int playerhold)
{
	double	tto;

	tto = 1.5;
	if (door->animate == 0)
	{
		door->time = gettime();
		door->opening = 1;
	}
	if (door->animate >= 1.0 && !playerhold)
	{
		door->opening = 2;
		door->time = gettime();
	}
	if (door->opening == 1)
		door->animate = (double)(gettime() - door->time) / 1000000.0 / tto;
	if (door->animate >= 1)
		door->animate = 1;
	if (door->animate >= 1 && door->opening == 1)
		return (1);
	else if (door->opening == 2)
		door->animate = 1 - (double)(gettime() - door->time) / 1000000.0 / tto;
	if (door->animate <= 0)
		door->animate = 0;
	if (door->animate <= 0)
		door->opening = 0;
	return (0);
}
