/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/30 12:59:24 by vtcsbza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	minimap_rays(t_cub3d *cube, int i)
{
	float	speed;
	float	ray_x;
	float	ray_y;
	float	dir_x;
	float	dir_y; 

	speed = 2;
	ray_x = cube->player.rays.rx;
	ray_y = cube->player.rays.ry;
	dir_x = cos(cube->player.rays.angle);
	dir_y = sin(cube->player.rays.angle);
	while (level_collision(cube, ray_x - 3, ray_y - 3, false))
	{
		//bresenham(cube, ray_x, ray_y);
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (level_collision(cube, ray_x, ray_y, false))
	{
		//bresenham(cube, ray_x, ray_y);
		 my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (level_collision(cube, ray_x, ray_y - 3, false))
	{
		//bresenham(cube, ray_x, ray_y);
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (level_collision(cube, ray_x - 3, ray_y, false))
	{
		//bresenham(cube, ray_x, ray_y);
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	cube->player.rays.rx1[i] = ray_x;
	cube->player.rays.ry1[i] = ray_y;
	printf("cube->player.rays.rx1[%d] = %f\n", i, cube->player.rays.rx1[i]);
	printf("cube->player.rays.ry1[%d] = %f\n", i, cube->player.rays.ry1[i]);
	//bresenham(cube, cube->player.rays.rx1[i], cube->player.rays.ry1[i]);
}

void	cast_rays_from_player(t_cub3d *cube)
{
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	cube->player.rays.angle = cube->player.transform.angle - (30.0 * RAD );
	cube->player.rays.angle_step = (60 * RAD) / 720;

	for (int i = 0; i < 720; i++)
	{
		minimap_rays(cube, i);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}