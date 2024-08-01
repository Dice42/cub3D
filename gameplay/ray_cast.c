

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
	printf("tan is %f\n", tan(angle));
    atan = 1 / tan(angle); // Correct atan calculation
    depth_of_field = 0;
	ntan = -tan(angle);
	ray_xy0[0] = cube->player.rays.rx;
	ray_xy0[1] = cube->player.rays.ry;

	//HORIZONTAL LINES CHECK

	printf("position y is %f nd x is %f\n", cube->player.transform.y0, cube->player.transform.x0);
	if (angle > PI) //looking down
	{
		//calculate the next y position of the ray:
		ray_xy0[1] = (((int)(cube->player.rays.ry / MINIMAP_Y)) * MINIMAP_Y) - 0.0001;
		//calculate the next x position of the ray:
		ray_xy0[0] = (cube->player.rays.ry - ray_xy0[1]) * atan + cube->player.rays.rx;
		// calculate the y offset:
		cube->player.rays.y_offset = -MINIMAP_Y;
		// calculate the x offset:
		cube->player.rays.x_offset = -MINIMAP_Y * atan;
	}
	else if (angle < PI) //looking up
	{
		//calculate the next y position of the ray:
		ray_xy0[1] = (((int)(cube->player.rays.ry / MINIMAP_Y)) * MINIMAP_Y) + MINIMAP_Y;
		//calculate the next x position of the ray:		
		ray_xy0[0] = (cube->player.rays.ry - ray_xy0[1]) * atan + cube->player.rays.rx; // Fixed calculation
		// calculate the y offset:
		cube->player.rays.y_offset = MINIMAP_Y;
		// calculate the x offset:
		cube->player.rays.x_offset = -MINIMAP_Y * atan;			
	}
	else if (angle == 0 || angle == PI) //looking right and left
	{
		printf("looking left or right\n");
		ray_xy0[0] = cube->player.rays.rx;
		ray_xy0[1] = cube->player.rays.ry;
		depth_of_field = cube->level.num_of_columns;
	}

    while (depth_of_field < cube->level.num_of_columns)
    {
        current_x = (int)(ray_xy0[0] / MINIMAP_X);
        current_y = (int)(ray_xy0[1] / MINIMAP_Y);

        if (current_x >= 0 && current_x < cube->level.num_of_columns &&
            current_y >= 0 && current_y < cube->level.num_of_rows) 
		{
            if (cube->level.map[current_y][current_x] == '1')
                break;
        }
        ray_xy0[0] += cube->player.rays.x_offset;
        ray_xy0[1] += cube->player.rays.y_offset;
        depth_of_field++;
    }
	draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)ray_xy0[0], (int)ray_xy0[1], 0xFF0000);
}
