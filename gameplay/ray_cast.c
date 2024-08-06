/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:13 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/06 17:13:11 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"


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
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

float	calculate_vertical_distance(t_cub3d *cube, float *ray_dir)
{
	bool	subtract_mapsize;
	float	init_pos[2];
	float	step_x;
	float	step_y;

	// if (ray_dir[0] == 0) // cos angle = 0: looking straight up or staright down
	// {
	// 	printf("LOOKING UP OR DOWN\n");
	// 	if (ray_dir[1] > 0) //looking at the upper side of the map
	// 	{
	// 		printf("looking towards the upper side of the map\n");
	// 		init_pos[1] = ((int)(cube->player.rays.ry / MINIMAP_Y) + 1) * MINIMAP_Y;
	// 	}
	// 	else
	// 	{
	// 		printf("looking towards the lower side of the map\n");
	// 		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
	// 	}
	// 	init_pos[0] = cube->player.rays.rx;  // Vertical ray, so no x adjustment
	// 	step_y = (ray_dir[1] > 0) ? MINIMAP_Y : -MINIMAP_Y;
	// 	while (1)
	// 	{
	// 		int x = (int)(init_pos[0] / MINIMAP_X);
	// 		int y = (int)(init_pos[1] / MINIMAP_Y);
	// 		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
	// 		{
	// 			if (cube->level.map[y][x] == '1')
	// 			{
	// 				cube->player.rays.vertical_intersection_x = init_pos[0];
	// 				cube->player.rays.vertical_intersection_y = init_pos[1];
	// 			//	draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
	// 				return (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
	// 			}
	// 			else
	// 				init_pos[1] += step_y;
	// 		}
	// 		else
	// 			break;
	// 	}
	// }
	// else
	// {
		// Non-vertical rays
		init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
		if (ray_dir[0] > 0)
		{
			printf("LOOKING RIGHT?\n");
			subtract_mapsize = false;
			init_pos[0] += MINIMAP_X;
		}
		else
		{
			printf("LOOKING LEFT??\n");
			subtract_mapsize = true;
			init_pos[0] -= MINIMAP_X;
		}
		init_pos[1] = cube->player.rays.ry + (init_pos[0] - cube->player.rays.rx) * (ray_dir[1] / ray_dir[0]);
		step_x = (ray_dir[0] > 0) ? MINIMAP_X : -MINIMAP_X;
		step_y = step_x * (ray_dir[1] / ray_dir[0]);
		while (1)
		{
			int x = (int)(init_pos[0] / MINIMAP_X);
			int y = (int)(init_pos[1] / MINIMAP_Y);

			if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
				if (cube->level.map[y][x] == '1') {
					if (subtract_mapsize)
					{
						cube->player.rays.vertical_intersection_x = init_pos[0] + MINIMAP_X;
						cube->player.rays.vertical_intersection_y = init_pos[1];
						//draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0] + MINIMAP_X, (int)init_pos[1], 0X00FF00);
						return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]) + MINIMAP_X;
					}
					else
					{
						cube->player.rays.vertical_intersection_x = init_pos[0];
						cube->player.rays.vertical_intersection_y = init_pos[1];
						//draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
						return (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
					}
					break;
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
//	}
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

	// if (ray_dir[1] == 0)
	// {
	// 	if (ray_dir[0] > 0)
	// 		init_pos[0] = ((int)(cube->player.rays.rx / MINIMAP_X) + 1) * MINIMAP_X;
	// 	else
	// 		init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
	// 	init_pos[1] = cube->player.rays.ry;  // Horizontal ray, so no y adjustment
	// 	step_x = (ray_dir[0] > 0) ? MINIMAP_X : -MINIMAP_X;
	// 	while (1)
	// 	{
	// 		int x = (int)(init_pos[0] / MINIMAP_X);
	// 		int y = (int)(init_pos[1] / MINIMAP_Y);
	// 		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) 
	// 		{
	// 			if (cube->level.map[y][x] == '1') 
	// 			{
	// 				cube->player.rays.horizontal_intersection_x = init_pos[0];
	// 				cube->player.rays.horizontal_intersection_y = init_pos[1];
	// 				//draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
	// 				return (init_pos[0] - cube->player.rays.rx) / ray_dir[0];
	// 			} 
	// 			else
	// 			{
	// 				init_pos[0] += step_x;
	// 			}
	// 		} 
	// 		else
	// 			break;
	// 	}
	// }
	// else
	//{
		// Non-horizontal rays
		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
		if (ray_dir[1] > 0)
		{
			//printf("LOOKING DOWN?\n");
			subtract_mapsize = false;
			init_pos[1] += MINIMAP_Y;
		}
		else
		{
			// printf("LOOKING UP?\n");
			subtract_mapsize = true;
			init_pos[1] -= MINIMAP_Y;
		}
		init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry) * (ray_dir[0] / ray_dir[1]);
		step_y = (ray_dir[1] > 0) ? MINIMAP_Y : -MINIMAP_Y;
		step_x = step_y * (ray_dir[0] / ray_dir[1]);

		while (1)
		{
			x = (int)(init_pos[0] / MINIMAP_X);
			y = (int)(init_pos[1] / MINIMAP_Y);
			printf("x is %d and y is %d\n", x, y);
			if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
			{
				if (cube->level.map[y][x] == '1')
				{
					if (subtract_mapsize)
					{
						cube->player.rays.horizontal_intersection_x = init_pos[0];
						cube->player.rays.horizontal_intersection_y = init_pos[1] + MINIMAP_Y;
						//draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1] + MINIMAP_Y, 0X0000FF);
						return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]) - MINIMAP_Y;
					}
					else
					{
						cube->player.rays.horizontal_intersection_x = init_pos[0];
						cube->player.rays.horizontal_intersection_y = init_pos[1];
						//draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
						return ((init_pos[1] - cube->player.rays.ry) / ray_dir[1]);
					}
					break;
				} 
				else
				{
					init_pos[0] += step_x;
					init_pos[1] += step_y;
				}
			}
			else
			{
				printf("out of bounds\n");
				break;
			}
		}
	//}
	printf("the horizontal intersection is with x %d and y y%d\n", x, y );
	printf("something's wrong\n");
	return (0);
}



