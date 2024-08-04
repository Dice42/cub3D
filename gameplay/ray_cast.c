

#include "../includes/cub3D.h"


void draw_ray(t_cub3d *cube, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	int e2;

	//printf("x0 is (%d)	y0 is (%d)\n", x0, y0 );
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


float cast_rays(t_cub3d *cube)
{
    float angle;
    float init_pos[2];
    float ray_length[2] = {0};
    float ray_dir_x;
    float ray_dir_y;
    float step_x;
    float step_y;

    angle = cube->player.rays.angle + 0.001;

    ray_dir_x = cos(angle);
    ray_dir_y = sin(angle);

    // Handle vertical rays
    if (ray_dir_x == 0) {
        if (ray_dir_y > 0) {
            init_pos[1] = ((int)(cube->player.rays.ry / MINIMAP_Y) + 1) * MINIMAP_Y;
        } else {
            init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
        }
        init_pos[0] = cube->player.rays.rx;  // Vertical ray, so no x adjustment

        step_y = (ray_dir_y > 0) ? MINIMAP_Y : -MINIMAP_Y;

        while (1) {
            int x = (int)(init_pos[0] / MINIMAP_X);
            int y = (int)(init_pos[1] / MINIMAP_Y);

            if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
                if (cube->level.map[y][x] == '1') {
                    ray_length[0] = (init_pos[1] - cube->player.rays.ry) / ray_dir_y;
                    draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
                    break;
                } else {
                    init_pos[1] += step_y;
                }
            } else {
                break;
            }
        }
    } else {
        // Non-vertical rays
        init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
        if (ray_dir_x > 0)
            init_pos[0] += MINIMAP_X;
        else
            init_pos[0] -= MINIMAP_X;

        init_pos[1] = cube->player.rays.ry + (init_pos[0] - cube->player.rays.rx) * (ray_dir_y / ray_dir_x);
        step_x = (ray_dir_x > 0) ? MINIMAP_X : -MINIMAP_X;
        step_y = step_x * (ray_dir_y / ray_dir_x);

        while (1) {
            int x = (int)(init_pos[0] / MINIMAP_X);
            int y = (int)(init_pos[1] / MINIMAP_Y);

            if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
                if (cube->level.map[y][x] == '1') {
                    ray_length[0] = (init_pos[1] - cube->player.rays.ry) / ray_dir_y;
                    draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
                    break;
                } else {
                    init_pos[0] += step_x;
                    init_pos[1] += step_y;
                }
            } else {
                break;
            }
        }
    }

    // Handle horizontal rays
    if (ray_dir_y == 0) {
        if (ray_dir_x > 0) {
            init_pos[0] = ((int)(cube->player.rays.rx / MINIMAP_X) + 1) * MINIMAP_X;
        } else {
            init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
        }
        init_pos[1] = cube->player.rays.ry;  // Horizontal ray, so no y adjustment

        step_x = (ray_dir_x > 0) ? MINIMAP_X : -MINIMAP_X;

        while (1) {
            int x = (int)(init_pos[0] / MINIMAP_X);
            int y = (int)(init_pos[1] / MINIMAP_Y);

            if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
                if (cube->level.map[y][x] == '1') {
                    ray_length[1] = (init_pos[0] - cube->player.rays.rx) / ray_dir_x;
                    draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
                    break;
                } else {
                    init_pos[0] += step_x;
                }
            } else {
                break;
            }
        }
    } else {
        // Non-horizontal rays
        init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
        if (ray_dir_y > 0)
            init_pos[1] += MINIMAP_Y;
        else
            init_pos[1] -= MINIMAP_Y;

        init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry) * (ray_dir_x / ray_dir_y);
        step_y = (ray_dir_y > 0) ? MINIMAP_Y : -MINIMAP_Y;
        step_x = step_y * (ray_dir_x / ray_dir_y);

        while (1) {
            int x = (int)(init_pos[0] / MINIMAP_X);
            int y = (int)(init_pos[1] / MINIMAP_Y);

            if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows)) {
                if (cube->level.map[y][x] == '1') {
                    ray_length[1] = (init_pos[1] - cube->player.rays.ry) / ray_dir_y;
                    draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
                    break;
                } else {
                    init_pos[0] += step_x;
                    init_pos[1] += step_y;
                }
            } else {
                break;
            }
        }
    }

    // Return the shortest ray length
    printf("ray 0 is %f and ray 1 is %f\n ", ray_length[0], ray_length[1]);
    if (ray_length[0] == 0 && ray_length[1] == 0)
        return 0;
    else if (ray_length[0] == 0)
        return ray_length[1];
    else if (ray_length[1] == 0)
        return ray_length[0];
    return ((ray_length[1] > ray_length[0]) ? ray_length[0] : ray_length[1]);
}




// float	cast_rays(t_cub3d *cube)
// {
// 	float	angle;
// 	float	init_pos[2];
// 	float	ray_length[2] = {0};
// 	float	ray_dir_x;
// 	float	ray_dir_y;
// 	float	len;

// 	angle = cube->player.rays.angle;

