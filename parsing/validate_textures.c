/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:02:51 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 23:33:48 by ssibai           ###   ########.fr       */
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

bool	itirate_clr_info(t_level *level, t_ctr *ctr)
{
	if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr->i]), "F ", 2))
	{
		ctr->i++;
		return (true);
	}
	else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr->i]), "C ", 2))
	{
		ctr->i++;
		return (true);
	}
	return (false);
}

bool	itirate_dir_info(t_level *level, t_ctr *ctr)
{
	if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr->i]), "NO", 2))
	{
		if (!set_texture(level, 'N', &ctr->i))
			return (false);
	}
	else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr->i]), "SO", 2))
	{
		if (!set_texture(level, 'S', &ctr->i))
			return (false);
	}
	else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr->i]), "WE", 2))
	{
		if (!set_texture(level, 'W', &ctr->i))
			return (false);
	}
	else if (!ft_strncmp(ft_ignorespaces(level->map_info[ctr->i]), "EA", 2))
	{
		if (!set_texture(level, 'E', &ctr->i))
			return (false);
	}
	else if (itirate_clr_info(level, ctr))
		return (true);
	else
		return (false);
	return (true);
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
		if (!itirate_dir_info(level, &ctr))
			return (false);
	}
	return (true);
}
