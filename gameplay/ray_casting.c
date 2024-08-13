/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 22:10:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_rays(t_cub3d *cube, int i, float distance)
{
	t_draw_line	line;

	init_draw_line(&line);
	distance = distance * cos(cube->player.rays.angle
			- cube->player.transform.angle);
	line.height = (float)(((MINIMAP_Y / 2) * HEIGHT) / distance);
	line.offset = HEIGHT / 2 - (line.height / 2);
	line.end_y = line.offset + line.height;
	if (cube->player.rays.distance == cube->player.rays.vertical_distance)
		line.texture_x = ((float)((int)cube->player.rays.intersection_y
					% MINIMAP_X) / (float)(MINIMAP_X))
			* cube->data.texture->width;
	if (cube->player.rays.distance == cube->player.rays.horizontal_distance)
		line.texture_x = ((float)((int)cube->player.rays.intersection_x
					% MINIMAP_X) / (float)(MINIMAP_X))
			* cube->data.texture->width;
	line.texture_y_step = (float)cube->data.texture->height / line.height;
	while (line.offset < line.end_y)
	{
		line.color = get_texture_pixel(cube->data.texture, (int)line.texture_x,
				(int)line.texture_y, cube);
		my_mlx_pixel_put(&cube->data.img, i, line.offset, line.color);
		line.texture_y += line.texture_y_step;
		line.offset++;
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
void	draw_3d_rays(t_cub3d *cube)
{
	int	i;

	i = 0;
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	if (cube->player.transform.angle == 1.5)
		cube->player.transform.angle = 1.55;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * RAD));
	reset_angles(&cube->player.rays.angle);
	cube->player.rays.angle_step = (float)(60 * RAD) / WIDTH;
	while (++i < WIDTH)
	{
		cube->player.rays.distance = cast_rays(cube);
		check_coordinate(cube);
		draw_rays(cube, i, cube->player.rays.distance);
		draw_ray(cube, cube->player.rays.rx, cube->player.rays.ry,
			cube->player.rays.intersection_x, cube->player.rays.intersection_y,
			cube->player.rays.clr);
		cube->player.rays.angle += cube->player.rays.angle_step;
		reset_angles(&cube->player.rays.angle);
	}
}
