/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:07:17 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/17 18:40:00 by ssibai           ###   ########.fr       */
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

typedef struct s_level
{
	char		**map;
	char		*full_file;
	int			row_start_point;
	t_textures	textures;
	int			ceiling_color[3];
	int			floor_color[3];
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
}	t_cub3d;

/* ************************************************************************** */
/* 									parsing									  */
/* ************************************************************************** */

bool	validate_level(char *level_path, t_cub3d *cube);
bool	init_cube(t_cub3d *cube);

#endif