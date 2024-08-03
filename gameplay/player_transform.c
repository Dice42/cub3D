/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:14:24 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/03 15:51:43 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_player_direction(t_cub3d *cube)
{
	//printf("angle of the player is %f\n", cube->player.transform.angle);

	cube->player.transform.dx = cos(cube->player.transform.angle);
	cube->player.transform.dy = sin(cube->player.transform.angle);
}

void	move_player(t_cub3d *cube, int dir, bool is_vertical)
{
	float	speed;
	float	x;
	float	y;

	speed = 2;
	//printf("the angle of the player is %f\n", cube->player.transform.angle);
	update_player_direction(cube);
	x = cube->player.transform.x0;
	y = cube->player.transform.y0;
	if (is_vertical)
	{
		//printf("vertical\n");
		cube->player.transform.x0 -= dir * cube->player.transform.dx * speed;
		cube->player.transform.y0 -= dir * cube->player.transform.dy * speed;
	}
	else
	{
		cube->player.transform.x0 -= dir * cube->player.transform.dy * speed;
		cube->player.transform.y0 += dir * cube->player.transform.dx * speed;
	}
	if (!level_collision(cube, cube->player.transform.x0,
			cube->player.transform.y0, true))
	{
		cube->player.transform.x0 = x;
		cube->player.transform.y0 = y;
	}

	printf("player x is %f, player y is %f\n", cube->player.transform.x0, cube->player.transform.y0);
}
