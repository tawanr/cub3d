/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:28:36 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/10 13:25:18 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keycode, t_gamevars *gv)
{
	if (keycode == KEY_D)
		gv->input->d_down = 1;
	else if (keycode == KEY_A)
		gv->input->a_down = 1;
	else if (keycode == KEY_S)
		gv->input->s_down = 1;
	else if (keycode == KEY_W)
		gv->input->w_down = 1;
	else if (keycode == KEY_Q)
		gv->input->q_down = 1;
	else if (keycode == KEY_E)
		gv->input->e_down = 1;
	else if (keycode == KEY_LEFT)
		gv->input->left_down = 1;
	else if (keycode == KEY_RGHT)
		gv->input->right_down = 1;
	else if (keycode == KEY_ESC)
		end_win(gv);
	keypress_cont(keycode, gv);
	return (0);
}

int	keypress_cont(int keycode, t_gamevars *gv)
{
	if (keycode == KEY_UP)
		gv->input->up_down = 1;
	else if (keycode == KEY_DOWN)
		gv->input->down_down = 1;
	else if (keycode == KEY_Q)
		gv->input->q_down = 1;
	else if (keycode == KEY_E)
		gv->input->e_down = 1;
	else if (keycode == KEY_B)
	{
		gv->debug.border = !gv->debug.border;
		gv->player->moved = 1;
	}
	else if (keycode == KEY_C)
		gv->input->mouse_cam = !gv->input->mouse_cam;
	return (0);
}

int	keyrelease(int keycode, t_gamevars *gv)
{
	if (keycode == KEY_D)
		gv->input->d_down = 0;
	else if (keycode == KEY_A)
		gv->input->a_down = 0;
	else if (keycode == KEY_S)
		gv->input->s_down = 0;
	else if (keycode == KEY_W)
		gv->input->w_down = 0;
	else if (keycode == KEY_Q)
		gv->input->q_down = 0;
	else if (keycode == KEY_E)
		gv->input->e_down = 0;
	else if (keycode == KEY_LEFT)
		gv->input->left_down = 0;
	else if (keycode == KEY_RGHT)
		gv->input->right_down = 0;
	else if (keycode == KEY_ESC)
		end_win(gv);
	keyrelease_cont(keycode, gv);
	return (0);
}

int	keyrelease_cont(int keycode, t_gamevars *gv)
{
	if (keycode == KEY_UP)
		gv->input->up_down = 0;
	else if (keycode == KEY_DOWN)
		gv->input->down_down = 0;
	else if (keycode == KEY_Q)
		gv->input->q_down = 0;
	else if (keycode == KEY_E)
		gv->input->e_down = 0;
	return (0);
}
