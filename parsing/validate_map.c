/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:21:21 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/19 14:51:07 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	copy_map(t_level *level)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	ctr.i = 6;
	while (level->map_info[ctr.i])
	{
		level->map[ctr.j] = ft_strdup(level->map_info[ctr.i]);
		ctr.j++;
		ctr.i++;
	}
	level->num_of_rows = ctr.j;
}

bool	validate_map_content(char *map_row)
{
	int	i;

	i = 0;
	while (map_row[i])
	{
		if (map_row[i] == '0' || map_row[i] == '1'
			|| map_row[i] == 'N' || map_row[i] == 'S'
			|| map_row[i] == 'E' || map_row[i] == 'W' || map_row[i] == ' ')
			i ++ ;
		else
		{
			printf("false\n");
			return (false);
		}
	}
	return (true);
}


/* ************************************************************************** */
bool	check_sides(int x, int y, t_level *level, char *expected)
{

	char	entry;
	char	*exp;

	entry = level->map[x][y];
	exp = NULL;
	if ( x == -1 || y == -1 || x >= ft_strlen(level->map[x])
		|| y >= level->num_of_rows || level->visited[x][y])
		return (true);
	else
	{
		if (!ft_strchr(expected, entry))
			return (false);
		level->visited[x][y] = true;
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
	printf("my entry is and my expected is : %s\n", exp);
	return (recursive_call(x, y, level, exp));
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

// bool	check_borders(t_level *level, int row)
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
// 	if (ctr.j > level->columns)
// 		level->columns = ctr.j;
// 	if (!edge)
// 		return (false);
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
	t_ctr ctr;

	init_ctrs(&ctr);
	copy_map(level);

	while (level->map[ctr.i])
	{
		printf("%s\n", level->map[ctr.i++]);
	}

	while (level->map[ctr.i])
	{
		if (!validate_map_content(level->map[ctr.i]))
			return (false);
		if (!check_sides(0, 0, level, " 1"))
			return (false);
	}
	return (true);
}