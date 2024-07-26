/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/26 20:58:56 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	cast_ray(t_cub3d *cube, float start_x, float start_y, float angle)
{
	float	ray_x = start_x;
	float	ray_y = start_y;
	float	dir_x = cos(angle * PI / 180);
	float	dir_y = sin(angle * PI / 180);
	float	speed = 1.1;

	printf("ray_x: %f, ray_y: %f\n", ray_x, ray_y);
	printf("ray_x: %f, ray_y: %f\n", start_x, start_y);
	while (player_collisions(cube, ray_x + 1, ray_y + 1))
	{
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
		// mlx_pixel_put(cube->data.mlx_ptr, cube->data.win, ray_x, ray_y, 0x00FF00);
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
	}
}

void	cast_rays_from_player(t_cub3d *cube)
{
	float	start_x = cube->player.transform.x0;
	float	start_y = cube->player.transform.y0;

	for (int i = 0; i < 360; i++)
	{
		float angle = i;
		cast_ray(cube, start_x, start_y, angle);
	}
}