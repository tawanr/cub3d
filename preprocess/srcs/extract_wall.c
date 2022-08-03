/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:51:55 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 17:07:12 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

static void	error_add(t_cub *cub, char *array[], char *msg)
{
	free_strarray(array);
	map_error(cub, msg);
}

void	add_wall(t_cub *cub, char *array[], int id)
{
	if (id == NORTH)
	{
		if (cub->north != NULL)
			error_add(cub, array, "Duplicate type identifier");
		cub->north = ft_strdup(array[1]);
	}
	else if (id == SOUTH)
	{
		if (cub->south != NULL)
			error_add(cub, array, "Duplicate type identifier");
		cub->south = ft_strdup(array[1]);
	}
	else if (id == WEST)
	{
		if (cub->west != NULL)
			error_add(cub, array, "Duplicate type identifier");
		cub->west = ft_strdup(array[1]);
	}
	else if (id == EAST)
	{
		if (cub->east != NULL)
			error_add(cub, array, "Duplicate type identifier");
		cub->east = ft_strdup(array[1]);
	}
}

void	add_flcl(t_cub *cub, char *array[], t_rgb **flcl, char *rgb[])
{
	if (*flcl != NULL)
	{
		free_strarray(rgb);
		error_add(cub, array, "Duplicate type identifier");
	}
	if (strarray_len(rgb) != 3)
	{
		free_strarray(rgb);
		error_add(cub, array, "Invalid RGB");
	}
	*flcl = (t_rgb *)malloc(sizeof(t_rgb) * 1);
	(*flcl)->r = ft_atoi(rgb[0]);
	(*flcl)->g = ft_atoi(rgb[1]);
	(*flcl)->b = ft_atoi(rgb[2]);
	free_strarray(rgb);
}

void	add_cub_wall(t_cub *cub, char *array[])
{
	if (strarray_len(array) > 2)
		error_add(cub, array, "Excess information found");
	if (ft_strcmp("NO", array[0]) == 0)
		add_wall(cub, array, NORTH);
	else if (ft_strcmp("SO", array[0]) == 0)
		add_wall(cub, array, SOUTH);
	else if (ft_strcmp("EA", array[0]) == 0)
		add_wall(cub, array, EAST);
	else if (ft_strcmp("WE", array[0]) == 0)
		add_wall(cub, array, WEST);
	else if (ft_strcmp("F", array[0]) == 0)
		add_flcl(cub, array, &cub->floor, ft_split(array[1], ','));
	else if (ft_strcmp("C", array[0]) == 0)
		add_flcl(cub, array, &cub->ceiling, ft_split(array[1], ','));
	else
		error_add(cub, array, "Invalid type identifier");
}
