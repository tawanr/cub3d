/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:07:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 16:03:38 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_object(t_gamevars *gv, int map_x, int map_y)
{
	t_object	*temp;

	temp = *gv->objectque;
	while (temp)
	{
		if (temp->pos.x == map_x && temp->pos.y == map_y)
		{
			temp->visible = 1;
			return ;
		}
		temp = temp->next;
	}
	temp = new_object(gv, map_x, map_y);
	temp->next = *gv->objectque;
	if (temp->next)
		temp->next->prev = temp;
	*gv->objectque = temp;
}

t_object	*new_object(t_gamevars *gv, int map_x, int map_y)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	obj->pos.x = map_x;
	obj->pos.y = map_y;
	obj->textures = gv->sprite.frames;
	obj->frames = gv->sprite.count;
	obj->scale = 0.8;
	obj->ani_loop = 0.9;
	obj->visible = 1;
	obj->time = gettime();
	obj->next = NULL;
	obj->prev = NULL;
	return (obj);
}

void	run_objectque(t_gamevars *gv)
{
	t_object	*temp;
	t_object	*clean;

	temp = *gv->objectque;
	while (temp)
	{
		if (!temp->visible)
		{
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				*gv->objectque = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			clean = temp;
			temp = temp->next;
			free(clean);
			continue ;
		}
		temp->visible = 0;
		temp->animate = (int)((double)((gettime() - temp->time) % \
		(int)(temp->ani_loop * USEC)) / (temp->ani_loop * USEC) * temp->frames);
		draw_object(gv, temp);
		temp = temp->next;
	}
}

void	draw_object(t_gamevars *gv, t_object *obj)
{
	t_draw		s;
	int			col;

	init_object_draw(gv, obj, &s);
	s.height = abs((int)(WHEIGHT / s.ty));
	s.off = (int)((1 - obj->scale) * (double)s.height);
	s.height -= s.off;
	s.starty = -s.height / 2 + WHEIGHT / 2 + s.off;
	if (s.starty < 0)
		s.starty = 0;
	s.endy = s.height / 2 + WHEIGHT / 2 + s.off;
	if (s.endy >= WHEIGHT)
		s.endy = WHEIGHT - 1;
	s.width = abs((int)(WHEIGHT / s.ty)) - s.off;
	s.startx = -s.width / 2 + s.screenx + (s.off / 2);
	if (s.startx < 0)
		s.startx = 0;
	s.endx = s.width / 2 + s.screenx - (s.off / 2);
	if (s.endy >= WWIDTH)
		s.endy = WWIDTH - 1;
	col = s.startx;
	while (col++ < s.endx)
		draw_obj_col(gv, &s, obj, col);
}

void	draw_obj_col(t_gamevars *gv, t_draw *s, t_object *obj, int x)
{
	int	x_off;
	int	y_off;
	int	y;
	int	color;
	int	tex_pos;

	x_off = (int)(256 * (x - (-s->width / 2 + s->screenx + (s->off / 2))) * \
			obj->textures[obj->animate]->width / (s->width - s->off)) / 256 % \
			obj->textures[obj->animate]->width;
	y = s->starty;
	while (s->ty > 0 && x > 0 && x < WWIDTH && y < s->endy)
	{
		y_off = y * 256 - WHEIGHT * 128 + s->height * 128 - (s->off * 256);
		y_off = (y_off * obj->textures[obj->animate]->height);
		y_off /= s->height - s->off;
		y_off /= 256;
		tex_pos = y_off * obj->textures[obj->animate]->width * 4;
		tex_pos += x_off * 4;
		color = *(int *)(&obj->textures[obj->animate]->img->addr[tex_pos]);
		if (x >= 0 && x < WWIDTH && y >= 0 && y < WHEIGHT && (color & BLK) != 0)
			if (s->ty < gv->zd[x])
				pixel_put(gv->img, x, y, color);
		y++;
	}
}
