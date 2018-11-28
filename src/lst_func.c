/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:13:22 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
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

void	ft_wpush(t_way **alst, t_way *new)
{
	t_way *tl;

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

void	ft_qpush(t_queue **tq, t_queue *new)
{
	t_queue *tl;

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

void	ft_qadd(t_queue **alst, t_queue *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_queue	*add_queue(t_room *tv, t_queue *tq)
{
	t_queue *tmp;

	if (!tq)
	{
		tq = (t_queue *)malloc(sizeof(t_queue));
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
