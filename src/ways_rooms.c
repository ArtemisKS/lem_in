/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 08:58:46 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 08:58:47 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		stend_connected(t_room *room)
{
	t_room *node;

	node = room;
	while (room && room->beg != -1)
		room = room->next;
	if (!(room->distance))
	{
		room = node;
		br_first_search(room);
		while (room && room->beg != -1)
			room = room->next;
		if (room->distance)
			return (true);
	}
	else
		puterr("Error: some error occured");
	return (false);
}

int			assign_ways_sth(t_path **path)
{
	if (gl->n_ants - gl->n_ants_arr >= (*path)->distance - 1 && !((*path)->occupied))
	{
		(*path)->occupied = 1;
		return (0);
	}
	if (((*path)->next)->distance - (*path)->distance <= gl->n_ants - gl->n_ants_arr
		&& (*path)->occupied && !(((*path)->next)->occupied))
	{
		(*path) = (*path)->next;
		(*path)->occupied = 1;
		return (0);
	}
	return (1);
}

int			assign_ways_thing(t_path **path, t_path *tmp)
{
	if ((!((*path)->next)) &&
		(gl->n_ants - gl->n_ants_arr < (*path)->distance - 1 || (*path)->occupied))
	{
		(*path) = tmp;
		while ((*path) && gl->n_ants - gl->n_ants_arr >= (*path)->distance - 1)
		{
			(*path)->occupied = 0;
			(*path) = (*path)->next;
		}
		(*path) = tmp;
		(*path)->occupied = 1;
		return (0);
	}
	if (!assign_ways_sth(path))
		return (0);
	(*path) = (*path)->next;
	return (1);
}

void		assign_ways(t_emmet **ant_arr, t_path *path)
{
	int		i;
	t_path	*tmp;

	tmp = path;
	i = 0;
	while (i < gl->n_ants)
	{
		while (path)
			if (!assign_ways_thing(&path, tmp))
				break ;
		ant_arr[i]->path = path;
		path->n_ants++;
		gl->n_ants_arr++;
		path = tmp;
		i++;
	}
}

t_room	*make_rooms(t_path *path, t_room *room)
{
	int			i;
	t_room	*res;
	t_room	*tmp;
	t_room	*t;

	tmp = room;
	res = copy_kid(room);
	i = path->distance - 2;
	while (i >= 0)
	{
		room = tmp;
		while (room->next && path->path[i] != room->id)
			room = room->next;
		t = copy_kid(room);
		ft_vpush(&res, t);
		i--;
	}
	return (res);
}
