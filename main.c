/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:12:01 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/20 22:23:37 by mohammoh         ###   ########.fr       */
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
		return (0); //print error
	ft_start(&cube);
	return (0);
}
