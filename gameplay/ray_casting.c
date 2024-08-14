/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/14 10:41:09 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void draw_walls(t_cub3d *cube, int x, float dist)
{
	t_wall wall;
	int		color;

	dist = dist * cos(cube->player.rays.angle - cube->player.transform.angle);
	wall.height = (float)(((MINIMAP_Y / 2) * HEIGHT) / dist);
	wall.texture_y = 0.0f;
	cube->player.rays.line_offset = HEIGHT / 2 - (wall.height / 2);
	wall.end_y = cube->player.rays.line_offset + wall.height;
	wall.start_y = cube->player.rays.line_offset;
	if (cube->player.rays.distance == cube->player.rays.vertical_distance)
		wall.texture_x1 = ((float)((int)cube->player.rays.intersection_y % 21)
			/ (float)(21)) * cube->data.texture->width;
	if (cube->player.rays.distance == cube->player.rays.horizontal_distance)
		wall.texture_x1 = ((float)((int)cube->player.rays.intersection_x % 21)
			/ (float)(21)) * cube->data.texture->width;
	wall.texture_y_step =  (float)cube->data.texture->height / wall.height;
	while (wall.start_y < wall.end_y)
	{
		color = get_texture_pixel(cube->data.texture, (int)wall.texture_x1,
			(int)wall.texture_y, cube);
		my_mlx_pixel_put(&cube->data.img, x, wall.start_y, color);
		wall.texture_y += wall.texture_y_step;
		wall.start_y++;
	}
}

void	reset_angles(float *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
}

/**
 * @brief this function casts rays from the player 
 * 
 * @param cube 
 */
void draw_3d_rays(t_cub3d *cube)
{
	int	i;

	i = 0;
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	if (cube->player.transform.angle == 1.5)
		cube->player.transform.angle = 1.55;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * RAD));
	reset_angles(&cube->player.rays.angle);
	cube->player.rays.angle_step = (float)(60 * RAD)/ WIDTH ;
	while (++i < WIDTH)
	{
		cube->player.rays.distance = cast_rays(cube);
		check_coordinate(cube);
		draw_walls(cube, i, cube->player.rays.distance);
		draw_ray(cube, cube->player.rays.rx, cube->player.rays.ry,
			cube->player.rays.intersection_x, cube->player.rays.intersection_y,
			cube->player.rays.clr);
		cube->player.rays.angle += cube->player.rays.angle_step;
		reset_angles(&cube->player.rays.angle);
	}
}