/*

	2) calculate vertical distance:

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

	3) calculate the horizontal distance:

		1) if (looking upwards)
		{
			stop at the pixel + Y side length
				How:
					1) reduce y by y step length
					2) find the corresponding x to that y step
					3) set the intersections to the above calculated values
					4) calculate the length of the ray from the start pos to that end position
		}
		2) else
		{
			1) stop where 1 is found in the map.
			2) set the intersections to the above calculated values
			4) calculate the length of the ray from the start pos to that end position
		}


*/



/* ************************************************************************** */
/**
 * @brief 	2) calculate the horizontal distance:
 * 				1) floor the position of y
				2) find the corresponding x to that y step
				3) if (looking upwards)
				{
					stop at the pixel + Y side length
						How:
							1) stop where 1 is found in the map.
							3) set the intersections to the above calculated values
							4) calculate the length of the ray from the start pos to 
								that end position
				}
				4) else
				{
					1) stop where 1 is found in the map.
					2) set the intersections to the above calculated values
					3) calculate the length of the ray from the start pos to that 
						end position
				}
 * 
 * @param cube 
 * @param ray_dir 
 * @return float the horizontal length
 */
void	get_horizontal_length(t_cub3d *cube, float *ray_dir)
{
	float	init_pos[2];
	bool	subtract_mapsize;
	float	step[2];
	int		x;
	int		y;

	init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
	init_pos[0]= (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
	if (ray_dir[1] < 0) //looking upwards
	{
		printf("looking up\n");
		subtract_mapsize = true;
		//init_pos[1] -= MINIMAP_Y;
		step[1] = -MINIMAP_Y;
		step[0] = step[1] * (ray_dir[0] / ray_dir[1]);
	}
	else if (ray_dir[1] > 0)
	{
		//init_pos[1] += MINIMAP_Y;
		subtract_mapsize = false;
		//init_pos[1] += MINIMAP_Y;
		step[1] = MINIMAP_Y;
		step[0] = step[1] * (ray_dir[0] / ray_dir[1]);
		printf("looking down\n");
	}
	else
	{
		printf("sin of angle is 0 \n");
	}
	//init_pos[0] = fabs(cube->player.rays.rx + ((init_pos[1] - cube->player.rays.ry)) * (ray_dir[0] / ray_dir[1]));
	printf("initial x: {%f}	initial y {%f}\n", init_pos[0], init_pos[1]);
	printf("step for x is: %f step for y is: %f\n", step[0], step[1]);
	while (1)
	{
		x = (int)(init_pos[0] / MINIMAP_X);
		y = (int)(init_pos[1] / MINIMAP_Y);
		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
		{
			if (cube->level.map[y][x] == '1')
			{
				if (subtract_mapsize)
				{
					printf("------------SUBTRACT MAPSIZE------------\n");
					init_pos[1] -= step[1];
					init_pos[0] = cube->player.rays.rx + (fabs(init_pos[1] - cube->player.rays.ry)) * (ray_dir[0] / ray_dir[1]);
					printf("y is {%f} aand its corresponding x is {%f}\n", init_pos[0], init_pos[1]);
					cube->player.rays.horizontal_intersection_x = init_pos[0];
					cube->player.rays.horizontal_intersection_y = init_pos[1];
					cube->player.rays.horizontal_distance = (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
					printf("distance is: {%f}\n",cube->player.rays.horizontal_distance );
					break ;
				}
				else
				{
					cube->player.rays.horizontal_intersection_x = init_pos[0];
					cube->player.rays.horizontal_intersection_y = init_pos[1];
					printf("y is {%f} aand its corresponding x is {%f}\n", init_pos[0], init_pos[1]);
					cube->player.rays.horizontal_distance =  (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
					printf("distance is: {%f}\n",cube->player.rays.horizontal_distance );
					break ;
				}
			} 
			else
			{
				init_pos[0] += step[0];
				init_pos[1] += step[1];
			}
		}
		else
		{
			printf("out of bounds\n");
			break;
		}
	}
	return ;
}
/* ************************************************************************** */



















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
	printf("cos is %f and sin is %f\n", ray_dir[0], ray_dir[1]);
	get_horizontal_length(cube, &ray_dir[0]);
	//cube->player.rays.vertical_distance = calculate_vertical_distance(cube, &ray_dir[0]);
	// printf("horizontal distance is %f\n",cube->player.rays.horizontal_distance);
	// printf("vertical distance is %f\n",cube->player.rays.vertical_distance);
	
	// if (cube->player.rays.vertical_distance == 0)
	// {
	// 	cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
	// 	cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
	// 	cube->player.rays.clr = GREEN;
	// 	return (cube->player.rays.horizontal_distance);
	// }
	// else if (cube->player.rays.horizontal_distance == 0)
	// {
	// 	cube->player.rays.clr = BLUE;
	// 	cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
	// 	cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
	// 	return (cube->player.rays.vertical_distance);
	// }
	// if (cube->player.rays.vertical_distance > cube->player.rays.horizontal_distance) 
	// {
	// 	printf("returning the horizontal distance\n");
	// 	cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
	// 	cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
	// 	cube->player.rays.clr = GREEN;
	// 	return (cube->player.rays.horizontal_distance);
	// }
	// cube->player.rays.clr = BLUE;
	// cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
	// cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
	// printf("returning the vertical distance\n");
	// return (cube->player.rays.vertical_distance);
	return (0);
}




