/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 21:05:23 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/23 21:05:26 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			ft_putchar(s[i++]);
	}
}
