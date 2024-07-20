/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:25:54 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/20 14:39:24 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_columns_num(t_level *level)
{
	t_ctr ctr;

	init_ctrs(&ctr);
	while (level->map[ctr.i])
	{
		ctr.j = 0;
		while (level->map[ctr.i][ctr.j])
		{
			ctr.j++;
		}
		if (ctr.j > level->num_of_columns)
			level->num_of_columns = ctr.j;
		ctr.i++;
	}
	printf("number of columns is : %d\n", level->num_of_columns);
}