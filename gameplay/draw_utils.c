/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:56 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/24 08:23:15 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	rotate_player(t_cub3d *cube, float angle)
{
	float	old_dir_x;
	float	old_dir_y;

	old_dir_x = cube->player.transform.x_pos;
	old_dir_y = cube->player.transform.y_pos;
	printf("before (%f, %f)\n", cube->player.transform.x_pos, cube->player.transform.y_pos);
	cube->player.transform.x_pos = old_dir_x * cos(angle);
	cube->player.transform.y_pos = old_dir_y * cos(angle);
	printf("after (%f, %f)\n", cube->player.transform.x_pos, cube->player.transform.y_pos);
}