/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:14:24 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/24 14:58:06 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_move_direction(t_cub3d *cube)
{
	// printf("dx before is: %f\n", cube->player.transform.dx);
	// printf("dy before is: %f\n", cube->player.transform.dy);
	cube->player.transform.dx = cos(cube->player.transform.angle);
	cube->player.transform.dy = sin(cube->player.transform.angle);
	printf("dx after is: %f\n", cube->player.transform.dx);
	printf("dy after is: %f\n", cube->player.transform.dy);
}

void	move_player(t_cub3d *cube, int dir, bool is_vertical)
{
	float	speed;

	speed = 2;
	update_move_direction(cube);
	if (cube->player.orientation == 'N' || cube->player.orientation == 'S')
	{
		if (is_vertical)
		{
			printf("dir = %d\n", dir);
			const float x_val = cube->player.transform.dx * speed * dir;
			const float y_val = cube->player.transform.dy * speed * dir;
			printf("x_val = {%f}\n", x_val);
			printf("y_val = {%f}\n", y_val);
			cube->player.transform.x_pos +=  x_val;
			cube->player.transform.y_pos += y_val;
			printf("( %f, %f )\n", cube->player.transform.x_pos, cube->player.transform.y_pos);
		}
		else
		{
			cube->player.transform.x_pos += dir * cube->player.transform.dy * speed;
			cube->player.transform.y_pos -= dir * cube->player.transform.dx * speed;
		}
	}
	else
	{
		if (is_vertical)
		{
			cube->player.transform.x_pos -= dir * cube->player.transform.dx * speed;
			cube->player.transform.y_pos -= dir * cube->player.transform.dy * speed;
		}
		else
		{
			cube->player.transform.x_pos -= dir * cube->player.transform.dy * speed;
			cube->player.transform.y_pos += dir * cube->player.transform.dx * speed;
		}
	}
}
