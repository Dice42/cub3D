/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_visuals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:27:33 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 21:17:30 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_borders(t_cub3d *cube, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 63)
	{
		j = 0;
		while (j < 63)
		{
			my_mlx_pixel_put(&cube->data.img, x * 64 + i, y * 64 + j, 0xADD8E6);
			j++;
		}
		i++;
	}
}

int	draw_mini_map(t_cub3d *cube)
{
	int	x;
	int	y;

	y = 0;
	while (cube->level.map[y])
	{
		x = 0;
		while (cube->level.map[y][x])
		{
			if (cube->level.map[y][x] == '1')
				draw_borders(cube, x, y);
			else if (cube->level.map[y][x] == cube->player.orientation)
			{
				if (!cube->level.start)
				{
					// if (cube->level.map[y][x] == cube->player.orientation)
					// {
						// printf("first draw\n");
						//init_draw_player(cube, x, y);
						// cube->level.start = true;
						cube->player.pos.x = x * 64 + 24;
						cube->player.pos.y = y * 64 + 24;
						//printf("x is {%d} y is {%d} and player x is [%d] player y [%d]\n", x*64, y*64, cube->player.pos.x,cube->player.pos.y);
				}
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->data.mlx_ptr, cube->data.win,
		cube->data.img.img, 0, 0);
	return (0);
}