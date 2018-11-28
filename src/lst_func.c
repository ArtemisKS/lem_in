/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:13:22 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:46:01 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_vpush(t_room **alst, t_room *new)
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

void	ft_wpush(t_path **alst, t_path *new)
{
	t_path *tl;

	tl = NULL;
	if (alst && new)
	{
		if (*alst)
			tl = *alst;
		while ((*alst)->next)
		{
			*alst = (*alst)->next;
		}
		(*alst)->next = new;
	}
	*alst = tl;
}

void	ft_qpush(t_bfs **tq, t_bfs *new)
{
	t_bfs *tl;

	tl = NULL;
	if (tq && new)
	{
		if (*tq)
			tl = *tq;
		while ((*tq)->next)
		{
			*tq = (*tq)->next;
		}
		(*tq)->next = new;
	}
	*tq = tl;
}

void	ft_qadd(t_bfs **alst, t_bfs *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_bfs	*add_queue(t_room *tv, t_bfs *tq)
{
	t_bfs *tmp;

	if (!tq)
	{
		tq = (t_bfs *)malloc(sizeof(t_bfs));
		tq->tv = tv;
		tq->next = NULL;
	}
	else
	{
		tmp = add_queue(tv, NULL);
		ft_qadd(&tq, tmp);
	}
	return (tq);
}
