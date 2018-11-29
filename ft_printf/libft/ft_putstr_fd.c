/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:48:09 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 12:43:27 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(const char *str, int fd)
{
	size_t i;

	i = 0;
	if (str)
	{
		i = ft_strlen(str);
		write(fd, str, i);
	}
	return (i);
}
