/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 08:58:40 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 08:58:41 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs				*pop_queue(t_bfs **queue)
{
	t_bfs		*q_ret;
	t_bfs		*queue_tmp;

	q_ret = NULL;
	if ((*queue)->next)
	{
		queue_tmp = *queue;
		while ((queue_tmp->next)->next)
			queue_tmp = queue_tmp->next;
		q_ret = queue_tmp->next;
		ft_memdel((void **)&queue_tmp->next);
		queue_tmp->next = NULL;
	}
	else
	{
		q_ret = *queue;
		ft_memdel((void **)queue);
		*queue = NULL;
	}
	return (q_ret);
}

void				ft_wpush(t_path **alst, t_path *new)
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

void				ft_vpush(t_room **alst, t_room *new)
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

static inline void	ft_qadd(t_bfs **alst, t_bfs *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_bfs				*add_to_q(t_room *tv, t_bfs *tq)
{
	t_bfs *tmp;

	if (!tq)
	{
		tq = (t_bfs *)malloc(sizeof(t_bfs));
		tq->room = tv;
		tq->next = NULL;
	}
	else
	{
		tmp = add_to_q(tv, NULL);
		ft_qadd(&tq, tmp);
	}
	return (tq);
}
