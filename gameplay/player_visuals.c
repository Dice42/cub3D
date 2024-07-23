/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:39:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 21:17:30 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_player(t_cub3d *cube)
{
	t_ctr ctr;

	init_ctrs(&ctr);
	while (ctr.i < 15)
	{
		ctr.j = 0;
		while (ctr.j < 15)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, cube->player.pos.x + ctr.i, cube->player.pos.y + ctr.j, 0xFF0000);
			ctr.j ++;
		}
		ctr.i ++;
	}
}


void	draw_horizental_vector(t_cub3d *cube)
{
	t_ctr ctr;
	int	x;
	int	y;

	if (cube->player.orientation == 'W')
		x = -10, y = 6;
	else if (cube->player.orientation == 'E')
		x = 15, y = 6;
	init_ctrs(&ctr);
	while (ctr.i < 10)
	{
		ctr.j = 0;
		while (ctr.j < 3)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, cube->player.pos.x + ctr.i + x, cube->player.pos.y + y + ctr.j, 0xFFC251);
			ctr.j ++;
		}
		ctr.i ++;
	}
}

void	draw_vertical_vector(t_cub3d *cube)
{
	t_ctr ctr;
	int	x;
	int	y;

	if (cube->player.orientation == 'N')
		y = -10, x = 6;
	else if (cube->player.orientation == 'S')
		y = 15, x = 6;
	init_ctrs(&ctr);
	while (ctr.i < 3)
	{
		ctr.j = 0;
		while (ctr.j < 10)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, cube->player.pos.x + ctr.i + x, cube->player.pos.y + y + ctr.j, 0xFFC251);
			ctr.j ++;
		}
		ctr.i ++;
	}
}

void	draw_forwad_vector(t_cub3d *cube)
{
	if (cube->player.orientation == 'W' || cube->player.orientation == 'E')
		draw_horizental_vector(cube);
	else if (cube->player.orientation == 'N' || cube->player.orientation == 'S')
		draw_vertical_vector(cube);
}

void	draw_eyes(t_cub3d *cube)
{
	t_ctr ctr;

	init_ctrs(&ctr);
	while (ctr.i < 3)
	{
		ctr.j = 0;
		while (ctr.j < 3)
		{
			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, cube->player.pos.x + 5 + ctr.i, cube->player.pos.y+ 4 + ctr.j, 0xFFC251);
			ctr.j ++;
		}
		ctr.i ++;
	}
}