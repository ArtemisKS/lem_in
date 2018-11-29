/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:11:24 by vdzhanaz          #+#    #+#             */
/*   Updated: 2018/11/29 16:49:02 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void					puterr(const char *strerr)
{
	ft_putstr(RED);
	ft_putendl(strerr);
	ft_putstr(RESET);
	(g_gl->disp_leaks) ? system("leaks -q lem-in") : 1;
	exit(1);
}

t_room					*link_cpy(t_room *room)
{
	t_room	*res;

	res = (t_room *)ft_memalloc(sizeof(t_room));
	res->marked = room->marked;
	res->occupied = room->occupied;
	res->beg = room->beg;
	res->x = room->x;
	res->y = room->y;
	res->distance = room->distance;
	res->n_links = room->n_links;
	res->id = room->id;
	res->name = ft_strdup(room->name);
	res->links = NULL;
	res->father = NULL;
	res->next = NULL;
	return (res);
}

static inline t_room	*init_room(void)
{
	t_room *room;

	room = ft_memalloc(sizeof(t_room *) * 1000);
	room->links = (t_room **)ft_memalloc(sizeof(t_room *) * 100);
	room->father = NULL;
	room->name = NULL;
	room->next = NULL;
	return (room);
}

t_room					*add_room(char **room_n, t_room *node, char stend)
{
	t_room		*room;
	static int	i = 0;

	room = init_room();
	room->beg = stend;
	room->x = ft_atoi(room_n[1]);
	room->y = ft_atoi(room_n[2]);
	room->id = i + 1;
	room->name = ft_strdup(room_n[0]);
	(!i) ? node = room : push_room(&node, room);
	i++;
	memdel_arr((void **)room_n, ft_arrlen((void **)room_n));
	return (node);
}
