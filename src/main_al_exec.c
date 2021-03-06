/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_al_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:34 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 04:19:01 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static bool				fill_queue(t_room *room, int distance, t_bfs **queue)
{
	int i;

	i = -1;
	while (room->status != 's')
		room = room->next;
	while (room->links[++i])
		if (!room->links[i]->used)
		{
			distance = i;
			break ;
		}
	if (!room->links[distance]->used)
	{
		*queue = add_to_q(room->links[distance], *queue);
		room->links[distance]->father = room;
		room->links[distance]->distance = 1;
		room->links[distance]->marked = 1;
		room->marked = 1;
	}
	else
		return (false);
	return (true);
}

static void				add_tq_assign_ind(t_room *room, int *distance,
	t_room *tmp, t_bfs **queue)
{
	int i;

	i = -1;
	if (room->father && tmp->father)
	{
		if (room->father->id != tmp->father->id)
			(*distance)++;
	}
	else if (!room->father || !tmp->father)
		(*distance)++;
	while (room->links[++i] && i < room->n_links)
	{
		if (!room->links[i]->marked && !room->links[i]->used)
		{
			*queue = add_to_q(room->links[i], *queue);
			room->links[i]->distance = *distance;
			room->links[i]->father = room;
			room->links[i]->marked = 1;
		}
	}
}

static inline bool		links_marked(t_room *room)
{
	int i;

	i = -1;
	while (room->links[++i])
		if (!room->links[i]->marked && !room->links[i]->used)
			return (false);
	return (true);
}

void					br_first_search(t_room *room)
{
	t_bfs		*queue;
	t_bfs		*tmp_q;
	t_room		*node;
	int			distance;

	distance = 0;
	queue = NULL;
	node = room;
	if (!fill_queue(room, distance, &queue))
		return ;
	while (queue || !links_marked(room))
	{
		add_tq_assign_ind(room, &distance, node, &queue);
		node = room;
		if ((tmp_q = pop_q(&queue)))
			room = tmp_q->room;
	}
}
