/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:21:21 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/20 15:34:31 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	copy_map(t_level *level);
bool	validate_map_content(char **map, int n_rows, t_player *player);
void	fill_visited(bool **visited, char **map, int n_rows);
bool	check_if_valid(int x, int y, t_level *level);
bool	check_sides(int x, int y, t_level *level, char *expected);
bool	vertical_borders(t_level *level, int row);
bool	validate_map(t_level *level, t_player *player);



void	copy_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	ctr.i = 6;
	level->num_of_rows = ft_arrlen(level->map_info + 6);
	level->map = ft_calloc(sizeof(char *), level->num_of_rows);
	while (level->map_info[ctr.i])
	{
		level->map[ctr.j] = ft_strdup(level->map_info[ctr.i]);
		ctr.j++;
		ctr.i++;
	}
}

/* ************************************************************************** */
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
			if (map[ctr.i][ctr.j] == '0' || map[ctr.i][ctr.j] == '1'
				|| map[ctr.i][ctr.j] == 'N' || map[ctr.i][ctr.j] == 'S'
				|| map[ctr.i][ctr.j] == 'E' || map[ctr.i][ctr.j] == 'W' 
				|| map[ctr.i][ctr.j] == ' ')
			{
				if ((map[ctr.i][ctr.j] == 'N' || map[ctr.i][ctr.j] == 'S'
					|| map[ctr.i][ctr.j] == 'E' || map[ctr.i][ctr.j] == 'W'))
				{
					if (player_found)
						return (false);
					player_found = true;
					player->start_pos[0] = ctr.i;
					player->start_pos[1] = ctr.j;
					player->rot = map[ctr.i][ctr.j];
				}
				ctr.j ++ ;
			}
			else
				return (false);
		}
		ctr.i ++;
	}
	if (!player_found)
		return (false);
	return (true);
}

void	fill_visited(bool **visited, char **map, int n_rows)
{
	int	i;
	int j;

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
//check next row if it avaialbe if not return false
			//and if this charcter index is more than the next row length
			//if so return false else return true
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
	return (true);
}

/* ************************************************************************** */
bool	check_sides(int x, int y, t_level *level, char *expected)
{
	char	entry;
	char	*exp;
	exp = NULL;
	if ( x < 0 || y < 0 || x > (level->num_of_rows)
		|| y > (ft_strlen(level->map[x]) - 1))
		return (true);
	else if (level->visited[x][y])
		return (true);
	else
	{
		entry = level->map[x][y];
		if (!ft_strchr(expected, entry))
			return (false);
		if (entry == ' ')
			exp = " 1";
		else if (entry == '1')
			exp = " 10NESW";
		else if (entry == '0')
		{
			if (!check_if_valid(x, y, level))
				return (false);
			exp = "10NESW";
		}
		else if (entry == 'N' || entry == 'S'
			|| entry == 'W' || entry == 'E')
		{
			exp = "10";
			if (!check_if_valid(x, y, level))
				return (false);
		}
	}
	level->visited[x][y] = true;
	return (check_sides((x - 1), (y), level, exp)
		&& check_sides((x + 1), (y), level, exp)
		&& check_sides((x), (y + 1), level, exp)
		&& check_sides((x), (y - 1), level, exp));
}

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
		{
			printf("THE ENTRY IS %c\n", level->map[row][ctr.i]);
			return (false);
		}
		if (level->map[row][ctr.i] == ' ')
			ctr.i = ft_skip_char(level->map[row], ' ');
		if (level->map[row][ctr.i] != '1')
			return (false);
		ctr.i ++;
	}
	if (!edge)
		return (false);
	if (ctr.i > level->num_of_columns)
		level->num_of_columns = ctr.i;
	return (true);
}

/**
 * @brief validates whether the map is closed or not
 * 		 check the content of the map and validate it.
 * 
 * 1) the first and last row must all be 1 or space.
 * 2) the first and las characters of every row must be 1.
 * 3) only 0 1 N S E W or space can be in each row
 */
bool	validate_map(t_level *level, t_player *player)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	copy_map(level);
	get_columns_num(level);
	level->visited = ft_calloc(sizeof(bool *), level->num_of_rows);
	fill_visited(level->visited, level->map, level->num_of_rows);
	if (!validate_map_content(level->map, level->num_of_rows, player))
	{
		printf("NO\n");
		return (false);
	}
	if (!vertical_borders(level, 0) 
		|| !vertical_borders(level, level->num_of_rows - 1))
	{
		printf("NOT ALL 1 OR SPACE\n");
		return (false);
	}
	if (!check_sides(0, 0, level, " 1"))
	{
		printf("sides NO\n");
		return (false);
	}
	return (true);
}
