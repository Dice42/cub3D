/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:12:01 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/17 14:37:37 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int main(void)
{
//	t_cub3d	cube;
	
	printf("helo!\n");
	if (ac != 2)
		return (0);
	if (!init_cube(&cube))
		return (0); //print error
	if (!validate_level(av[1], &cube.level))
		return (0); //print error
	return (0);
}
