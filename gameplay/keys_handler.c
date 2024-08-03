/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:43:14 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/03 15:51:36 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	set_keys_setting(t_cub3d *cube, int key, bool setting)
{
	if (key == D)
		cube->player.move_dir[0] = setting;
	if (key == W)
		cube->player.move_dir[1] = setting;
	if (key == A)
		cube->player.move_dir[2] = setting;
	if (key == S)
		cube->player.move_dir[3] = setting;
	if (key == LOOK_RIGHT)
		cube->player.rot_dir[0] = setting;
	if (key == LOOK_LEFT)
	{
		//printf("LEFT\n");
		cube->player.rot_dir[1] = setting;
	}
}


int	handle_keypress(int key, t_cub3d *cube)
{
	if (key == ESC)
		close_window(cube);
	set_keys_setting(cube, key, true);
	if (key == W || key == S || key == D || key == A)
		cube->player.move = true;
	if (key == LOOK_RIGHT || key == LOOK_LEFT)
		cube->player.rotate = true;
	return (0);
}

int	handle_keyrelease(int key, t_cub3d *cube)
{
	set_keys_setting(cube, key, false);
	if (!cube->player.move_dir[0] && !cube->player.move_dir[1]
		&& !cube->player.move_dir[2] && !cube->player.move_dir[3])
		cube->player.move = false;
	if (!cube->player.rot_dir[0] && !cube->player.rot_dir[0])
		cube->player.rotate = false;
	return (0);
}