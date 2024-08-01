/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_visuals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:27:33 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/01 13:20:51 by vtcsbza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_borders(t_cub3d *cube, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_X - 1)
	{
		j = 0;
		while (j < MINIMAP_Y - 1)
		{
			my_mlx_pixel_put(&cube->data.img, x * MINIMAP_X + i, y * MINIMAP_Y + j, 0xADD8E6);
			j++;
		}
		i++;
	}
}
void	draw_background(t_cub3d *cube, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_X - 1)
	{
		j = 0;
		while (j < MINIMAP_Y - 1)
		{
			my_mlx_pixel_put(&cube->data.img, x * MINIMAP_X + i, y * MINIMAP_Y + j, 0x8e918a);
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
	init_mlx_img(cube);
	draw_floor(cube);
	draw_ceiling(cube);
	while (cube->level.map[y])
	{
		x = 0;
		while (cube->level.map[y][x])
		{
			if (cube->level.map[y][x] == '1' || cube->level.map[y][x] == ' ')
				draw_borders(cube, x, y);
			else if (cube->level.map[y][x] == '0')
				draw_background(cube, x, y);
			else if (cube->level.map[y][x] == cube->player.orientation)
			{
				draw_background(cube, x, y);
				if (!cube->level.start)
					init_player_pos(cube, x, y);
			}
			x++;
		}
		y++;
	}
	cast_rays_from_player(cube);
	draw_line(cube);
	mlx_put_image_to_window(cube->data.mlx_ptr, cube->data.win,
		cube->data.img.img, 0, 0);
	return (0);
}
