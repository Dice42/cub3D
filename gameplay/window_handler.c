/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:53:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/20 14:55:31 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_window(t_cub3d	*cube)
{
	mlx_clear_window(cube->data.mlx_ptr, cube->data.win);
	mlx_destroy_window(cube->data.mlx_ptr, cube->data.win);
	//call cleanup and exit (0);
	exit(0);
	//exit_game(sl);
	return (0);
}