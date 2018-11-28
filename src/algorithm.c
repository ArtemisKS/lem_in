/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 20:07:25 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/28 23:46:38 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_links(t_room **tv, int distance, t_bfs **tq)
{
	int i;

	i = 0;
	while ((*tv)->beg != 1)
		*tv = (*tv)->next;
	while ((*tv)->links[i])
	{
		if (!(*tv)->links[i]->used)
		{
			distance = i;
			break ;
		}
		i++;
	}
	if (!(*tv)->links[distance]->used)
	{
		*tq = add_queue((*tv)->links[distance], *tq);
		(*tv)->links[distance]->marked = 1;
		(*tv)->links[distance]->distance = 1;
		(*tv)->links[distance]->father = (*tv);
		(*tv)->marked = 1;
	}
	else
		return (0);
	return (1);
}

void		bfs_algo(t_room **tv, int *distance, t_room *tmp, t_bfs **tq)
{
	int i;

	i = 0;
	if ((*tv)->father && tmp->father)
	{
		if ((*tv)->father->id != tmp->father->id)
			(*distance)++;
	}
	else if (!(*tv)->father || !tmp->father)
		(*distance)++;
	while ((*tv)->links[i] && i < (*tv)->n_links)
	{
		if (!(*tv)->links[i]->marked && !(*tv)->links[i]->used)
		{
			*tq = add_queue((*tv)->links[i], *tq);
			(*tv)->links[i]->distance = *distance;
			(*tv)->links[i]->father = (*tv);
			(*tv)->links[i]->marked = 1;
		}
		i++;
	}
}

void		bfs(t_room *tv)
{
	t_bfs		*tq;
	t_bfs		*temp;
	t_room	*tmp;
	int			distance;

	distance = 0;
	tq = NULL;
	tmp = tv;
	if (!check_links(&tv, distance, &tq))
		return ;
	while (tq || !links_marked(tv))
	{
		bfs_algo(&tv, &distance, tmp, &tq);
		tmp = tv;
		if ((temp = pop_queue(&tq)))
			tv = temp->tv;
	}
}

t_bfs		*pop_queue(t_bfs **tq)
{
	t_bfs		*res;
	t_bfs		*tmp;

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
