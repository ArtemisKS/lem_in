/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:07:25 by akupriia          #+#    #+#             */
/*   Updated: 2018/06/03 20:07:26 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_kids(t_vertex **tv, int dist, t_queue **tq)
{
	int i;

	i = 0;
	while ((*tv)->start != 1)
		*tv = (*tv)->next;
	while ((*tv)->kids[i])
	{
		if (!(*tv)->kids[i]->taken)
		{
			dist = i;
			break ;
		}
		i++;
	}
	if (!(*tv)->kids[dist]->taken)
	{
		*tq = add_queue((*tv)->kids[dist], *tq);
		(*tv)->kids[dist]->visited = 1;
		(*tv)->kids[dist]->dist = 1;
		(*tv)->kids[dist]->parent = (*tv);
		(*tv)->visited = 1;
	}
	else
		return (0);
	return (1);
}

void		bfs_algo(t_vertex **tv, int *dist, t_vertex *tmp, t_queue **tq)
{
	int i;

	i = 0;
	if ((*tv)->parent && tmp->parent)
	{
		if ((*tv)->parent->id != tmp->parent->id)
			(*dist)++;
	}
	else if (!(*tv)->parent || !tmp->parent)
		(*dist)++;
	while ((*tv)->kids[i] && i < (*tv)->kids_num)
	{
		if (!(*tv)->kids[i]->visited && !(*tv)->kids[i]->taken)
		{
			*tq = add_queue((*tv)->kids[i], *tq);
			(*tv)->kids[i]->dist = *dist;
			(*tv)->kids[i]->parent = (*tv);
			(*tv)->kids[i]->visited = 1;
		}
		i++;
	}
}

void		bfs(t_vertex *tv)
{
	t_queue		*tq;
	t_queue		*temp;
	t_vertex	*tmp;
	int			dist;

	dist = 0;
	tq = NULL;
	tmp = tv;
	if (!check_kids(&tv, dist, &tq))
		return ;
	while (tq || !kids_visited(tv))
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

int			room_correct_3(char ***name, t_vertex *tv)
{
	while (tv)
	{
		if (!(ft_strcmp(tv->name, (*name)[0])))
			return (0);
		tv = tv->next;
	}
	return (1);
}
