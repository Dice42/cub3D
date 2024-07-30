/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/30 20:46:00 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void draw_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, int color)
{
    int y;

    if (start_y > end_y)
    {
        int temp = start_y;
        start_y = end_y;
        end_y = temp;
    }

    y = start_y;
    while (y <= end_y)
    {
        my_mlx_pixel_put(&cube->data.img, x, y, color);
        y++;
    }
}


void	minimap_rays(t_cub3d *cube, int i)
{
	float	speed;
	float	ray_x;
	float	ray_y;
	float	dir_x;
	float	dir_y; 
	float	distance;
	float	line_3d;
	int screen_center_x;
	int screen_center_y;
	int projected_x;

	speed = 2;
	ray_x = cube->player.rays.rx;
	ray_y = cube->player.rays.ry;
	dir_x = cos(cube->player.rays.angle);
	dir_y = sin(cube->player.rays.angle);
	while (level_collision(cube, ray_x, ray_y, false))
	{
		//bresenham(cube, ray_x, ray_y);
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	// while (level_collision(cube, ray_x, ray_y, false))
	// {
	// 	//bresenham(cube, ray_x, ray_y);
	// 	 my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
	// 	ray_x += dir_x * speed;
	// 	ray_y += dir_y * speed;
	// }
	// while (level_collision(cube, ray_x, ray_y - 3, false))
	// {
	// 	//bresenham(cube, ray_x, ray_y);
	// 	my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
	// 	ray_x += dir_x * speed;
	// 	ray_y += dir_y * speed;
	// }
	// while (level_collision(cube, ray_x - 3, ray_y, false))
	// {
	// 	//bresenham(cube, ray_x, ray_y);
	// 	my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
	// 	ray_x += dir_x * speed;
	// 	ray_y += dir_y * speed;
	// }
	cube->player.rays.rx1[i] = ray_x;
	cube->player.rays.ry1[i] = ray_y;
	distance = sqrt((pow(ray_x, 2) + pow(ray_y, 2)));
	// my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
	line_3d = (64 * 1080) / distance;
	if (line_3d > 1080)
		line_3d = 1080;
	screen_center_x = WIDTH / 2;
	screen_center_y = HEIGHT / 2;
	projected_x = screen_center_x + (ray_x - cube->player.rays.rx);
//    draw_vertical_line(cube, i + projected_x, screen_center_y, screen_center_y + distance, 0x00FF00);
	draw_vertical_line(cube, (i * 1920) / 1080, 1080 / 2, distance, 0x00FF00);
	printf("distance is: %f\n", distance);
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
		cube->player.rays.dof = 0;
		cube->player.rays.verical_distance = 100000;
		minimap_rays(cube, i);
		//cast_ray(cube);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}