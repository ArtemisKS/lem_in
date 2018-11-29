/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:28:41 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 15:35:03 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_min(int a, int b)
{
	return (a < b ? a : b);
}

bool			n_ants_valid(char *line)
{
	int i;

	i = -1;
	if (!(is_int(line)) || line[0] == '0')
		return (false);
	while (line[++i])
		if (!(ft_isdigit(line[i])))
			return (false);
	gl->n_ants = ft_atoi(line);
	return (true);
}

void			bzero_room(t_room *room)
{
	while (room)
	{
		room->distance = 0;
		room->marked = 0;
		room->father = NULL;
		room = room->next;
	}
}

bool			realloc_darr(void)
{
	static	int		iterator = 1;
	char			**t_map;
	int				i;

	if ((gl->map && gl->map[BUFF - 1]) || iterator == 1)
	{
		gl->n_lines = BUFF * iterator;
		t_map = ft_memalloc(sizeof(char *) * (gl->n_lines + 1));
		gl->n_lines -= BUFF;
		i = -1;
		while (++i < gl->n_lines && (t_map[i] = gl->map[i]))
			;
		(iterator != 1) ? (free(gl->map))
		: (gl->iter = 0);
		gl->map = t_map;
		iterator++;
	}
	return (true);
}

t_bfs				*pop_q(t_bfs **queue)
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
