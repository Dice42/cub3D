/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:21:26 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/12 22:27:38 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_space_surroundings(t_level *level, int x, int y)
{
	char	entry;

	entry = level->map[x][y];
	if (x != 0 && x - 1 < level->num_of_rows)
		
}


/**
 * @brief makes a copy of the given map
 * @param level
 */
void	copy_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	ctr.i = 6;
	level->num_of_rows = ft_arrlen(level->map_info + 6);
	level->map = ft_calloc(sizeof(char *), level->num_of_rows + 1);
	while (level->map_info[ctr.i])
	{
		level->map[ctr.j] = ft_strdup(level->map_info[ctr.i]);
		ctr.j++;
		ctr.i++;
	}
}

/**
 * @brief fill the visited array with false in intial state
 * @param visited
 * @param map
 * @param n_rows
 */
void	fill_visited(bool **visited, char **map, int n_rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_rows)
	{
		visited[i] = ft_calloc(sizeof(bool), ft_strlen(map[i]));
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
