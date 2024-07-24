/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:31:00 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/24 13:51:52 by ssibai           ###   ########.fr       */
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

// void	move_x(t_cub3d *cube, int dir)
// {
// 	if (dir > 0)
// 		(cube->player.pos.x) ++;
// 	else
// 		(cube->player.pos.x) --;
// }
// void	move_y(t_cub3d *cube, int dir)
// {
// 	if (dir > 0)
// 		(cube->player.pos.y) --;
// 	else
// 		(cube->player.pos.y) ++;
// }

// void	rotate_right(t_cub3d *cube)
// {

// }

// void	rotate_left(t_cub3d *cube)
// {
	
// }

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
 * 
 * 	
 * @param cube 
 */
void	player_movement(t_cub3d *cube, bool dir[4])
{
	//int	side;

	//side = get_direction();
	// if (cube->player.orientation == 'N' || cube->player.orientation == 'S')
	// {
	// 	if (cube->player.orientation == 'S')
	// 	{
	// 		side *= -1;
	// 		int	y_dir;
	// 		int	x_dir;
			
	// 	}

	// if (dir[0])
	// 	x_dir = 1;
	// else if (dir[])
	// 	x_dir = -1;
		// if (dir[0])
		// 	move_player(cube, 1, false);
		// if (dir[1])
		// 	move_player(cube, 1, true);
		// if (dir[2])
		// 	move_player(cube, -1, false);
		// if (dir[3])
		// 	move_player(cube, -1, true);

	// else if (cube->player.orientation == 'E' || cube->player.orientation == 'W')
	// {
	// 	if (cube->player.orientation == 'W')
	// 		side *= -1;
	// 	else
			
		if (dir[0])
			move_player(cube, 1, false);
		if (dir[1])
			move_player(cube, -1, true);
		if (dir[2])
			move_player(cube, -1, false);
		if (dir[3])
			move_player(cube, 1, true);
		
		// if (dir[0])
		// 	move_y(cube, -side);
		// if (dir[1])
		// 	move_x(cube, side);
		// if (dir[2])
		// 	move_y(cube, side);
		// if (dir[3])
		// 	move_x(cube, -side);
//	}
}

void	player_rotation(t_cub3d *cube, int rot_dir)
{
	if (rot_dir == 1)
	{
		printf("clockwise\n");
		//rotate clockwise
		cube->player.transform.angle += 0.1;
		if (cube->player.transform.angle > 2 * PI)
			cube->player.transform.angle = 0;
	}
	else if (rot_dir == -1)
	{
		//rotate counter clockwise
		printf("counter clockwise\n");
		cube->player.transform.angle -= 0.1;
		if (cube->player.transform.angle < 0)
			cube->player.transform.angle = 2 * PI;
	}
}

