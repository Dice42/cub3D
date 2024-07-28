/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:39:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/28 12:35:46 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_line(t_cub3d *cube)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		my_mlx_pixel_put(&cube->data.img,
			((cube->player.transform.x0 + 3) + (cube->player.transform.dx * i)),
			((cube->player.transform.y0 + 3) + (cube->player.transform.dy * i)),
			0xFF0000);
		i ++;
	}
}

void	draw_player(t_cub3d *cube)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	while (ctr.i < 6)
	{
		ctr.j = 0;
		while (ctr.j < 6)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win,
				cube->player.transform.x0 + ctr.i,
				cube->player.transform.y0 + ctr.j, 0xFF0000);
			ctr.j ++;
		}
		ctr.i ++;
	}
}

// void	draw_rays(t_cub3d *cube)
// {
// 	t_ctr	ctr;

// 	init_ctrs(&ctr);
// 	while (ctr.i < 30)
// 	{
// 		mlx_pixel_put(cube->data.mlx_ptr, cube->data.win,
// 			cube->transform.rays.x, cube->transform.rays.y, 0x00FF00);
// 		ctr.i ++;
// 	}
// }
