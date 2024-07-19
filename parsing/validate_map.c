/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:21:21 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/19 19:04:16 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

bool	validate_map_content(char **map, int n_rows)
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
				|| map[ctr.i][ctr.j] == 'E' || map[ctr.i][ctr.j] == 'W' || map[ctr.i][ctr.j] == ' ')
			{
				if ((map[ctr.i][ctr.j] == 'N' || map[ctr.i][ctr.j] == 'S'
					|| map[ctr.i][ctr.j] == 'E' || map[ctr.i][ctr.j] == 'W'))
				{
					if (player_found)
						return (false);
					player_found = true;
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

/* ************************************************************************** */
bool	check_sides(int x, int y, t_level *level, char *expected)
{
	char	entry;
	char	*exp;
	
	exp = NULL;
	if ( x == -1 || y == -1 || y >= (level->num_of_rows)
		|| x >= (ft_strlen(level->map[x])))
		return (true);
	else if (level->visited[y][x])
		return (true);
	else
	{
		entry = level->map[y][x];
		printf("X is %d and Y is %d for entry %c\n" , x, y ,entry);
		if (!ft_strchr(expected, entry))
		{
			printf("Not within the expected string\n");
			return (false);
		}
		level->visited[y][x] = true;
		if (entry == ' ')
			exp = " 1";
		else if (entry == '1')
			exp = " 10NESW";
		else if (entry == '0')
			exp = "10NESW";
		else if (entry == 'N' || entry == 'S'
			|| entry == 'W' || entry == 'E')
			exp = "10";
	}
	printf("my entry %c is and my expected is : [%s]\n", entry, exp);
	return (recursive_call(y, x, level, exp));
}

bool	recursive_call(int x, int y, t_level *level, char *expected)
{
	return (check_sides((x + 1), (y), level, expected)
		&& check_sides((x), (y + 1), level, expected)
		&& check_sides((x - 1), y, level, expected)
		&& check_sides((x), (y - 1), level, expected));
}
/*
	we must check:

	1) check the length of the row.
	2) if we find a space, the character under must be one
	3) 
 */

// bool	vertical_borders(t_level *level)
// {
// 	bool	edge;
// 	t_ctr	ctr;

// 	init_ctrs(&ctr);
// 	while (level->map[ctr.i])
// 	{
// 		if (level->map[ctr.i][ctr.j] == 1 || ' ')
// 			edge = true;
// 		else
// 			edge = false;
// 		ctr.j ++;
// 	}
// 	if (!edge)
// 		return (false);
// }

// bool	horizontal_borders(t_level *level)
// {
// 	int	i;
	
// 	while (level->map[0])
// 	{
// 		if (level->map[0][i] != ' ' && level->map[0][i] != 1)
// 			return (false);
// 	}
// }

/**
 * @brief validates whether the map is closed or not
 * 		 check the content of the map and validate it.
 * 
 * 1) the first and last row must all be 1 or space.
 * 2) the first and las characters of every row must be 1.
 * 3) only 0 1 N S E W or space can be in each row
 */
bool	validate_map(t_level *level)
{
	t_ctr	ctr;
	//int		row_lengt
	
	init_ctrs(&ctr);
	copy_map(level);
	level->visited = ft_calloc(sizeof(bool *), level->num_of_rows);
	fill_visited(level->visited, level->map, level->num_of_rows);
	if (!validate_map_content(level->map, level->num_of_rows))
	{
		printf("NO\n");
		return (false);
	}
	if (!check_sides(0, 0, level, " 1"))
	{
		printf("sides NO\n");
		return (false);
	}
	return (true);
}