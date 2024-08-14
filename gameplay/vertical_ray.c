/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:51:32 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/14 13:09:20 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_vertical_ray(t_cub3d *cube, float *ray_dir, float *step,
		float *pos)
{
	if (ray_dir[0] > 0)
	{
		pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X
			+ MINIMAP_X;
		step[0] = MINIMAP_X;
	}
	else
	{
		pos[0] = ((int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X) - 0.0001;
		step[0] = -MINIMAP_X;
	}
	pos[1] = cube->player.rays.ry + (pos[0] - cube->player.rays.rx)
		* (ray_dir[1] / ray_dir[0]);
	step[1] = step[0] * (ray_dir[1] / ray_dir[0]);
}

/**
 * @brief Get the vertical intersection of the ray
 * @param cube cube struct reference
 * @param ray_dir
 */
bool	get_vertical_intersection(t_cub3d *cube, float *ray_dir, float *step,
		float *init_pos)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	init_vertical_ray(cube, ray_dir, step, init_pos);
	while (1)
	{
		ctr.x = (int)(init_pos[0] / MINIMAP_X);
		ctr.y = (int)(init_pos[1] / MINIMAP_Y);
		if ((ctr.x >= 0 && ctr.x < cube->level.num_of_columns) && (ctr.y >= 0
				&& ctr.y < cube->level.num_of_rows))
		{
			if (cube->level.map[ctr.y][ctr.x] == '1')
			{
				cube->player.rays.vertical_point_x = init_pos[0];
				cube->player.rays.vertical_point_y = init_pos[1];
				return (true);
			}
			init_pos[0] += step[0];
			init_pos[1] += step[1];
		}
		else
			break ;
	}
	return (false);
}

float	calc_vertical_distance(t_cub3d *cube, float *ray_dir)
{
	float	step[2];
	float	init_pos[2];
	float	distance;

	ft_bzero(&step, 2);
	ft_bzero(&init_pos, 2);
	if (ray_dir[0] == 0)
		return (0);
	if (!get_vertical_intersection(cube, ray_dir, &step[0], &init_pos[0]))
		return (0);
	distance = (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
	return (distance);
}
