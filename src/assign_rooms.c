/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:57:58 by akupriia          #+#    #+#             */
/*   Updated: 2018/06/03 19:57:59 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		assign_rooms(t_lemin *tl, t_ant **ant_arr, t_vertex *tv)
{
	int i;

	i = 0;
	while (i < tl->ant_num)
	{
		ant_arr[i]->room = make_rooms(ant_arr[i]->way, tv);
		i++;
	}
}

int			ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int			ant_can_go(t_lemin *tl, t_ant *ant, t_vertex *tv)
{
	int i;

	i = 0;
	while ((ant->room)->next && ((ant->room)->next)->id != tv->id)
		tv = tv->next;
	if ((ant->room)->start == -1 && ant->id < tl->ant_num)
		return (1);
	if ((!(ant->room)->next && (ant->room)->start == -1
		&& ant->id == tl->ant_num) || tv->busy)
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

void		null_vertex(t_vertex *tv)
{
	while (tv)
	{
		tv->parent = NULL;
		tv->visited = 0;
		tv->dist = 0;
		tv = tv->next;
	}
}
