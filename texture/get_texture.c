#include "../includes/cub3D.h"

t_img_data	*check_coordinate(t_cub3d *cube)
{
	if (cube->player.rays.angle >= 0 &&cube->player.rays.angle < M_PI / 2)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 1));
	if (cube->player.rays.angle >= M_PI / 2 &&cube->player.rays.angle < M_PI)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 2));
	if (cube->player.rays.angle >= M_PI &&cube->player.rays.angle < 3 * M_PI / 2)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 3));
	if (cube->player.rays.angle >= 3 * M_PI / 2 &&cube->player.rays.angle <= 2 * M_PI)
		return (choose_texture(cube, cube->player.rays.distance, cube->player.rays.distance, 4));
	return (NULL);
}