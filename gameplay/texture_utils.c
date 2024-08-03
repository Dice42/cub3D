/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:42:18 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/03 17:49:53 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	load_textures(t_cub3d *cube)
{
	cube->data.textures[0].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.north_texture,
			&cube->data.textures[0].bits_per_pixel,
			&cube->data.textures[0].line_length);
	cube->data.textures[1].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.south_texture,
			&cube->data.textures[1].bits_per_pixel,
			&cube->data.textures[1].line_length);
	cube->data.textures[2].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.east_texture,
			&cube->data.textures[2].bits_per_pixel,
			&cube->data.textures[2].line_length);
	cube->data.textures[3].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.west_texture,
			&cube->data.textures[3].bits_per_pixel,
			&cube->data.textures[3].line_length);
}

int	get_texture_pixel(t_img_data *texture, int x, int y)
{
	char	*data;
	int		pixel_index;

	data = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	pixel_index = (y * texture->line_length) + (x * (texture->bits_per_pixel / 8));
	return (*(int *)(data + pixel_index));
}

t_img_data	choose_texture(t_cub3d *cube, float dir_x, float dir_y)
{
	bool	is_vertical;

	is_vertical = fabs(dir_x) > fabs(dir_y);
	if (is_vertical)
	{
		if (dir_x > 0)
			return (cube->data.textures[2]);
		else
			return (cube->data.textures[3]);
	}
	else
	{
		if (dir_y > 0)
			return (cube->data.textures[1]);
		else
			return (cube->data.textures[0]);
	}
	return (cube->data.textures[0]);
}