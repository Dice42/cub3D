/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/26 12:43:48 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
