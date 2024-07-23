/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/23 21:23:01 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	init_cube(t_cub3d *cube)
{
	ft_bzero(&cube->data, sizeof(t_mlx_data));
	ft_bzero(&cube->level, sizeof(t_level));
	ft_bzero(&cube->player, sizeof(t_player));
	ft_bzero(&cube->player.pos, sizeof(cube->player.pos));
	ft_bzero(&cube->data.img, sizeof(cube->data.img));
	return (true);
}