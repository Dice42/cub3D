/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:40:51 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/13 23:01:03 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_level(t_level *level)
{
	if (level->map)
		ft_free2d((void **)level->map);
	if (level->map_info)
		ft_free2d((void **)level->map_info);
	if (level->visited)
		ft_free2d((void **)level->visited);
	if (level->full_file)
		free(level->full_file);
	if (level->textures.north_texture)
		free(level->textures.north_texture);
	if (level->textures.west_texture)
		free(level->textures.west_texture);
	if (level->textures.east_texture)
		free(level->textures.east_texture);
	if (level->textures.south_texture)
		free(level->textures.south_texture);
}

void	error_handler(char *err_msg, t_cub3d *cub, t_level *level, bool frees)
{
	ft_putstr_fd(err_msg, 2);
	if (frees)
		free_level(level);
	(void)cub;
}
