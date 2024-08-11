#include "../includes/cub3D.h"

t_img_data	*check_coordinate(t_cub3d *cube)
{
	if (cube->player.rays.angle >= 0 && cube->player.rays.angle < M_PI / 2)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 1));
	else if (cube->player.rays.angle >= M_PI / 2 && cube->player.rays.angle < M_PI)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 2));
	else if (cube->player.rays.angle >= M_PI && cube->player.rays.angle < 3 * M_PI / 2)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 3));
	else if (cube->player.rays.angle >= 3 * M_PI / 2 && cube->player.rays.angle <= 2 * M_PI)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 4));
	return (NULL);
}

void	check_coordinate(t_data *data, t_raycast *ray)
{
	float	angle_rad;

	angle_rad = deg_to_rad(ray->angle);
	if (angle_rad >= 0 && angle_rad < M_PI / 2)
		data->texture = first_coordinate(data, ray);
	if (angle_rad >= M_PI / 2 && angle_rad < M_PI)
		data->texture = second_coordinate(data, ray);
	if (angle_rad >= M_PI && angle_rad < 3 * M_PI / 2)
		data->texture = third_coordinate(data, ray);
	if (angle_rad >= 3 * M_PI / 2 && angle_rad <= 2 * M_PI)
		data->texture = fourth_coordinate(data, ray);
}
