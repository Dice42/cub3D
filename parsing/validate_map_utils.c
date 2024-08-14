/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:21:26 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/14 10:32:07 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	check_map_content(char **map, t_ctr *ctr, t_player *plyr, bool *found)
{
	if (map[ctr->i][ctr->j] == '0' || map[ctr->i][ctr->j] == '1'
		|| map[ctr->i][ctr->j] == 'N' || map[ctr->i][ctr->j] == 'S'
		|| map[ctr->i][ctr->j] == 'E' || map[ctr->i][ctr->j] == 'W'
		|| map[ctr->i][ctr->j] == ' ')
	{
		if ((map[ctr->i][ctr->j] == 'N' || map[ctr->i][ctr->j] == 'S'
				|| map[ctr->i][ctr->j] == 'E'
				|| map[ctr->i][ctr->j] == 'W'))
		{
			if (*found)
				return (false);
			*found = true;
			plyr->orientation = map[ctr->i][ctr->j];
		}
		ctr->j++;
	}
	else
		return (false);
	return (true);
}

char	*set_expected(int x, int y, t_level *level)
{
	char	*exp;

	exp = NULL;
	if (level->map[x][y] == ' ')
	{
		if (!check_space_surroundings(level, x, y))
			return (NULL);
		exp = " 1";
	}
	else if (level->map[x][y] == '1')
		exp = " 10NESW";
	else if (level->map[x][y] == '0')
	{
		if (!check_if_valid(x, y, level))
			return (NULL);
		exp = "10NESW";
	}
	else if (level->map[x][y] == 'N' || level->map[x][y] == 'S'
		|| level->map[x][y] == 'W' || level->map[x][y] == 'E')
	{
		exp = "10";
		if (!check_if_valid(x, y, level))
			return (NULL);
	}
	return (exp);
}

bool	check_space_surroundings(t_level *level, int x, int y)
{
	char	entry;

	entry = level->map[x][y];
	if (x > 0 && x < level->num_of_rows - 1)
	{
		if (level->map[x - 1][y] == '0')
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
