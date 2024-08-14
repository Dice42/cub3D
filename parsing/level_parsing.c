/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:08 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/14 11:25:20 by mohammoh         ###   ########.fr       */
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
			free(temp);
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
				if (!ft_strncmp(&map[ctr.i][ctr.j], &letter_list[ctr.c++], 1))
					return (false);
			}
			ctr.i++;
		}
		else
			return (false);
		ctr.j = 0;
	}
	return (true);
}

bool	validate_level(char *level_path, t_cub3d *cub, t_player *player)
{
	if (ft_strncmp((level_path + (ft_strlen(level_path) - 4)), ".cub", 4) != 0)
		return (error_handler(INVALID_FILE_TYPE, false, NULL, false), false);
	cub->level.full_file = open_read_level(level_path, 0);
	if (!cub->level.full_file)
		return (error_handler(INVALID_FILE, false, cub, true), false);
	cub->level.map_info = ft_split(cub->level.full_file, '\n');
	if (!cub->level.map_info)
		return (error_handler(INVALID_FILE_INFO, false, cub, true), false);
	if (!validate_order(cub->level.map_info))
		return (error_handler(INVALID_MAP_INFO, false, cub, true), false);
	if (!find_colors_info(&cub->level))
		return (error_handler(INVALID_RGB, false, cub, true), false);
	if (!validate_map(&cub->level, player))
		return (error_handler(INVALID_MAP, false, cub, true), false);
	if (!validate_textures_info(&cub->level))
		return (error_handler(INVALID_MAP_TEXTURE, false, cub, true), false);
	return (true);
}
