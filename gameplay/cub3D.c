/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/20 15:28:30 by ssibai           ###   ########.fr       */
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

void	ft_start(t_cub3d *cube)
{
	printf("ENTERED\n");
	printf("from cube: columns num %d\n", cube->level.num_of_columns);
	
	cube->data.mlx_ptr = mlx_init();
	cube->data.win = mlx_new_window(cube->data.mlx_ptr, cube->level.num_of_columns * 64,
			cube->level.num_of_rows * 64, "Cube 3D");
	mlx_hook(cube->data.win, 2, 0, &handle_keypress, cube);
	mlx_hook(cube->data.win, 17, 0, &close_window, cube);
	mlx_loop(cube->data.mlx_ptr);
}