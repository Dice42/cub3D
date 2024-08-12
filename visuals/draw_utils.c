/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:56 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/12 17:04:46 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void draw_ray(t_cub3d *cube, int x0, int y0, int x1, int y1, int color)
{
	(void)cube;
	(void)color;
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		// if ((x0 >= 0 && x0 < cube->level.num_of_columns * MINIMAP_X)
		// 	&&  (y0 >= 0 && y0 < cube->level.num_of_rows * MINIMAP_Y))
		// 	my_mlx_pixel_put(&cube->data.img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
