/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:13 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/11 20:20:11 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"


void normalize_vector(float *vector)
{
	float magnitude;

	magnitude = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	if (magnitude > 0)
	{
		vector[0] /= magnitude;
		vector[1] /= magnitude;
	}
}

void	init_ray_dir(t_cub3d *cube, float *ray_dir)
{
	float	angle;

	angle = cube->player.rays.angle + 0.001;
	cube->player.rays.vertical_distance = 1000000;
	cube->player.rays.horizontal_distance = 1000000;
	ray_dir[0] = cos(angle);
	ray_dir[1] = sin(angle);
	normalize_vector(&ray_dir[0]);
}

float	find_smaller_distance(t_cub3d *cube)
{
	if (cube->player.rays.vertical_distance == 0)
	{
		cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
		cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
		cube->player.rays.clr = GREEN;
		return (cube->player.rays.horizontal_distance);
	}
	else if (cube->player.rays.horizontal_distance == 0)
	{
		cube->player.rays.clr = BLUE;
		cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
		cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
		return (cube->player.rays.vertical_distance);
	}
	if (cube->player.rays.vertical_distance > cube->player.rays.horizontal_distance)
	{
		cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
		cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
		cube->player.rays.clr = GREEN;
		return (cube->player.rays.horizontal_distance);
	}
	cube->player.rays.clr = BLUE;
	cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
	cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
	return (cube->player.rays.vertical_distance);
}

/**
 * @brief 		1) calculate the cos and sin of the angle (store in ray_dir)
 *				2) get horizontal intersection
 * 				3) get vertical intersection
 * 				4) calculate both lengths and return the shorter length
				if (horizontal > vertical)
					return vertical
				return horizontal
 * @param cube cube struct reference
 * @return float the shrtest ray length
 */
float	cast_rays(t_cub3d *cube)
{
	float	ray_dir[2];

	ft_bzero(&ray_dir[0], 2);
	printf("angle is: %f\n", (cube->player.transform.angle) / PI * 180 );
	init_ray_dir(cube, &ray_dir[0]);
	cube->player.rays.horizontal_distance =
		calc_horizontal_distance(cube, &ray_dir[0]);
	cube->player.rays.vertical_distance =
		calc_vertical_distance(cube, &ray_dir[0]);
	printf("horizontal distance: %f\n vertical distance%f\n",
		cube->player.rays.horizontal_distance, cube->player.rays.vertical_distance);
	return (find_smaller_distance(cube));
}
