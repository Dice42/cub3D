/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 13:51:57 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	handle_keypress(int key, t_cub3d *cube)
{
	if (key == ESC)
		close_window(cube);
	if (key == W || key == S
		|| key == D || key == A)
	{
		if (key == D)
			cube->player.move_dir[0] = true;
		if (key == W)
			cube->player.move_dir[1] = true;
		if (key == A)
			cube->player.move_dir[2] = true;
		if (key == S)
			cube->player.move_dir[3] = true;
		cube->player.move = true;
	}
	return (0);
}

int	handle_keyrelease(int key, t_cub3d *cube)
{
	int	i;

	i = 0;
	if (key == W || key == S
		|| key == D || key == A)
		{
			if (key == D)
				cube->player.move_dir[0] = false;
			if (key == W)
				cube->player.move_dir[1] = false;
			if (key == A)
				cube->player.move_dir[2] = false;
			if (key == S)
				cube->player.move_dir[3] = false;
			while (i < 4)
			{
				if (!cube->player.move_dir[i])
					i++;
				break;
			}
			if (i == 4)
				cube->player.move = false;
		}
	if (key == LOOK_LEFT || key == LOOK_RIGHT)
		cube->player.rotate = false;
	return (0);
}

int	update(t_cub3d *cube)
{
	if (cube->player.move)
	{
		player_movement(cube, cube->player.move_dir);
		mlx_clear_window(cube->data.mlx_ptr, cube->data.win);
		draw_mini_map(cube);
	}
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

	draw_mini_map(cube);
	cube->level.start = true;
	init_draw_player(cube, cube->player.pos[0] - 32, cube->player.pos[1] - 32);
	//draw_player(cube);
	//mlx_loop_hook(cube->data.mlx_ptr, &draw_mini_map, cube);
	// printf("the x pos of the player is {%d} and the y is {%d} \n", cube->player.pos[0], cube->player.pos[1]);
	mlx_hook(cube->data.win, 2, 0, &handle_keypress, cube);
	mlx_hook(cube->data.win, 3, 1L<<1, &handle_keyrelease, cube);
	mlx_loop_hook(cube->data.mlx_ptr, &update, cube);
	
	mlx_loop(cube->data.mlx_ptr);
}