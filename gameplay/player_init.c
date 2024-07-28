/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:05:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/28 12:44:21 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player_pos(t_cub3d *cube, int x, int y)
{
	cube->player.transform.x0 = x * MINIMAP_X + 10.7;
	cube->player.transform.y0 = y * MINIMAP_Y + 10.7;
	if (cube->player.orientation == 'N')
		cube->player.transform.angle = 3 * PI / 2;
	else if (cube->player.orientation == 'E')
		cube->player.transform.angle = 0;
	else if (cube->player.orientation == 'S')
		cube->player.transform.angle = PI / 2;
	else if (cube->player.orientation == 'W')
		cube->player.transform.angle = PI;
	update_player_direction(cube);
}
