

#include "../includes/cub3D.h"

char	*get_texture(char *str)
{
	char	*textures_path;

	textures_path = ft_ignorespaces(str);
	if (access(textures_path, F_OK) == -1)
		return (NULL);
	return (textures_path);
}
bool	set_texture(t_level *level, char direction, int *i)
{
	char *str;

	str = get_texture(ft_ignorespaces(level->map[*i]) + 2);
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
bool	validate_map_textures(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	while (ctr.i < 6)
	{
		if (ft_strncmp(ft_ignorespaces(level->map[ctr.i]), "NO", 2) == 0)
		{
			if (!set_texture(level, 'N', &ctr.i))
				return (false);
		}
		else if (ft_strncmp(ft_ignorespaces(level->map[ctr.i]), "SO", 2) == 0)
		{
			if (!set_texture(level, 'S', &ctr.i))
				return (false);
		}
		else if (ft_strncmp(ft_ignorespaces(level->map[ctr.i]), "WE", 2) == 0)
		{
			if (!set_texture(level, 'W', &ctr.i))
				return (false);
		}
		else if (ft_strncmp(ft_ignorespaces(level->map[ctr.i]), "EA", 2) == 0)
		{
			if (!set_texture(level, 'E', &ctr.i))
				return (false);
		}
		else if (ft_strncmp(ft_ignorespaces(level->map[ctr.i]), "F", 1) == 0)
			ctr.i ++;
		else if (ft_strncmp(ft_ignorespaces(level->map[ctr.i]), "C", 1) == 0)
			ctr.i ++;
		else
			return (false);
	}
	return (true);
}

// int main()
// {
// 	t_level	level;

// 	level.map = malloc(sizeof(char *) * 4);

// 	level.map[0] = ft_strdup("    Npath_to_north_texture");
//     level.map[1] = ft_strdup("    Wpath_to_west_texture");
//     level.map[2] = ft_strdup("    Spath_to_south_texture");
//     level.map[3] = ft_strdup("    Epath_to_east_texture");
// 	validate_map_textures(&level);
// 	return (0);
// }
