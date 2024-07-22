/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/22 20:16:31 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_direction(int dr)
{
	if (dr == D)
		return (1);
	else if (dr == W)
		return (2);
	else if (dr == A)
		return (3);
	else if (dr == S)
		return (4);
	return (0);
}
void	add_move_dir(t_cub3d *cube, int dir)
{
	cube->player.move_dir[dir] = true;
}

void	remove_move_dir)

void	move_x(t_cub3d *cube, int dir)
{
	if (dir > 0)
	{
		//increment by 1 pixel at a time
		cube->player.pos[0] ++;
	}
	else
	{
		//decrement by 1 pixel at a time
		cube->player.pos[0] --;
	}
}
void	move_y(t_cub3d *cube, int dir)
{
	if (dir > 0)
	{
		//increment by 1 pixel at a time
		cube->player.pos[1] ++;
	}
	else
	{
		//decrement by 1 pixel at a time
		cube->player.pos[1] --;
	}
}

void	player_movement(t_cub3d *cube)
{
	if (cube->player.move_dir[0] == true)
		move_x(cube, 1);
	if (cube->player.move_dir[1] == true)
		move_x(cube, -1);
	if (cube->player.move_dir[2] == true)
		move_y(cube, 1);
	if (cube->player.move_dir[3] == true)
		move_y(cube, -1);
}