/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:32:01 by mohammoh          #+#    #+#             */
/*   Updated: 2024/07/25 16:49:17 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ctrs(t_ctr *ctr)
{
	ctr->i = 0;
	ctr->j = 0;
	ctr->c = 0;
}

void	convert_hex(int num, int *o, char *hex)
{
	char	*base = "0123456789ABCDEF";
	char	temp[2];

	if (num > 15)
		convert_hex(num / 16, o, hex);
	temp[0] = base[num % 16];
	temp[1] = '\0';
	if (*o == 0)
	{
		hex[0] = temp[0];
		hex[1] = '\0';
		*o = 1;
	}
	else
	{
		ft_strcat(hex, temp);
		hex[2] = '\0';
	}
}

void	convert_rgb_hex(t_level *level)
{
	t_ctr	ctr;
	char	f_hex[3];
	char	c_hex[3];

	init_ctrs(&ctr);
	while (ctr.i < 3)
	{
		convert_hex(level->floor_color[ctr.i], &ctr.j, f_hex);
		convert_hex(level->ceiling_color[ctr.i], &ctr.c, c_hex);
		level->floor_color_hex = ft_strjoin(level->floor_color_hex, f_hex);
		level->ceiling_color_hex = ft_strjoin(level->ceiling_color_hex, c_hex);
		ft_bzero(f_hex, sizeof(f_hex));
		ft_bzero(c_hex, sizeof(c_hex));
		ctr.i++;
	}
}
