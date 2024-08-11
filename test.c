/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:29:42 by heltayb           #+#    #+#             */
/*   Updated: 2024/08/11 22:59:41 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>


typedef struct s_data {
    void *mlx;
    void *win;
    int width;
    int height;
    float px;
    float py;
    float pdx;
    float pdy;
    int pa;
} t_data;

# define RAD(x) (x * M_PI / 180.0)

void init(t_data *data);
int draw_player(t_data *data);
int draw(t_data *data);
int handle_keys(int keycode, t_data *data);

int handle_keys(int keycode, t_data *data)
{
    if (keycode == 0x00) // 'a' key
    {
        data->pa += 5;
        data->pa = data->pa % 360;
        data->pdx = cos(RAD(data->pa));
        data->pdy = -sin(RAD(data->pa));
    }
    if (keycode == 0x02) // 'd' key
    {
        data->pa -= 5;
        data->pa = data->pa % 360;
        data->pdx = cos(RAD(data->pa));
        data->pdy = -sin(RAD(data->pa));
    }
    if (keycode == 0x0D) // 'w' key
    {
        data->px += data->pdx * 5;
        data->py += data->pdy * 5;
    }
    if (keycode == 0x01) // 's' key
    {
        data->px -= data->pdx * 5;
        data->py -= data->pdy * 5;
    }
    if (keycode == 0x35) // 'ESC' key
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    return (0);
}


int draw_player(t_data *data)
{
    int x = (int)data->px;
    int y = (int)data->py;
    int size = 8;

    // Draw player as a small rectangle
    for (int i = -size; i < size; i++)
    {
        for (int j = -size; j < size; j++)
        {
            mlx_pixel_put(data->mlx, data->win, x + i, y + j, 0xFFFF00);
        }
    }

    // Draw player direction
    mlx_pixel_put(data->mlx, data->win, x + data->pdx * 20, y + data->pdy * 20, 0xFFFF00);
	return (0);
}

int draw(t_data *data)
{
    // Clear the window by drawing a background
    mlx_clear_window(data->mlx, data->win);

    // Draw the player
    draw_player(data);

    return (0);
}


void init(t_data *data)
{
    data->width = 1024;
    data->height = 510;
    data->px = 150;
    data->py = 400;
    data->pa = 90;
    data->pdx = cos(RAD(data->pa));
    data->pdy = -sin(RAD(data->pa));
}

int main(void)
{
    t_data data;

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.win = mlx_new_window(data.mlx, 1024, 510, "MiniLibX 2D");
    if (!data.win)
        return (1);

    init(&data);

    // Hook your drawing and key handling functions here
    mlx_loop_hook(data.mlx, draw, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_keys, &data);
    // mlx_key_hook(data.win, handle_keys, &data);
    
    mlx_loop(data.mlx);
    return (0);
}








// float	calculate_vertical_distance(t_cub3d *cube, float *ray_dir)
// {
// 	bool	subtract_mapsize;
// 	float	init_pos[2];
// 	float	step_x;
// 	float	step_y;

// 	if (ray_dir[0] > 0)
// 	{
// 		printf("looking right\n");
// 		init_pos[0] = (int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X + MINIMAP_X;
// 		step_x = MINIMAP_X;
// 	}
// 	else
// 	{
// 		init_pos[0] = ((int)(cube->player.rays.rx / MINIMAP_X) * MINIMAP_X) - 0.0001;
// 		step_x = -MINIMAP_X;
// 	}
// 	init_pos[1] = cube->player.rays.ry + (init_pos[0] - cube->player.rays.rx) * (ray_dir[1] / ray_dir[0]);
// 	step_y = step_x * (ray_dir[1] / ray_dir[0]);
// 	while (1)
// 	{
// 		int x = (int)(init_pos[0] / MINIMAP_X);
// 		int y = (int)(init_pos[1] / MINIMAP_Y);
// 		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
// 		{
// 			if (cube->level.map[y][x] == '1') 
// 			{
// 			//	draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X0000FF);
// 				cube->player.rays.vertical_intersection_x = init_pos[0];
// 				cube->player.rays.vertical_intersection_y = init_pos[1];
// 				return (init_pos[1] - cube->player.rays.ry) / ray_dir[1];
// 			}
// 			else
// 			{
// 				init_pos[0] += step_x;
// 				init_pos[1] += step_y;
// 			}
// 		}
// 		else
// 			break;
// 	}
// 	return (0);
// }




















// float	calculate_horizontal_distance(t_cub3d *cube, float *ray_dir)
// {
// 	bool	subtract_mapsize;
// 	float	init_pos[2];
// 	float	step_x;
// 	float	step_y;
// 	int x;
// 	int y;

// 	if (ray_dir[1] > 0)
// 	{
// 		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y + MINIMAP_Y;
// 		step_y = MINIMAP_Y;
// 	}
// 	else
// 	{
// 		init_pos[1] = (int)(cube->player.rays.ry / MINIMAP_Y) * MINIMAP_Y - 0.0001;
// 		step_y = -MINIMAP_Y;
// 	}
// 	init_pos[0] = cube->player.rays.rx + (init_pos[1] - cube->player.rays.ry) * (ray_dir[0] / ray_dir[1]);
// 	step_x = step_y * (ray_dir[0] / ray_dir[1]);

// 	while (1)
// 	{
// 		int x = (int)(init_pos[0] / MINIMAP_X);
// 		int y = (int)(init_pos[1] / MINIMAP_Y);
// 		if ((x >= 0 && x < cube->level.num_of_columns) && (y >= 0 && y < cube->level.num_of_rows))
// 		{
// 			if (cube->level.map[y][x] == '1')
// 			{
// 				//draw_ray(cube, (int)cube->player.rays.rx, (int)cube->player.rays.ry, (int)init_pos[0], (int)init_pos[1], 0X00FF00);
// 				cube->player.rays.horizontal_intersection_x = init_pos[0];
// 				cube->player.rays.horizontal_intersection_y = init_pos[1];
// 				return ((init_pos[0] - cube->player.rays.rx) / ray_dir[0]);
// 			}
// 			else
// 			{
// 				init_pos[0] += step_x;
// 				init_pos[1] += step_y;
// 			}
// 		}
// 		else
// 			break;
// 	}
// 	return (0);
// }







// float cast_rays_1(t_cub3d *cube)
// {
// 	float	angle;
// 	float	ray_dir[2];

// 	cube->player.rays.vertical_distance = 1000000;
// 	cube->player.rays.horizontal_distance = 1000000;
// 	angle = cube->player.rays.angle + 0.001;

	
// 	printf("*************************************\n");
// 	printf("ANGLE IS %f\n", (angle * 180/PI));
// 	ray_dir[0] = cos(angle);
// 	ray_dir[1] = sin(angle);
// 	normalize_vector(&ray_dir[0]);
// 	cube->player.rays.vertical_distance = calculate_vertical_distance(cube, &ray_dir[0]);
// 	cube->player.rays.horizontal_distance = calculate_horizontal_distance(cube, &ray_dir[0]);
// 	printf("horizontal distance is %f\n",cube->player.rays.horizontal_distance);
// 	printf("vertical distance is %f\n",cube->player.rays.vertical_distance);
// 	if (cube->player.rays.vertical_distance == 0)
// 	{
// 		cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
// 		cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
// 		cube->player.rays.clr = GREEN;
// 		return (cube->player.rays.horizontal_distance);
// 	}
// 	else if (cube->player.rays.horizontal_distance == 0)
// 	{
// 		cube->player.rays.clr = BLUE;
// 		cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
// 		cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
// 		return (cube->player.rays.vertical_distance);
// 	}
// 	if (cube->player.rays.vertical_distance > cube->player.rays.horizontal_distance) 
// 	{
// 		printf("returning the horizontal distance\n");
// 		cube->player.rays.intersection_x = cube->player.rays.horizontal_intersection_x;
// 		cube->player.rays.intersection_y = cube->player.rays.horizontal_intersection_y;
// 		cube->player.rays.clr = GREEN;
// 		return (cube->player.rays.horizontal_distance);
// 	}
// 	cube->player.rays.clr = BLUE;
// 	cube->player.rays.intersection_x = cube->player.rays.vertical_intersection_x;
// 	cube->player.rays.intersection_y = cube->player.rays.vertical_intersection_y;
// 	printf("returning the vertical distance\n");
// 	return (cube->player.rays.vertical_distance);
// }




