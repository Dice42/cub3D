/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/20 22:36:51 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	init_cube(t_cub3d *cube)
{
	ft_bzero(&cube->data, sizeof(cube->data));
	ft_bzero(&cube->level, sizeof(cube->level));
	ft_bzero(&cube->player, sizeof(cube->player));
	ft_bzero(&cube->data.img, sizeof(cube->data.img));
	return (true);
}