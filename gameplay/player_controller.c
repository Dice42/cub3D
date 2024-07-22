/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/22 16:31:20 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_player(t_cub3d *cube)
{
	my_mlx_pixel_put(&cube->data.img, cube->player.pos[0],
		cube->player.pos[1], 0xFF0000);
}

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
	int	dir;
	
	dir = get_direction(cube->player.move_dir);
	if (dir == 1)
		move_x(cube, 1);
	else if (dir == 3)
		move_x(cube, -1);
	else if (dir == 2)
		move_y(cube, 1);
	else if (dir == 4)
		move_y(cube, -1);
}