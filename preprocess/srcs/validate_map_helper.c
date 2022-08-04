/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:14:55 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/04 21:52:37 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

int	check_left(t_map *map, int i, int j)
{
	int	checking;

	if (j <= 0)
		return (0);
	checking = map->map[i][j - 1];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i, j - 1));
	return (1);
}

int	check_low(t_map *map, int i, int j)
{
	int	checking;

	if (i + 1 >= map->height)
		return (0);
	checking = map->map[i + 1][j];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i + 1, j));
	return (1);
}

int	check_low_right(t_map *map, int i, int j)
{
	int	checking;

	if (i + 1 >= map->height || j + 1 >= map->width)
		return (0);
	checking = map->map[i + 1][j + 1];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i + 1, j + 1));
	return (1);
}

int	check_low_left(t_map *map, int i, int j)
{
	int	checking;

	if (i + 1 >= map->height || j <= 0)
		return (0);
	checking = map->map[i + 1][j - 1];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i + 1, j - 1));
	return (1);
}