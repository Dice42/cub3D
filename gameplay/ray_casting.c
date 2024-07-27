/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/27 16:46:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	cast_ray(t_cub3d *cube, int i)
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
	while (player_collisions(cube, ray_x - 14, ray_y - 14))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (player_collisions(cube, ray_x, ray_y))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (player_collisions(cube, ray_x, ray_y - 14))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (player_collisions(cube, ray_x - 14, ray_y))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	cube->player.rays.rx1[i] = ray_x;
	cube->player.rays.ry1[i] = ray_y;
}

void	cast_rays_from_player(t_cub3d *cube)
{
	cube->player.rays.rx = cube->player.transform.x0 + 7;
	cube->player.rays.ry = cube->player.transform.y0 + 7;
	cube->player.rays.angle = cube->player.transform.angle - (45.0 * RAD );
	cube->player.rays.angle_step = (90 * RAD) / 1080;

	for (int i = 0; i < 1080; i++)
	{
		cast_ray(cube, i);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}