// 	//VERTICAL CHECKS
// 	init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X;
// 	ray_dir_x = cos(angle);
// 	ray_dir_y = sin(angle);
// 	if (ray_dir_x > 0)
// 		init_pos[0] += MINIMAP_X;
// 	else if (ray_dir_x < 0)
// 		init_pos[0] -= MINIMAP_X;
// 	//printf("angle is : %f\n", angle);
// 	printf("RAY DIR X IS: %f\n", ray_dir_x);
// 	printf("RAY DIR y IS: %f\n", ray_dir_y);
// 	float magnitude = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
// 	if (magnitude > 0) {
// 		ray_dir_x /= magnitude;
// 		ray_dir_y /= magnitude;
// 	}
// 	init_pos[1] = cube->player.rays.ry + (init_pos[0] - cube->player.rays.rx) * (ray_dir_y / ray_dir_x);
// 	float step_x = (ray_dir_x > 0) ? MINIMAP_X : -MINIMAP_X;
// 	float step_y = step_x * (ray_dir_y / ray_dir_x);

// 	while (1)
// 	{
// 		int x = (int)(init_pos[0] / MINIMAP_X);
// 		int y = (int)(init_pos[1] / MINIMAP_Y);
		
// 		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
// 		{
// 			if (cube->level.map[y][x] == '1')
// 			{
// 				//printf("HIT at x %d y %d\n", x, y);
// 				ray_length[0] = (init_pos[1] - cube->player.rays.ry) / sin(angle);
// 			//	printf("init_pos[1] %f and length is %f\n", init_pos[1],ray_length[0]);
// 			//	printf("step_y: %f\n", step_y);
// 				draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
// 				break;
// 			}
// 			else
// 			{
// 				init_pos[0] += step_x;
// 				init_pos[1] += step_y;
// 			}
// 		}
// 		else
// 		{
// 			break;
// 		}
// 	}

// 	//MUST ADD CHECKS FOR WHEN THE RAY IS LOOKING DIRECTLY TO THE RIGHT OR DIRECTLY TO THE LEFT.


// 	//HORIZONTAL CHECKS
// 	init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y;
// 	ray_dir_x = cos(angle);
// 	ray_dir_y = sin(angle);
// 	if (ray_dir_y > 0)
// 		init_pos[1] += MINIMAP_Y;
// 	else if (ray_dir_y < 0)
// 		init_pos[1] -= MINIMAP_Y;
// 	//printf("RAY DIR X IS: %f\n", ray_dir_x);
// 	init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry) * (ray_dir_x / ray_dir_y);
// 	step_y = (ray_dir_y > 0) ? MINIMAP_Y : -MINIMAP_Y;
// 	step_x = step_y * (ray_dir_x / ray_dir_y);

// 	while (1)
// 	{
// 		int x = (int)(init_pos[0] / MINIMAP_X);
// 		int y = (int)(init_pos[1] / MINIMAP_Y);
		
// 		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
// 		{
// 			if (cube->level.map[y][x] == '1')
// 			{
// 				//printf("HIT at x %d y %d\n", x, y);
// 				ray_length[1] = (init_pos[1] - cube->player.rays.ry) / sin(angle);
// 				draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
// 				break;
// 			}
// 			else
// 			{
// 				init_pos[0] += step_x;
// 				init_pos[1] += step_y;
// 			}
// 		}
// 		else
// 		{
// 			break;
// 		}
// 	}
// 	// //printf("ray length [1] is : (%f) ray length [0] is : (%f)\n", ray_length[1], ray_length[0]);
// 	printf("ray 0 is %f and ray 1 is %f\n ", ray_length[0], ray_length[1]);
// 	if (ray_length[0] == 0)
// 		return (ray_length[1]);
// 	else if (ray_length[1] == 0)
// 		return (ray_length[0]);
// 	return ((ray_length[1] > ray_length[0]) ? ray_length[0] : ray_length[1]);
// }















void	cast_ray(t_cub3d *cube)
{
	float	cotan;
	float	ntan;
	float	angle;
	float	ray_xy0[2];
	float	ray_xy1[2];
	int		depth_of_field;
	int		current_x;
	int		current_y;
	float	vertical_distance;
	float	horizontal_distance;

	vertical_distance = 0.0;
	horizontal_distance = 0.0;

	angle = cube->player.rays.angle;
	if (tan(angle) != 0)
		cotan = 1 / tan(angle); // Correct cotan calculation
	else
		cotan = 0;
	depth_of_field = 0;
	ntan = -tan(angle);
	ray_xy0[0] = cube->player.rays.rx;
	ray_xy0[1] = cube->player.rays.ry;

	ray_xy1[0] = cube->player.rays.rx;
	ray_xy1[1] = cube->player.rays.ry;
	//printf("tan is %f\n", tan(angle));
	
	float	temp_ray_length = 0.5;

float x , y;
	// while (1)
	// {
	// 	x = (cube->player.rays.rx + MINIMAP_X * ray_length* cos(angle)) / MINIMAP_X;
	// 	y = (cube->player.rays.ry + MINIMAP_Y * ray_length * sin(angle)) / MINIMAP_Y;
	// 	if ( (int)x >= 0 && (int)x < cube->level.num_of_columns &&
    //       	(int)y >= 0 && (int)y < cube->level.num_of_rows)
	// 		{
	// 			if (cube->level.map[(int)y][(int)x] == '1')
	// 			{
	// 				printf("HIT at x %d y %d", (int)x, (int)y);
	// 				draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, x * MINIMAP_X, y * MINIMAP_Y, 0xFF0000);
	// 				break;
	// 			}
	// 			else
	// 			{
	// 				ray_length += 0.5;
	// 			}
	// 		}
	// }

}
