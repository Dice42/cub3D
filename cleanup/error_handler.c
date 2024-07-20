/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:40:51 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/20 17:07:28 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_handler(char *err_msg, t_cub3d *cub, t_level *level, bool frees)
{
	ft_putstr_fd(err_msg, 2);
	if (frees)
	{
		if (level->map)
			ft_free(level->map, 'a');
		if (level->map_info)
			ft_free(level->map_info, 'a');
		// if (level->visited)
		// 	ft_free(level->visited, 'a');
		if (level->full_file)
			ft_free(level->full_file, 'p');
		if (level->textures.north_texture)
			free(level->textures.north_texture);
		if (level->textures.west_texture)
			free(level->textures.west_texture);
		if (level->textures.east_texture)
			free(level->textures.east_texture);
		if (level->textures.south_texture)
			free(level->textures.south_texture);
			
	}
	(void)cub;
}