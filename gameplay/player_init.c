/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:05:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/24 08:34:39 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player(t_cub3d *cube, int x, int y)
{
	cube->player.transform.x_pos = x * 64 + 24;
	cube->player.transform.y_pos = y * 64 + 24;
	if (cube->player.orientation == 'S')
		cube->player.transform.angle = (3 * PI) / 2;
	else if (cube->player.orientation == 'E')
		cube->player.transform.angle = 0;
	else if (cube->player.orientation == 'W')
		cube->player.transform.angle = PI / 2;
	else if (cube->player.orientation == 'N')
		cube->player.transform.angle = PI;
	printf("THE ANGLE IS : %f\n", cube->player.transform.angle);
	cube->player.transform.dx = cos(cube->player.transform.angle) * 5;
	cube->player.transform.dy = sin(cube->player.transform.angle) * 5;
}
