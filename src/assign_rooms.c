/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:57:58 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 00:21:17 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		assign_rooms(t_global *tl, t_emmet **ant_arr, t_room *tv)
{
	int i;

	i = 0;
	while (i < tl->n_ants)
	{
		ant_arr[i]->room = make_rooms(ant_arr[i]->path, tv);
		i++;
	}
}

int			ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int			ant_can_go(t_global *tl, t_emmet *ant, t_room *tv)
{
	int i;

	i = 0;
	while ((ant->room)->next && ((ant->room)->next)->id != tv->id)
		tv = tv->next;
	if ((ant->room)->beg == -1 && ant->id < tl->n_ants)
		return (1);
	if ((!(ant->room)->next && (ant->room)->beg == -1
		&& ant->id == tl->n_ants) || tv->occupied)
		return (0);
	return (1);
}

int			antnum_cor(char *line)
{
	int i;

	i = 0;
	if (!(int_value(line)))
		return (0);
	if (line[i] == '0')
		return (0);
	while (line[i])
	{
		if (!(ft_isdigit(line[i])))
			return (0);
		i++;
	}
	return (1);
}

void		null_vertex(t_room *tv)
{
	while (tv)
	{
		tv->father = NULL;
		tv->marked = 0;
		tv->distance = 0;
		tv = tv->next;
	}
}
