

#include "../includes/cub3D.h"


int	ft_skipspaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}



char	*ft_strdup(char *src)
{
	int		len;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(src)+ 1));
	if (dest == NULL)
		return (0);
	len = 0;
	while (src[len] != '\0')
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = '\0';
	return (dest);
}


void    init_ctrs(t_ctr *ctr)
{
    ctr->i = 0;
    ctr->j = 0;
    ctr->c = 0;
}


char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}


char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	size = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcat(ft_strcpy(res, (char *)s1), (char *)s2);
		return (res);
	}
	else if (s1 != NULL && s2 == NULL)
	{
		return (free((char *)s2), ft_strcpy(res, (char *)s1));
	}
	else if (s1 == NULL && s2 != NULL)
		return (free((char *)s1), ft_strcpy(res, (char *)s2));
	else
		return (free((char *)s1), NULL);
}







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
