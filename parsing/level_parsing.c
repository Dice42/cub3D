/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:08 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/07 14:05:35 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*open_read_level(char *level_path, char *file)
{
	int		fd;
	char	*temp;
	char	buf[BUFFER_SIZE + 1];
	size_t	red;

	fd = open(level_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	red = read(fd, buf, BUFFER_SIZE);
	while (red > 0)
	{
		buf[red] = '\0';
		if (file)
		{
			temp = file;
			file = ft_strjoin(file, buf);
			free (temp);
		}
		else
			file = ft_strdup(buf);
		red = read(fd, buf, BUFFER_SIZE);
	}
	close(fd);
	return (file);
}

bool	validate_order(char **map)
{
	t_ctr	ctr;
	char	letter_list[6];

	init_ctrs(&ctr);
	while (ctr.i < 6)
	{
		ctr.j = ft_skipspaces(map[ctr.i]);
		if (map[ctr.i][ctr.j] == 'N' || map[ctr.i][ctr.j] == 'W'
			|| map[ctr.i][ctr.j] == 'S' || map[ctr.i][ctr.j] == 'E'
			|| map[ctr.i][ctr.j] == 'F' || map[ctr.i][ctr.j] == 'C')
		{
			letter_list[ctr.i] = map[ctr.i][ctr.j];
			ctr.c = 0;
			while (ctr.c < ctr.i)
			{
				if (!ft_strncmp(&map[ctr.i][ctr.j] , &letter_list[ctr.c++], 1))
					return (false);
			}
			ctr.i ++;
		}
		else
			return (false);
		ctr.j = 0;
	}
	return (true);
}

bool	validate_rgb_values(char *rgb, t_level *level)
{
	bool	floor;
	char	**rgb_list;
	int		i;
	int		temp;

	i = 0;
	temp = 0;
	floor = true;
	if (rgb[0] == 'C')
		floor = false;
	rgb_list = ft_split(rgb + 1, ',');
	while (rgb_list[i] != NULL)
		i++;
	if (i != 3)
		return (ft_free2d((void **)rgb_list), false);
	i = 0;
	while (i < 3)
	{
		temp = ft_atoi(ft_ignorespaces(rgb_list[i]));
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
		ctr.i ++;
	}
	return (true);
}

bool	validate_level(char *level_path, t_level *level, t_player *player)
{
	if (ft_strncmp((level_path + (ft_strlen(level_path) - 4)), ".cub", 4) != 0)
		return (error_handler(INVALID_FILE_TYPE, NULL, NULL, false),false);
	level->full_file = open_read_level(level_path, 0);
	if (!level->full_file)
		return (error_handler(INVALID_FILE, NULL, level, true),false);
	level->map_info = ft_split(level->full_file, '\n');
	if (!level->map_info)
		return (error_handler(INVALID_FILE_INFO, NULL, level, true),false);
	if (!validate_order(level->map_info))
		return (error_handler(INVALID_MAP_INFO, NULL, level, true),false);
	if (!find_colors_info(level))
		return (error_handler(INVALID_RGB, NULL, level, true),false);
	if (!validate_map(level, player))
		return (error_handler(INVALID_MAP, NULL, level, true),false);
	if (!validate_textures_info(level))
		return (error_handler(INVALID_MAP_TEXTURE, NULL, level, true),false);
	return (true);
}
