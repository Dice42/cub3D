/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by ssibai            #+#    #+#             */
/*   Updated: 2024/08/13 23:01:42 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	init_cube(t_cub3d *cube)
{
	ft_bzero(&cube->data, sizeof(t_mlx_data));
	ft_bzero(&cube->level, sizeof(t_level));
	ft_bzero(&cube->player, sizeof(t_player));
	ft_bzero(&cube->player.transform, sizeof(cube->player.transform));
	ft_bzero(&cube->data.img, sizeof(cube->data.img));
	return (true);
}
