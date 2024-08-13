/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:12:01 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 19:07:14 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int main(int ac, char **av)
{
	t_cub3d	cube;

	if (ac != 2)
		return (0);
	if (!init_cube(&cube))
		return (0);
	if (!validate_level(av[1], &cube.level, &cube.player))
		return (0);
	//ft_start(&cube);
	return (0);
}
