/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:55:28 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			linked_with_end(t_room *tv)
{
	t_room *tmp;

	tmp = tv;
	while (tv && tv->beg != -1)
		tv = tv->next;
	if (!(tv->dist))
	{
		tv = tmp;
		bfs(tv);
		while (tv && tv->beg != -1)
			tv = tv->next;
		if (tv->dist)
			return (1);
	}
	return (0);
}

int			assign_ways_sth(t_lemin *tl, t_way **tw)
{
	if (tl->ant_num - tl->gone_ants >= (*tw)->dist - 1 && !((*tw)->occupied))
	{
		(*tw)->occupied = 1;
		return (0);
	}
	if (((*tw)->next)->dist - (*tw)->dist <= tl->ant_num - tl->gone_ants
		&& (*tw)->occupied && !(((*tw)->next)->occupied))
	{
		(*tw) = (*tw)->next;
		(*tw)->occupied = 1;
		return (0);
	}
	return (1);
}

int			assign_ways_thing(t_lemin *tl, t_way **tw, t_way *tmp)
{
	if ((!((*tw)->next)) &&
		(tl->ant_num - tl->gone_ants < (*tw)->dist - 1 || (*tw)->occupied))
	{
		(*tw) = tmp;
		while ((*tw) && tl->ant_num - tl->gone_ants >= (*tw)->dist - 1)
		{
			(*tw)->occupied = 0;
			(*tw) = (*tw)->next;
		}
		(*tw) = tmp;
		(*tw)->occupied = 1;
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

t_room	*make_rooms(t_way *tw, t_room *tv)
{
	int			i;
	t_room	*res;
	t_room	*tmp;
	t_room	*t;

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
