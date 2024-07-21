/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/21 18:54:23 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	handle_keypress(int key, t_cub3d *cube)
{
	if (key == ESC)
		close_window(cube);
	else
	{
		if (key == W || key == S
			|| key == D || key == A)
		{
			// player translation
		}
		// else if (key == LOOK_LEFT || key = LOOK_RIGHT)
		// {
		// 	//change rotation
		// }
	}
	return (0);
}

int	draw_map(t_cub3d *cube)
{
	int	x;
	int	y;

	y = 0;
	while (cube->level.map[y])
	{
		x = 0;
		while (cube->level.map[y][x])
		{
			if (cube->level.map[y][x] == '1')
				draw_cube(cube, x, y);
			else if (cube->level.map[y][x] == cube->player.rot)
				draw_player(cube, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->data.mlx_ptr, cube->data.win, 
		cube->data.img.img, 0, 0);
	return (0);
}


void	ft_start(t_cub3d *cube)
{
	int	height;
	int	width;

	height = cube->level.num_of_rows * 64;
	width = cube->level.num_of_columns * 64;

	cube->data.mlx_ptr = mlx_init();
	cube->data.win = mlx_new_window(cube->data.mlx_ptr, width, height, "Cube 3D");
	
	cube->data.img.img = mlx_new_image(cube->data.mlx_ptr, width, height);
	cube->data.img.addr = mlx_get_data_addr(cube->data.img.img,
			&cube->data.img.bits_per_pixel, 
			&cube->data.img.line_length, &cube->data.img.endian);
	// draw_map(cube);
	mlx_loop_hook(cube->data.mlx_ptr, &draw_map, cube);
	mlx_hook(cube->data.win, 2, 0, &handle_keypress, cube);
	mlx_hook(cube->data.win, 17, 0, &close_window, cube);
	mlx_loop(cube->data.mlx_ptr);
}