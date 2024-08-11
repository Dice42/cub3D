/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:56 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/11 19:47:11 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


// void	param(t_cub3d *cube, int x1, int y1)
// {
// 	cube->player.rays.dx = fabs(x1 - cube->player.rays.rx);
// 	cube->player.rays.dy = -fabs(y1 - cube->player.rays.ry);
// 	if (cube->player.rays.rx < x1)
// 		cube->player.rays.sx = 1;
// 	else
// 		cube->player.rays.sx = -1;
// 	if (cube->player.rays.ry < y1)
// 		cube->player.rays.sy = 1;
// 	else
// 		cube->player.rays.sy = -1;
// 	cube->player.rays.err = cube->player.rays.dx + cube->player.rays.dy;
// 	// cube->player.transform.x0 = x1;
// 	// cube->player.transform.y0 = y1;
// }

// void	bresenham(t_cub3d *cube, int x1, int y1)
// {
// 	//t_transform	*transform;
// 	// printf("sd");
// 	float ray_start_x = cube->player.rays.rx;
// 	float ray_start_y = cube->player.rays.ry;
// 	param(cube, x1, y1);
// //	printf("ray start is x %f and the end is x1 %d\n", ray_start_x, x1);
// //	printf("ray start is y %f and the end is y1 %d\n", ray_start_y, y1);
// 	//transform = &cube->player.transform;
// 	while (1)
// 	{
// 		if ((int)cube->player.rays.rx < 720 && (int)cube->player.rays.rx > 0 &&
// 			(int)cube->player.rays.ry < 420 && (int)cube->player.rays.ry > 0)
// 			my_mlx_pixel_put(&cube->data.img, ray_start_x, ray_start_y, 0x00FF00);
// 		if (ray_start_x  == x1 && ray_start_y == y1)
// 			break;
// 		if ((2 * cube->player.rays.err) >= cube->player.rays.dy)
// 		{
// 			cube->player.rays.err += cube->player.rays.dy;
// 			cube->player.rays.rx += cube->player.rays.sx;
// 		}
// 		if ((2 * cube->player.rays.err) <= cube->player.rays.dx)
// 		{
// 			cube->player.rays.err += cube->player.rays.dx;
// 			cube->player.rays.ry += cube->player.rays.sy;
// 		}
// 	}
// }

// void	draw_direction_vector(t_cub3d *cube, int length)
// {
// 	int x1;
// 	int y1;

// 	// x1 = cube->player.transform.x0 + length * cube->player.transform.dx;
// 	// y1 = cube->player.transform.y0 + length * cube->player.transform.dy;
// 	bresenham(cube, x1, y1);
// }


void draw_ray(t_cub3d *cube, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		if ((x0 >= 0 && x0 < cube->level.num_of_columns * MINIMAP_X)
			&&  (y0 >= 0 && y0 < cube->level.num_of_rows * MINIMAP_Y))
			my_mlx_pixel_put(&cube->data.img, x0, y0, color);
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
