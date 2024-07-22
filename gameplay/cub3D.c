/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/22 16:32:17 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	handle_close_window(int key, t_cub3d *cube)
{
	if (key == ESC)
		close_window(cube);
	return (0);
}

int	handle_movement_keypress(int key, t_cub3d *cube)
{
	if (key == W || key == S
		|| key == D || key == A)
	{
		cube->player.move = true;
		//fill the array with whatever movement direction is added.
		//cube->player.move_dir = key;
		//player_movement(cube);
	}
	return (0);
}

int	handle_keyrelease(int key, t_cub3d *cube)
{
	if (key == W || key == S
		|| key == D || key == A)
		{
			//empty out the move_dir array
		}
		cube->player.move = false;
	if (key == LOOK_LEFT || key == LOOK_RIGHT)
		cube->player.rotate = false;
	//if no key is pressed: set move to false;
	return (0);
}

int	update(t_cub3d *cube)
{
	//draw player
	//draw_mini_map(cube);
	if (cube->player.move)
	{
		printf("SHOULD MOVE\n");
		//call player movement
		player_movement(cube);
	}
	draw_mini_map(cube);
	draw_player(cube);
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
			
//	cube->player.move = false;
	draw_mini_map(cube);
	//mlx_loop_hook(cube->data.mlx_ptr, &draw_mini_map, cube);
	mlx_hook(cube->data.win, 17, 0, &close_window, cube);
	mlx_hook(cube->data.win, 2, 0, &handle_movement_keypress, cube);
	mlx_key_hook(cube->data.win, &handle_keyrelease, cube);
	mlx_loop_hook(cube->data.mlx_ptr, &update, cube);
	mlx_loop(cube->data.mlx_ptr);
}