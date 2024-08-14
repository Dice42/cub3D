/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:21:21 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/14 09:40:49 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief this function validates if the map has only one player
 * spaces 0s and 1s
 * @param map
 * @param n_rows
 * @return
 */
bool	validate_map_content(char **map, int n_rows, t_player *player)
{
	t_ctr	ctr;
	bool	player_found;

	init_ctrs(&ctr);
	player_found = false;
	while (ctr.i < n_rows)
	{
		ctr.j = 0;
		while (map[ctr.i][ctr.j])
		{
			if (!check_map_content(map, &ctr, player, &player_found))
				return (false);
		}
		ctr.i++;
	}
	if (!player_found)
		return (false);
	return (true);
}

/**
 * @brief check each value of the map and validate it
 * this function calls it self recursively checking all the four sides
 * of each position in the map
 */
bool	check_sides(int x, int y, t_level *level, char *expected)
{
	char	entry;
	char	*exp;

	exp = NULL;
	if (x < 0 || y < 0 || x > (level->num_of_rows)
		|| y > (ft_strlen(level->map[x]) - 1))
		return (true);
	else if (level->visited[x][y])
		return (true);
	else
	{
		entry = level->map[x][y];
		if (!ft_strchr(expected, entry))
			return (false);
		exp = set_expected(x, y, level);
		if (!exp)
			return (false);
	}
	level->visited[x][y] = true;
	return (check_sides((x - 1), (y), level, exp) && check_sides((x + 1), (y),
			level, exp) && check_sides((x), (y + 1), level, exp)
		&& check_sides((x), (y - 1), level, exp));
}

/**
 * @brief checks if the map has vertical borders are all 1s
 * @param level level details
 * @param row row number
 * @return true
 * @return false
 */
bool	vertical_borders(t_level *level, int row)
{
	bool	edge;
	t_ctr	ctr;

	init_ctrs(&ctr);
	while (level->map[row][ctr.i])
	{
		if (level->map[row][ctr.i] == '1' || level->map[row][ctr.i] == ' ')
			edge = true;
		else
			return (false);
		if (level->map[row][ctr.i] == ' ')
			ctr.i = ft_skip_char(level->map[row], ' ', true, ctr.i);
		if (!level->map[row][ctr.i])
			break ;
		if (level->map[row][ctr.i] != '1')
			return (false);
		ctr.i++;
	}
	if (!edge)
		return (false);
	if (ctr.i > level->num_of_columns)
		level->num_of_columns = ctr.i;
	return (true);
}

/**
 * @brief validates whether the map is closed or not
 * 			check the content of the map and validate it.
 *
 * 1) the first and last row must all be 1 or space.
 * 2) the first and las characters of every row must be 1.
 * 3) only 0 1 N S E W or space can be in each row
 */
bool	validate_map(t_level *level, t_player *player)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	copy_init_map(level);
	get_columns_num(level);
	make_map(level);
	level->visited = ft_calloc(sizeof(bool *), level->num_of_rows + 1);
	fill_visited(level, level->visited, level->num_of_rows);
	if (!validate_map_content(level->map, level->num_of_rows, player))
		return (false);
	if (!vertical_borders(level, 0) || !vertical_borders(level,
			level->num_of_rows - 1))
		return (false);
	if (!check_sides(0, 0, level, " 1"))
		return (false);
	return (true);
}
