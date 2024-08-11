/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:05:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/11 22:41:49 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player_pos(t_cub3d *cube, int x, int y)
{
	cube->player.transform.x0 = x * MINIMAP_X + 7;
	cube->player.transform.y0 = y * MINIMAP_Y + 7;
	if (cube->player.orientation == 'N')
		cube->player.transform.angle = (3 * PI) / 2;
	else if (cube->player.orientation == 'E')
		cube->player.transform.angle = atan2(0, 1);
	else if (cube->player.orientation == 'S')
		cube->player.transform.angle = atan2(1, 0);
	else if (cube->player.orientation == 'W')
		cube->player.transform.angle = atan2(0, -1);

	cube->player.transform.angle = 4.612390;
	cube->player.transform.x0 = 49.039989;
	cube->player.transform.y0 = 66.372009;
	update_player_direction(cube);
}
