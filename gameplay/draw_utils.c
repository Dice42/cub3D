/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:56 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/25 18:21:40 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


// void	param(t_transform *transform, int x1, int y1)
// {
// 	// transform->dx = fabs(x1 - transform->x0);
// 	// transform->dy = -fabs(y1 - transform->y0);
// 	if (transform->x0 < x1)
// 		transform->sx = 1;
// 	else
// 		transform->sx = -1;
// 	if (transform->y0 < y1)
// 		transform->sy = 1;
// 	else
// 		transform->sy = -1;
// 	transform->err = transform->dx + transform->dy;
// 	transform->x0 = x1;
// 	transform->y0 = y1;
// }

// void	bresenham(t_cub3d *cube, int x1, int y1)
// {
// 	t_transform	*transform;

// 	transform = &cube->player.transform;
// 	param(transform, x1, y1);
// 	while (1)
// 	{
// 		if ((int)transform->x0 < 600 && (int)transform->x0 > 0 &&
// 			(int)transform->y0 < 500 && (int)transform->y0 > 0)
// 			mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, transform->x0, transform->y0, 0xFFC251);
// 		if ((int)transform->x0 == x1 && (int)transform->y0 == y1)
// 			break;
// 		if ((2 * transform->err) >= transform->dy)
// 		{
// 			transform->err += transform->dy;
// 			transform->x0 += transform->sx;
// 		}
// 		if ((2 * transform->err) <= transform->dx)
// 		{
// 			transform->err += transform->dx;
// 			transform->y0 += transform->sy;
// 		}
// 	}
// }

// void	draw_direction_vector(t_cub3d *cube, int length)
// {
// 	int x1;
// 	int y1;

// 	x1 = cube->player.transform.x0 + length * cube->player.transform.dx;
// 	y1 = cube->player.transform.y0 + length * cube->player.transform.dy;
// 	bresenham(cube, x1, y1);
// }
