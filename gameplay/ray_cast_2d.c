/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:44:39 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/04 15:44:57 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void ray_cast_2d(t_cub3d *cube)
{
	float speed = 2.0;
	float ray_x = cube->player.rays.rx;
	float ray_y = cube->player.rays.ry;
	float dir_x = cos(cube->player.rays.angle);
	float dir_y = sin(cube->player.rays.angle);

	while (level_collision(cube, ray_x, ray_y, false))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
}

void minimap_rays(t_cub3d *cube)
{
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * RAD));
	cube->player.rays.angle_step = (float)(60 * RAD)/ MINIMAP_X ;
	for (int x = 0; x < MINIMAP_X; x++)
	{
		ray_cast_2d(cube);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}
