/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:39:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/22 18:39:31 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_player(t_cub3d *cube)
{
	my_mlx_pixel_put(&cube->data.img, cube->player.pos[0],
		cube->player.pos[1], 0xFF0000);
}