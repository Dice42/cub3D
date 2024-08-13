/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:21:26 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 20:21:27 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	check_space_surroundings(t_level *level, int x, int y)
{
	char	entry;

	entry = level->map[x][y];
	if (x > 0 && x < (ft_strlen(level->map[x]) - 1))
	{
		if (level->map[x-1][y] == '0')
			return (false);
		if (level->map[x + 1][y] == '0')
			return (false);
	}
	if (y > 0 && y < (level->num_of_columns - 1))
	{
		if (level->map[x][y - 1] == '0')
			return (false);
		if (level->map[x][y + 1] == '0')
			return (false);
	}
	return (true);
}


/**
 * @brief makes an inital copy of the given map
 * @param level
 */
void	copy_init_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	ctr.i = 6;
	level->num_of_rows = ft_arrlen(level->map_info + 6);
	level->init_map = ft_calloc(sizeof(char *), level->num_of_rows + 1);
	while (level->map_info[ctr.i])
	{
		level->init_map[ctr.j] = ft_strdup(level->map_info[ctr.i]);
		ctr.j++;
		ctr.i++;
	}
}

void	make_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	level->map = ft_calloc(sizeof(char *), level->num_of_rows + 1);
	while (ctr.i < level->num_of_rows)
	{
		ctr.j = 0;
		level->map[ctr.i] = ft_calloc(sizeof(char), level->num_of_columns + 1);
		while (ctr.j < ft_strlen(level->init_map[ctr.i]))
		{
			printf("%c", level->init_map[ctr.i][ctr.j]);
			level->map[ctr.i][ctr.j] = level->init_map[ctr.i][ctr.j];
			printf("%c ", level->map[ctr.i][ctr.j]);
			ctr.j ++;
		}
		printf("\n");
		if (ctr.j < level->num_of_columns)
		{
			printf("less than\n");
			while (ctr.j < level->num_of_columns)
				level->map[ctr.i][ctr.j++] = '1';
		}
		level->map[ctr.i][ctr.j] = '\0';
		printf("strlen: %d\n", ft_strlen(level->map[ctr.i]));
		printf("init strlen: %d\n", ft_strlen(level->init_map[ctr.i]));
		ctr.i ++;
	}
	printf("init size : %d\n", ft_strlen(level->init_map[0]));
	int i = 0;
	while (i < level->num_of_rows)
	{
		int j = 0;
		while (level->map[i][j] != '\0')
			printf("%c", level->map[i][j++]);
		printf("\n");
		i ++;
	}
	printf("size : %d\n", ft_strlen(level->map[0]));
}

/**
 * @brief fill the visited array with false in intial state
 * @param visited
 * @param map
 * @param n_rows
 */
void	fill_visited(t_level *lvl, bool **visited, int n_rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_rows)
	{
		visited[i] = ft_calloc(sizeof(bool), lvl->num_of_columns + 1);
		j = 0;
		while (visited[i][j])
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
}

/**
 * @brief this function checks if the value of the map is valid or not
 * by checking next and previous rows and columns of the map
 * @param x position of x in the map
 * @param y position of y in the map
 * @param level levels details
 * @return true
 * @return false
 */
bool	check_if_valid(int x, int y, t_level *level)
{
	if (level->map[x + 1] == NULL)
		return (false);
	if (y > ft_strlen(level->map[x + 1]) - 1)
		return (false);
	if (x > 0 && level->map[x - 1] == NULL)
		return (false);
	if (x > 0 && y > ft_strlen(level->map[x - 1]) - 1)
		return (false);
	if (y >= ft_strlen(level->map[x]) - 1)
		return (false);
	return (true);
}
