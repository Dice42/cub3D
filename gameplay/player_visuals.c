/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:39:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 12:32:24 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_player(t_cub3d *cube)
{
	t_ctr ctr;
	// printf("the x pos of the player is {%d} and the y is {%d} \n", cube->player.pos[0], cube->player.pos[1]);
	init_ctrs(&ctr);
	while (ctr.i < 15)
	{
		ctr.j = 0;
		while (ctr.j < 15)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, cube->player.pos[0] + ctr.i, cube->player.pos[1] + ctr.j, 0xFF0000);
			ctr.j ++;
		}
		ctr.i ++;
	}
}