/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:51:22 by akupriia          #+#    #+#             */
/*   Updated: 2018/06/03 19:51:23 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_correct_2(char ***name, t_vertex *tv)
{
	int i;
	int j;

	j = 1;
	while ((*name)[j])
	{
		i = 0;
		if (ft_strlen((*name)[j]) != 1 && (*name)[j][i] == '0')
			return (0);
		while ((*name)[j][i])
			if (!(ft_isdigit((*name)[j][i++])))
				return (0);
		j++;
	}
	if (!((*name)[1]) || !((*name)[2]) ||
		(*name)[0][ft_strlen((*name)[0]) - 1] == '-')
		return (0);
	while (tv)
	{
		if (tv->x == ft_atoi((*name)[1]) && tv->y == ft_atoi((*name)[2]))
			return (0);
		tv = tv->next;
	}
	return (1);
}

int				room_correct(char *line, char ***name, t_vertex *tv)
{
	int check;
	int check1;
	int i;

	i = 0;
	check = 0;
	check1 = 0;
	*name = ft_strsplit(line, ' ');
	if (line[0] == '#' || line[0] == 'L')
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i + 1] && line[i + 1] == ' ')
			check++;
		if (line[i] == ' ')
			check1++;
		i++;
	}
	if ((check != 2) || (check1 != 2) || (line[0] == ' '))
		return (0);
	if (!room_correct_2(name, tv))
		return (0);
	if (!room_correct_3(name, tv))
		return (0);
	return (1);
}

static int		link_correct_cycle(char ***name, t_vertex *tv, t_vertex *tmp)
{
	int j;
	int fl;

	j = 0;
	fl = 0;
	while (j < 2)
	{
		while (tmp)
		{
			if (!(ft_strcmp(tmp->name, (*name)[j])))
			{
				fl = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (!fl)
			return (0);
		tmp = tv;
		fl = 0;
		j++;
	}
	return (1);
}

int				link_correct(char *line, char ***name, t_vertex *tv)
{
	int			check;
	t_vertex	*tmp;
	int			i;

	check = 0;
	tmp = tv;
	i = -1;
	*name = ft_strsplit(line, '-');
	if (!((*name)[0]) || !((*name)[1]))
		return (0);
	while (line[++i])
		if (line[i] == '-')
			check++;
	if (!link_correct_cycle(name, tv, tmp))
		return (0);
	if (line[0] == '-' || line[ft_strlen(line) - 1] == '-' || check != 1)
		return (0);
	return (1);
}

int				room_exception(char *line, int *start, int *end, int *fl)
{
	if (!ft_strcmp(line, "##start") && !(*start))
	{
		*fl = 1;
		*start = 1;
		return (1);
	}
	else if (!ft_strcmp(line, "##end") && !(*end))
	{
		*fl = 0;
		*end = 1;
		return (1);
	}
	else if (((!ft_strcmp(line, "##end")) ||
		(!ft_strcmp(line, "##start"))) && ((*end) || (*start)))
		ft_error(7);
	else if (line && line[0] == '#')
		return (1);
	if (!(ft_strlen(line)))
		return (0);
	return (-1);
}
