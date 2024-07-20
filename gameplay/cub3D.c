/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:10:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/21 00:18:05 by mohammoh         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void	draw_map(t_cub3d *cube)
{
	int	x;
	int	y;

	cube->data.img.img = mlx_new_image(cube->data.mlx_ptr, 1920, 1080);
	cube->data.img.addr = mlx_get_data_addr(cube->data.img.img,
			&cube->data.img.bits_per_pixel, 
			&cube->data.img.line_length, &cube->data.img.endian);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH )
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(&cube->data.img, x, y, 0xFFFFFF);
			if (x < WIDTH - 1)
				my_mlx_pixel_put(&cube->data.img, x, y, 0x0000FF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->data.mlx_ptr, cube->data.win, 
		cube->data.img.img, 0, 0);
}


void	ft_start(t_cub3d *cube)
{
	printf("ENTERED\n");
	printf("from cube: columns num %d\n", cube->level.num_of_columns);
	
	cube->data.mlx_ptr = mlx_init();
	// cube->data.win = mlx_new_window(cube->data.mlx_ptr, cube->level.num_of_columns * 64,
	// 		cube->level.num_of_rows * 64, "Cube 3D");
	cube->data.win = mlx_new_window(cube->data.mlx_ptr, WIDTH, HEIGHT, "Cube 3D");
	draw_map(cube);
	mlx_hook(cube->data.win, 2, 0, &handle_keypress, cube);
	mlx_hook(cube->data.win, 17, 0, &close_window, cube);
	mlx_loop(cube->data.mlx_ptr);
}