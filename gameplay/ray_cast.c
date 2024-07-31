

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

void	cast_ray(t_cub3d *cube)
{
	float	atan;
	float	ntan;
	float	angle;
	float	ray_xy0[2];
	int		depth_of_field;
	int		current_x;
	int		current_y;

	angle = cube->player.rays.angle;
    atan = -1 / tan(angle); // Correct atan calculation
    depth_of_field = 0;
	ntan = -tan(angle);
	
	//HORIZONTAL LINES CHECK

	printf("position y is %f nd x is %f\n", cube->player.transform.y0, cube->player.transform.x0);
	if (angle > PI) //looking down
	{
		//calculate the next y position of the ray:
		ray_xy0[1] = (((int)(cube->player.transform.y0 / MINIMAP_Y)) * MINIMAP_Y) - 0.0001;
		//calculate the next x position of the ray:
		ray_xy0[0] = (cube->player.transform.y0 - ray_xy0[1]) * atan + cube->player.transform.x0;
		// calculate the y offset:
		cube->player.rays.y_offset = -MINIMAP_Y;
		// calculate the x offset:
		cube->player.rays.x_offset = -MINIMAP_Y * atan;
	}
	else if (angle < PI) //looking up
	{
		//calculate the next y position of the ray:
		ray_xy0[1] = (((int)(cube->player.transform.y0 / MINIMAP_Y)) * MINIMAP_Y) + MINIMAP_Y;
		//calculate the next x position of the ray:		
		ray_xy0[0] = (cube->player.transform.y0 - ray_xy0[1]) * atan + cube->player.transform.x0; // Fixed calculation
		// calculate the y offset:
		cube->player.rays.y_offset = MINIMAP_Y;
		// calculate the x offset:
		cube->player.rays.x_offset = -MINIMAP_Y * atan;			
	}
	else if (angle == 0 || angle == PI) //looking right and left
	{
		ray_xy0[0] = cube->player.transform.x0;
		ray_xy0[1] = cube->player.transform.y0;
		depth_of_field = cube->level.num_of_columns;
	}

	while (depth_of_field < cube->level.num_of_columns)
	{
		current_x = (int) (ray_xy0[0] / MINIMAP_X);
		current_y = (int) (ray_xy0[1] / MINIMAP_Y);

		printf("current x %d:\n current y: %d\n" , current_x, current_y);
		if (cube->level.map[current_y][current_x] == '1')
		{
			break;
		}
		else
		{
			ray_xy0[0] += cube->player.rays.x_offset;
			ray_xy0[1] += cube->player.rays.y_offset;
			depth_of_field ++;
		}
	}

	draw_ray(cube, (int)cube->player.transform.x0, (int)cube->player.transform.y0, (int)ray_xy0[0], (int)ray_xy0[1], 0xFF0000);
}

// void	cast_ray(t_cub3d *cube)
// {
// 	float	atan;

// 	atan = -1/tan(cube->player.rays.angle);
// 	cube->player.rays.depth_of_field = 0;
// 	//vertical intersection, which is why we set the x offset to just the size of the side (minimap x)
// 	if ((cos(cube->player.rays.angle) > (0.001)) && (cos(cube->player.rays.angle) < (0.999))) //looking towards left, since cos(angle) is grater than 0.001
// 	{
//         cube->player.rays.ray_x = (((int)cube->player.transform.x0 / MINIMAP_X) * MINIMAP_X) + MINIMAP_X;
//         cube->player.rays.ray_y = (cube->player.transform.x0 - cube->player.rays.ray_x) * tan(cube->player.rays.angle) + cube->player.transform.y0;
// 		cube->player.rays.x_offset = MINIMAP_X;
//         cube->player.rays.y_offset = -cube->player.rays.x_offset * tan(cube->player.rays.angle);
// 	}
// 	else if (cos(cube->player.rays.angle) < -0.001 && cos(cube->player.rays.angle) > -0.999) //looking towards right, since cos(angle) is grater than 0.001
// 	{
//         cube->player.rays.ray_x = (((int)cube->player.transform.x0 / MINIMAP_X) * MINIMAP_X) - 0.0001;
// 		cube->player.rays.ray_y = (cube->player.transform.x0 - cube->player.rays.ray_x) * tan(cube->player.rays.angle) + cube->player.transform.y0;
// 		cube->player.rays.x_offset = -MINIMAP_X;
//         cube->player.rays.y_offset = -cube->player.rays.x_offset * tan(cube->player.rays.angle);
// 	}
// 	else //looking straight right or left
// 	{
// 		//printf("LOOKING TO RIGHT\n";
// 		cube->player.rays.ray_x = cube->player.transform.x0;
// 		cube->player.rays.ray_y = (int) cube->player.transform.y0;
//         cube->player.rays.depth_of_field = cube->level.num_of_columns;
// 	}

