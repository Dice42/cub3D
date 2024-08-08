/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/08 19:22:10 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


// void draw_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, int color)
// {
//     int y;

//     if (start_y > end_y)
//     {
//         int temp = start_y;
//         start_y = end_y;
//         end_y = temp;
//     }

//     y = start_y;
//     while (y <= end_y)
//     {
//         my_mlx_pixel_put(&cube->data.img, x, y, color);
//         y++;
//     }
// }


// void	minimap_rays(t_cub3d *cube, int i)
// {
// 	float	speed;
// 	float	ray_x;
// 	float	ray_y;
// 	float	dir_x;
// 	float	dir_y; 
// 	float	distance;
// 	float	line_3d;
// 	int screen_center_x;
// 	int screen_center_y;
// 	int projected_x;

// 	speed = 2;
// 	ray_x = cube->player.rays.rx;
// 	ray_y = cube->player.rays.ry;
// 	dir_x = cos(cube->player.rays.angle);
// 	dir_y = sin(cube->player.rays.angle);
// 	while (level_collision(cube, ray_x, ray_y, false))
// 	{
// 		//bresenham(cube, ray_x, ray_y);
// 		my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
// 		ray_x += dir_x * speed;
// 		ray_y += dir_y * speed;
// 	}
// 	// while (level_collision(cube, ray_x, ray_y, false))
// 	// {
// 	// 	//bresenham(cube, ray_x, ray_y);
// 	// 	 my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
// 	// 	ray_x += dir_x * speed;
// 	// 	ray_y += dir_y * speed;
// 	// }
// 	// while (level_collision(cube, ray_x, ray_y - 3, false))
// 	// {
// 	// 	//bresenham(cube, ray_x, ray_y);
// 	// 	my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
// 	// 	ray_x += dir_x * speed;
// 	// 	ray_y += dir_y * speed;
// 	// }
// 	// while (level_collision(cube, ray_x - 3, ray_y, false))
// 	// {
// 	// 	//bresenham(cube, ray_x, ray_y);
// 	// 	my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
// 	// 	ray_x += dir_x * speed;
// 	// 	ray_y += dir_y * speed;
// 	// }
// 	cube->player.rays.rx1 = ray_x;
// 	cube->player.rays.ry1 = ray_y;
// 	distance = sqrt((pow(ray_x, 2) + pow(ray_y, 2)));
// 	printf("ray length from other way is : %f\n", distance);
// 	// my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
// 	line_3d = (64 * 1080) / distance;
// 	if (line_3d > 1080)
// 		line_3d = 1080;
// 	screen_center_x = WIDTH / 2;
// 	screen_center_y = HEIGHT / 2;
// //	projected_x = screen_center_x + (ray_x - cube->player.rays.rx);
// //    draw_vertical_line(cube, i + projected_x, screen_center_y, screen_center_y + distance, 0x00FF00);
// //	draw_vertical_line(cube, (i * 1920) / 1080, 1080 / 2, distance, 0x00FF00);
// 	//printf("distance is: %f\n", distance);
// //	printf("cube->player.rays.rx1[%d] = %f\n", i, cube->player.rays.rx1);
// //	printf("cube->player.rays.ry1[%d] = %f\n", i, cube->player.rays.ry1);
// 	//bresenham(cube, cube->player.rays.rx1[i], cube->player.rays.ry1[i]);
// }




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/05 14:34:07 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
// void	load_textures(t_cub3d *cube)
// {
// 	cube->data.textures[0].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
// 			cube->level.textures.north_texture,
// 			&cube->data.textures[0].bits_per_pixel,
// 			&cube->data.textures[0].line_length);
// 	cube->data.textures[1].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
// 			cube->level.textures.south_texture,
// 			&cube->data.textures[1].bits_per_pixel,
// 			&cube->data.textures[1].line_length);
// 	cube->data.textures[2].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
// 			cube->level.textures.east_texture,
// 			&cube->data.textures[2].bits_per_pixel,
// 			&cube->data.textures[2].line_length);
// 	cube->data.textures[3].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
// 			cube->level.textures.west_texture,
// 			&cube->data.textures[3].bits_per_pixel,
// 			&cube->data.textures[3].line_length);
// }
// int	get_texture_pixel(t_img_data *texture, int x, int y)
// {
// 	char	*data;
// 	int		pixel_index;

