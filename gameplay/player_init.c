/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:05:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/31 14:45:32 by vtcsbza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player_pos(t_cub3d *cube, int x, int y)
{
	cube->player.transform.x0 = x * MINIMAP_X + 7;
	cube->player.transform.y0 = y * MINIMAP_Y + 7;
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
