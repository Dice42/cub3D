/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:30 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/16 16:30:10 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	init_cube(t_cub3d *cube)
{
	ft_bzero(&cube->data, sizeof(cube->data));
	ft_bzero(&cube->level, sizeof(cube->level));
	return (true);
}