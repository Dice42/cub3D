/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:14:24 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/25 18:19:42 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_move_direction(t_cub3d *cube)
{
	cube->player.transform.dx = cos(cube->player.transform.angle);
	cube->player.transform.dy = sin(cube->player.transform.angle);
}

void	move_player(t_cub3d *cube, int dir, bool is_vertical)
{
	float	speed;

	speed = 2;
	update_move_direction(cube);
	if (cube->player.orientation == 'N' && cube->player.orientation == 'S')
	{
		if (is_vertical)
		{
			cube->player.transform.x0 += dir * cube->player.transform.dx * speed;
			cube->player.transform.y0 += dir * cube->player.transform.dy * speed;
		}
		else
		{
			cube->player.transform.x0 += dir * cube->player.transform.dy * speed;
			cube->player.transform.y0 -= dir * cube->player.transform.dx * speed;
		}
	}
	else
	{
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
	}
}
