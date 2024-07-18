

#include "../includes/cub3D.h"

char	*get_texture(char *str, int j, int c)
{
	char	*temp;
	char	*texture;

	temp = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (str[j])
	{
		j = ft_skipspaces(str);
		if (j == '\0')
			return (NULL);
		temp[c] = str[j];
		j++;
		c++;
	}
	temp[c] = '\0';
	texture = ft_strdup(temp);
	free (temp);
	printf("%s\n",texture);
	return (texture);
}

/**
 * @brief check the validity of the textures 
 * 			by checking whether the textures exist within a 
 * 			specified directory
 */
bool	validate_map_textures(t_level *level)
{
	t_ctr   ctr;
	char	*str;
	char	*full_path;

	str = NULL;
	full_path = NULL;
	init_ctrs(&ctr);
	//printf("%s\n", level->map[0]);
	while (ctr.i < 6)
	{
		str = get_texture(level->map[ctr.i], 0, 0);
		full_path = ft_strjoin(texture_path, str);
		if (access(full_path, F_OK) == -1)
			return (free(str), false);
		ctr.j = ft_skipspaces(level->map[ctr.i]);
		if (level->map[ctr.i][ctr.j] == 'N')
			level->textures.north_texture = str;
		else if (level->map[ctr.i][ctr.j] == 'W')
			level->textures.west_texture = str;
		else if (level->map[ctr.i][ctr.j] == 'S')
			level->textures.south_texture = str;
		else if (level->map[ctr.i][ctr.j] == 'E')
			level->textures.east_texture = str;
		ctr.i ++;
		printf("%s\n", str);
		free (str);
		free (full_path);
	}
	return (true);
}

int main()
{
	t_level	level;

	level.map = malloc(sizeof(char *) * 4);

	level.map[0] = ft_strdup("    Npath_to_north_texture");
    level.map[1] = ft_strdup("    Wpath_to_west_texture");
    level.map[2] = ft_strdup("    Spath_to_south_texture");
    level.map[3] = ft_strdup("    Epath_to_east_texture");
	validate_map_textures(&level);
	return (0);
}
