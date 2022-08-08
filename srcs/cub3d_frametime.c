/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_frametime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:23:20 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 08:50:54 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	gettime(void)
{
	struct timeval	tv;
	int				time;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	time = tv.tv_sec % 1000 * 1000000;
	time += tv.tv_usec;
	return (time);
}

unsigned int	getfps(t_gamevars *gamevars)
{
	int		old_time;
	double	frametime;

	old_time = gamevars->time;
	gamevars->time = gettime();
	frametime = (double)(gamevars->time - old_time) / 1000000.0;
	gamevars->frametime = frametime;
	return ((int)(1.0 / frametime));
}

void	display_fps(t_gamevars *gamevars)
{
	int		fps;
	char	*str;

	fps = getfps(gamevars);
	str = ft_itoa(fps);
	mlx_string_put(gamevars->mlx, gamevars->mlx_win, WWIDTH - 20, 20, 0, str);
	// printf("FPS: %s\n", str);
	free(str);
}
