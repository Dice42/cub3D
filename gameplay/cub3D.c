/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/26 11:37:59 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	set_keys_setting(t_cub3d *cube, int key, bool setting)
{
	if (key == D)
		cube->player.move_dir[0] = setting;
	if (key == W)
		cube->player.move_dir[1] = setting;
	if (key == A)
		cube->player.move_dir[2] = setting;
	if (key == S)
		cube->player.move_dir[3] = setting;
	if (key == LOOK_RIGHT)
		cube->player.rot_dir[0] = setting;
	if (key == LOOK_LEFT)
		cube->player.rot_dir[1] = setting;
}


int	handle_keypress(int key, t_cub3d *cube)
{
	if (key == ESC)
		close_window(cube);
	set_keys_setting(cube, key, true);
	if (key == W || key == S || key == D || key == A)
		cube->player.move = true;
	if (key == LOOK_RIGHT || key == LOOK_LEFT)
		cube->player.rotate = true;
	return (0);
}

int	handle_keyrelease(int key, t_cub3d *cube)
{
	set_keys_setting(cube, key, false);
	if (!cube->player.move_dir[0] && !cube->player.move_dir[1]
		&& !cube->player.move_dir[2] && !cube->player.move_dir[3])
		cube->player.move = false;
	if (!cube->player.rot_dir[0] && !cube->player.rot_dir[0])
		cube->player.rotate = false;
	return (0);
}

int	update(t_cub3d *cube)
{
	if (cube->player.move || cube->player.rotate)
	{
		player_movement(cube, cube->player.move_dir);
		player_rotation(cube, cube->player.rot_dir);
		mlx_clear_window(cube->data.mlx_ptr, cube->data.win);
		draw_mini_map(cube);
		draw_line(cube);
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
	draw_line(cube);
	cube->level.start = true;
	mlx_hook(cube->data.win, 2, 0, &handle_keypress, cube);
	mlx_hook(cube->data.win, 3, 1L<<1, &handle_keyrelease, cube);
	mlx_loop_hook(cube->data.mlx_ptr, &update, cube);
	mlx_loop(cube->data.mlx_ptr);
}
