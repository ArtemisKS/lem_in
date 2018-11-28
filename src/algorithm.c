/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:07:25 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:35:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_links(t_room **tv, int dist, t_queue **tq)
{
	int i;

	i = 0;
	while ((*tv)->beg != 1)
		*tv = (*tv)->next;
	while ((*tv)->links[i])
	{
		if (!(*tv)->links[i]->used)
		{
			dist = i;
			break ;
		}
		i++;
	}
	if (!(*tv)->links[dist]->used)
	{
		*tq = add_queue((*tv)->links[dist], *tq);
		(*tv)->links[dist]->marked = 1;
		(*tv)->links[dist]->dist = 1;
		(*tv)->links[dist]->father = (*tv);
		(*tv)->marked = 1;
	}
	else
		return (0);
	return (1);
}

void		bfs_algo(t_room **tv, int *dist, t_room *tmp, t_queue **tq)
{
	int i;

	i = 0;
	if ((*tv)->father && tmp->father)
	{
		if ((*tv)->father->id != tmp->father->id)
			(*dist)++;
	}
	else if (!(*tv)->father || !tmp->father)
		(*dist)++;
	while ((*tv)->links[i] && i < (*tv)->n_links)
	{
		if (!(*tv)->links[i]->marked && !(*tv)->links[i]->used)
		{
			*tq = add_queue((*tv)->links[i], *tq);
			(*tv)->links[i]->dist = *dist;
			(*tv)->links[i]->father = (*tv);
			(*tv)->links[i]->marked = 1;
		}
		i++;
	}
}

void		bfs(t_room *tv)
{
	t_queue		*tq;
	t_queue		*temp;
	t_room	*tmp;
	int			dist;

	dist = 0;
	tq = NULL;
	tmp = tv;
	if (!check_links(&tv, dist, &tq))
		return ;
	while (tq || !links_marked(tv))
	{
		bfs_algo(&tv, &dist, tmp, &tq);
		tmp = tv;
		if ((temp = pop_queue(&tq)))
			tv = temp->tv;
	}
}

t_queue		*pop_queue(t_queue **tq)
{
	t_queue		*res;
	t_queue		*tmp;

	tmp = NULL;
	if ((*tq)->next)
	{
		res = *tq;
		while ((res->next)->next)
			res = res->next;
		tmp = res->next;
		free(res->next);
		res->next = NULL;
	}
	else
	{
		tmp = *tq;
		free(*tq);
		*tq = NULL;
	}
	return (tmp);
}

int			room_correct_3(char ***name, t_room *tv)
{
	while (tv)
	{
		if (!(ft_strcmp(tv->name, (*name)[0])))
			return (0);
		tv = tv->next;
	}
	return (1);
}
