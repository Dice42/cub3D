/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:18:00 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/05 18:18:02 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void draw_ray(t_cub3d *cube, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		if ((x0 >= 0 && x0 < cube->level.num_of_columns * MINIMAP_X)
			&&  (y0 >= 0 && y0 < cube->level.num_of_rows * MINIMAP_Y))
			my_mlx_pixel_put(&cube->data.img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
			err += dy, x0 += sx;
		if (e2 <= dx)
			err += dx, y0 += sy;
	}
}

float	calculate_vertical_distance(t_cub3d *cube, float *ray_dir)
{
	bool	subtract_mapsize;
	float	init_pos[2];
	float	step_x;
	float	step_y;

if (ray_dir[0] == 0)
	{
		if (ray_dir[1] > 0)
			init_pos[1] = ((int)(cube->player.rays.ry / MINIMAP_Y) + 1) * MINIMAP_Y;
		else
			init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
		init_pos[0] = cube->player.rays.rx;  // Vertical ray, so no x adjustment
		step_y = (ray_dir[1] > 0) ? MINIMAP_Y : -MINIMAP_Y;
		while (1)
		{
			int x = (int)(init_pos[0] / MINIMAP_X);
			int y = (int)(init_pos[1] / MINIMAP_Y);
			if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
			{
				if (cube->level.map[y][x] == '1')
				{
					draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
					return (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
				}
				else
					init_pos[1] += step_y;
			}
			else
				break;
		}
	}
	else
	{
		// Non-vertical rays
		init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
		if (ray_dir[0] > 0)
		{
		  //  printf("LOOKING RIGHT?\n");
			subtract_mapsize = false;
			init_pos[0] += MINIMAP_X;
		}
		else
		{
		   // printf("LOOKING LEFT??\n");
			subtract_mapsize = true;
			init_pos[0] -= MINIMAP_X;
		}

		init_pos[1] = cube->player.rays.ry + (init_pos[0] - cube->player.rays.rx) * (ray_dir[1] / ray_dir[0]);
		step_x = (ray_dir[0] > 0) ? MINIMAP_X : -MINIMAP_X;
		step_y = step_x * (ray_dir[1] / ray_dir[0]);
		while (1)
		{
			int x = (int)(init_pos[0] / MINIMAP_X);
			int y = (int)(init_pos[1] / MINIMAP_Y);

			if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
				if (cube->level.map[y][x] == '1') {
					if (subtract_mapsize)
					{
						draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0] + MINIMAP_X, (int)init_pos[1], 0X00FF00);
						return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]) + MINIMAP_X;
					}
					else
					{
						draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
						return (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
					}
					break;
				}
				else
				{
					init_pos[0] += step_x;
					init_pos[1] += step_y;
				}
			}
			else
				break;
		}
	}
	return (0);
}


float	calculate_horizontal_distance(t_cub3d *cube, float *ray_dir)
{
	bool	subtract_mapsize;
	float	init_pos[2];
	float	step_x;
	float	step_y;

	if (ray_dir[1] == 0)
	{
		if (ray_dir[0] > 0)
			init_pos[0] = ((int)(cube->player.rays.rx / MINIMAP_X) + 1) * MINIMAP_X;
		else
			init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
		init_pos[1] = cube->player.rays.ry;  // Horizontal ray, so no y adjustment
		step_x = (ray_dir[0] > 0) ? MINIMAP_X : -MINIMAP_X;
		while (1)
		{
			int x = (int)(init_pos[0] / MINIMAP_X);
			int y = (int)(init_pos[1] / MINIMAP_Y);
			if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) 
			{
				if (cube->level.map[y][x] == '1') 
				{
					draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
					return (init_pos[0] - cube->player.rays.rx) / ray_dir[0];
				} 
				else
				{
					init_pos[0] += step_x;
				}
			} 
			else
				break;
		}
	}
	else
	{
		// Non-horizontal rays
		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
		if (ray_dir[1] > 0)
		{
			//printf("LOOKING DOWN?\n");
			subtract_mapsize = false;
			init_pos[1] += MINIMAP_Y;
		}
		else
		{
		   // printf("LOOKING UP?\n");
			subtract_mapsize = true;
			init_pos[1] -= MINIMAP_Y;
		}
		init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry) * (ray_dir[0] / ray_dir[1]);
		step_y = (ray_dir[1] > 0) ? MINIMAP_Y : -MINIMAP_Y;
		step_x = step_y * (ray_dir[0] / ray_dir[1]);

		while (1) {
			int x = (int)(init_pos[0] / MINIMAP_X);
			int y = (int)(init_pos[1] / MINIMAP_Y);
			if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
				if (cube->level.map[y][x] == '1') {
					if (subtract_mapsize)
					{
						draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1] + MINIMAP_Y, 0X0000FF);
						return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]) - MINIMAP_Y;
					}
					else
					{
						draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
						return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]);
					}
					break;
				} else {
					init_pos[0] += step_x;
					init_pos[1] += step_y;
				}
			} else 
				break;
		}
	}
	return (0);
}

float cast_rays(t_cub3d *cube)
{
	float	angle;
	float	ray_dir[2];

	angle = cube->player.rays.angle + 0.001;
	ray_dir[0] = cos(angle);
	ray_dir[1] = sin(angle);
	cube->player.rays.verical_distance = calculate_vertical_distance(cube, &ray_dir[0]);
	cube->player.rays.horizontal_distance = calculate_horizontal_distance(cube, &ray_dir[0]);
	if (cube->player.rays.verical_distance == 0)
	{
		cube->player.rays.clr = 0X00FF00;
		return (cube->player.rays.horizontal_distance);
	}
	else if (cube->player.rays.horizontal_distance == 0)
	{
		cube->player.rays.clr = 0X0000FF;
		return (cube->player.rays.verical_distance);
	}
	else if (cube->player.rays.verical_distance > cube->player.rays.horizontal_distance) 
	{
		cube->player.rays.clr = 0X0000FF;
		return (cube->player.rays.horizontal_distance);
	} 
	cube->player.rays.clr = 0X00FF00;
	return (cube->player.rays.verical_distance);
}
