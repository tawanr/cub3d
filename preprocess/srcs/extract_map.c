/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:50:04 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/09 08:51:22 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

static void	error_map(char *line, t_cub *cub, char *msg, int *map_line)
{
	if (map_line != NULL)
		free(map_line);
	if (line)
		free(line);
	map_error(cub, msg);
}

static int	assign_val(char c)
{
	if (c == '1')
		return (WALL);
	else if (c == '2')
		return (DOOR);
	else if (c == ' ')
		return (SPACE);
	else if (c == '3')
		return (OBJ);
	return (EMPTY);
}

int	*get_map_line(char *l, t_cub *cub, int *flag)
{
	int		i;
	int		*map_line;

	map_line = (int *)malloc(sizeof(int) * (ft_strlen(l) + 1));
	i = -1;
	while (l[++i])
	{
		if (l[i] == 'N' || l[i] == 'S' || l[i] == 'W' || l[i] == 'E')
		{
			if (*flag & P_FLAG)
				error_map(l, cub, "Duplicate player", map_line);
			*flag = *flag | P_FLAG;
			assign_player(cub, i, cub->map->height, l[i]);
			map_line[i] = EMPTY;
		}
		else if (l[i] == '0' || l[i] == '1' || l[i] == '2' || l[i] == ' ' || \
				l[i] == '3')
			map_line[i] = assign_val(l[i]);
		else if (l[i] == '!')
			map_line[i] = OBJ;
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
	if (!new_map)
		return ;
	dup_map(new_map, cub->map->map);
	while (new_map[i])
	{
		i++;
	}
	new_map[i] = map_line;
	cub->map->map = new_map;
}

void	add_map(char *line, t_cub *cub, int *flag)
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
	cub->map->height += 1;
}
