/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:50:08 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/29 07:08:32 by vdzhanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*init_room(void)
{
	t_room *room;

	room = ft_memalloc(sizeof(t_room));
	room->links = (t_room **)ft_memalloc(sizeof(t_room *) * 100);
	room->father = NULL;
	room->name = NULL;
	room->next = NULL;
	return (room);
}

t_room	*copy_kid(t_room *room)
{
	t_room	*res;
	int			j;

	j = 0;
	res = (t_room *)malloc(sizeof(t_room));
	res->links = NULL;
	res->father = NULL;
	res->marked = room->marked;
	res->occupied = room->occupied;
	res->x = room->x;
	res->y = room->y;
	res->distance = room->distance;
	res->n_links = room->n_links;
	res->id = room->id;
	res->beg = room->beg;
	res->next = NULL;
	res->name = ft_strdup(room->name);
	return (res);
}

void		puterr(const char *strerr)
{
	ft_putendl_fd(strerr, 2);
	exit(1);
}

void		free_arr(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
