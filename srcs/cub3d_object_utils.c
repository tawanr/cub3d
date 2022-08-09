/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:01:14 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 16:04:08 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_object_draw(t_gamevars *gv, t_object *obj, t_draw *s)
{
	t_player	*p;

	p = gv->player;
	obj->sx = (obj->pos.x + 0.5) - p->pos_x;
	obj->sy = (obj->pos.y + 0.5) - p->pos_y;
	s->tx = 1.0 / (p->cam_x * p->dir_y - p->dir_x * p->cam_y);
	s->ty = s->tx * (-p->cam_y * obj->sx + p->cam_x * obj->sy);
	s->tx *= (p->dir_y * obj->sx - p->dir_x * obj->sy);
	s->screenx = (int)((WWIDTH / 2) * (1 + s->tx / s->ty));
}
