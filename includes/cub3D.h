/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:07:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/20 15:32:40 by ssibai           ###   ########.fr       */
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
# include "./libft/libft.h"
# include "mlx/mlx.h"

#define texture_path "levels/textures/"

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
	int			floor_color[3];
	int			num_of_rows;
	int			num_of_columns;
}	t_level;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
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
bool	recursive_call(int x, int y, t_level *level, char *expected);
void	get_columns_num(t_level *level);

/* ************************************************************************** */
/* 									Gameplay								  */
/* ************************************************************************** */

void	ft_start(t_cub3d *cube);



/* ************************************************************************** */
/* 								Window Handling								  */
/* ************************************************************************** */

int	close_window(t_cub3d	*cube);

#endif