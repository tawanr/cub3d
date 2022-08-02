/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:26:16 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 17:21:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

int	map_start(t_cub *cub)
{
	if (!cub->north)
		return (0);
	if (!cub->south)
		return (0);
	if (!cub->west)
		return (0);
	if (!cub->east)
		return (0);
	if (!cub->floor)
		return (0);
	if (!cub->ceiling)
		return (0);
	return (1);
}

int	complete_check(t_cub *cub)
{
	if (!map_start(cub))
		return (0);
	if (!cub->map || !cub->map->map)
		return (0);
	return (1);
}
