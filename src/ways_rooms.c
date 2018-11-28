/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:55:28 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 00:21:19 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			linked_with_end(t_room *tv)
{
	t_room *tmp;

	tmp = tv;
	while (tv && tv->beg != -1)
		tv = tv->next;
	if (!(tv->distance))
	{
		tv = tmp;
		bfs(tv);
		while (tv && tv->beg != -1)
			tv = tv->next;
		if (tv->distance)
			return (1);
	}
	return (0);
}

int			assign_ways_sth(t_global *tl, t_path **tw)
{
	if (tl->n_ants - tl->n_ants_arr >= (*tw)->distance - 1 && !((*tw)->occupied))
	{
		(*tw)->occupied = 1;
		return (0);
	}
	if (((*tw)->next)->distance - (*tw)->distance <= tl->n_ants - tl->n_ants_arr
		&& (*tw)->occupied && !(((*tw)->next)->occupied))
	{
		(*tw) = (*tw)->next;
		(*tw)->occupied = 1;
		return (0);
	}
	return (1);
}

int			assign_ways_thing(t_global *tl, t_path **tw, t_path *tmp)
{
	if ((!((*tw)->next)) &&
		(tl->n_ants - tl->n_ants_arr < (*tw)->distance - 1 || (*tw)->occupied))
	{
		(*tw) = tmp;
		while ((*tw) && tl->n_ants - tl->n_ants_arr >= (*tw)->distance - 1)
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

void		assign_ways(t_global *tl, t_emmet **ant_arr, t_path *tw)
{
	int		i;
	t_path	*tmp;

	tmp = tw;
	i = 0;
	while (i < tl->n_ants)
	{
		while (tw)
			if (!assign_ways_thing(tl, &tw, tmp))
				break ;
		ant_arr[i]->path = tw;
		tw->n_ants++;
		tl->n_ants_arr++;
		tw = tmp;
		i++;
	}
}

t_room	*make_rooms(t_path *tw, t_room *tv)
{
	int			i;
	t_room	*res;
	t_room	*tmp;
	t_room	*t;

	tmp = tv;
	res = copy_kid(tv);
	i = tw->distance - 2;
	while (i >= 0)
	{
		tv = tmp;
		while (tv->next && tw->path[i] != tv->id)
			tv = tv->next;
		t = copy_kid(tv);
		ft_vpush(&res, t);
		i--;
	}
	return (res);
}
