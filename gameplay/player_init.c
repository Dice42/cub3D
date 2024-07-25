/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:05:26 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/25 19:16:30 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player(t_cub3d *cube, int x, int y)
{
	cube->player.transform.x0 = x * 64 + 24;
	cube->player.transform.y0 = y * 64 + 24;
	if (cube->player.orientation == 'N')
		cube->player.transform.angle = 3 * PI / 2;
	else if (cube->player.orientation == 'E')
		cube->player.transform.angle = 0;
	else if (cube->player.orientation == 'S')
		cube->player.transform.angle = PI / 2;
	else if (cube->player.orientation == 'W')
		cube->player.transform.angle = PI;
	cube->player.transform.dx = cos(cube->player.transform.angle);
	cube->player.transform.dy = sin(cube->player.transform.angle);
}
