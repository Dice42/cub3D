/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/14 13:12:59 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_walls(t_cub3d *cube, int i, float distance)
{
	t_draw_wall	wall;

	init_draw_wall(&wall);
	distance = distance * cos(cube->player.rays.angle
			- cube->player.transform.angle);
	wall.height = (float)((MINIMAP_Y * HEIGHT) / distance);
	wall.offset = HEIGHT / 2 - (wall.height / 2);
	wall.end_y = wall.offset + wall.height;
	if (cube->player.rays.distance == cube->player.rays.vertical_distance)
		wall.texture_x = ((float)((int)cube->player.rays.point_y % MINIMAP_X)
				/ (float)(MINIMAP_X)) * cube->data.texture->width;
	if (cube->player.rays.distance == cube->player.rays.horizontal_distance)
		wall.texture_x = ((float)((int)cube->player.rays.point_x % MINIMAP_X)
				/ (float)(MINIMAP_X)) * cube->data.texture->width;
	wall.texture_y_step = (float)cube->data.texture->height / wall.height;
	while (wall.offset < wall.end_y)
	{
		wall.color = get_texture_pixel(cube->data.texture, (int)wall.texture_x,
				(int)wall.texture_y, cube);
		my_mlx_pixel_put(&cube->data.img, i, wall.offset, wall.color);
		wall.texture_y += wall.texture_y_step;
		wall.offset++;
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

	i = -1;
	cube->player.rays.rx = cube->player.transform.x0 + 3;
	cube->player.rays.ry = cube->player.transform.y0 + 3;
	if (cube->player.transform.angle == 1.5)
		cube->player.transform.angle = 1.55;
	cube->player.rays.angle = (cube->player.transform.angle - (30 * (M_PI
					/ 180.0f)));
	reset_angles(&cube->player.rays.angle);
	cube->player.rays.angle_step = (float)(60 * (M_PI / 180.0f)) / WIDTH;
	while (++i < WIDTH)
	{
		cube->player.rays.distance = cast_rays(cube);
		check_coordinate(cube);
		draw_walls(cube, i, cube->player.rays.distance);
		cube->player.rays.angle += cube->player.rays.angle_step;
		reset_angles(&cube->player.rays.angle);
	}
}
