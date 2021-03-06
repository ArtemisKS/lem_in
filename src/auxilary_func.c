/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxilary_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:24:59 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 03:25:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void				push_way(t_path **alst, t_path *new)
{
	t_path *tl;

	tl = NULL;
	if (alst && new)
	{
		if (*alst)
			tl = *alst;
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
	}
	*alst = tl;
}

void				add_way(t_path **alst, t_path *new)
{
	t_path *tl;

	tl = NULL;
	if (alst && new)
	{
		if (*alst)
			tl = *alst;
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
	}
	*alst = tl;
}

void				push_room(t_room **alst, t_room *new)
{
	t_room *tl;

	tl = NULL;
	if (alst && new)
	{
		if (*alst)
			tl = *alst;
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
	}
	*alst = tl;
}

static inline void	add_q(t_bfs **alst, t_bfs *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_bfs				*add_to_q(t_room *room, t_bfs *tq)
{
	t_bfs *tmp;

	if (!tq)
	{
		tq = (t_bfs *)ft_memalloc(sizeof(t_bfs));
		tq->room = room;
		tq->next = NULL;
	}
	else
	{
		tmp = add_to_q(room, NULL);
		add_q(&tq, tmp);
	}
	return (tq);
}
