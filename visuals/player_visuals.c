/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:39:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/12 16:01:45 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_line(t_cub3d *cube)
{
	int	i;

	i = 0;
	while (i < 20)
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
	while (ctr.i < 7)
	{
		ctr.j = 0;
		while (ctr.j < 7)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win,
				cube->player.transform.x0 + ctr.i,
				cube->player.transform.y0 + ctr.j, 0xFF0000);
			ctr.j ++;
		}
		ctr.i ++;
	}
}
