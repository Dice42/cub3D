/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:14:24 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/26 14:10:15 by ssibai           ###   ########.fr       */
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
	float	new_x;
	float	new_y;
	float	old_x;
	float	old_y;

	speed = 2;
	old_x = cube->player.transform.x0;
	old_y = cube->player.transform.y0;
	update_player_direction(cube);
	printf("UPDATED DIRECTION\n");
	if (is_vertical)
	{
		new_x = (cube->player.transform.x0 - (dir * cube->player.transform.dx * speed));
		new_y = (cube->player.transform.y0 - (dir * cube->player.transform.dy * speed));
		// cube->player.transform.x0 -= dir * cube->player.transform.dx * speed;
		// cube->player.transform.y0 -= dir * cube->player.transform.dy * speed;
		// x = (int) cube->player.transform.x0;
		// y = (int) cube->player.transform.y0;
		printf("new_x: %d\n", (int) new_x);
		printf("new_y: %d\n", (int) new_y);
		if (!player_collisions(cube, (int) old_y, (int) old_x))
		{
			new_x = old_x;
			new_y = old_y;
			// new_x = cube->player.transform.x0;
			// new_y = cube->player.transform.y0;
		}
	}
	else
	{
		new_x = cube->player.transform.x0 - (dir * cube->player.transform.dx * speed);
		new_y = cube->player.transform.y0 + (dir * cube->player.transform.dy * speed);
		// x = (int) cube->player.transform.x0;
		// y = (int) cube->player.transform.y0;
		printf("new_x: %d\n", (int) cube->player.transform.x0);
		printf("new_y: %d\n", (int) cube->player.transform.y0 );
		if (!player_collisions(cube, (int) old_y, (int) old_x))
		{
			new_x = old_x;
			new_y = old_y;
			// new_x = cube->player.transform.x0;
			// new_y = cube->player.transform.y0;
		}
	}
	// cube->player.transform.x0 -= dir * cube->player.transform.dy * speed;
	// cube->player.transform.y0 += dir * cube->player.transform.dx * speed;
	cube->player.transform.x0 = new_x;
	cube->player.transform.y0 = new_y;
}
