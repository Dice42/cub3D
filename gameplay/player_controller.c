/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/25 17:57:18 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_direction(int dr)
{
	if (dr == D)
		return (0);
	else if (dr == W)
		return (1);
	else if (dr == A)
		return (2);
	else if (dr == S)
		return (3);
	return (-1);
}

void	player_movement(t_cub3d *cube, bool dir[4])
{
	if (dir[0])
		move_player(cube, 1, false);
	if (dir[1])
		move_player(cube, -1, true);
	if (dir[2])
		move_player(cube, -1, false);
	if (dir[3])
		move_player(cube, 1, true);
}

void	player_rotation(t_cub3d *cube, int rot_dir)
{
	if (rot_dir == 1)
	{
		cube->player.transform.angle += 0.1;
		if (cube->player.transform.angle > 2 * PI)
			cube->player.transform.angle = 0;
	}
	else if (rot_dir == -1)
	{
		cube->player.transform.angle -= 0.1;
		if (cube->player.transform.angle < 0)
			cube->player.transform.angle = 2 * PI;
	}
	cube->player.transform.dx = cos(cube->player.transform.angle);
	cube->player.transform.dy = sin(cube->player.transform.angle);
	cube->player.rotate = true;
}
