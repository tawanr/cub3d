/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:42:38 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 21:29:32 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

int	check_left(t_map *map, int i, int j);
int	check_low(t_map *map, int i, int j);
int	check_low_right(t_map *map, int i, int j);
int	check_low_left(t_map *map, int i, int j);

int	check_up(t_map *map, int i, int j)
{
	int	checking;

	if (i <= 0)
		return (0);
	checking = map->map[i - 1][j];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i - 1, j));
	if (checking >= N && checking <= E)
		return (check_close_map(map, i - 1, j));
	return (1);
}

int	check_up_right(t_map *map, int i, int j)
{
	int	checking;

	if (i <= 0 || j + 1 >= map->width)
		return (0);
	checking = map->map[i - 1][j + 1];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i - 1, j + 1));
	if (checking >= N && checking <= E)
		return (check_close_map(map, i - 1, j + 1));
	return (1);
}

int	check_up_left(t_map *map, int i, int j)
{
	int	checking;

	if (i <= 0 || j <= 0)
		return (0);
	checking = map->map[i - 1][j - 1];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i - 1, j - 1));
	if (checking >= N && checking <= E)
		return (check_close_map(map, i - 1, j - 1));
	return (1);
}

int	check_right(t_map *map, int i, int j)
{
	int	checking;

	if (j + 1 >= map->width)
		return (0);
	checking = map->map[i][j + 1];
	if (checking == SPACE)
		return (0);
	if (checking == EMPTY)
		return (check_close_map(map, i, j + 1));
	if (checking >= N && checking <= E)
		return (check_close_map(map, i, j + 1));
	return (1);
}

int	check_close_map(t_map *map, int i, int j)
{
	map->map[i][j] = CHECK;
	if (!check_up(map, i, j))
		return (0);
	if (!check_up_right(map, i, j))
		return (0);
	if (!check_up_left(map, i, j))
		return (0);
	if (!check_right(map, i, j))
		return (0);
	if (!check_left(map, i, j))
		return (0);
	if (!check_low(map, i, j))
		return (0);
	if (!check_low_right(map, i, j))
		return (0);
	if (!check_low_left(map, i, j))
		return (0);
	return (1);
}
