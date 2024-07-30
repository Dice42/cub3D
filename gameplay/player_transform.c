/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:14:24 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/30 12:55:07 by vtcsbza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_player_direction(t_cub3d *cube)
{
	cube->player.transform.dx = cos(cube->player.transform.angle);
	cube->player.transform.dy = sin(cube->player.transform.angle);
}

void	move_player(t_cub3d *cube, int dir, bool is_vertical)
{
	float	speed;
	float	x;
	float	y;

	speed = 2;
	update_player_direction(cube);
	x = cube->player.transform.x0;
	y = cube->player.transform.y0;
	if (is_vertical)
	{
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
}
