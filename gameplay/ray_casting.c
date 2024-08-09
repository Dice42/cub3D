/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:37:10 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/09 12:39:35 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void draw_textured_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, t_img_data *texture, float line_height)
{
	int y;
	float texture_y = 0.0f;
	// float texture_height = texture->line_length / (texture->bits_per_pixel / 8);
	// (void)texture_x;
	// if (start_y > end_y)
	// {
	// 	int temp = start_y;
	// 	start_y = end_y;
	// 	end_y = temp;
	// }
	int texture_x1;
	if (cube->player.rays.distance == cube->player.rays.vertical_distance)
	{
		printf("cube->player.rays.vertical_distance = %f\n", cube->player.rays.vertical_distance);
		printf("cube->player.rays.intersection_y = %f\n", cube->player.rays.intersection_y);
		printf("cube->player.rays.distance = %f\n", cube->player.rays.distance);
		printf("cube->data.texture = %p\n", cube->data.texture);
		printf("cube->data.texture->width = %d\n", cube->data.texture->width);
		texture_x1 = ((float)((int)cube->player.rays.intersection_y % MAP_X) / (float)(MAP_X)) * cube->data.texture->width;
	}
	if (cube->player.rays.distance == cube->player.rays.horizontal_distance)
		texture_x1 = ((float)((int)cube->player.rays.intersection_x % MAP_X) / (float)(MAP_X)) * cube->data.texture->width;
				
	float texture_y_step =  (float)cube->data.texture->height / line_height;
	y = start_y;
	while (y < end_y)
	{
		// int texture_y = (float)round((y - start_y) * (texture_height)) / (end_y - start_y);
		// if ((texture_y < 0) || (texture_y > texture_height) || texture_y > 1000)
		// 	break;
		int color = get_texture_pixel(cube->data.texture, texture_x1, (int)texture_y, cube);
		my_mlx_pixel_put(&cube->data.img, x, y, color);
		texture_y += texture_y_step;
		y++;
	}
}

// void	wall_height_cal(t_data *data, t_raycast *ray)
// {
// 	ray->line_height = (data->pixel_y / 2 * HEIGHT) / ray->final_dist;
// 	if (ray->line_height > HEIGHT)
// 		ray->line_height = HEIGHT;
// 	ray->line_offset = HEIGHT / 2 - (ray->line_height / 2);
// }

// void	fisheye_correction(t_data *data, t_raycast *ray)
// {
// 	ray->ca = data->player.angle - ray->angle;
// 	if (ray->ca < 0)
// 		ray->ca += 360;
// 	if (ray->ca > 360)
// 		ray->ca -= 360;
// 	ray->final_dist = ray->final_dist * cos(deg_to_rad(ray->ca));
// }

void minimap_rays(t_cub3d *cube, int x, float distance)
{
	printf("distance: %f\n", distance);
	distance = distance * cos(cube->player.rays.angle - cube->player.transform.angle);
	printf("MINIMAP_X: %d\n", MAP_X * 2);
	printf("MAP_Y: %d\n", MAP_Y * 2);
	// float line_height_f = (MINIMAP_Y / 2 * HEIGHT) / distance;
	float line_height = (float)(((MAP_Y / 2) * HEIGHT) / distance);
	// int line_height = (int)round(line_height_f);
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	cube->player.rays.line_offset = HEIGHT / 2 - (line_height / 2);
	// if (line_height < 1 && abs(line_height) < HEIGHT)
	// 	line_height = HEIGHT;
	// int screen_center_y = HEIGHT / 2;
	float line_end_y = cube->player.rays.line_offset + line_height;
	float line_start_y = cube->player.rays.line_offset;
	// printf("line_end_y: %f\n", line_end_y);
	// printf("line_start_y: %f\n", line_start_y);
	cube->data.texture = check_coordinate(cube);
	
	// int texture_x = 0;
	// if (cube->player.rays.distance == cube->player.rays.vertical_distance)
	// 	texture_x = ((double)((int)cube->player.rays.vertical_intersection_y % line_height) / (double)(line_height)) * cube->level.num_of_rows;
	// if (cube->player.rays.distance == cube->player.rays.horizontal_distance)
	// 	texture_x = ((double)((int)cube->player.rays.vertical_intersection_x % line_height) / (double)(line_height)) * cube->level.num_of_rows;
	
	draw_textured_vertical_line(cube, x, line_start_y, line_end_y, NULL, line_height);
}

/**
 * @brief this function casts rays from the player 
 * 
 * @param cube 
 */
void cast_rays_from_player(t_cub3d *cube)
{
	// cube->data.texture = ft_calloc(1, sizeof(t_img_data));
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * RAD));  // Start angle
	cube->player.rays.angle_step = (float)(60 * RAD)/ WIDTH ;  // Adjust step based on screen width
	load_textures(cube);
	for (int x = WIDTH; x > 0; x--) 
	{
		cube->player.rays.distance = cast_rays(cube);
		printf("horizontal distance is %f\n",cube->player.rays.horizontal_distance);
		printf("vertical distance is %f\n",cube->player.rays.vertical_distance);
		printf("distance is %f\n",cube->player.rays.distance);
		printf("cube->player.rays.intersection_y is %f\n",cube->player.rays.intersection_y);
		printf("cube->player.rays.intersection_x is %f\n",cube->player.rays.intersection_x);
		minimap_rays(cube, x, cube->player.rays.distance);
		cube->player.rays.angle += cube->player.rays.angle_step;
	}
}

