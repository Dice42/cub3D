/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:53:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/14 11:23:06 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_cub3d *cube)
{
	int	i;

	i = 0;
	if (cube->data.img.img)
		mlx_destroy_image(cube->data.mlx_ptr, cube->data.img.img);
	while (i < 4)
	{
		if (cube->data.textures[i].img)
			mlx_destroy_image(cube->data.mlx_ptr, cube->data.textures[i].img);
		i++;
	}
	mlx_clear_window(cube->data.mlx_ptr, cube->data.win);
	mlx_destroy_window(cube->data.mlx_ptr, cube->data.win);
	exit(0);
	return (0);
}

void	init_mlx_img(t_cub3d *cube)
{
	cube->data.img.img = mlx_new_image(cube->data.mlx_ptr, WIDTH, HEIGHT);
	cube->data.img.addr = mlx_get_data_addr(cube->data.img.img,
			&cube->data.img.bits_per_pixel, &cube->data.img.line_length,
			&cube->data.img.endian);
}
