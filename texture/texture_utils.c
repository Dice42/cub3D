/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:42:18 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 22:57:10 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_texture_pixel(t_img_data *texture, int x, int y, t_cub3d *cube)
{
	char	*data;

	if (x < 0 || x >= cube->data.texture->width)
		x = 0;
	if (y < 0 || y >= cube->data.texture->height)
		y = 0;
	data = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)data);
}

void	set_quarter_texture(t_cub3d *cube, int img1, int img2)
{
	float	h_dis;

	h_dis = cube->player.rays.horizontal_distance;
	if (cube->player.rays.distance == h_dis)
		cube->data.texture = &cube->data.textures[img1];
	else
		cube->data.texture = &cube->data.textures[img2];
}

void	choose_texture(t_cub3d *cube, int quarter)
{
	if (quarter == 1)
		set_quarter_texture(cube, 1, 3);
	if (quarter == 2)
		set_quarter_texture(cube, 1, 2);
	if (quarter == 3)
		set_quarter_texture(cube, 0, 2);
	if (quarter == 4)
		set_quarter_texture(cube, 0, 3);
}

void	check_coordinate(t_cub3d *cube)
{
	float	angle;

	angle = fabs(cube->player.rays.angle * (180 / PI));
	if (angle >= 360)
		angle = 0;
	if (angle >= 0 && angle <= 90)
		choose_texture(cube, 1);
	if (angle >= 90 && angle <= 180)
		choose_texture(cube, 2);
	if (angle >= 180 && angle <= 270)
		choose_texture(cube, 3);
	if (angle >= 270 && angle <= 360)
		choose_texture(cube, 4);
}
