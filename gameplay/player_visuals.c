/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:39:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/25 19:57:06 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_line(t_cub3d *cube)
{
	int	i;

	i = 0;
	while (i < 40)
	{
		mlx_pixel_put(cube->data.mlx_ptr, cube->data.win,
		((cube->player.transform.x0 + 7) + (cube->player.transform.dx * i)),
		((cube->player.transform.y0 + 7) + (cube->player.transform.dy * i)), 0xFF0000);
		i ++;
	}
}

void	draw_player(t_cub3d *cube)
{
	t_ctr ctr;

	init_ctrs(&ctr);
	while (ctr.i < 15)
	{
		ctr.j = 0;
		while (ctr.j < 15)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win,
					cube->player.transform.x0 + ctr.i,
					cube->player.transform.y0 + ctr.j, 0xFF0000);
			ctr.j ++;
		}
		ctr.i ++;
	}
}
