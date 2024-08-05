/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/02 16:19:21 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	update(t_cub3d *cube)
{
	if (cube->player.move || cube->player.rotate)
	{
		mlx_destroy_image(cube->data.mlx_ptr, cube->data.img.img);
		player_movement(cube, cube->player.move_dir);
		player_rotation(cube, cube->player.rot_dir);
		draw_mini_map(cube);
	}
	draw_player(cube);
	return (0);
}

void	ft_start(t_cub3d *cube)
{
	cube->data.mlx_ptr = mlx_init();
	cube->data.win = mlx_new_window(cube->data.mlx_ptr, WIDTH, HEIGHT, "Cube 3D");
	draw_mini_map(cube);
	cube->level.start = true;
	mlx_hook(cube->data.win, 2, 0, &handle_keypress, cube);
	mlx_hook(cube->data.win, 3, 1L<<1, &handle_keyrelease, cube);
	mlx_loop_hook(cube->data.mlx_ptr, &update, cube);
	mlx_loop(cube->data.mlx_ptr);
}
