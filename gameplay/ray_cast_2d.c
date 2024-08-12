/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:44:39 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/12 21:42:19 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void ray_cast_2d(t_cub3d *cube)
{
	float speed;
	float ray_x;
	float ray_y;
	float dir_x;
	float dir_y;

	speed = 2.0;
	ray_x = cube->player.rays.rx;
	ray_y = cube->player.rays.ry;
	dir_x = cos(cube->player.rays.angle);
	dir_y = sin(cube->player.rays.angle);
	while (level_collision(cube, ray_x, ray_y, false))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
}

void minimap_rays(t_cub3d *cube)
{
	int	i;

	i = -1;
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * RAD));
	cube->player.rays.angle_step = (float)(60 * RAD)/ 500 ;
	while (++i < 500)
	{
		ray_cast_2d(cube);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}