// 	//loop through them till we hit a wall
// 	while (cube->player.rays.depth_of_field < cube->level.num_of_columns)
// 	{
// 		cube->player.rays.current_ray_x = (int)(cube->player.rays.ray_x / MINIMAP_X);
// 	   	cube->player.rays.current_ray_y = (int)(cube->player.rays.ray_y / MINIMAP_Y);
// 		printf("current y is %d and current x is %d\n", cube->player.rays.current_ray_y, cube->player.rays.current_ray_x);
// 		printf("current map char is {%c}\n", cube->level.map[cube->player.rays.current_ray_y][cube->player.rays.current_ray_x]);
// 		printf("x offset is %f and y offset is %f \n", cube->player.rays.x_offset, cube->player.rays.y_offset);
// 		//if (!level_collision(cube, cube->player.rays.current_ray_x, cube->player.rays.current_ray_y, false))
// 		if (cube->level.map[cube->player.rays.current_ray_y][cube->player.rays.current_ray_x] == '1')
// 		{
// 			printf("STOP\n");
// 			cube->player.rays.verical_distance = cos(cube->player.rays.angle) * (cube->player.rays.ray_x - cube->player.transform.x0) - sin(cube->player.rays.angle) * (cube->player.rays.ray_y - cube->player.transform.y0); // Calculate distance
//             break;
// 		}
//         cube->player.rays.ray_x += cube->player.rays.x_offset;
//         cube->player.rays.ray_y += cube->player.rays.y_offset;
//         cube->player.rays.depth_of_field++;
// 	}

// 	printf("calculate horizontal!\n");
// 	printf("PLAYER ANGLE IS : %f\n", cube->player.transform.angle);
// 	//calculate horizontal line intersections for sin(angle) > 0.001 for looking
// 	if (sin(cube->player.rays.angle) < -0.001 && sin(cube->player.rays.angle) > -0.999) //looking towards up, since sin(angle) is grater than 0.001
// 	{
// 		printf("looking up~\n");
//         cube->player.rays.ray_y = (((int)cube->player.transform.y0 / MINIMAP_Y) * MINIMAP_Y) - 0.0001;
//         cube->player.rays.ray_x = (cube->player.transform.y0 - cube->player.rays.ray_y) * (1 / tan(cube->player.rays.angle)) + cube->player.transform.x0;
// 		cube->player.rays.y_offset = -MINIMAP_Y;
//         cube->player.rays.x_offset = -cube->player.rays.y_offset * (1 / tan(cube->player.rays.angle));
// 	}
// 	else if (sin(cube->player.rays.angle) > 0.001 && sin(cube->player.rays.angle) < 0.999) //looking towards down, since sin(angle) is grater than 0.001
// 	{
// 		printf("looking down~\n");
//         cube->player.rays.ray_y = (((int)cube->player.transform.y0 / MINIMAP_Y) * MINIMAP_Y) + MINIMAP_Y;
// 		cube->player.rays.ray_x = (cube->player.transform.y0 - cube->player.rays.ray_y) * (1 / tan(cube->player.rays.angle)) + cube->player.transform.x0;
// 		cube->player.rays.y_offset = MINIMAP_Y;
//         cube->player.rays.x_offset = -cube->player.rays.y_offset * (1 / tan(cube->player.rays.angle));
// 	}
// 	else //looking straight UP or DOWN
// 	{
// 		printf("looking straight~\n");
// 		cube->player.rays.ray_x = cube->player.transform.x0;
// 		cube->player.rays.ray_y = (int) cube->player.transform.y0;
//         cube->player.rays.depth_of_field = cube->level.num_of_rows;
// 	}
// 	//loop through them till we hit a wall
// 	while (cube->player.rays.depth_of_field < cube->level.num_of_rows)
// 	{
// 		cube->player.rays.current_ray_x = (int)(cube->player.rays.ray_x / MINIMAP_X) * MINIMAP_X;
// 	   	cube->player.rays.current_ray_y = (int)(cube->player.rays.ray_y / MINIMAP_Y) * MINIMAP_Y;
// 		//if (!level_collision(cube, cube->player.rays.current_ray_x, cube->player.rays.current_ray_y, false))
// 		printf("HORIZONTAL current y is %d and current x is %d \n", cube->player.rays.current_ray_y , cube->player.rays.current_ray_x);
// 		printf("HORIZONTAL current map char is {%c}\n", cube->level.map[cube->player.rays.current_ray_y][cube->player.rays.current_ray_x]);
// 		printf("HORIZONTAL x offset is %f and y offset is %f \n", cube->player.rays.x_offset, cube->player.rays.y_offset);
// 		if (cube->level.map[cube->player.rays.current_ray_y][cube->player.rays.current_ray_x] == '1')
// 		{
// 			cube->player.rays.horizontal_distance = cos(cube->player.rays.angle) * (cube->player.rays.ray_x - cube->player.transform.x0) - sin(cube->player.rays.angle) * (cube->player.rays.ray_y - cube->player.transform.y0); // Calculate distance
//             break;
// 		}
//         cube->player.rays.ray_x += cube->player.rays.x_offset;
//         cube->player.rays.ray_y += cube->player.rays.y_offset;
//         cube->player.rays.depth_of_field++;
// 	}
// 	if (cube->player.rays.horizontal_distance > cube->player.rays.verical_distance)
// 	{
// 		cube->player.rays.distance = cube->player.rays.verical_distance;
// 		cube->player.rays.x_intersection = cube->player.rays.ray_x;
// 		cube->player.rays.y_intersection = cube->player.rays.ray_y;
// 	}
// 	else
//     {
//         cube->player.rays.distance = cube->player.rays.horizontal_distance;
//         cube->player.rays.x_intersection = cube->player.rays.ray_x;
//         cube->player.rays.y_intersection = cube->player.rays.ray_y;
//     }
// 	int start_x = (int)cube->player.transform.x0;
//     int start_y = (int)cube->player.transform.y0;
//    	int end_x = (int)cube->player.rays.x_intersection;
//     int end_y = (int)cube->player.rays.y_intersection;
//     draw_ray(cube, start_x, start_y, end_x, end_y, 0xFF0000);
// }
