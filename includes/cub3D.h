/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:07:17 by mohammoh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/21 21:09:02 by mohammoh         ###   ########.fr       */
=======
/*   Updated: 2024/07/22 13:00:58 by ssibai           ###   ########.fr       */
>>>>>>> 1de689764939fdf7825a1946935308a6f24312ff
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

typedef struct s_player
{
	int		start_pos[2];
	char	rot;
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
void	draw_cube(t_cub3d *cube, int x, int y);
void	draw_player(t_cub3d *cube, int x, int y);


/* ************************************************************************** */
/* 								Window Handling								  */
/* ************************************************************************** */

int		close_window(t_cub3d	*cube);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);

void 	convert_rgb_hex(t_level *level);

#endif