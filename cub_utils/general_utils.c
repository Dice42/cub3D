/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:32:01 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 22:05:45 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ctrs(t_ctr *ctr)
{
	ctr->i = 0;
	ctr->j = 0;
	ctr->c = 0;
}

void	init_draw_line(t_draw_line *line)
{
	line->height = 0;
	line->offset = 0;
	line->end_y = 0;
	line->texture_y = 0.0f;
	line->texture_x = 0.0f;
	line->texture_y_step = 0.0f;
	line->color = 0;
}

void	convert_hex(int num, int *o, char *hex)
{
	char	*base;
	char	temp[2];

	base = "0123456789ABCDEF";
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
		if (ctr.i == 0)
		{
			level->floor_clr_hex = ft_strjoin(level->floor_clr_hex, f_hex);
			level->ceiling_clr_hex = ft_strjoin(level->ceiling_clr_hex, c_hex);
		}
		level->floor_clr_hex = ft_strjoin_free(level->floor_clr_hex, f_hex, 1);
		level->ceiling_clr_hex = ft_strjoin_free(level->ceiling_clr_hex, c_hex,
				1);
		ft_bzero(f_hex, sizeof(f_hex));
		ft_bzero(c_hex, sizeof(c_hex));
		ctr.i++;
	}
	level->floor_clr = ft_atoi_hex(level->floor_clr_hex);
	level->ceiling_clr = ft_atoi_hex(level->ceiling_clr_hex);
	free(level->floor_clr_hex);
	free(level->ceiling_clr_hex);
}
