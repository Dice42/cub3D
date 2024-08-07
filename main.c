/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:12:01 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/07 07:32:54 by vtcsbza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int main(int ac, char **av)
{
	t_cub3d	cube;

	if (ac != 2)
		return (0);
	if (!init_cube(&cube))
		return (0); //print error
	if (!validate_level(av[1], &cube.level, &cube.player))
	{
		printf("ERROR!\n");
		return (0); //print error
	}
	printf("success!\n");
	// convert_rgb_hex(&cube.level);
	//printf("the minimap x is %d and minimap y is %d\n", MINIMAP_X, MINIMAP_Y);
	//ft_start(&cube);
	return (0);
}
