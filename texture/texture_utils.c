/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:42:18 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/09 12:46:04 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	load_textures(t_cub3d *cube)
{
	cube->data.textures[0].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.north_texture,
			&cube->data.textures[0].width,
			&cube->data.textures[0].height);
		if (!cube->data.textures[0].img)
			error_handler("Error\nCourrupted north path\n", NULL, NULL, false);
	cube->data.textures[0].addr = mlx_get_data_addr(cube->data.textures[0].img,
			&cube->data.textures[0].bits_per_pixel,
			&cube->data.textures[0].line_length,
			&cube->data.textures[0].endian);
			
	cube->data.textures[1].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.south_texture,
			&cube->data.textures[1].width,
			&cube->data.textures[1].height);
		if (!cube->data.textures[1].img)
			error_handler("Error\nCourrupted south path\n", NULL, NULL, false);
	cube->data.textures[1].addr = mlx_get_data_addr(cube->data.textures[1].img,
			&cube->data.textures[1].bits_per_pixel,
			&cube->data.textures[1].line_length,
			&cube->data.textures[1].endian);
			
	cube->data.textures[2].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.east_texture,
			&cube->data.textures[2].width,
			&cube->data.textures[2].height);
		if (!cube->data.textures[2].img)
			error_handler("Error\nCourrupted east path\n", NULL, NULL, false);
	cube->data.textures[2].addr = mlx_get_data_addr(cube->data.textures[2].img,
			&cube->data.textures[2].bits_per_pixel,
			&cube->data.textures[2].line_length,
			&cube->data.textures[2].endian);
			
	cube->data.textures[3].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
			cube->level.textures.west_texture,
			&cube->data.textures[3].width,
			&cube->data.textures[3].height);
		if (!cube->data.textures[3].img)
			error_handler("Error\nCourrupted west path\n", NULL, NULL, false);
	cube->data.textures[3].addr = mlx_get_data_addr(cube->data.textures[3].img,
			&cube->data.textures[3].bits_per_pixel,
			&cube->data.textures[3].line_length,
			&cube->data.textures[3].endian);
}

int	get_texture_pixel(t_img_data *texture, int x, int y, t_cub3d *cube)
{
	char	*data;

	if (x < 0 || x >= cube->data.texture->width)
		x = 0;
	if (y < 0 || y >= cube->data.texture->height)
		y = 0;
	data = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)data);
}

t_img_data	*choose_texture(t_cub3d *cube, float v_dis, float h_dis, int quarter)
{
	if (quarter == 1)
	{	
		if (cube->player.rays.distance == h_dis)
			return (&cube->data.textures[0]);
		else
			return (&cube->data.textures[2]);
	}
	if (quarter == 2)
	{
		if (cube->player.rays.distance == h_dis)
			return (&cube->data.textures[0]);
		else
			return (&cube->data.textures[3]);
	}
	if (quarter == 3)
	{
		if (cube->player.rays.distance == h_dis)
			return (&cube->data.textures[1]);
		else
			return (&cube->data.textures[3]);
	}
	if (quarter == 4)
	{
		if (cube->player.rays.distance == h_dis)
			return (&cube->data.textures[1]);
		else
			return (&cube->data.textures[2]);
	}
	return (&cube->data.textures[0]);
}

t_img_data	*check_coordinate(t_cub3d *cube)
{
	printf("cube->player.rays.angle = %f\n", cube->player.rays.angle);
	if ((cube->player.rays.angle >= 0 && cube->player.rays.angle < M_PI / 2) || (cube->player.rays.angle <= 0 && cube->player.rays.angle >= -M_PI / 2))
	{
		return (choose_texture(cube, cube->player.rays.vertical_distance, cube->player.rays.horizontal_distance, 1));
	}
	else if ((cube->player.rays.angle >= M_PI / 2 && cube->player.rays.angle < M_PI) || (cube->player.rays.angle <= -M_PI / 2 && cube->player.rays.angle > -M_PI))
	{
		return (choose_texture(cube, cube->player.rays.vertical_distance, cube->player.rays.horizontal_distance, 2));
	}
	else if ((cube->player.rays.angle >= M_PI && cube->player.rays.angle < 3 * M_PI / 2) || (cube->player.rays.angle <= -M_PI && cube->player.rays.angle > -3 * M_PI / 2))
	{
		return (choose_texture(cube, cube->player.rays.vertical_distance, cube->player.rays.horizontal_distance, 3));
	}
	else if ((cube->player.rays.angle >= 3 * M_PI / 2 && cube->player.rays.angle <= 2 * M_PI) || (cube->player.rays.angle <= -3 * M_PI / 2 && cube->player.rays.angle >= -2 * M_PI))
	{
		return (choose_texture(cube, cube->player.rays.vertical_distance, cube->player.rays.horizontal_distance, 4));
	}
	else
	{
		printf("ERROR\n");
		return (choose_texture(cube, cube->player.rays.vertical_distance, cube->player.rays.horizontal_distance, 1));
	}
	return (NULL);
}