#include "../includes/cub3D.h"


int get_texture_pixel(t_img_data *texture, int x, int y)
{
    char *data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    int pixel_index = (y * texture->line_length) + (x * (texture->bits_per_pixel / 8));
    return *(int *)(data + pixel_index);
}


void load_textures(t_cub3d *cube)
{
    cube->data.textures[0].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.north_texture, &cube->data.textures[0].bits_per_pixel, &cube->data.textures[0].line_length);
    cube->data.textures[1].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.south_texture, &cube->data.textures[1].bits_per_pixel, &cube->data.textures[1].line_length);
    cube->data.textures[2].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.east_texture, &cube->data.textures[2].bits_per_pixel, &cube->data.textures[2].line_length);
    cube->data.textures[3].img = mlx_xpm_file_to_image(cube->data.mlx_ptr, cube->level.textures.west_texture, &cube->data.textures[3].bits_per_pixel, &cube->data.textures[3].line_length);
}

t_img_data choose_texture(t_cub3d *cube, float ray_x, float ray_y)
{
    // Placeholder logic for choosing textures
    // For a more accurate choice, use ray direction and wall orientation

    // Example logic (needs refinement based on actual ray and wall direction)
    if (/* condition for north */) 
        return cube->data.textures[0];
    else if (/* condition for south */) 
        return cube->data.textures[1];
    else if (/* condition for east */) 
        return cube->data.textures[2];
    else if (/* condition for west */) 
        return cube->data.textures[3];
    
    // Default to north if no condition matches
    return cube->data.textures[0];
}

void draw_textured_vertical_line(t_cub3d *cube, int x, int start_y, int end_y, t_img_data *texture, int texture_x)
{
    int y;
    int texture_height = texture->line_length / (texture->bits_per_pixel / 8); // Assuming square texture

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
        int color = get_texture_pixel(texture, texture_x, texture_y);
        my_mlx_pixel_put(&cube->data.img, x, y, color);
        y++;
    }
}
