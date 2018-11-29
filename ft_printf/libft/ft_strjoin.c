/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:48:43 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 12:54:54 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*joy;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup((char*)s1));
	if (!s1 && s2)
		return (ft_strdup((char*)s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	joy = ft_strnew(len);
	if (joy && len > 0)
	{
		while (len-- > ft_strlen(s1))
			joy[len] = s2[len - ft_strlen(s1)];
		len++;
		while (len-- > 0)
			joy[len] = s1[len];
	}
	return (joy);
}
