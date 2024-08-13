/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_clr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:20:23 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 16:24:20 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**rgb_values(char *rgb)
{
	char	**rgb_list;
	char	*str;
	t_ctr	ctr;

	init_ctrs(&ctr);
	if (ft_count_char(rgb, ',') != 2)
		return (NULL);
	rgb_list = ft_split(rgb + 1, ',');
	while (rgb_list[ctr.i] != NULL)
	{
		str = ft_ignorespaces(rgb_list[ctr.i]);
		ctr.j = 0;
		while (str[ctr.j] && ft_ignorespaces(&str[ctr.j]))
		{
			while (str[ctr.j] == ' ' || str[ctr.j] == '+')
				ctr.j++;
			if (str[ctr.j] && !ft_isdigit(str[ctr.j++]))
				return (ft_free2d((void **)rgb_list), NULL);
		}
		ctr.i++;
	}
	if (ctr.i != 3)
		return (ft_free2d((void **)rgb_list), NULL);
	return (rgb_list);
}

bool	validate_rgb_values(char *rgb, t_level *level)
{
	char	**rgb_list;
	bool	floor;
	int		temp;
	int		i;

	i = 0;
	floor = true;
	if (rgb[0] == 'C')
		floor = false;
	rgb_list = rgb_values(rgb);
	if (!rgb_list)
		return (false);
	while (i < 3)
	{
		temp = ft_atoi(ft_ignorespaces(rgb_list[i]));
		if (temp == -1)
			return (ft_free2d((void **)rgb_list), false);
		if (temp < 0 || temp > 255)
			return (ft_free2d((void **)rgb_list), false);
		if (floor)
			level->floor_color[i++] = temp;
		else
			level->ceiling_color[i++] = temp;
	}
	return (ft_free2d((void **)rgb_list), true);
}

bool	find_colors_info(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	while (ctr.i < 6)
	{
		ctr.j = ft_skipspaces(level->map_info[ctr.i]);
		if (level->map_info[ctr.i][ctr.j] == 'C'
			|| level->map_info[ctr.i][ctr.j] == 'F')
		{
			if (!validate_rgb_values(level->map_info[ctr.i] + ctr.j, level))
				return (false);
		}
		ctr.i++;
	}
	return (true);
}
