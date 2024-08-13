/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:02:51 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 17:33:35 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief check the path of the texture
 *
 * @param str
 * @return
 */
char	*get_texture(char *str)
{
	char	*textures_path;

	textures_path = ft_ignorespaces(str);
	if (access(textures_path, F_OK) == -1)
		return (NULL);
	return (textures_path);
}

/**
 * @brief allocate the texture to the level struct
 * @return
 */
bool	set_texture(t_level *level, char direction, int *i)
{
	char	*str;

	str = NULL;
	str = get_texture(ft_ignorespaces(level->map_info[*i]) + 2);
	if (!str)
		return (false);
	if (direction == 'N')
		level->textures.north_texture = ft_strdup(str);
	else if (direction == 'S')
		level->textures.south_texture = ft_strdup(str);
	else if (direction == 'W')
		level->textures.west_texture = ft_strdup(str);
	else if (direction == 'E')
		level->textures.east_texture = ft_strdup(str);
	return ((*i)++, true);
}

/**
 * @brief check the validity of the textures
 * 			by checking whether the textures exist within a
 * 			specified directory
 */
bool	validate_textures_info(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	while (ctr.i < 6)
	{
		if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr.i]), "NO", 2))
		{
			if (!set_texture(level, 'N', &ctr.i))
				return (false);
		}
		else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr.i]), "SO", 2))
		{
			if (!set_texture(level, 'S', &ctr.i))
				return (false);
		}
		else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr.i]), "WE", 2))
		{
			if (!set_texture(level, 'W', &ctr.i))
				return (false);
		}
		else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr.i]), "EA", 2))
		{
			if (!set_texture(level, 'E', &ctr.i))
				return (false);
		}
		else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr.i]), "F ", 2))
			ctr.i++;
		else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr.i]), "C ", 2))
			ctr.i++;
		else
			return (false);
	}
	return (true);
}
