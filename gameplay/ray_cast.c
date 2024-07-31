

#include "../includes/cub3D.h"


void draw_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, int color)
{
    int y;

    if (start_y > end_y)
    {
        int temp = start_y;
        start_y = end_y;
        end_y = temp;
    }

    y = start_y;
    while (y <= end_y)
    {
        my_mlx_pixel_put(&cube->data.img, x, y, color);
        y++;
    }
}

void	cast_ray(t_cub3d *cube)
{
	cube->player.rays.depth_of_field = 0;
	//vertical intersection, which is why we set the x offset to just the size of the side (minimap x)
	if (cos(cube->player.rays.angle) > 0.001) //looking towards left, since cos(angle) is grater than 0.001
	{
        cube->player.rays.ray_x = (((int)cube->player.transform.x0 / MINIMAP_X) * MINIMAP_X) + MINIMAP_X;
        cube->player.rays.ray_y = (cube->player.transform.x0 - cube->player.rays.ray_x) * tan(cube->player.rays.angle) + cube->player.transform.y0;
		cube->player.rays.x_offset = MINIMAP_X;
        cube->player.rays.y_offset = -cube->player.rays.x_offset * tan(cube->player.rays.angle);
	}
	else if (cos(cube->player.rays.angle) < -0.001) //looking towards right, since cos(angle) is grater than 0.001
	{
        cube->player.rays.ray_x = (((int)cube->player.transform.x0 / MINIMAP_X) * MINIMAP_X) - 0.0001;
		cube->player.rays.ray_y = (cube->player.transform.x0 - cube->player.rays.ray_x) * tan(cube->player.rays.angle) + cube->player.transform.y0;
		cube->player.rays.x_offset = -MINIMAP_X;
        cube->player.rays.y_offset = -cube->player.rays.x_offset * tan(cube->player.rays.angle);
	}
	else //looking straight right or left
	{
		cube->player.rays.ray_x = cube->player.transform.x0;
		cube->player.rays.ray_y = (int) cube->player.transform.y0;
        cube->player.rays.depth_of_field = cube->level.num_of_columns;
	}
	//loop through them till we hit a wall
	while (cube->player.rays.depth_of_field < cube->level.num_of_columns)
	{
		cube->player.rays.current_ray_x = (int)(cube->player.rays.ray_x / MINIMAP_X);
	   	cube->player.rays.current_ray_y = (int)(cube->player.rays.ray_y / MINIMAP_Y);
		printf("current y is %d and current x is %d \n", cube->player.rays.current_ray_x , cube->player.rays.current_ray_y);
		if (!level_collision(cube, cube->player.rays.current_ray_x, cube->player.rays.current_ray_y, false))
		{
			cube->player.rays.verical_distance = cos(cube->player.rays.angle) * (cube->player.rays.ray_x - cube->player.transform.x0) - sin(cube->player.rays.angle) * (cube->player.rays.ray_y - cube->player.transform.y0); // Calculate distance
            break;
		}
        cube->player.rays.ray_x += cube->player.rays.x_offset;
        cube->player.rays.ray_y += cube->player.rays.y_offset;
        cube->player.rays.depth_of_field++;
	}




	//calculate horizontal line intersections for sin(angle) > 0.001 for looking
	if (sin(cube->player.rays.angle) > 0.001) //looking towards up, since sin(angle) is grater than 0.001
	{
        cube->player.rays.ray_y = (((int)cube->player.transform.y0 / MINIMAP_Y) * MINIMAP_Y) - 0.0001;
        cube->player.rays.ray_x = (cube->player.transform.y0 - cube->player.rays.ray_y) * (1 / tan(cube->player.rays.angle)) + cube->player.transform.x0;
		cube->player.rays.y_offset = -MINIMAP_Y;
        cube->player.rays.x_offset = -cube->player.rays.y_offset * (1 / tan(cube->player.rays.angle));
	}
	else if (sin(cube->player.rays.angle) < -0.001) //looking towards right, since sin(angle) is grater than 0.001
	{
        cube->player.rays.ray_y = (((int)cube->player.transform.y0 / MINIMAP_Y) * MINIMAP_Y) + MINIMAP_Y;
		cube->player.rays.ray_x = (cube->player.transform.y0 - cube->player.rays.ray_y) * (1 / tan(cube->player.rays.angle)) + cube->player.transform.x0;
		cube->player.rays.y_offset = MINIMAP_Y;
        cube->player.rays.x_offset = -cube->player.rays.y_offset * (1 / tan(cube->player.rays.angle));
	}
	else //looking straight right or left
	{
		cube->player.rays.ray_x = cube->player.transform.x0;
		cube->player.rays.ray_y = (int) cube->player.transform.y0;
        cube->player.rays.depth_of_field = cube->level.num_of_rows;
	}
	//loop through them till we hit a wall
	while (cube->player.rays.depth_of_field < cube->level.num_of_rows)
	{
		cube->player.rays.current_ray_x = (int)(cube->player.rays.ray_x / MINIMAP_X);
	   	cube->player.rays.current_ray_y = (int)(cube->player.rays.ray_y / MINIMAP_Y);
		if (!level_collision(cube, cube->player.rays.current_ray_x, cube->player.rays.current_ray_y, false))
		{
			cube->player.rays.horizontal_distance = cos(cube->player.rays.angle) * (cube->player.rays.ray_x - cube->player.transform.x0) - sin(cube->player.rays.angle) * (cube->player.rays.ray_y - cube->player.transform.y0); // Calculate distance
            break;
		}
        cube->player.rays.ray_x += cube->player.rays.x_offset;
        cube->player.rays.ray_y += cube->player.rays.y_offset;
        cube->player.rays.depth_of_field++;
	}

	if (cube->player.rays.horizontal_distance > cube->player.rays.verical_distance)
	{
		cube->player.rays.distance = cube->player.rays.verical_distance;
		cube->player.rays.x_intersection = cube->player.rays.ray_x;
		cube->player.rays.y_intersection = cube->player.rays.ray_y;
	}
	else
    {
        cube->player.rays.distance = cube->player.rays.horizontal_distance;
        cube->player.rays.x_intersection = cube->player.rays.ray_x;
        cube->player.rays.y_intersection = cube->player.rays.ray_y;
    }
	int start_x = (int)cube->player.transform.x0;
    int start_y = (int)cube->player.transform.y0;
   // int end_x = (int)cube->player.rays.x_intersection;
    int end_y = (int)cube->player.rays.y_intersection;
    draw_vertical_line(cube, start_x, start_y, end_y, 0xFF0000);
}


