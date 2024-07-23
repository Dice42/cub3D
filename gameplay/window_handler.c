/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:53:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 21:25:58 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_cub3d	*cube)
{
	mlx_clear_window(cube->data.mlx_ptr, cube->data.win);
	mlx_destroy_window(cube->data.mlx_ptr, cube->data.win);
	//call cleanup and exit (0);
	exit(0);
	//exit_game(sl);
	return (0);
}