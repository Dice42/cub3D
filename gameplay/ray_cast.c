

#include "../includes/cub3D.h"


void normalize_vector(float *vector)
{
	float magnitude;

	magnitude = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	if (magnitude > 0)
	{
		vector[0] /= magnitude;
		vector[1] /= magnitude;
	}
}

void draw_ray(t_cub3d *cube, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		if ((x0 >= 0 && x0 < cube->level.num_of_columns * MINIMAP_X)
			&&  (y0 >= 0 && y0 < cube->level.num_of_rows * MINIMAP_Y))
			my_mlx_pixel_put(&cube->data.img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
			err += dy, x0 += sx;
		if (e2 <= dx)
			err += dx, y0 += sy;
	}
}

float	calculate_vertical_distance(t_cub3d *cube, float *ray_dir)
{
	bool	subtract_mapsize;
	float	init_pos[2];
	float	step_x;
	float	step_y;

	init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
	if (ray_dir[0] > 0)
		init_pos[0] += MINIMAP_X;
	else
		init_pos[0] -= 0.00001;

	init_pos[1] = cube->player.rays.ry + (init_pos[0] - cube->player.rays.rx) * (ray_dir[1] / ray_dir[0]);
	step_x = (ray_dir[0] > 0) ? MINIMAP_X : -MINIMAP_X;
	step_y = step_x * (ray_dir[1] / ray_dir[0]);
	while (1)
	{
		int x = (int)(init_pos[0] / MINIMAP_X);
		int y = (int)(init_pos[1] / MINIMAP_Y);
		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
		{
			if (cube->level.map[y][x] == '1') 
			{
				draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
				cube->player.rays.vertical_intersection_x = init_pos[0];
				cube->player.rays.vertical_intersection_y = init_pos[1];
				return (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
			}
			else
			{
				init_pos[0] += step_x;
				init_pos[1] += step_y;
			}
		}
		else
			break;
	}
	return (0);
}


float	calculate_horizontal_distance(t_cub3d *cube, float *ray_dir)
{
	bool	subtract_mapsize;
	float	init_pos[2];
	float	step_x;
	float	step_y;
	int x;
	int y;

	init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
	if (ray_dir[1] > 0)
		init_pos[1] += MINIMAP_Y;
	else
		init_pos[1] -= 0.00001;
	init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry) * (ray_dir[0] / ray_dir[1]);
	step_y = (ray_dir[1] > 0) ? MINIMAP_Y : -MINIMAP_Y;
	step_x = step_y * (ray_dir[0] / ray_dir[1]);

	while (1)
	{
		int x = (int)(init_pos[0] / MINIMAP_X);
		int y = (int)(init_pos[1] / MINIMAP_Y);
		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
		{
			if (cube->level.map[y][x] == '1')
			{
				draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
				cube->player.rays.horizontal_intersection_x = init_pos[0];
				cube->player.rays.horizontal_intersection_y = init_pos[1];
				return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]);
			}
			else
			{
				init_pos[0] += step_x;
				init_pos[1] += step_y;
			}
		}
		else
			break;
	}
	return (0);
}

/* ************************************************************************** */



/**
 * @brief 2) calculate vertical distance:
			1) if (looking to right)
			{
				1) stop where 1 is found in the map.
				2) set the intersections to the above calculated values
				4) calculate the length of the ray from the start pos to that end position
			}
			2) else
			{
				stop at the pixel + X side length
					How:
						1) reduce x by x step length
						2) find the corresponding y to that x step
						3) set the intersections to the above calculated values
						4) calculate the length of the ray from the start pos to that end position
			}
			
 * @param cube 
 * @param ray_dir 
 */
// float	get_vertical_length(t_cub3d *cube, float *ray_dir)
// {
// 	float	init_pos[2];
// 	bool	subtract_mapsize;
// 	float	step[2];
// 	int		x;
// 	int		y;

// 	init_pos[0] = (int)(cube->player.rays.rx  / MINIMAP_X) * MINIMAP_X;
// 	if (ray_dir[0] > 0)
//         init_pos[0] += MINIMAP_X;
// 	init_pos[1] = (int)(cube->player.rays.ry + ((init_pos[0] - cube->player.rays.rx)) * (ray_dir[1]));
// 	if (ray_dir[0] < 0)
// 	{
// 		//printf("looking left\n");
// 		subtract_mapsize = true;
// 		step[0] = -MINIMAP_X;
// 		step[1] = step[0] * (ray_dir[1] / ray_dir[0]);
// 	}
// 	else if (ray_dir[0] > 0)
// 	{
// 		//printf("looking right\n");
// 		subtract_mapsize = false;
// 		step[0] = MINIMAP_X;
// 		step[1] = step[0] * (ray_dir[1] / ray_dir[0]);
// 	}
// 	else
// 	{
//         return(10000);
// 	}
// 	while(1)
// 	{
// 		cube->player.rays.clr = 0X00FF00;
// 		return (cube->player.rays.horizontal_distance);
// 	} 
// 	cube->player.rays.clr = 0X0000FF;
// 	return (cube->player.rays.verical_distance);
// }














/**
 * @brief 		1) calculate the cos and sin of the angle
 * 					2) get horizontal length
 * 					3) get vertical length
 * 				4) compare the lengths of the horizontal distance and vertical distance
				if (horizontal > vertical)
					return vertical
				return horizontal
 * @param cube cube struct reference
 * @return float the shrtest ray length
 */
float cast_rays(t_cub3d *cube)
{
	float	angle;
	float	ray_dir[2];

	cube->player.rays.vertical_distance = 1000000;
	cube->player.rays.horizontal_distance = 1000000;
	angle = cube->player.rays.angle;

	
printf("*************************************\n");
	printf("ANGLE IS %f\n", (angle * 180/PI));
	ray_dir[0] = cos(angle);
	ray_dir[1] = sin(angle);
	normalize_vector(&ray_dir[0]);
	cube->player.rays.vertical_distance = calculate_vertical_distance(cube, &ray_dir[0]);
	cube->player.rays.horizontal_distance = calculate_horizontal_distance(cube, &ray_dir[0]);
	printf("horizontal distance is %f\n",cube->player.rays.horizontal_distance);
	printf("vertical distance is %f\n",cube->player.rays.vertical_distance);
	if (cube->player.rays.vertical_distance == 0)
	{
		cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
		cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
		cube->player.rays.clr = GREEN;
		return (cube->player.rays.horizontal_distance);
	}
	else if (cube->player.rays.horizontal_distance == 0)
	{
		cube->player.rays.clr = BLUE;
		cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
		cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
		return (cube->player.rays.vertical_distance);
	}
	if (cube->player.rays.vertical_distance > cube->player.rays.horizontal_distance) 
	{
		printf("returning the horizontal distance\n");
		cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
		cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
		cube->player.rays.clr = GREEN;
		return (cube->player.rays.horizontal_distance);
	}
	cube->player.rays.clr = BLUE;
	cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
	cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
	printf("returning the vertical distance\n");
	return (cube->player.rays.vertical_distance);
}




