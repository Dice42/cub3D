/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:20:31 by mohammoh          #+#    #+#             */
/*   Updated: 2024/08/07 14:00:06 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief 
 * @param str 
 * @return returns a the string pointed at character after
 *  finding a space in the string
 */
bool	ft_isspace(const char str)
{
	if (str == '\t' || str == '\n' || str == '\v'
		|| str == '\f' || str == '\r' || str == ' ')
		return (true);
	return (false);
}

/**
 * @brief 
 * 
 * @param str 
 * @return returns a the int pointed at character after 
 * finding a space in the string
 */
int	ft_skipspaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

char	*ft_ignorespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (str + i);
}

int	ft_skip_char(char *str, char skipped, bool index_given, int i)
{
	if (!index_given)
		i = 0;
	else
	{
		while (str[i] == skipped)
			i ++;
	}
	return (i);
}