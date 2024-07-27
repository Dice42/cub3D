/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/27 15:30:44 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	cast_ray(t_cub3d *cube, float start_x, float start_y, float angle)
{
	float	ray_x = start_x + 7;
	float	ray_y = start_y + 7;
	float	dir_x = cos(angle);
	float	dir_y = sin(angle);
	float	speed = 0.2;

	while (player_collisions(cube, ray_x - 15, ray_y - 15))
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
	while (player_collisions(cube, ray_x, ray_y - 15))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	while (player_collisions(cube, ray_x - 15, ray_y))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
}

void	cast_rays_from_player(t_cub3d *cube)
{
	float	start_x = cube->player.transform.x0;
	float	start_y = cube->player.transform.y0;
	float	angle = cube->player.transform.angle - (45.0 * RAD ); 
	float	angle_step = (90 * RAD) / 30; // 40 degrees span divided by the number of rays

	printf("angle_step: %f\n", angle_step);
	for (int i = 0; i < 30; i++)
	{
		cast_ray(cube, start_x, start_y, angle);
		angle += angle_step;
	}
}