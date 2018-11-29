/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:05:29 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 12:43:22 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr(const char *str)
{
	size_t i;

	i = 0;
	if (str)
	{
		i = ft_strlen(str);
		write(1, str, i);
	}
	return (i);
}
