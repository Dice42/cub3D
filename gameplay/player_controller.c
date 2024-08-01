/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/01 12:04:39 by vtcsbza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// bool	level_collisions(t_cub3d *cube, int x, int y, bool	player_collision)
// {
// 	int	length_buff;

// 	if (player_collision)
// 		length_buff = 6;
// 	else
// 		length_buff = 
// 	if ((x / MINIMAP_X >= 0 && y / MINIMAP_Y >= 0))
// 	{
// 		if (cube->level.map[y / MINIMAP_Y][x / MINIMAP_X] == '1')
// 			return (false);
// 		else if (cube->level.map[y / MINIMAP_Y][(x + 6) / MINIMAP_X] == '1')
// 			return (false);
// 		else if (cube->level.map[(y + 6) / MINIMAP_Y][x / MINIMAP_X] == '1')
// 			return (false);
// 		else if (cube->level.map[(y + 6) / MINIMAP_Y][(x + 6) / MINIMAP_X] == '1')
// 			return (false);
// 		else
// 			return (true);
// 	}
// 	return (true);
// }

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
