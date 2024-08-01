/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:12:13 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/30 18:32:53 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void load_textures(t_cub3d *cube)
{
    cube->data.textures[0].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.north_texture, &cube->data.textures[0].bits_per_pixel, &cube->data.textures[0].line_length);
    cube->data.textures[1].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.south_texture, &cube->data.textures[1].bits_per_pixel, &cube->data.textures[1].line_length);
    cube->data.textures[2].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.east_texture, &cube->data.textures[2].bits_per_pixel, &cube->data.textures[2].line_length);
    cube->data.textures[3].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.west_texture, &cube->data.textures[3].bits_per_pixel, &cube->data.textures[3].line_length);
}

int get_texture_pixel(t_img_data *texture, int x, int y)
{
    char *data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    int pixel_index = (y * texture->line_length) + (x * (texture->bits_per_pixel / 8));
    return *(int *)(data + pixel_index);
}
void draw_textured_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, t_img_data *texture, int texture_x)
{
    int y;
    int texture_height = texture->line_length / (texture->bits_per_pixel / 8); // Calculate texture height

    if (start_y > end_y)
    {
        int temp = start_y;
        start_y = end_y;
        end_y = temp;
    }
    y = start_y;
    while (y <= end_y)
    {
        int texture_y = ((y - start_y) * texture_height) / (end_y - start_y);
        if ((texture_y < 0) || (texture_y >= texture_height))
            texture_y = 0;
        printf("texture_x: %d, texture_y: %d\n", texture_x, texture_y);
        int color = get_texture_pixel(texture, texture_x, texture_y);
        printf("y: %d, color: %d\n", y, color);
        my_mlx_pixel_put(&cube->data.img, x, y, color);
        y++;
    }
}

void minimap_rays(t_cub3d *cube, int x)
{
    float speed = 2.0;
    float ray_x = cube->player.rays.rx;
    float ray_y = cube->player.rays.ry;
    float dir_x = cos(cube->player.rays.angle);
    float dir_y = sin(cube->player.rays.angle);

    // Trace the ray until it hits a wall
    while (level_collision(cube, ray_x, ray_y, false))
    {
        // my_mlx_pixel_put(&cube->data.img, ray_x, ray_y, 0x00FF00);
        ray_x += dir_x * speed;
        ray_y += dir_y * speed;
    }

    cube->player.rays.rx1 = ray_x;
    cube->player.rays.ry1 = ray_y;

    float distance = sqrt(pow(ray_x - cube->player.rays.rx, 2) + pow(ray_y - cube->player.rays.ry, 2));
    if (distance < EPSILON)
        distance = EPSILON;

    float line_height = (3 * HEIGHT) / distance;
    if (line_height >= HEIGHT)
        line_height = HEIGHT;

    if (line_height < MIN_HEIGHT)
        line_height = MIN_HEIGHT;

    int screen_center_y = HEIGHT / 2;
    int line_start_y = screen_center_y - line_height / 2;
    int line_end_y = screen_center_y + line_height / 2;
    // load_textures(cube);

    float wall_x = (ray_x - (int)ray_x) * cube->data.textures[0].line_length;
    int texture_x = (int)wall_x;

    draw_textured_vertical_line(cube, x, line_start_y, line_end_y, &cube->data.textures[0], texture_x);
}


/**
 * @brief this function casts rays from the player 
 * 
 * @param cube 
 */
void cast_rays_from_player(t_cub3d *cube)
{
    cube->player.rays.rx = cube->player.transform.x0 + 3;
    cube->player.rays.ry = cube->player.transform.y0 + 3;
    cube->player.rays.angle = cube->player.transform.angle - (30.0 * RAD);
    cube->player.rays.angle_step = (60 * RAD) / WIDTH;  // Adjust step based on screen width
    load_textures(cube);
    for (int x = 0; x < WIDTH; x++)  // Loop through every pixel width
    {
        minimap_rays(cube, x);
        cube->player.rays.angle += cube->player.rays.angle_step;
    }
}
