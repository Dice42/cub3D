/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:07:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/05 18:05:47 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*****Sys/Libraries******/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "./libs/libft/libft.h"
# include "./libs/mlx_mac/mlx.h"
//# include "./libs/mlx_linux/mlx.h"

# define INVALID_FILE_TYPE "Error: not a valid file type\n"
# define INVALID_FILE "Error: No such file\n"
# define INVALID_FILE_INFO "Error: invalid file info\n"
# define INVALID_MAP "Error: invalid map\n"
# define INVALID_MAP_INFO "Error: invalid map information\n"
# define INVALID_MAP_TEXTURE "Error: invalid textures\n"
# define INVALID_RGB "Error: invalid map colors\n"
# define PI 3.14159265358979323846
# define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_X (((1280*64) / WIDTH) / 2)
# define MINIMAP_Y (((720*64) / HEIGHT) / 2)
# define RAD PI / 180

typedef enum keys
{
	ESC = 53,
	LOOK_RIGHT = 124,
	LOOK_LEFT = 123,
	W = 13,
	A = 0,
	S = 1,
	D = 2
}	t_keys;

typedef struct s_counters
{
	int	i;
	int	j;
	int	c;
}	t_ctr;

typedef struct s_transform
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	float	dx;
	float	dy;
	float	angle;
}	t_transform;

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
	float	rx;
	float	ry;
	float	angle;
	float	angle_step;
	float	verical_distance;
	float	horizontal_distance;
	float	distance;
	int		clr;
}	t_rays;

typedef struct s_player
{
	t_rays		rays;
	t_transform	transform;
	char		orientation;
	bool		move_dir[4];
	bool		move;
	bool		rot_dir[2];
	bool		rotate;
}	t_player;

typedef struct s_textures
{
	char	*north_texture;
	char	*west_texture;
	char	*east_texture;
	char	*south_texture;
}	t_textures;

/*	
		column		    column3
row	______|________|_________|_____
				 
	______|________|_________|_____
*/
typedef struct s_level
{
	char		**map_info;
	char		**map;
	bool		**visited;
	char		*full_file;
	int			row_start_point;
	t_textures	textures;
	int			ceiling_color[3];
	char		*ceiling_color_hex;
	int			floor_color[3];
	char		*floor_color_hex;
	int			num_of_rows;
	int			num_of_columns;
	bool		start;
}	t_level;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_img_data;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win;
	t_img_data		img;
}	t_mlx_data;

typedef struct s_cub3d
{
	t_mlx_data	data;
	t_level		level;
	t_player	player;

}	t_cub3d;

/* ************************************************************************** */
/* 								General Utils								  */
/* ************************************************************************** */

void	init_ctrs(t_ctr *ctr);
bool	init_cube(t_cub3d *cube);
void 	convert_rgb_hex(t_level *level);

/* ************************************************************************** */
/* 									Parsing									  */
/* ************************************************************************** */

bool	validate_level(char *level_path, t_level *level, t_player *player);
bool	validate_textures_info(t_level *level);
bool	validate_map(t_level *level, t_player *player);
void	copy_map(t_level *level);
bool	check_sides(int x, int y, t_level *level, char *expected);
bool	check_if_valid(int x, int y, t_level *level);
void	fill_visited(bool **visited, char **map, int n_rows);
void	get_columns_num(t_level *level);

/* ************************************************************************** */
/* 									ERROR HANDLING							  */
/* ************************************************************************** */

void	error_handler(char *err_msg, t_cub3d *cub, t_level *level, bool free);

/* ************************************************************************** */
/* 									Gameplay								  */
/* ************************************************************************** */

void	ft_start(t_cub3d *cube);
int		handle_keyrelease(int key, t_cub3d *cube);
int		handle_keypress(int key, t_cub3d *cube);
bool	level_collision(t_cub3d *cube, int x, int y, bool	player_collision);

/* ************************************************************************** */
/* 								Player Controller							  */
/* ************************************************************************** */

void	init_player_pos(t_cub3d *cube, int x, int y);
//bool	player_collisions(t_cub3d *cube, int x, int y);
void    cast_ray(t_cub3d *cube);
float	cast_rays(t_cub3d *cube); //actual raycaster
void	player_movement(t_cub3d *cube, bool dir[4]);
void	player_rotation(t_cub3d *cube, bool rot_dir[2]);
void	move_player(t_cub3d *cube, int dir, bool is_vertical);
void	update_player_direction(t_cub3d *cube);

/* ************************************************************************** */
/* 									Visuals									  */
/* ************************************************************************** */

void	init_draw_player(t_cub3d *cube, int x, int y);
void	draw_line(t_cub3d *cube);
void	draw_ray(t_cub3d *cube, int x0, int y0, int x1, int y1, int color);
void	draw_player(t_cub3d *cube);
void	draw_borders(t_cub3d *cube, int x, int y);
int		draw_mini_map(t_cub3d *cube);
void	cast_rays_from_player(t_cub3d *cube);
void	draw_floor(t_cub3d *cube);
void	draw_ceiling(t_cub3d *cube);
void	bresenham(t_cub3d *cube, int x1, int y1);

/* ************************************************************************** */
/* 								Window Handling								  */
/* ************************************************************************** */

void	init_mlx_img(t_cub3d *cube);
int		close_window(t_cub3d *cube);
void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color);



#endif