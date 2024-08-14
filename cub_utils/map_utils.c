/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:25:54 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/14 09:37:07 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_columns_num(t_level *level)
{
	t_ctr ctr;

	init_ctrs(&ctr);
	while (level->init_map[ctr.i])
	{
		ctr.j = 0;
		while (level->init_map[ctr.i][ctr.j])
			ctr.j++;
		if (ctr.j > level->num_of_columns)
			level->num_of_columns = ctr.j;
		ctr.i++;
	}
}

/**
 * @brief makes an inital copy of the given map
 * @param level
 */
void	copy_init_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	ctr.i = 6;
	level->num_of_rows = ft_arrlen(level->map_info + 6);
	level->init_map = ft_calloc(sizeof(char *), level->num_of_rows + 1);
	while (level->map_info[ctr.i])
	{
		level->init_map[ctr.j] = ft_strdup(level->map_info[ctr.i]);
		ctr.j++;
		ctr.i++;
	}
}
void	make_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	level->map = ft_calloc(sizeof(char *), level->num_of_rows + 1);
	while (ctr.i < level->num_of_rows)
	{
		ctr.j = 0;
		level->map[ctr.i] = ft_calloc(sizeof(char), level->num_of_columns + 1);
		while (ctr.j < ft_strlen(level->init_map[ctr.i]))
		{
			level->map[ctr.i][ctr.j] = level->init_map[ctr.i][ctr.j];
			ctr.j ++;
		}
		if (ctr.j < level->num_of_columns)
		{
			while (ctr.j < level->num_of_columns)
				level->map[ctr.i][ctr.j++] = ' ';
		}
		level->map[ctr.i][ctr.j] = '\0';
		ctr.i ++;
	}
}

void	replace_exs(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	level->map = ft_calloc(sizeof(char *), level->num_of_rows + 1);
	while (ctr.i < level->num_of_rows)
	{
		ctr.j = 0;
		if (ctr.j < level->num_of_columns)
		{
			if (level->map[ctr.i][ctr.i] == 'x')
				level->map[ctr.i][ctr.i] = '1';
			ctr.j ++;
		}
		ctr.i ++;
	}
}
