/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:55:48 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/14 10:59:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	xpm_to_image(t_cub3d *cube, t_img_data *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(cube->data.mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
		error_handler("Error\nCourrupted path\n", true, cube, true);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

void	load_textures(t_cub3d *cube)
{
	xpm_to_image(cube, &cube->data.textures[0],
		cube->level.textures.north_texture);
	xpm_to_image(cube, &cube->data.textures[1],
		cube->level.textures.south_texture);
	xpm_to_image(cube, &cube->data.textures[2],
		cube->level.textures.east_texture);
	xpm_to_image(cube, &cube->data.textures[3],
		cube->level.textures.west_texture);
}
