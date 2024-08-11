/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:42:18 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/12 00:52:23 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	xpm_to_image(t_cub3d *cube, t_img_data *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(cube->data.mlx_ptr, path, 
			&texture->width, &texture->height);
	if (!texture->img)
		error_handler("Error\nCourrupted path\n", NULL, NULL, false);
	texture->addr = mlx_get_data_addr(texture->img, 
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	load_textures(t_cub3d *cube)
{
	xpm_to_image(cube, &cube->data.textures[0], cube->level.textures.north_texture);
	xpm_to_image(cube, &cube->data.textures[1], cube->level.textures.south_texture);
	xpm_to_image(cube, &cube->data.textures[2], cube->level.textures.east_texture);
	xpm_to_image(cube, &cube->data.textures[3], cube->level.textures.west_texture);
}

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

void	choose_texture(t_cub3d *cube, int quarter)
{
	float	h_dis;
	
	h_dis = cube->player.rays.horizontal_distance;
	if (quarter == 1)
	{	
		if (cube->player.rays.distance == h_dis)
			cube->data.texture = &cube->data.textures[1];
		else
			cube->data.texture = &cube->data.textures[3];
	}
	if (quarter == 2)
	{
		if (cube->player.rays.distance == h_dis)
			cube->data.texture = &cube->data.textures[1];
		else
			cube->data.texture = &cube->data.textures[2];
	}
	if (quarter == 3)
	{
		if (cube->player.rays.distance == h_dis)
			cube->data.texture = &cube->data.textures[0];
		else
			cube->data.texture = &cube->data.textures[2];
	}
	if (quarter == 4)
	{
		if (cube->player.rays.distance == h_dis)
			cube->data.texture = &cube->data.textures[0];
		else
			cube->data.texture = &cube->data.textures[3];
	}
}

void	check_coordinate(t_cub3d *cube)
{
	float angle;

	angle = fabs(cube->player.rays.angle * DEG);
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
