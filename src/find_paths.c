/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 08:59:07 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 15:47:43 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	calibrate_dist(t_room *room)
{
	t_room		*node;
	int			i;

	while (room)
	{
		i = 0;
		node = room;
		while (room && ++i)
			room = room->father;
		room = node;
		room->distance = i;
		room = room->next;
	}
}

t_path				*det_way(t_room *room)
{
	t_path		*path;
	t_room		*node;
	int			i;

	i = 0;
	path = ft_memalloc(sizeof(t_path));
	calibrate_dist(room);
	node = room;
	while (room && room->beg != 'e')
		room = room->next;
	path->path = ft_memalloc(sizeof(int) * room->distance);
	path->distance = room->distance;
	while (room)
	{
		path->path[i++] = room->id;
		room = room->father;
		(room && room->father) ? room->used = 1 : 1;
	}
	path->n_ants = 0;
	path->next = NULL;
	room = node;
	(!(st_end_nearby(room))) ? bzero_room(room) : 1;
	return (path);
}

bool				check_n_emm(char *line)
{
	if (!(ft_strlen(line)))
		puterr("Error: empty line before number of ants");
	if (ft_strequ(line, "##start"))
		puterr("Error: ##start before number of ants");
	else if (ft_strequ(line, "##end"))
		puterr("Error: ##end before number of ants");
	return (COMMENT(line) ? (false) : (true));
}



bool				emm_may_move(t_emmet *ant, t_room *room)
{
	int i;

	i = 0;
	while ((ant->room)->next && ((ant->room)->next)->id != room->id)
		room = room->next;
	if (ant->id < gl->n_ants && (ant->room)->beg == 'e')
		return (true);
	if ((!(ant->room)->next && (ant->room)->beg == 'e'
		&& ant->id == gl->n_ants) || room->occupied)
		return (false);
	return (true);
}
