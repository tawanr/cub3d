/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:34:15 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 14:09:23 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "preprocess.h"

static void	usage(void)
{
	char	*msg;

	msg = "Usage: ./cub3d *.cub\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

static int	endswith(char *str, char *end)
{
	size_t	i;
	size_t	str_len;
	size_t	end_len;

	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len >= str_len)
	{
		return (0);
	}
	i = 0;
	while (i < end_len)
	{
		if (str[(str_len - end_len) + i] != end[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

t_cub	*preprocess_cub(int argc, char *argv[])
{
	int	fd;

	if (argc != 2 || !endswith(argv[1], ".cub"))
	{
		usage();
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	return (extract_cub(fd));
}
