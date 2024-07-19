/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:21:21 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/19 19:59:06 by ssibai           ###   ########.fr       */
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
	
	printf("CALLED\n");
	exp = NULL;
	if ( x == -1 || y == -1 || y >= (level->num_of_rows)
		|| x >= (ft_strlen(level->map[x])))
	{
		printf("true cuz border\n");
		return (true);
	}
	else if (level->visited[x][y])
	{
		printf("true cuz visited\n");
		return (true);
	}
	else
	{
		entry = level->map[x][y];
		printf("X is %d and Y is %d for entry %c\n" , x, y ,entry);
		if (!ft_strchr(expected, entry))
		{
			//printf("Not within the expected string\n");
			return (false);
		}
		if (entry == ' ')
			exp = " 1";
		else if (entry == '1')
			exp = " 10NESW";
		else if (entry == '0')
		{
			printf("x is %d", x);
			printf(" and strlen of next row is %d\n", ft_strlen(level->map[x + 1]));
			if (x >= ft_strlen(level->map[x + 1]))
			{
				printf("NOT TRUE\n");
				return (false);
			}
			exp = "10NESW";
		}
		else if (entry == 'N' || entry == 'S'
			|| entry == 'W' || entry == 'E')
			exp = "10";
	}
	level->visited[x][y] = true;
	return (recursive_call(x, y, level, exp));
}

bool	recursive_call(int x, int y, t_level *level, char *expected)
{
	return (check_sides((x + 1), (y), level, expected)
		&& check_sides((x - 1), (y), level, expected)
		&& check_sides((x), (y - 1), level, expected)
		&& check_sides((x), (y + 1), level, expected));
}
/*
	we must check:

	1) check the length of the row.
	2) if we find a space, the character under must be one
	3) 
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
		{
			printf("THE ENTRY IS %c\n", level->map[row][ctr.i]);
			return (false);
		}
		ctr.i ++;
	}
	if (!edge)
		return (false);
	return (true);
}

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
	if (!vertical_borders(level, 0) || !vertical_borders(level, level->num_of_rows - 1))
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