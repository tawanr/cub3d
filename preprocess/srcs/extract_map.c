/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:50:04 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 22:14:38 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"
#include <stdio.h>

static void	error_map(char *line, t_cub *cub, char *msg, int *map_line)
{
	if (map_line)
		free(map_line);
	if (line)
		free(line);
	map_error(cub, msg);
}

static int	assign_val(char c, int *flag)
{
	if (c == 'N')
	{
		*flag = *flag | P_FLAG;
		return (N);
	}
	else if (c == 'S')
	{
		*flag = *flag | P_FLAG;
		return (S);
	}
	else if (c == 'W')
	{
		*flag = *flag | P_FLAG;
		return (W);
	}
	else if (c == 'E')
	{
		*flag = *flag | P_FLAG;
		return (E);
	}
	else if (c == '1')
		return (1);
	return (0);
}

int	*get_map_line(char *l, t_cub *cub, int *flag)
{
	int		i;
	int		width;
	int		*map_line;

	width = ft_strlen(l);
	map_line = (int *)malloc(sizeof(int) * (width + 1));
	i = -1;
	while (l[++i])
	{
		if (l[i] == 'N' || l[i] == 'S' || l[i] == 'W' || l[i] == 'E')
		{
			if (*flag & P_FLAG)
				error_map(l, cub, "Duplicate player", map_line);
			map_line[i] = assign_val(l[i], flag);
		}
		else if (l[i] == ' ')
			map_line[i] = SPACE;
		else if (l[i] == '0' || l[i] == '1')
			map_line[i] = assign_val(l[i], flag);
		else
			error_map(l, cub, "Invalid character in map", map_line);
	}
	map_line[i] = END;
	return (map_line);
}

void	add_map_line(int *map_line, t_cub *cub)
{
	int	i;
	int	new_size;
	int	**new_map;

	i = 0;
	new_size = intarray_len(cub->map->map) + 2;
	new_map = (int **)malloc(sizeof(int *) * new_size);
	dup_map(new_map, cub->map->map);
	while (new_map[i])
	{
		i++;
	}
	new_map[i] = map_line;
	cub->map->map = new_map;
}

void	add_map(char *line, t_cub *cub, int *i, int *flag)
{
	int		width;
	int		*map_line;
	char	*l_trim;

	if (line[0] == '\n')
	{
		*flag = *flag | SEP_FLAG;
		free(line);
		return ;
	}
	l_trim = ft_strtrim(line, "\n");
	free(line);
	width = ft_strlen(l_trim);
	if (width > cub->map->width)
		cub->map->width = width;
	if (*flag & SEP_FLAG)
		error_map(l_trim, cub, "Map seperate by newline", NULL);
	map_line = get_map_line(l_trim, cub, flag);
	free(l_trim);
	add_map_line(map_line, cub);
	*i = *i + 1;
}
