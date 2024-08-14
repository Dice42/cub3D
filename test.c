


typedef struct s_wall
{
	float	height;
	float	end_y;
	float	start_y;
	float	texture_y;
	float	texture_x1;
	float	texture_y_step;
}	t_wall;

void draw_walls(t_cub3d *cube, int x, float dist)
{
	t_wall wall;
	int		color;

	dist = dist * cos(cube->player.rays.angle - cube->player.transform.angle);
	wall.height = (float)(((MINIMAP_Y / 2) * HEIGHT) / dist);
	wall.texture_y = 0.0f;
	cube->player.rays.line_offset = HEIGHT / 2 - (wall.height / 2);
	wall.end_y = cube->player.rays.line_offset + wall.height;
	wall.start_y = cube->player.rays.line_offset;
	if (cube->player.rays.distance == cube->player.rays.vertical_distance)
		wall.texture_x1 = ((float)((int)cube->player.rays.intersection_y % 21)
			/ (float)(21)) * cube->data.texture->width;
	if (cube->player.rays.distance == cube->player.rays.horizontal_distance)
		wall.texture_x1 = ((float)((int)cube->player.rays.intersection_x % 21)
			/ (float)(21)) * cube->data.texture->width;
	wall.texture_y_step =  (float)cube->data.texture->height / wall.height;
	while (wall.start_y < wall.end_y)
	{
		color = get_texture_pixel(cube->data.texture, (int)wall.texture_x1,
			(int)wall.texture_y, cube);
		my_mlx_pixel_put(&cube->data.img, x, wall.start_y, color);
		wall.texture_y += wall.texture_y_step;
		wall.start_y++;
	}
}