/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:14:24 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/24 10:26:47 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_move_direction(t_cub3d *cube)
{
	cube->player.transform.dx = cos(cube->player.transform.angle) * 5;
	cube->player.transform.dy = -sin(cube->player.transform.angle) * 5;
}

void	move_player(t_cub3d *cube, int dir, bool is_vertical)
{
	printf("moving\n");
	float	speed;

	speed = 1;
	update_move_direction(cube);
	if (is_vertical)
	{
		cube->player.transform.x_pos += dir * cube->player.transform.dx * speed;
		cube->player.transform.y_pos += dir * cube->player.transform.dy * speed;
	}
	else
	{
		cube->player.transform.x_pos += dir * cube->player.transform.dy * speed;
		cube->player.transform.y_pos -= dir * cube->player.transform.dx * speed;
	}
}
