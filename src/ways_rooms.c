/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:55:28 by akupriia          #+#    #+#             */
/*   Updated: 2018/06/03 19:55:28 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			linked_with_end(t_vertex *tv)
{
	t_vertex *tmp;

	tmp = tv;
	while (tv && tv->start != -1)
		tv = tv->next;
	if (!(tv->dist))
	{
		tv = tmp;
		bfs(tv);
		while (tv && tv->start != -1)
			tv = tv->next;
		if (tv->dist)
			return (1);
	}
	return (0);
}

int			assign_ways_sth(t_lemin *tl, t_way **tw)
{
	if (tl->ant_num - tl->gone_ants >= (*tw)->dist - 1 && !((*tw)->busy))
	{
		(*tw)->busy = 1;
		return (0);
	}
	if (((*tw)->next)->dist - (*tw)->dist <= tl->ant_num - tl->gone_ants
		&& (*tw)->busy && !(((*tw)->next)->busy))
	{
		(*tw) = (*tw)->next;
		(*tw)->busy = 1;
		return (0);
	}
	return (1);
}

int			assign_ways_thing(t_lemin *tl, t_way **tw, t_way *tmp)
{
	if ((!((*tw)->next)) &&
		(tl->ant_num - tl->gone_ants < (*tw)->dist - 1 || (*tw)->busy))
	{
		(*tw) = tmp;
		while ((*tw) && tl->ant_num - tl->gone_ants >= (*tw)->dist - 1)
		{
			(*tw)->busy = 0;
			(*tw) = (*tw)->next;
		}
		(*tw) = tmp;
		(*tw)->busy = 1;
		return (0);
	}
	if (!assign_ways_sth(tl, tw))
		return (0);
	(*tw) = (*tw)->next;
	return (1);
}

void		assign_ways(t_lemin *tl, t_ant **ant_arr, t_way *tw)
{
	int		i;
	t_way	*tmp;

	tmp = tw;
	i = 0;
	while (i < tl->ant_num)
	{
		while (tw)
			if (!assign_ways_thing(tl, &tw, tmp))
				break ;
		ant_arr[i]->way = tw;
		tw->ant_num++;
		tl->gone_ants++;
		tw = tmp;
		i++;
	}
}

t_vertex	*make_rooms(t_way *tw, t_vertex *tv)
{
	int			i;
	t_vertex	*res;
	t_vertex	*tmp;
	t_vertex	*t;

	tmp = tv;
	res = copy_kid(tv);
	i = tw->dist - 2;
	while (i >= 0)
	{
		tv = tmp;
		while (tv->next && tw->way[i] != tv->id)
			tv = tv->next;
		t = copy_kid(tv);
		ft_vpush(&res, t);
		i--;
	}
	return (res);
}
