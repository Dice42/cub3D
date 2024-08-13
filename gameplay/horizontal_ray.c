/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:15:46 by ssibai            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/08/13 23:16:06 by mohammoh         ###   ########.fr       */
=======
/*   Updated: 2024/08/13 23:13:06 by ssibai           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_horizontal_ray(t_cub3d *cube, float *ray_dir, float *step,
		float *init_pos)
{
	if (ray_dir[1] > 0)
	{
		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y
			+ MINIMAP_Y;
		step[1] = MINIMAP_Y;
	}
	else
	{
		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y
			- 0.0001;
		step[1] = -MINIMAP_Y;
	}
	init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry)
		* (ray_dir[0] / ray_dir[1]);
	step[0] = step[1] * (ray_dir[0] / ray_dir[1]);
}

/**
 * @brief Get the horizontal intersection of the ray
 * @param cube cube struct reference
 * @param ray_dir ray_dir[0]: cos(angle) ray_dir[1]: sin(angle)
 */
bool	get_horizontal_intersection(t_cub3d *cube, float *ray_dir, float *step,
		float *init_pos)
{
	t_ctr	ctr;

	init_ctrs(&ctr);
	init_horizontal_ray(cube, ray_dir, step, init_pos);
	while ((ctr.x >= 0 && ctr.x < cube->level.num_of_columns) && (ctr.y >= 0
			&& ctr.y < cube->level.num_of_rows))
	{
		ctr.x = (int)(init_pos[0] / MINIMAP_X);
		ctr.y = (int)(init_pos[1] / MINIMAP_Y);
		if ((ctr.x >= 0 && ctr.x < cube->level.num_of_columns) && (ctr.y >= 0
				&& ctr.y < cube->level.num_of_rows))
		{
			if (cube->level.map[ctr.y][ctr.x] == '1')
			{
				cube->player.rays.horizontal_point_x = init_pos[0];
				cube->player.rays.horizontal_point_y = init_pos[1];
				return (true);
			}
			init_pos[0] += step[0];
			init_pos[1] += step[1];
		}
		else
			break;
	}
	return (false);
}

float	calc_horizontal_distance(t_cub3d *cube, float *ray_dir)
{
	float	step[2];
	float	init_pos[2];
	float	distance;

	ft_bzero(&step, 2);
	ft_bzero(&init_pos, 2);
	if (ray_dir[1] == 0)
		return (0);
	if (!get_horizontal_intersection(cube, ray_dir, &step[0], &init_pos[0]))
		return (0);
	distance = ((init_pos[0] - cube->player.rays.rx) / ray_dir[0]);
	return (distance);
}
