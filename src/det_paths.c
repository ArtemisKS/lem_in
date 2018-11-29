/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:12:50 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 16:34:58 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

#define ANT_DIFF()	(g_gl->n_ants - g_gl->n_ants_arr)
#define P_DIST()	((*path)->distance - 1)

bool			stend_connected(t_room *room)
{
	t_room *node;

	node = room;
	while (room && room->beg != 'e')
		room = room->next;
	if (!(room->distance))
	{
		room = node;
		br_first_search(room);
		while (room && room->beg != 'e')
			room = room->next;
		if (room->distance)
			return (true);
	}
	else
		puterr("Error: some error occured");
	return (false);
}

static bool		help_det_palgo(t_path **path)
{
	bool	res;

	res = true;
	if (ANT_DIFF() >= P_DIST() && !((*path)->occupied)
		&& ((*path)->occupied = 1))
		res = false;
	else if (((*path)->next)->distance - (*path)->distance <= ANT_DIFF()
		&& (*path)->occupied && !(((*path)->next)->occupied))
	{
		(*path) = (*path)->next;
		(*path)->occupied = 1;
		res = false;
	}
	return (res);
}

static bool		det_paths_algo(t_path **path, t_path *way)
{
	if ((!((*path)->next)) &&
		(ANT_DIFF() < P_DIST() || (*path)->occupied))
	{
		(*path) = way;
		while ((*path) && ANT_DIFF() >= P_DIST() && !((*path)->occupied = 0))
			(*path) = (*path)->next;
		(*path) = way;
		(*path)->occupied = 1;
		return (false);
	}
	if (!help_det_palgo(path))
		return (false);
	(*path) = (*path)->next;
	return (true);
}

void			det_paths(t_emmet **ant_arr, t_path *path)
{
	int		i;
	t_path	*way;

	way = path;
	i = -1;
	while (++i < g_gl->n_ants)
	{
		while (path)
			if (!det_paths_algo(&path, way))
				break ;
		ant_arr[i]->path = path;
		path->n_ants++;
		g_gl->n_ants_arr++;
		path = way;
	}
}
