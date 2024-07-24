/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:56 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/24 07:58:32 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	rotate_player(t_cub3d *cube, float angle)
{
	float	old_dir_x;
	float	old_dir_y;

	old_dir_x = cube->player.pos.x;
	old_dir_y = cube->player.pos.y;
	printf("before (%f, %f)\n", cube->player.pos.x, cube->player.pos.y);
	cube->player.pos.x = old_dir_x * cos(angle);
	cube->player.pos.y = old_dir_y * cos(angle);
	printf("after (%f, %f)\n", cube->player.pos.x, cube->player.pos.y);
}