// 	data = mlx_get_data_addr(texture->img,
// 			&texture->bits_per_pixel,
// 			&texture->line_length, &texture->endian);
// 	pixel_index = (y * texture->line_length) + (x * (texture->bits_per_pixel / 8));
// 	return (*(int *)(data + pixel_index));
// }
void draw_textured_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, t_img_data *texture, float texture_x)
{
	int y;
	// float texture_height = texture->line_length / (texture->bits_per_pixel / 8);
	(void)texture_x;
	// if (start_y > end_y)
	// {
	// 	int temp = start_y;
	// 	start_y = end_y;
	// 	end_y = temp;
	// }
	y = start_y;
	while (y < end_y)
	{
		// int texture_y = (float)round((y - start_y) * (texture_height)) / (end_y - start_y);
		// if ((texture_y < 0) || (texture_y > texture_height) || texture_y > 1000)
		// 	break;
		// int color = get_texture_pixel(texture, texture_x, texture_y);
		my_mlx_pixel_put(&cube->data.img, x, y, cube->player.rays.clr);
		y++;
	}
}

void minimap_rays(t_cub3d *cube, int x, float distance)
{
	// float speed = 2.0;
	// float ray_x = cube->player.rays.rx; 
	// float ray_y = cube->player.rays.ry;
	// float dir_x = cos(cube->player.rays.angle);
	// float dir_y = sin(cube->player.rays.angle);

	// // Trace the ray until it hits a wall
	// while (level_collision(cube, ray_x, ray_y, false))
	// {
	// 	// my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
	// 	ray_x += dir_x * speed;
	// 	ray_y += dir_y * speed;
	// }
	// cube->player.rays.rx1 = ray_x - dir_x * speed;
	// cube->player.rays.ry1 = ray_y - dir_y * speed;
	// float distance = (cube->player.rays.rx1 + cube->player.rays.ry1) / 2;

	// // float distance = ray_y - cube->player.rays.ry1;
	// // float distance = ray_x - cube->player.rays.rx;
	// distance *= cos(cube->player.rays.angle);
	// printf("ray_x: %f, cube->player.rays.rx: %f\n", ray_x, cube->player.rays.rx);
	// printf("ray_y: %f, cube->player.rays.ry: %f\n", ray_y, cube->player.rays.ry);
	// printf
	// if (distance < 0.1f)
	// 	distance = 0.1;
	//printf("distance: %f\n", distance);
	float line_height_f = (8 * HEIGHT) / distance;
	int line_height = (int)round(line_height_f);
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	if (line_height < 1 && abs(line_height) < HEIGHT)
		line_height = HEIGHT;
	int screen_center_y = HEIGHT / 2;
	int line_start_y = (int)round(screen_center_y - (line_height / 2));
	int line_end_y = (int)round(screen_center_y + (line_height / 2));

	// t_img_data texture = choose_texture(cube, dir_x, dir_y);
	// float texture_x = cube->data.textures[0].line_length;
	draw_textured_vertical_line(cube, x, line_start_y, line_end_y, NULL, 0);
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
	cube->player.rays.angle_step = (float)(60 * RAD)/ WIDTH ;  // Adjust step based on screen width
	if (cube->player.rays.angle > (2 * PI))
		cube->player.rays.angle -= 2 * PI;
	else if (cube->player.rays.angle < 0)
		cube->player.rays.angle += 2 * PI;
	// load_textures(cube);
	for (int x = 0; x < WIDTH; x++)  // Loop through every pixel width
	{
		cube->player.rays.distance = cast_rays(cube);
		minimap_rays(cube, x, cube->player.rays.distance);
		cube->player.rays.angle += cube->player.rays.angle_step;
		draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, cube->player.rays.intersection_x, cube->player.rays.intersection_y, cube->player.rays.clr);
		if (cube->player.rays.angle > (2 * PI))
			cube->player.rays.angle -= 2 * PI;
		else if (cube->player.rays.angle < 0)
			cube->player.rays.angle += 2 * PI;
	}
}

