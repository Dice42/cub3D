/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:21:04 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/13 23:02:54 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*is_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	return ((char *)str + i);
}

static int	check_if_negative(int sign, char c)
{
	if (c == '-')
		sign = -sign;
	return (sign);
}

int	ft_atoi_hex(const char *str)
{
	unsigned int	i;
	int				sign;
	long			ret;

	i = 0;
	ret = 0;
	sign = 1;
	str = is_space(str);
	while ((str[i] == '+' || str[i] == '-') && (str[i + 1] != '+'
			&& str[i + 1] != '-'))
		sign = check_if_negative(sign, str[i++]);
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
		|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			ret = ret * 16 + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			ret = ret * 16 + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			ret = ret * 16 + (str[i] - 'A' + 10);
		i++;
	}
	return (sign * ret);
}
