/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:40:51 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/17 16:47:28 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	error_handler(char *err_msg, t_cub3d *cub)
{
	ft_putstr_fd(err_msg, 2);
	
}