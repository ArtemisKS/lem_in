/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:03:05 by vdzhanaz          #+#    #+#             */
/*   Updated: 2017/11/09 11:03:06 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strequ(char const *s1, char const *s2)
{
	int i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
			i++;
		if (s1[i] - s2[i] == 0)
			return (1);
		else
			return (0);
	}
	else if (!s1 ^ !s2)
		return (0);
	else
		return (1);
}
