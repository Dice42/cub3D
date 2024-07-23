/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 12:02:54 by ssibai           ###   ########.fr       */
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
// void	move_dir_flipflop(t_cub3d *cube, int dir)
// {
// 	if (!cube->player.move_dir[dir])
// 		cube->player.move_dir[dir] = true;
// 	else
// 		cube->player.move_dir[dir] = false;
// }

void	move_x(t_cub3d *cube, int dir)
{
	if (dir > 0)
	{
		printf("MOVE X TO POS\n");
		//increment by 1 pixel at a time
		(cube->player.pos[0]) ++;
	}
	else
	{
		printf("MOVE X TO NEGATIVE\n");
		//decrement by 1 pixel at a time
		(cube->player.pos[0]) --;
	}
}
void	move_y(t_cub3d *cube, int dir)
{
	if (dir > 0)
	{
		printf("MOVE Y TO POSITIVE\n");
		//increment by 1 pixel at a time
		(cube->player.pos[1]) --;
	}
	else
	{
		printf("MOVE Y TO NEGATIVE\n");
		//decrement by 1 pixel at a time
		(cube->player.pos[1]) ++;
	}
}

/**
 * @brief moves player depending on the movement direction set
 * 	if (dir[0] && !dir[2]) //TO THE RIGHT AND NOT TO THE LEFT
 * 		move to right
 * 	if (dir[1] && !dir[3]) //TO THE FRONT AND NOT TO THE BACK
 * 		move to the front
 * 	if (dir[2] && !dir[0]) //TO THE LEFT AND NOT TO THE RIGHT
 * 		move to the left
 * 	if (dir[3] && !dir[1]) //TO THE BACK AND NOT TO THE FRONT
 * 		move to the back
 * @param cube 
 */
void	player_movement(t_cub3d *cube, int key)
{
	int dir;
	
	//printf("WE NEED TO GO TO SALALAH!");
	dir = get_direction(key);
	printf("dir is : %d\n", dir);
	if (dir == 0)
		move_x(cube, 1);
	if (dir == 1)
		move_y(cube, 1);
	if (dir == 2)
		move_x(cube, -1);
	if (dir == 3)
		move_y(cube, -1);
}

