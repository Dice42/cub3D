/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:08 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/16 21:24:25 by mohammoh         ###   ########.fr       */
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

bool	validate_level(char *level_path, t_level *level)
{
	char	*full_file;

	(void)level;
	if (ft_strncmp((level_path + (ft_strlen(level_path) - 4)), ".cub", 4) != 0)
		return (false);//	error_handler(NULL, , "Error: file type is wrong\n", 1);
	full_file = open_read_level(level_path, 0);
	if (!full_file)
		return (false);//error_handler(full_file, sl, "Error: couldn't open file\n", 1);
	
	
	return (true);
}