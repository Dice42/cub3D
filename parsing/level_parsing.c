/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:08 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/17 18:41:13 by ssibai           ###   ########.fr       */
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
	int		i;
	int		j;
	char	last[6];
	int		c;

	i = 0;
	j = 0;
	c = 0;
	while (i < 6)
	{
		j = ft_skipspaces(map[i]);
		if (map[i][j] == 'N'
			|| map[i][j] == 'W'
			|| map[i][j] == 'S'
			|| map[i][j] == 'E'
			|| map[i][j] == 'F'
			|| map[i][j] == 'C')
		{
			last[i] = map[i][j];
			c = 0;
			while (c < i)
			{
				if (!ft_strncmp(&map[i][j] , &last[c], 1))
					return (false);
				c ++;
			}
			i ++;
		}
		else
			return (false);
		j = 0;
	}
	return (true);
}

/**
 * @brief check the validity of the textures 
 * 			by checking whether the textures exist within a 
 * 			specified directory
 */
// bool	validate_map_textures()
// {
	
// }

bool	validate_rgb_values(char *rgb, t_level *level)
{
	bool	ceiling;
	char	**rgb_list;
	int		i;
	int		temp;

	i = 0;
	temp = 0;
	ceiling = false;
	if (rgb[0] == 'C')
		ceiling = true;
	rgb_list = ft_split(rgb + 1, ',');
	while (rgb_list[i] != NULL)
		i ++;
	if (i < 3)
		return (ft_free2d((void **)rgb_list), false);
	i = 0;
	while (i < 3)
	{
		temp = ft_atoi(ft_ignorespaces(rgb_list[i]));
		if (temp < 0 || temp > 255)
			return (false);
		if (ceiling)
			level->ceiling_color[i] = temp;
		else
			level->floor_color[i] = temp;
		i ++;
	}
	return (ft_free2d((void **)rgb_list), true);
}

bool	find_colors_info(t_level *level)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 6)
	{
		j = ft_skipspaces(level->map[i]);
		if (level->map[i][j] == 'C'
			|| level->map[i][j] == 'F')
		{
			if (!validate_rgb_values(level->map[i] + j, level))
				return (false);
		}
		i ++;
	}
	return (true);
}

// bool	validate_map_content(char **map)
// {
// 	int	i;

// 	i = 6;
// }

bool	validate_level(char *level_path, t_cub3d *cube)
{
	t_level	level;
	int		i;
	
	i = 0;
	level = cube->level;
	if (ft_strncmp((level_path + (ft_strlen(level_path) - 4)), ".cub", 4) != 0)
		return (false);//	error_handler(NULL, , "Error: file type is wrong\n", 1);
	level.full_file = open_read_level(level_path, 0);
	if (!level.full_file)
		return (false);//error_handler(full_file, sl, "Error: couldn't open file\n", 1);
	level.map = ft_split(level.full_file, '\n');
	if (!level.map)
		return (false);
	if (!validate_order(level.map))
		return (false);
	if (!find_colors_info(&level))
		return (false);
	
	
	
	return (true);
}