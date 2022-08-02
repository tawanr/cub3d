/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:44:28 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/02 13:37:03 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c);

static int	append_array(char **array, int i, char **start, int n)
{
	int		j;
	char	*str;

	j = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
	{
		while (j < n)
		{
			free(array[j++]);
		}
		free(array);
		return (0);
	}
	(void)ft_strlcpy(str, *start, n + 1);
	array[i] = str;
	*start = *start + n;
	return (1);
}

static int	cnt_size(char *str)
{
	int		cnt;
	char	*start;
	char	*end;

	cnt = 0;
	start = str;
	end = str;
	while (*str)
	{
		if (is_space(*str))
			end = str;
		if (end - start > 1 || (end - start > 0 && !is_space(*start)))
			cnt = cnt + 1;
		start = end;
		str++;
	}
	end = str;
	if (end - start > 1)
		cnt = cnt + 1;
	return (cnt + 1);
}

static int	cond_check(char **array, int *i, char **start, int n)
{
	char	*str;

	if (n > 1)
	{
		str = *start + 1;
		if (!append_array(array, *i, &str, n - 1))
			return (-1);
		*i = *i + 1;
		*start = *start + n;
		return (1);
	}
	*start = *start + n;
	return (0);
}

static int	cutting_string(const char *s, char **array, char *start)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (is_space(*s++))
		{
			if (((s - 1) - start > 0 && !is_space(*start)))
			{
				if (!append_array(array, i++, &start, (s - 1) - start))
					return (0);
			}
			if (cond_check(array, &i, &start, (s - 1) - start) < 0)
				return (0);
		}
	}
	if (((s - 1) - start > 0 && !is_space(*start)))
	{
		if (!append_array(array, i++, &start, s - start))
			return (0);
	}
	else if (cond_check(array, &i, &start, s - start) < 0)
		return (0);
	array[i] = 0;
	return (1);
}

char	**split_space(char *s)
{
	char	*start;
	char	**array;

	if (!s)
		return (NULL);
	start = (char *)s;
	array = (char **)malloc(sizeof(char *) * cnt_size(s));
	if (!array)
		return (NULL);
	if (!cutting_string(s, array, start))
		return (NULL);
	return (array);
}
