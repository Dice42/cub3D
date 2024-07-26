/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/26 14:09:44 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	player_collisions(t_cub3d *cube, int x, int y)
{
	//check_left
	if ((x/64 >= 0 && y/64 >= 0))
		printf("map of ( %d, %d ) is %c \n", x/64, y/64, cube->level.map[x/64][y/64]);
	if ((x/64 >= 0 && y/64 >= 0))
	{
		if (cube->level.map[x/64][y/64] == '1')
		{
			printf("NOT SAFE\n");
			return (false);
		}
		else if (cube->level.map[x / 64][(y + 16)/64] == '1')
		{
			printf("NOT SAFE\n");
			return (false);
		}
		else if (cube->level.map[(x + 16) / 64][(y)/64] == '1')
		{
			printf("NOT SAFE\n");
			return (false);
		}
	}
	return (true);
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

void	player_rotation(t_cub3d *cube, bool rot_dir[2])
{
	if (rot_dir[0])
	{
		cube->player.transform.angle += 0.1;
		if (cube->player.transform.angle > 2 * PI)
			cube->player.transform.angle = 0;
	}
	if (rot_dir[1])
	{
		cube->player.transform.angle -= 0.1;
		if (cube->player.transform.angle < 0)
			cube->player.transform.angle = 2 * PI;
	}
	update_player_direction(cube);
}
