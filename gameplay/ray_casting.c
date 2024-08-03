/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/03 22:07:28 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void draw_textured_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, t_img_data *texture, float texture_x)
{
	int y;
	float texture_height = texture->line_length / (texture->bits_per_pixel / 4);
	(void)texture_x;
	if (start_y > end_y)
	{
		int temp = start_y;
		start_y = end_y;
		end_y = temp;
	}
	y = start_y;
	while (y < end_y)
	{
		int texture_y = (float)round((y - start_y) * (texture_height)) / (end_y - start_y);
		if ((texture_y < 0) || (texture_y > texture_height) || texture_y > 1020)
			break;
		int color = get_texture_pixel(texture, texture_x, texture_y);
		my_mlx_pixel_put(&cube->data.img, x, y, color);
		y++;
	}
}


void minimap_rays(t_cub3d *cube, int x)
{

	float speed = 2.0;
	float ray_x = cube->player.rays.rx; 
	float ray_y = cube->player.rays.ry;
	float dir_x = cos(cube->player.rays.angle);
	float dir_y = sin(cube->player.rays.angle);

	// Trace the ray until it hits a wall
	while (level_collision(cube, ray_x, ray_y, false))
	{
		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
		ray_x += dir_x * speed;
		ray_y += dir_y * speed;
	}
	cube->player.rays.rx1 = ray_x - dir_x * speed;
	cube->player.rays.ry1 = ray_y - dir_y * speed;
	float distance = (sqrt(pow(cube->player.rays.rx1, 2) + pow(cube->player.rays.ry1, 2)));

	// float distance = ray_y - cube->player.rays.ry1;
	// float distance = ray_x - cube->player.rays.rx;
	// distance *= cos(cube->player.rays.angle);
	// printf("ray_x: %f, cube->player.rays.rx: %f\n", ray_x, cube->player.rays.rx);
	// printf("ray_y: %f, cube->player.rays.ry: %f\n", ray_y, cube->player.rays.ry);
	// printf
	if (distance < EPSILON)
		distance = EPSILON;
	printf("distance: %f\n", distance);
	// printf("angle: %f\n", cube->player.rays.angle * (180 / PI));
	float line_height_f = (8 * HEIGHT) / distance;
	int line_height = (int)round(line_height_f);
	// printf("line_height: %d\n", line_height);
	if (line_height < MIN_HEIGHT || line_height > HEIGHT)
		line_height = (HEIGHT);
	int screen_center_y = HEIGHT / 2;
	int line_start_y = (int)round(screen_center_y - (line_height / 2));
	int line_end_y = (int)round(screen_center_y + (line_height / 2));

	// t_img_data texture = choose_texture(cube, dir_x, dir_y);
	float texture_x = (ray_x - (int)ray_x) * cube->data.textures[0].line_length;
	// printf("texture_x: %f\n", texture_x);
	// printf("line_start_y: %d, line_end_y: %d\n", line_start_y, line_end_y);
	// printf("--------------------\n");
	draw_textured_vertical_line(cube, x, line_start_y, line_end_y, &cube->data.textures[0], texture_x);
}

/**
 * @brief this function casts rays from the player 
 * 
 * @param cube 
 */
void cast_rays_from_player(t_cub3d *cube)
{
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * RAD));  // Start angle
	printf("angle: %f\n", cube->player.rays.angle * (180 / PI));
	cube->player.rays.angle_step = (float)(60 * RAD)/ WIDTH ;  // Adjust step based on screen width
	load_textures(cube);
	for (int x = 0; x < WIDTH; x++)  // Loop through every pixel width
	{
		// printf("x: %d\n", x);
		minimap_rays(cube, x);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}
