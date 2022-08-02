/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:41:09 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 17:18:44 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

static void	cub_init(t_cub *cub)
{
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
	cub->floor = NULL;
	cub->ceiling = NULL;
	cub->map = NULL;
}

static void	read_map(char *line, int fd, t_cub *cub)
{
	int	i;
	int	flag;

	flag = 0;
	if (!line)
		map_error(cub, "Missing map");
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	cub->map = (t_map *)malloc(sizeof(t_map) * 1);
	cub->map->map = NULL;
	cub->map->height = 0;
	cub->map->width = 0;
	i = 0;
	while (line)
	{
		add_map(line, cub, &i, &flag);
		line = get_next_line(fd);
	}
	cub->map->height = i;
}

static int	read_cub(int fd, t_cub *cub)
{
	char	*line;
	char	**array;

	line = get_next_line(fd);
	while (line && !map_start(cub))
	{
		array = split_space(line);
		free(line);
		if (array[0] != NULL)
			add_cub_wall(cub, array);
		free_strarray(array);
		line = get_next_line(fd);
	}
	read_map(line, fd, cub);
	if (complete_check(cub) == 0)
		return (0);
	return (1);
}

t_cub	*extract_cub(int fd)
{
	int		status;
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub) * 1);
	if (!cub)
	{
		perror("");
		close(fd);
		exit(EXIT_FAILURE);
	}
	cub_init(cub);
	status = read_cub(fd, cub);
	close(fd);
	if (status == 0)
	{
		free_cub(cub);
		exit(EXIT_FAILURE);
	}
	return (cub);
}