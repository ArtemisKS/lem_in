/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:51:06 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:54:52 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int			colouror_func(const char **colourors, char *s, int *fl)
{
	int i;

	i = 0;
	while (colourors[i])
	{
		if (ft_strstr_start(s, colourors[i]))
		{
			*fl = 1;
			break ;
		}
		i++;
	}
	return (i);
}

char		*check_for_colourors(char *fmt, int *fl, int ind)
{
	const char	*colourors[] = {"{RED}", "{RESET}", "{BROWN}", "{LRED}",
	"{GREEN}", "{YELLOW}", "{BLUE}", "{MAGENTA}", "{CYAN}", "{WHITE}", NULL};
	const char	*colour[] = {"\033[31;1m", "\033[0m", "\033[22;33m",
	"\033[01;31m", "\033[32;1m", "\033[33;1m", "\033[01;34m",
	"\033[35;1m", "\033[36;1m", "\033[37;1m", NULL};
	char		*s;
	int			i;

	s = &fmt[ind];
	i = colouror_func(colourors, s, fl);
	if (*fl)
	{
		s += ft_strlen(colourors[i]);
		write(1, colour[i], ft_strlen(colour[i]));
		fmt = s;
	}
	return (fmt);
}

static int	do_cycle(va_list ap, char **fmt, int *i, t_spec *ts)
{
	static int	j = 0;
	int			fl;

	fl = 0;
	*fmt = check_for_colourors(*fmt, &fl, *i);
	if (fl)
		*i = 0;
	if ((*fmt)[*i] == '%' && (*fmt)[*i + 1])
	{
		(*i)++;
		*i += parse_spec(&((*fmt)[*i]), ts, ap);
		j = output_fstring(ap, (*fmt)[*i], j, ts);
	}
	else if ((*fmt)[*i] != '%')
	{
		write(1, &((*fmt)[*i]), 1);
		j++;
	}
	(*i)++;
	return (j);
}

int			parse_format(va_list ap, char *fmt)
{
	int		i;
	int		j;
	t_spec	*ts;

	i = 0;
	j = 0;
	ts = (t_spec *)malloc(sizeof(t_spec));
	while (fmt[i])
		j = do_cycle(ap, &fmt, &i, ts);
	ft_memdel((void**)&ts);
	return (j);
}

int			ft_printf(char *fmt, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, fmt);
	n = parse_format(ap, fmt);
	va_end(ap);
	return (n);
}
