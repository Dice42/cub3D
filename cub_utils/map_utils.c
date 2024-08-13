/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:25:54 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/13 18:24:21 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_columns_num(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	while (level->map[ctr.i])
	{
		ctr.j = 0;
		while (level->map[ctr.i][ctr.j])
			ctr.j++;
		if (ctr.j > level->num_of_columns)
			level->num_of_columns = ctr.j;
		ctr.i++;
	}
}
