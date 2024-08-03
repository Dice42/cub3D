/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:05:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/03 17:53:20 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player_pos(t_cub3d *cube, int x, int y)
{
	cube->player.transform.x0 = x * MINIMAP_X + 7;
	cube->player.transform.y0 = y * MINIMAP_Y + 7;
	if (cube->player.orientation == 'N')
		cube->player.transform.angle = atan2(-1, 0) + 0.001;
	else if (cube->player.orientation == 'E')
		cube->player.transform.angle = atan2(0, 1);
	else if (cube->player.orientation == 'S')
		cube->player.transform.angle = atan2(1, 0);
	else if (cube->player.orientation == 'W')
		cube->player.transform.angle = atan2(0, -1);
		
	//printf("the angle of the player is %f\n", cube->player.transform.angle);
	update_player_direction(cube);
}