//send rx and ry of each ray to the function
// void    cast_ray(t_cub3d *cube)
// {
//     float     quotient;
//     float   atan = -1/tan(cube->player.rays.angle);
//     float   x_offset;
//     float   y_offset;
//     int     dof; //depth of field
//     int     mx = 0;
//     int     my = 0;
//     int     map_index;
//     int     rx;
//     int     ry;

//     rx = cube->player.rays.rx;
//     ry = cube->player.rays.ry;
//     y_offset = 0;
//     x_offset = 0;
//     dof = 0;
//     //check the direction where the player is looking
//     if (cube->player.rays.angle > PI) //looking down
//     {
//         //find the closest grid line from the player relative to his y position
//         //player y position 
//         y_offset = -64;
//         quotient = cube->player.transform.y0 / 64;
//         ry = (quotient * 64 )- 0.0001;
//         rx = (cube->player.transform.y0 - cube->player.rays.ry) * atan + cube->player.transform.x0;
//         x_offset = -y_offset * atan;
//     }
//     if (cube->player.rays.angle < PI)
//     {
//         y_offset = 64;
//         quotient = cube->player.transform.y0 / 64;
//         ry = (quotient * 64) + 64;
//         rx = (cube->player.transform.y0 - cube->player.rays.ry) * atan + cube->player.transform.x0;
//         x_offset = -y_offset * atan;
//      }
//     if (cube->player.rays.angle == PI || cube->player.rays.angle == 0) //will never hit a vertical line
//     {
//         rx = cube->player.transform.x0;
//         ry = cube->player.transform.y0;
//         dof = 8;
//     }

//     while (dof < 8)
//     {
//         mx = rx / 64;
//         my = ry / 64;
//         map_index = my * (cube->level.num_of_columns + mx);
//         if (map_index < cube->level.num_of_columns * cube->level.num_of_rows && cube->level.map[my][mx] == '1')
//             break ;
//         else
//         {
//             rx += x_offset;
//             ry += y_offset;
//         }
//         my_mlx_pixel_put(&cube->data.img, rx, ry, 0x00FF00);
//         dof ++;
//     }
// }