/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 03:25:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/03 04:19:01 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void					puterr(const char *strerr)
{
	ft_printf("%s%s%s\n", RED, strerr, RESET);
	(g_gl->disp_leaks) ? system("leaks -q lem-in") : 1;
	exit(1);
}

t_room					*link_cpy(t_room *room)
{
	t_room	*res;

	res = (t_room *)ft_memalloc(sizeof(t_room));
	res->marked = room->marked;
	res->occupied = room->occupied;
	res->status = room->status;
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
	room->status = stend;
	room->x = ft_atoi(room_n[1]);
	room->y = ft_atoi(room_n[2]);
	room->id = i + 1;
	room->name = ft_strdup(room_n[0]);
	(!i) ? node = room : push_room(&node, room);
	i++;
	memdel_arr((void **)room_n, ft_arrlen((void **)room_n));
	return (node);
}
