// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ray_casting.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
// /*   Updated: 2024/07/30 18:32:53 by mohammoh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

void minimap_rays(t_cub3d *cube, int i)
{
	float speed;
	float ray_x;
	float ray_y;
	float dir_x;
	float dir_y;
	float distance;
	float line_height;

	speed = 2;
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

	cube->player.rays.rx1[i] = ray_x;
	cube->player.rays.ry1[i] = ray_y;

	// Calculate the distance from the player to the wall
	distance = sqrt(pow(ray_x - cube->player.rays.rx, 2) + pow(ray_y - cube->player.rays.ry, 2));
	if (distance == 0)
		distance = 1;
	line_height = ( 3.5 * HEIGHT) / distance;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	// int screen_center_x = WIDTH / 2;
	int screen_center_y = HEIGHT / 2;

	// Determine the starting and ending y-coordinates for the vertical line
	int line_start_y = screen_center_y - line_height / 2;
	int line_end_y = screen_center_y + line_height / 2;
		int x = (i * WIDTH) / 720;
	// Draw the vertical line on the main screen
	draw_vertical_line(cube, x, line_start_y, line_end_y, 0x00FF00);

	printf("Distance: %f\n", distance);
	printf("Line Height: %f\n", line_height);
	printf("cube->player.rays.rx1[%d] = %f\n", i, cube->player.rays.rx1[i]);
	printf("cube->player.rays.ry1[%d] = %f\n", i, cube->player.rays.ry1[i]);
}

void cast_rays_from_player(t_cub3d *cube)
{
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	cube->player.rays.angle = cube->player.transform.angle - (30.0 * RAD);
	cube->player.rays.angle_step = (60 * RAD) / 720;

	for (int i = 0; i < 720; i++)
	{
		minimap_rays(cube, i);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}
