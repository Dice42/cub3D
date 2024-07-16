/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/16 21:39:18 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

bool	init_cube(t_cub3d *cube)
{
	ft_bzero(&cube->data, sizeof(cube->data));
	ft_bzero(&cube->level, sizeof(cube->level));
	return (true);
}