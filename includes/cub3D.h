/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:07:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 23:11:16 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libs/libft/libft.h"
# include "./libs/mlx_mac/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INVALID_FILE_TYPE "Error: not a valid file type\n"
# define INVALID_FILE "Error: No such file\n"
# define INVALID_FILE_INFO "Error: invalid file info\n"
# define INVALID_MAP "Error: invalid map\n"
# define INVALID_MAP_INFO "Error: invalid map information\n"
# define INVALID_MAP_TEXTURE "Error: invalid textures\n"
# define INVALID_RGB "Error: invalid map colors\n"
# define PI 3.14159265358979323846
# define WIDTH 1080
# define HEIGHT 1080
# define MINIMAP_X 64
# define MINIMAP_Y 64
# define FOV 60.0
# define GREEN 0X00FF00
# define BLUE 0X0000FF

typedef enum keys
{
	ESC = 53,
	LOOK_RIGHT = 124,
	LOOK_LEFT = 123,
	W = 13,
	A = 0,
	S = 1,
	D = 2
}				t_keys;

typedef struct s_counters
{
	int			i;
	int			j;
	int			c;
	int			x;
	int			y;
}				t_ctr;

typedef struct s_draw_line
{
	float		height;
	float		end_y;
	float		offset;
	float		texture_y;
	float		texture_x;
	float		texture_y_step;
	int			color;
}				t_draw_line;

typedef struct s_transform
{
	float		x0;
	float		y0;
	float		x1;
	float		y1;
	float		map_x0;
	float		map_x1;
	float		map_y0;
	float		map_y1;
	float		dx;
	float		dy;
	float		angle;
}				t_transform;

/**
 * @brief everything related to rays
 *
 * side represents the side the ray intersects with
 * (vertical or horizontal)
 *
 * vx and vy coordinates of the vertical intersection
 * point where the ray hits a wall.
 *
 */
typedef struct s_rays
{
	float		rx;
	float		ry;
	float		horizontal_point_x;
	float		horizontal_point_y;
	float		vertical_point_x;
	float		vertical_point_y;
	float		point_x;
	float		point_y;
	float		angle;
	float		angle_step;
	float		vertical_distance;
	float		horizontal_distance;
	float		distance;
	float		prev_distance;
	int			clr;
}				t_rays;

typedef struct s_player
{
	t_rays		rays;
	t_transform	transform;
	char		orientation;
	bool		move_dir[4];
	bool		move;
	bool		rot_dir[2];
	bool		rotate;
}				t_player;

typedef struct s_textures
{
	char		*north_texture;
	char		*west_texture;
	char		*east_texture;
	char		*south_texture;
}				t_textures;

typedef struct s_level
{
	char		**map_info;
	char		**map;
	char		**init_map;
	bool		**visited;
	char		*full_file;
	int			row_start_point;
	t_textures	textures;
	char		*ceiling_clr_hex;
	char		*floor_clr_hex;
	int			ceiling_color[3];
	int			floor_color[3];
	int			floor_clr;
	int			ceiling_clr;
	int			num_of_rows;
	int			num_of_columns;
	bool		start;
}				t_level;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img_data;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win;
	t_img_data	img;
	t_img_data	textures[4];
	t_img_data	*texture;
}				t_mlx_data;

typedef struct s_cub3d
{
	t_mlx_data	data;
	t_level		level;
	t_player	player;

}				t_cub3d;

/* ************************************************************************** */
/* 								General Utils								  */
/* ************************************************************************** */

void			init_ctrs(t_ctr *ctr);
bool			init_cube(t_cub3d *cube);
void			init_draw_line(t_draw_line *line);
void			convert_rgb_hex(t_level *level);

/* ************************************************************************** */
/* 									Parsing									  */
/* ************************************************************************** */

bool			validate_level(char *level_path, t_level *level,
					t_player *player);
bool			validate_textures_info(t_level *level);
bool			validate_map(t_level *level, t_player *player);
bool			find_colors_info(t_level *level);
void			copy_init_map(t_level *level);
void			make_map(t_level *level);
bool			check_sides(int x, int y, t_level *level, char *expected);
bool			check_if_valid(int x, int y, t_level *level);
void			fill_visited(t_level *level, bool **visited, int n_rows);
void			get_columns_num(t_level *level);
bool			check_space_surroundings(t_level *level, int x, int y);
bool			check_map_content(char **map, t_ctr *ctr, t_player *plyr,
					bool *found);
char			*set_expected(int x, int y, t_level *level);

/* ************************************************************************** */
/* 									ERROR HANDLING							  */
/* ************************************************************************** */

void			error_handler(char *err_msg, t_cub3d *cub, t_level *level,
					bool free);

/* ************************************************************************** */
/* 									Gameplay								  */
/* ************************************************************************** */

void			ft_start(t_cub3d *cube);
int				handle_keyrelease(int key, t_cub3d *cube);
int				handle_keypress(int key, t_cub3d *cube);
bool			level_collision(t_cub3d *cube, int x, int y,
					bool player_collision);

/* ************************************************************************** */
/* 									RAYCASTS							  	  */
/* ************************************************************************** */

float			cast_rays(t_cub3d *cube); // actual raycaster
float			calc_horizontal_distance(t_cub3d *cube, float *ray_dir);
float			calc_vertical_distance(t_cub3d *cube, float *ray_dir);

/* ************************************************************************** */
/* 									Texture									  */
/* ************************************************************************** */

void			load_textures(t_cub3d *cube);
int				get_texture_pixel(t_img_data *texture, int x, int y,
					t_cub3d *cube);
void			choose_texture(t_cub3d *cube, int quarter);
void			check_coordinate(t_cub3d *cube);

/* ************************************************************************** */
/* 								Player Controller							  */
/* ************************************************************************** */

void			init_player_pos(t_cub3d *cube, int x, int y);
void			init_player(t_cub3d *cube);
float			cast_rays(t_cub3d *cube); // actual raycaster
void			player_movement(t_cub3d *cube, bool dir[4]);
void			player_rotation(t_cub3d *cube, bool rot_dir[2]);
void			move_player(t_cub3d *cube, int dir, bool is_vertical);
void			update_player_direction(t_cub3d *cube);

/* ************************************************************************** */
/* 									Visuals									  */
/* ************************************************************************** */

void			draw_line(t_cub3d *cube);
void			draw_map(t_cub3d *cube);
void			draw_player(t_cub3d *cube);
void			draw_borders(t_cub3d *cube, int x, int y);
void			draw_mini_map(t_cub3d *cube);
void			draw_3d_rays(t_cub3d *cube);
void			draw_floor(t_cub3d *cube);
void			draw_ceiling(t_cub3d *cube);

/* ************************************************************************** */
/* 								Window Handling								  */
/* ************************************************************************** */

void			init_mlx_img(t_cub3d *cube);
int				close_window(t_cub3d *cube);
void			my_mlx_pixel_put(t_img_data *img, int x, int y, int color);

#endif