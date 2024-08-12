/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_visuals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:50:52 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/12 22:04:16 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_ceiling(t_cub3d *cube)
{
	int	i;
	int	j;
	int	 clr = cube->level.ceiling_clr;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			my_mlx_pixel_put(&cube->data.img, i, j, clr);
			j++;
		}
		i++;
	}
}

void	draw_floor(t_cub3d *cube)
{
	int	i;
	int	j;
	int	clr = cube->level.floor_clr;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			my_mlx_pixel_put(&cube->data.img, i, j, clr);
			j++;
		}
		i++;
	}
}