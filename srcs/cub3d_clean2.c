/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_clean2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:46:14 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/09 16:54:56 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_doorcalls(t_gamevars *gv)
{
	t_door	*temp;
	t_door	*clean;

	temp = *gv->doorcalls;
	while (temp)
	{
		clean = temp;
		temp = temp->next;
		free(clean);
	}
	free(gv->doorcalls);
}

void	clean_objque(t_gamevars *gv)
{
	t_object	*temp;
	t_object	*clean;

	temp = *gv->objectque;
	while (temp)
	{
		clean = temp;
		temp = temp->next;
		free(clean);
	}
	free(gv->objectque);
}
