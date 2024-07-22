/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:07:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/22 20:07:08 by ssibai           ###   ########.fr       */
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


typedef struct node
{
	int			value;
	struct node	*next;
}	t_node;

typedef struct s_player
{
	int		pos[2];
	char	orientation;
	bool	move;
	bool	rotate;
	bool	move_dir[4];
//	t_node	*move_dir;
	float	forward_vector;
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
	int			floor_color[3];
	int			num_of_rows;
	int			num_of_columns;
	bool		start;
}	t_level;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_data		img;
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

/* ************************************************************************** */
/* 									Parsing									  */
/* ************************************************************************** */

bool	validate_level(char *level_path, t_level *level, t_player *player);
bool	validate_textures_info(t_level *level);
bool	validate_map(t_level *level, t_player *player);
bool	check_sides(int x, int y, t_level *level, char *expected);
void	copy_map(t_level *level);
void	fill_visited(bool **visited, char **map, int n_rows);
bool	check_if_valid(int x, int y, t_level *level);

/* ************************************************************************** */
/* 									ERROR HANDLING							  */
/* ************************************************************************** */

void	error_handler(char *err_msg, t_cub3d *cub, t_level *level, bool free);
void	get_columns_num(t_level *level);

/* ************************************************************************** */
/* 									Gameplay								  */
/* ************************************************************************** */

void	ft_start(t_cub3d *cube);

/* ************************************************************************** */
/* 								Player Controller							  */
/* ************************************************************************** */

void	player_movement(t_cub3d *cube);
void	draw_player(t_cub3d *cube);
int		get_direction(int dr);
void	move_dir_flipflop(t_cub3d *cube, int dir);

/* ************************************************************************** */
/* 									Visuals									  */
/* ************************************************************************** */

void	draw_borders(t_cub3d *cube, int x, int y);
void	init_draw_player(t_cub3d *cube, int x, int y);
int		draw_mini_map(t_cub3d *cube);

/* ************************************************************************** */
/* 								Window Handling								  */
/* ************************************************************************** */

int		close_window(t_cub3d	*cube);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);

#endif