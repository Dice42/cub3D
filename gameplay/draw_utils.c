/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:56 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/21 20:17:11 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	draw_player(t_cub3d *cube, int x, int y)
{
	int	i;
	int	j;

	i = 24;
	while (i < 40)
	{
		j = 24;
		while (j < 40)
		{
			my_mlx_pixel_put(&cube->data.img, x * 64 + i, y * 64 + j, 0x21214B);
			j++;
		}
		i++;
	}
}

void	draw_cube(t_cub3d *cube, int x, int y)
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